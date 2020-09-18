TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
#  Optimization of db files using dbst (DEFAULT: NO)
#DB_OPT = YES

#----------------------------------------------------
# Create and install (or just install)
# databases, templates, substitutions like this

#----------------------------------------------------
# Create and install (or just install)
# Archive files, templates, substitutions like this
#
ARCHIVE +=
REQ +=

DB += EthercatMC.template
DB += EthercatMCdebug.template
DB += EthercatMChome.template
DB += EthercatMCreadback.template
DB += EthercatMCslitAvoidCollSoftlimits.template
DB += EthercatMCslit_hard.template
DB += EthercatMCslit_soft.template
DB += caPutLog.db
DB += TwinCAT_TaskInfo.db
DB += TwinCAT_AppInfo.db

DB_INSTALLS += $(IOCADMIN)/db/iocSoft.db
DB_INSTALLS += $(IOCADMIN)/db/devIocInfo.db
DB_INSTALLS += $(AUTOSAVE)/db/save_restoreStatus.db
DB_INSTALLS += $(ASYN)/db/asynRecord.db

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

