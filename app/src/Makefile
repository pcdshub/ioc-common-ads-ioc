TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# tcmotor record type — TwinCAT motor record with motor record field naming
# convention (.VAL, .RBV, .DMOV etc.) and no internal motion logic.
# Built as a standalone library so it can be used by other IOCs in the module.
# DBDINC triggers auto-generation of tcmotorRecord.h from tcmotorRecord.dbd
# before the C source is compiled.
DBDINC += tcmotorRecord
LIBRARY_IOC += tcmotorRecord
tcmotorRecord_SRCS += tcmotorRecord.c
tcmotorRecord_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build an ioc application
PROD_IOC = adsIoc

# adsIoc.dbd will be created and installed
DBD += adsIoc.dbd

# adsIoc.dbd will be made up from these files:
adsIoc_DBD += base.dbd
adsIoc_DBD += iocAdmin.dbd
adsIoc_DBD += asSupport.dbd
adsIoc_DBD += ads.dbd
adsIoc_DBD += stream.dbd
adsIoc_DBD += asyn.dbd
adsIoc_DBD += drvAsynIPPort.dbd
adsIoc_DBD += dbArchive.dbd
adsIoc_DBD += system.dbd
adsIoc_DBD += tcmotorRecord.dbd

ifneq (,$(findstring /,$(CAPUTLOG)))
  adsIoc_DBD += caPutLog.dbd
  adsIoc_LIBS += caPutLog
endif

ifneq (,$(findstring /,$(CALC)))
  adsIoc_DBD += calcSupport.dbd
  adsIoc_LIBS += calc
endif

ifneq (,$(findstring /,$(ADS)))
  adsIoc_LIBS += ads
  adsIoc_DBD  += ads.dbd
endif

ifneq (,$(findstring /,$(MOTOR)))
  adsIoc_DBD += motorSupport.dbd
  adsIoc_DBD += devSoftMotor.dbd
  adsIoc_DBD += EthercatMcSupport.dbd

  adsIoc_LIBS += motor
  adsIoc_LIBS += softMotor
  adsIoc_LIBS += EthercatMcSupport
endif

ifdef PCRE
LIB_LIBS += pcre
else
ifneq ($(words $(PCRE_LIB) $(PCRE_INCLUDE)),0)
PROD_SYS_LIBS_DEFAULT += pcre
PROD_SYS_LIBS_WIN32 += $(PCRE_LIB)\\pcre
SHRLIB_DEPLIB_DIRS += $(PCRE_LIB)
USR_LDFLAGS+=-L$(PCRE_LIB)
endif
endif

# adsIoc_registerRecordDeviceDriver.cpp will be created from adsIoc.dbd
adsIoc_SRCS += adsIoc_registerRecordDeviceDriver.cpp
adsIoc_SRCS += infoFieldArchive.c
adsIoc_SRCS += afterIocRunning.c
adsIoc_SRCS_DEFAULT += adsIocMain.cpp

adsIoc_LIBS += tcmotorRecord
adsIoc_LIBS += devIocStats
adsIoc_LIBS += asyn
adsIoc_LIBS += autosave
adsIoc_LIBS += stream
adsIoc_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
