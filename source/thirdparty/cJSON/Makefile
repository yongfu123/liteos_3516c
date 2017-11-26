# Base Define
COMPILE_ROOT := $(shell pwd)

HIARCH := hi3518e
OSTYPE := HuaweiLite
CROSS_COMPILE = arm-hisiv500-linux-
LITEOSTOPDIR := $(shell pwd)/../../../osdrv/$(HIARCH)v200/opensource/liteos/liteos
include $(LITEOSTOPDIR)/config.mk

# Path Define
SRC_ROOT := ./src
INC_ROOT	:= ./include
LIBOUT = lib


# Module Include Path
MOD_INC_PATH     := $(sort $(dir $(shell find $(INC_ROOT) -name '*.h')))
VSS_INCLUDE_PATH += $(foreach dir, $(MOD_INC_PATH), -I$(dir))

# Create Object and Release Directory
CreateResult :=


# Lib Name
LIB  := $(LIBOUT)/libcJSON.a


.PHONY: all lib clean 
all: lib

cJSON.o : $(SRC_ROOT)/cJSON.c
	@$(CC) $(CFLAGS) -c $< $(VSS_INCLUDE_PATH) -o $@ 
lib: $(SRC_ROOT)/cJSON.c cJSON.o
	@mkdir -p $(LIBOUT)
	@$(AR) rcs $(LIB) cJSON.o
	@rm cJSON.o

clean:
	@rm -rf $(LIBOUT) cJSON.o 
	