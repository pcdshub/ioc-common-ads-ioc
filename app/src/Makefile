TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build an ioc application
PROD_IOC = adsMotion

# adsMotion.dbd will be created and installed
DBD += adsMotion.dbd

# adsMotion.dbd will be made up from these files:
adsMotion_DBD += base.dbd
adsMotion_DBD += iocAdmin.dbd
adsMotion_DBD += asSupport.dbd
adsMotion_DBD += ads.dbd
adsMotion_DBD += asyn.dbd
adsMotion_DBD += drvAsynIPPort.dbd

ifneq (,$(findstring /,$(CALC)))
  adsMotion_DBD += calcSupport.dbd
  adsMotion_LIBS += calc
endif

ifneq (,$(findstring /,$(ADS)))
  adsMotion_LIBS += ads
  adsMotion_DBD  += ads.dbd
endif

ifneq (,$(findstring /,$(MOTOR)))
  adsMotion_DBD += motorSupport.dbd
  adsMotion_DBD += devSoftMotor.dbd
  adsMotion_DBD += EthercatMcSupport.dbd

  adsMotion_LIBS += motor
  adsMotion_LIBS += softMotor
  adsMotion_LIBS += EthercatMcSupport
endif

# adsMotion_registerRecordDeviceDriver.cpp will be created from adsMotion.dbd
adsMotion_SRCS += adsMotion_registerRecordDeviceDriver.cpp
adsMotion_SRCS_DEFAULT += adsMotionMain.cpp

adsMotion_LIBS += devIocStats
adsMotion_LIBS += asyn
adsMotion_LIBS += autosave
adsMotion_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
