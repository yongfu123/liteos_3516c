ifeq ($(MAPI_PARAM_FILE), ) 
    MAPI_PARAM_FILE:=../../../../Makefile.param
	OSTYPE=HuaweiLite
    include $(MAPI_PARAM_FILE)
endif

#*************************************************************************
# all source file in this module
SRCS := src/hi_mapi_gyro.c


#*************************************************************************
TARGET := $(HIARCH)_mapi_gyro

CFLAGS += -I$(REL_INC)
CFLAGS += -I./include
#这个地方后续整理驱动的目录时需要整改
CFLAGS += -I$(DRV_ROOT)/extdrv/hi3519v101/gyro_bosch

#*************************************************************************
# compile linux or HuaweiLite
include $(PWD)/../../Make.$(OSTYPE)