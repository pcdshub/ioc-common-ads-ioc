TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

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
adsIoc_DBD += asyn.dbd
adsIoc_DBD += drvAsynIPPort.dbd
adsIoc_DBD += dbArchive.dbd

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

# adsIoc_registerRecordDeviceDriver.cpp will be created from adsIoc.dbd
adsIoc_SRCS += adsIoc_registerRecordDeviceDriver.cpp
adsIoc_SRCS += infoFieldArchive.c
adsIoc_SRCS_DEFAULT += adsIocMain.cpp

adsIoc_LIBS += devIocStats
adsIoc_LIBS += asyn
adsIoc_LIBS += autosave
adsIoc_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
