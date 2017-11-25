ifeq ($(MAPI_PARAM_FILE), ) 
    MAPI_PARAM_FILE:=../../../../Makefile.param
    OSTYPE=HuaweiLite
    include $(MAPI_PARAM_FILE)
endif

.PHONY:all clean

all:
	@cd $(HIARCH); make
clean:
	@cd $(HIARCH); make clean

