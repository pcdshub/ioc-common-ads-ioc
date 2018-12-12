TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

USR_CXXFLAGS += -std=c++11

#=============================
# Build an ioc application
# Use PROD_IOC_RTEMS for RTEMS only
# Use PROD_IOC_Linux for Linux only
PROD_IOC = adsMotion

# adsMotion.dbd will be created and installed
DBD += adsMotion.dbd

# Include dbd files from all support applications:
adsMotion_DBD += base.dbd
adsMotion_DBD += iocAdmin.dbd
adsMotion_DBD += autosaveSupport.dbd
adsMotion_DBD += axisSupport.dbd
adsMotion_DBD += EthercatMCSupport.dbd
adsMotion_DBD += ads.dbd
adsMotion_DBD += asyn.dbd
adsMotion_DBD += drvAsynIPPort.dbd

# Add all the support libraries needed by this IOC
adsMotion_LIBS += axis
adsMotion_LIBS += EthercatMCSupport
adsMotion_LIBS += ads
adsMotion_LIBS += asyn

# Build the main IOC entry point on workstation OSs.
adsMotion_SRCS += adsMotion_registerRecordDeviceDriver.cpp
adsMotion_SRCS_DEFAULT += adsMotionMain.cpp
adsMotion_SRCS_vxWorks += -nil-

# Finally link to the EPICS Base libraries
adsMotion_LIBS += devIocStats
adsMotion_LIBS += autosave
adsMotion_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

