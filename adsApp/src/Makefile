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
PROD_IOC = ads

# ipimbIoc.dbd will be created and installed
DBD += ads.dbd

# ads.dbd will be made up from these files:
ads_DBD += base.dbd
ads_DBD += iocAdmin.dbd
ads_DBD += autosaveSupport.dbd
ads_DBD += ads.dbd
# Include dbd files from all support applications:
#ads_DBD += xxx.dbd
ifdef AXIS
ads_DBD += axisSupport.dbd
ads_DBD += EthercatMCSupport.dbd
#ads_DBD += axis.dbd
endif
ads_DBD += asyn.dbd
ads_DBD += drvAsynIPPort.dbd

# Add all the support libraries needed by this IOC
ifdef AXIS
ads_LIBS += axis
ads_LIBS += EthercatMCSupport
endif
ads_LIBS += ads
ads_LIBS += asyn

# Build the main IOC entry point on workstation OSs.
ads_SRCS += ads_registerRecordDeviceDriver.cpp
ads_SRCS_DEFAULT += adsMain.cpp
ads_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#ads_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
ads_LIBS += devIocStats
ads_LIBS += autosave
ads_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

