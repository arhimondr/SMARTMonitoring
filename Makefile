ifndef POCO_BASE
	POCO_BASE := ${POCO_BASE}
endif

ifndef POCO_BASE
$(error POCO_BASE is not defined.)
endif

export POCO_BASE

PROJECT_BASE := ${CURDIR}

$(info POCO_BASE:  $(POCO_BASE))
$(info PROJECT_BASE:  $(PROJECT_BASE))

export PROJECT_BASE

include $(POCO_BASE)/build/rules/global 

SYSLIBS += -ludev -lparted
export  SYSLIBS

objects = atasmart HDDExplorer IdentifyInfo SmartAttribute SmartInfo DiskInfo DiskInfoRequestHandler HandlerFactory SmartDeamonApplication main

target = main
target_libs = PocoNet PocoJSON PocoUtil PocoFoundation

include $(POCO_BASE)/build/rules/exec
