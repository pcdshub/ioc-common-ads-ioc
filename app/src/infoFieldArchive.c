// Creates PCDS-compliant .archive files from `info` node tags

#define VERSION "0.0"

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dbAccess.h>    /* includes dbDefs.h, dbBase.h, dbAddr.h, dbFldTypes.h */
#include    <dbStaticLib.h>
#include    <errlog.h>
#include    <iocsh.h>
#include    <epicsStdio.h>
#include    <epicsExport.h>


// distinct settings (interval/scan/monitor) per record
#define MAX_ARCHIVE_ENTRIES 10

// max number of fields per entry
#define MAX_ARCHIVE_FIELDS  100
#define MAX_FIELD_LENGTH    100

// being lazy not wanting to malloc/free:
#define MAX_INTERVAL_STRING 10  // max length of interval string in info value

// Default is scan
#define ARCHIVE_DEFAULT_MONITOR  0
// Default interval is 1 second
#define ARCHIVE_DEFAULT_INTERVAL "1"

#define ARCHIVE_DEBUG            0


typedef struct {
    int is_monitor;
    char interval_string[MAX_INTERVAL_STRING];
    char fields[MAX_ARCHIVE_FIELDS][MAX_FIELD_LENGTH];
    epicsUInt32 num_fields;
} ArchiveEntry;

typedef struct {
    epicsUInt32 num_entries;
    ArchiveEntry entries[MAX_ARCHIVE_ENTRIES];
} ArchiveSettings;



int parseArchiveInfoString(const char *info_string, ArchiveSettings *settings) {
    char *token, *string, *tofree, *s;
    int is_new_entry = 0;
    int is_monitor = 0;
    int is_scan = 0;
    int section_idx = -1;
    ArchiveEntry *entry = NULL;

    if (!info_string || !settings) {
        return FALSE;
    }
    memset(settings, 0, sizeof(ArchiveSettings));

    tofree = string = strdup(info_string);
    assert(string != NULL);

    while ((token = strsep(&string, " ")) != NULL) {
        if (!strlen(token))
            continue;

        is_monitor = !strcmp(token, "monitor");
        is_scan = !strcmp(token, "scan");

#if ARCHIVE_DEBUG
        printf("%s is_monitor=%d is_scan=%d (is_new_entry=%d)\n",
                 token, is_monitor, is_scan, is_new_entry);
#endif
        if (is_monitor || is_scan || section_idx == -1) {
            section_idx++;
            if (settings->num_entries == MAX_ARCHIVE_ENTRIES) {
                errlogPrintf("infoFieldArchive: Maximum archive entries per record reached (%s)\n", info_string);
                break;
            }
            settings->num_entries++;
            entry = &settings->entries[section_idx];

            if (is_monitor || is_scan) {
                entry->is_monitor = is_monitor;
                is_new_entry = 1;
                continue;
            } else {
                // Use defaults
                strncpy(entry->interval_string, ARCHIVE_DEFAULT_INTERVAL,
                        MAX_INTERVAL_STRING);
                entry->is_monitor = ARCHIVE_DEFAULT_MONITOR;
            }
        } else if (is_new_entry == 1) {
            // TODO: verify it's actually the interval. strtod(token, ...); errno
            strncpy(entry->interval_string, token, MAX_INTERVAL_STRING);
            // Remove trailing ":" if in the interval string
            if ((s = strstr(entry->interval_string, ":")) != NULL) {
                s[0] = '\0';
            }
            is_new_entry = 0;
            continue;
        }

        if (entry->num_fields == MAX_ARCHIVE_FIELDS) {
            errlogPrintf("infoFieldArchive: Maximum field count per entry reached (%s)\n", info_string);
            break;
        }
        strncpy(entry->fields[entry->num_fields], token, MAX_FIELD_LENGTH);
        entry->num_fields++;
    }

    free(tofree);
    return TRUE;
}

void dumpArchiveEntry(ArchiveEntry *entry, FILE *fp) {
    int idx;
    if (!entry)
        return;

    fprintf(fp, "is_monitor: %d\n", entry->is_monitor);
    fprintf(fp, "interval  : %s\n", entry->interval_string);

    if (entry->num_fields > 0) {
        fprintf(fp, "fields (%d): ", entry->num_fields);
        for (idx=0; idx < entry->num_fields; idx++) {
            fprintf(fp, "%s ", entry->fields[idx]);
        }
        fprintf(fp, "\n");
    }
}


