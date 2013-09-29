include $(POCO_BASE)/build/rules/global 

SYSLIBS += -ludev -lparted
export  SYSLIBS

objects = atasmart HDDExplorer IdentifyInfo SmartAttribute SmartInfo DiskInfo DiskInfoRequestHandler HandlerFactory SmartDeamonApplication main

target = main
target_libs = PocoNet PocoJSON PocoUtil PocoFoundation

include $(POCO_BASE)/build/rules/exec
