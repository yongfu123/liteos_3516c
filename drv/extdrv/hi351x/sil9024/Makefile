
ifeq ($(EXTDRV_PARAM_FILE), ) 
    EXTDRV_PARAM_FILE:=../Makefile.param
    include $(EXTDRV_PARAM_FILE)
endif



#SRCS = $(wildcard *.c)
SRCS := sil9024.c
#INC := -I$(REL_INC)
#INC += -I./arch/$(ARCH_DIR)/
INC += -I$(OSAL_ROOT)/linux/kernel/himedia
INC += -I$(OSAL_ROOT)/include
INC += -I$(DRV_ROOT)/extdrv/$(EXTDRVVER)/sil9024/arch/$(ARCH_DIR)/

EXTDRV_CFLAGS += $(INC)



		

#*************************************************************************
TARGET := hi_sil9024

#*************************************************************************
# compile linux or HuaweiLite
include $(PWD)/../Make.$(OSTYPE)