void dumpArchiveSettings(ArchiveSettings *settings, FILE *fp) {
    int idx;
    if (!settings)
        return;

    for (idx=0; idx < settings->num_entries; idx++) {
        if (settings->num_entries > 1) {
            fprintf(fp, "-- entry %d:\n", idx);
        }
        dumpArchiveEntry(&settings->entries[idx], fp);
    }
}


void archiveSettingsToFile(const char *record_name, ArchiveSettings *settings, FILE *fp) {
    int entry_idx = 0;
    int field_idx;
    ArchiveEntry *entry;
    for (; entry_idx < settings->num_entries; entry_idx++) {
        entry = &settings->entries[entry_idx];
        for (field_idx=0; field_idx < entry->num_fields; field_idx++) {
            fprintf(fp, "%s.%s\t%s", record_name, entry->fields[field_idx],
                    entry->interval_string);
            if (entry->is_monitor) {
                fprintf(fp, "\tmonitor");
            }
            fprintf(fp, "\n");
        }
    }
}

/*
 * Look through the database for info nodes with the specified info_pattern
 * (glob match), and get the associated info_value string.  Interpret this
 * string as a list of field names in the following format:
 *
 *  [(scan/monitor) (rate in seconds)[:]] [field1 [field2 [...]]]
 *  e.g., scan 1: FLD1 FLD2 FLD3
 *        scan 2  FLD1 FLD2 FLD3
 *        monitor 1 FLD1
 *
 * The info node may contain one or more of these items.
 * Write the accumulated PVs to the file <fname>.
 * */
static void makeArchiveFromDbInfo(const char *fname, char *info_pattern)
{
    DBENTRY         dbentry;
    FILE            *fp;
    ArchiveSettings settings;
    const char      *record_name;
    int             num_records = 0;

    if (!pdbbase) {
        errlogPrintf("infoFieldArchive:makeArchiveFromDbInfo: No Database Loaded\n");
        return;
    }

    if ((fp = fopen(fname,"w")) == NULL) {
        errlogPrintf("infoFieldArchive:makeArchiveFromDbInfo - unable to open file '%s'\n", fname);
        return;
    }

    fprintf(fp, "# AUTO GENERATED Archive Appliance cron-job-compatible settings\n");
    fprintf(fp, "# Do not modify by hand.\n\n");
    dbInitEntry(pdbbase, &dbentry);
    while (dbNextMatchingInfo(&dbentry, info_pattern) == 0)
    {
        record_name = dbGetRecordName(&dbentry);
#if ARCHIVE_DEBUG
        printf("%s info(%s, \"%s\")\n", record_name,
            dbGetInfoName(&dbentry), dbGetInfoString(&dbentry));
#endif

        if (parseArchiveInfoString(dbGetInfoString(&dbentry), &settings)) {
#if ARCHIVE_DEBUG
            dumpArchiveSettings(&settings, stdout);
            archiveSettingsToFile(record_name, &settings, stdout);
#endif
            archiveSettingsToFile(record_name, &settings, fp);
            num_records++;
        }
    }
    printf("makeArchiveFromDbInfo: Wrote archive settings file containing %d records\n", num_records);
    dbFinishEntry(&dbentry);
    fclose(fp);
    return;
}


/* void makeArchiveFromDbInfo(char *filename, char *info_name) */
static const iocshArg makeArchiveFromDbInfo_Arg0 = {"filename",iocshArgString};
static const iocshArg makeArchiveFromDbInfo_Arg1 = {"info_name",iocshArgString};
static const iocshArg * const makeArchiveFromDbInfo_Args[2] = {&makeArchiveFromDbInfo_Arg0, &makeArchiveFromDbInfo_Arg1};
static const iocshFuncDef makeArchiveFromDbInfo_FuncDef = {"makeArchiveFromDbInfo",2,makeArchiveFromDbInfo_Args};
static void makeArchiveFromDbInfo_CallFunc(const iocshArgBuf *args)
{
    makeArchiveFromDbInfo(args[0].sval, args[1].sval);
}

void infoFieldArchiveRegister(void)
{
    iocshRegister(&makeArchiveFromDbInfo_FuncDef, makeArchiveFromDbInfo_CallFunc);
}

epicsExportRegistrar(infoFieldArchiveRegister);
