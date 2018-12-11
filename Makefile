#Makefile at top of application tree
TOP = .
-include $(TOP)/IOC_APPL_TOP
ifneq (,$(IOC_APPL_TOP))
TOP = $(IOC_APPL_TOP)
endif

include $(TOP)/configure/CONFIG
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard configure))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *Lib))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *App))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *app))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard iocBoot))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard iocboot))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard children))
include $(TOP)/configure/RULES_TOP
