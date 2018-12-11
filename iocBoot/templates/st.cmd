#!$$IOCTOP/bin/$$IF(ARCH,$$ARCH,linux-x86)/ads

epicsEnvSet("IOCNAME", "$$IOCNAME" )
epicsEnvSet("ENGINEER", "$$ENGINEER" )
epicsEnvSet("LOCATION", "$$LOCATION" )
epicsEnvSet("IOCSH_PS1", "$(IOCNAME)> " )
epicsEnvSet("IOC_PV", "$$IOC_PV")
epicsEnvSet("IOCTOP", "$$IOCTOP")
< envPaths
epicsEnvSet("TOP", "$$TOP")
cd( "$(IOCTOP)" )

# Run common startup commands for linux soft IOC's
< /reg/d/iocCommon/All/pre_linux.cmd

# Register all support components
dbLoadDatabase("dbd/ads.dbd")
ads_registerRecordDeviceDriver(pdbbase)

## LOAD STUFF HERE!!!  DRIVERS FIRST, THEN RECORDS!
## connect to TwinCAT runtime
adsAsynPortDriverConfigure("A","$$PLC","$$AMSID",851,1000,0,0,500,1000,1000,0)
##
## debuging
asynReport(2,"A")
#asynSetTraceMask("A",-1,0xFF)

####
##############################################################################
############# Configure and load axis record:
EthercatMCCreateController("MCU", "A", "32", "200", "1000", "")

epicsEnvSet("MOTOR_PORT",    "MCU")
epicsEnvSet("ASYN_PORT",     "MC_CPU")
epicsEnvSet("PREFIX",        "$$PREFIX")

$$LOOP(MOTOR)
EthercatMCCreateAxis("$(MOTOR_PORT)", "$$AXIS", "6", "")
dbLoadRecords("db/EthercatMC.template", "PREFIX=$(PREFIX), MOTOR_NAME=$$NAME, R=$$NAME:, MOTOR_PORT=$(MOTOR_PORT), ASYN_PORT=$(ASYN_PORT), AXIS_NO=$$AXIS, DESC=$$IF(DESC,$$DESC,Axis $$AXIS), VELO=0, JVEL=0, ACCL=0, PREC=4, DHLM=0, DLLM=0")
$$ENDLOOP(MOTOR)

##############################################################################

## Load records
dbLoadRecords("db/iocSoft.db", "IOC=$(IOC_PV)")
dbLoadRecords("db/save_restoreStatus.db", "IOC=$(IOC_PV)")

## debuging
asynReport(2,"A")

# Setup autosave
set_savefile_path( "$(IOC_DATA)/$(IOC)/autosave" )
set_requestfile_path( "$(TOP)/autosave" )
save_restoreSet_status_prefix( "$(IOC_PV):" )
save_restoreSet_IncompleteSetsOk( 1 )
save_restoreSet_DatedBackupFiles( 1 )
set_pass0_restoreFile( "$(IOCNAME).sav" )
set_pass1_restoreFile( "$(IOCNAME).sav" )

# Initialize the IOC and start processing records
iocInit()

# Start autosave backups
create_monitor_set( "$(IOCNAME).req", 5, "IOC=$(IOC_PV)" )

# All IOCs should dump some common info after initial startup.
< /reg/d/iocCommon/All/post_linux.cmd
