#Create by t00241283,2015/12/29
ifeq ($(PARAM_FILE), ) 
    PARAM_FILE:= ../../mpp/Makefile.param
    include $(PARAM_FILE)
endif

.PHONY:clean all drv

all: drv
	
drv:
	@cd $(INTERDRVVER) && make
	@cd common && make
	
clean:
	@cd $(INTERDRVVER) && make clean
	@cd common && make clean
