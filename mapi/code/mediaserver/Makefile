ifeq ($(MAPI_PARAM_FILE), ) 
    MAPI_PARAM_FILE:=../../Makefile.param
	include ./OSTYPE.param
    include $(MAPI_PARAM_FILE)
endif

ifeq ($(MS_PARAM_FILE), )
    MS_PARAM_FILE:=./Makefile.param
    include $(MS_PARAM_FILE)
endif

.PHONY:all comm mapi vcap vproc venc adapt disp acap aenc ao isp msg base component config clean

all: comm mapi vcap vproc venc acap adapt aenc ao disp isp base component config 

base:
	@cd base; make

comm:
	@cd comm; make

vcap:
	@cd vcap; make

vproc:
	@cd vproc; make

venc:
	@cd venc; make

aenc:
	@cd aenc; make
	
adapt:
	@cd adapt; make
	
ao:
	@cd ao; make
	
component:
	@cd component; make
	
isp:
	@cd isp; make
	
disp:
	@cd disp; make

acap:
	@cd acap; make
	
config:
	@cd configs; make
	

mapi:
	@mkdir -p $(REL_INC)
	@cp ../include/*h $(REL_INC)
	@cp ../include/mediaserver/*.h $(REL_INC)

clean:
	@cd base; make clean
	@cd comm; make clean
	@cd vcap; make clean
	@cd vproc; make clean
	@cd venc; make clean
	@cd aenc; make clean
	@cd adapt; make clean
	@cd component; make clean
	@cd acap; make clean
	@cd disp; make clean
	@cd configs; make clean
	@cd isp; make clean
	#@cd msg; make clean
	@rm -fr $(REL_INC)/*.h
