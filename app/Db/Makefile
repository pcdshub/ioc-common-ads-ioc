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

DB_INSTALLS += EthercatMC.template
DB_INSTALLS += EthercatMCdebug.template
DB_INSTALLS += EthercatMChome.template
DB_INSTALLS += EthercatMCreadback.template
DB_INSTALLS += EthercatMCslitAvoidCollSoftlimits.template
DB_INSTALLS += EthercatMCslit_hard.template
DB_INSTALLS += EthercatMCslit_soft.template

DB_INSTALLS += $(IOCADMIN)/db/iocSoft.db
DB_INSTALLS += $(IOCADMIN)/db/devIocInfo.db
DB_INSTALLS += $(AUTOSAVE)/db/save_restoreStatus.db
DB_INSTALLS += $(ASYN)/db/asynRecord.db

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

