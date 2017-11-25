cur_dir:=$(PWD)
SAMPLE_TOP_ROOT = $(cur_dir)
MAPI_TOP_ROOT = $(SAMPLE_TOP_ROOT)/../../..

OSTYPE=HuaweiLite

#LITEOSTOPDIR = $(cur_dir)/../..
LITEOSTOPDIR := $(MAPI_TOP_ROOT)/../osdrv/hi3518ev200/opensource/liteos/liteos

export LITEOSTOPDIR
SAMPLE_TOP_ROOT = $(cur_dir)

SAMPLE_OUT_ROOT = $(SAMPLE_TOP_ROOT)/out
SAMPLE_OUT_LIB_ROOT = $(SAMPLE_TOP_ROOT)/out/lib
SAMPLE_OUT_OBJ_ROOT = $(SAMPLE_TOP_ROOT)/out/obj

SAMPLE_SCRIPT_ROOT = $(SAMPLE_TOP_ROOT)/script
SAMPLE_SRC_ROOT = $(SAMPLE_TOP_ROOT)/src

include $(LITEOSTOPDIR)/config.mk

RM = -rm -rf



SRCS := 
SRCS += $(shell find $(cur_dir)/src/mcu_uart -name '*.c')
SRCS += $(shell find $(cur_dir)/src/net -name '*.c')
SRCS += $(shell find $(cur_dir)/src/reg_set -name '*.c')
SRCS += $(shell find $(cur_dir)/src/ipmsg -name '*.c')

SRCS += $(SAMPLE_SRC_ROOT)/common.c

ifeq ($(image_type),1)
SRCS += $(SAMPLE_SRC_ROOT)/sample_sta_wakeup.c
endif

ifeq ($(image_type),2)
SRCS += $(SAMPLE_SRC_ROOT)/sample_ap_wakeup.c
endif



SRCS := $(notdir $(SRCS))



OBJS = $(patsubst %.c,$(SAMPLE_OUT_OBJ_ROOT)/%.o,$(SRCS))


.PHONY: all clean liteos_image prepare 


include $(SAMPLE_TOP_ROOT)/cfg.mak
include $(SAMPLE_TOP_ROOT)/script/config_to_macro.mak

DEFAULT:all

TARGET = sample


CreateDir        =   $(shell [ -d $1 ] || mkdir -p $1 || echo ":mkdir '$1' fail")
RemoveDir        =   $(shell [ -d $1 ] && rm -rf $1 && echo -e "rmdir '$1'\t [ OK ]" || echo ":rm dir '$1' fail")

TMP_DIR := $(cur_dir)/out/tmp/
OBJ_DIR := $(cur_dir)/out/lib/OBJ



dummy :=  $(call CreateDir, $(SAMPLE_OUT_ROOT))
dummy :=  $(call CreateDir, $(SAMPLE_OUT_ROOT)/bin)
dummy :=  $(call CreateDir, $(SAMPLE_OUT_ROOT)/burn)
dummy :=  $(call CreateDir, $(SAMPLE_OUT_LIB_ROOT))
dummy :=  $(call CreateDir, $(SAMPLE_OUT_OBJ_ROOT))
dummy :=  $(call CreateDir, $(SAMPLE_OUT_LIB_ROOT))

dummy :=  $(call CreateDir, $(TMP_DIR))
dummy :=  $(call CreateDir, $(OBJ_DIR))


prepare:
	@echo "--------------prepare-------------" 

	
all: prepare $(OBJS)  $(TARGET)
	@echo "--------------make finish-------------" 

clean:
	@$(RM) -rf $(SAMPLE_OUT_ROOT)

VSS_INCLUDE := 

#VSS_INCLUDE += -I$(LITEOSTOPDIR)/drivers/mmc/himmcv100/src/
VSS_INCLUDE += -I$(LITEOSTOPDIR)/drivers/mmc/include/
VSS_INCLUDE += -I$(LITEOSTOPDIR)/drivers/mmc/host/himci/
VSS_INCLUDE += -I$(SAMPLE_SRC_ROOT)/mcu_uart
VSS_INCLUDE += -I$(SAMPLE_SRC_ROOT)/reg_set
VSS_INCLUDE += -I$(SAMPLE_SRC_ROOT)/ipmsg
VSS_INCLUDE += -I$(SAMPLE_SRC_ROOT)/net

mcu_uart_srcs := $(wildcard src/mcu_uart/*.c)
reg_set_srcs := $(wildcard src/reg_set/*.c)
ipmsg_srcs := $(wildcard src/ipmsg/*.c)
net_srcs := $(wildcard src/net/*.c)


ifeq ($(image_type),1)
top_srcs = $(SAMPLE_SRC_ROOT)/sample_sta_wakeup.c
endif

ifeq ($(image_type),2)
top_srcs = $(SAMPLE_SRC_ROOT)/sample_ap_wakeup.c
endif


top_srcs += $(SAMPLE_SRC_ROOT)/common.c

mcu_uart_objs = $(patsubst %.c,$(SAMPLE_OUT_OBJ_ROOT)/%.o, $(notdir $(mcu_uart_srcs)))
reg_set_objs = $(patsubst %.c,$(SAMPLE_OUT_OBJ_ROOT)/%.o, $(notdir $(reg_set_srcs)))
ipmsg_objs = $(patsubst %.c,$(SAMPLE_OUT_OBJ_ROOT)/%.o, $(notdir $(ipmsg_srcs)))
net_objs = $(patsubst %.c,$(SAMPLE_OUT_OBJ_ROOT)/%.o, $(notdir $(net_srcs)))
top_objs = $(patsubst %.c,$(SAMPLE_OUT_OBJ_ROOT)/%.o, $(notdir $(top_srcs)))



$(mcu_uart_objs):$(SAMPLE_OUT_OBJ_ROOT)/%.o:$(SAMPLE_SRC_ROOT)/mcu_uart/%.c
	@$(CC) $(LITEOS_CFLAGS) $(VSS_DEFS) $(VSS_INCLUDE) -c $< -o $@

$(reg_set_objs):$(SAMPLE_OUT_OBJ_ROOT)/%.o:$(SAMPLE_SRC_ROOT)/reg_set/%.c
	@$(CC) $(LITEOS_CFLAGS) $(VSS_DEFS) $(VSS_INCLUDE) -c $< -o $@
	
$(ipmsg_objs):$(SAMPLE_OUT_OBJ_ROOT)/%.o:$(SAMPLE_SRC_ROOT)/ipmsg/%.c
	@$(CC) $(LITEOS_CFLAGS) $(VSS_DEFS) $(VSS_INCLUDE) -c $< -o $@

$(net_objs):$(SAMPLE_OUT_OBJ_ROOT)/%.o:$(SAMPLE_SRC_ROOT)/net/%.c
	@$(CC) $(LITEOS_CFLAGS) $(VSS_DEFS) $(VSS_INCLUDE) -c $< -o $@
	
$(top_objs):$(SAMPLE_OUT_OBJ_ROOT)/%.o:$(SAMPLE_SRC_ROOT)/%.c
	@$(CC) $(LITEOS_CFLAGS) $(VSS_DEFS) $(VSS_INCLUDE) -c $< -o $@
	

LITEOS_LIBS += -lsample -lmhd  -lmhd_util


SAMPLELIB = $(SAMPLE_TOP_ROOT)/out/libsample.a

$(SAMPLELIB):$(OBJS)
	@$(AR) -rcs $@ $(OBJS) 
	
#$(error ------$(LITEOS_PLATFORM))
lib_copy:
	# This step is very important. All the lib files should be copied to the 
	# $(SAMPLE_OUT_LIB_ROOT) .
	@cp -rf $(LITEOSTOPDIR)/out/$(LITEOS_PLATFORM)/lib/*.a     $(SAMPLE_OUT_LIB_ROOT)
	@cp -rf $(SAMPLE_TOP_ROOT)/deps/wifi/out/$(LITEOS_PLATFORM)/*.a    $(SAMPLE_OUT_LIB_ROOT)
	mv $(SAMPLE_TOP_ROOT)/out/libsample.a  $(SAMPLE_OUT_LIB_ROOT)/libsample.a
	# sta wakeup
	if [[ "$(CFG_SCATTER_FLAG)" == "yes" && "$(CFG_WIFI_IMAGE)" != "yes"  && "$(image_type)" == "1" ]];then \
		echo  -------------------------$(image_type)-------------; \
		$(LITEOSTOPDIR)/tools/scripts/scatter_sr/scatter.sh   $(CROSS_COMPILE)  $(LITEOS_PLATFORM)    y    n    $(LITEOSTOPDIR)/tools/scripts/scatter_sr \
		$(LITEOSTOPDIR)/tools/scripts/ld     $(TMP_DIR)    $(OBJ_DIR)   ;\
	fi
	# ap wakeup
	if [[ "$(CFG_SCATTER_FLAG)" == "yes" && "$(CFG_WIFI_IMAGE)" != "yes"  && "$(image_type)" == "2" ]];then \
		echo  -------------------------$(image_type)-------------; \
		$(LITEOSTOPDIR)/tools/scripts/scatter_sr/scatter.sh   $(CROSS_COMPILE)  $(LITEOS_PLATFORM)    y    n    $(LITEOSTOPDIR)/tools/scripts/scatter_sr \
		$(LITEOSTOPDIR)/tools/scripts/ld     $(TMP_DIR)    $(OBJ_DIR)  $(SAMPLE_OUT_LIB_ROOT)  ;\
	fi

	if [[ "$(CFG_SCATTER_FLAG)" != "yes" ]] ;then \
		cp $(SAMPLE_TOP_ROOT)/script/wow_orignal.ld   $(CROSS_COMPILE)  $(LITEOSTOPDIR)/tools/scripts/ld/wow.ld;\
		cp $(SAMPLE_TOP_ROOT)/script/scatter_orignal.ld   $(LITEOSTOPDIR)/tools/scripts/ld/scatter.ld;\
	fi
LITEOS_LIBDEP := --start-group $(LITEOS_LIBS)   --end-group

MY_LD_FLAGS = -nostartfiles -static  -L$(LITEOSTOPDIR)/platform/bsp/$(LITEOS_PLATFORM) \
		-L$(LITEOSTOPDIR)/tools/scripts/ld -T$(LITEOSTOPDIR)/liteos.ld $(LITEOS_TABLES_LDFLAGS)
MY_LD_FLAGS += -L$(SAMPLE_OUT_LIB_ROOT)/OBJ   -L$(SAMPLE_OUT_LIB_ROOT)


$(TARGET):  $(SAMPLELIB) lib_copy
	$(LD) $(MY_LD_FLAGS) --gc-sections -Map=$(SAMPLE_OUT_ROOT)/bin/sample.map -o $(SAMPLE_OUT_ROOT)/bin/sample   $(LITEOS_LIBDEP)
	$(OBJCOPY) -O binary $(SAMPLE_OUT_ROOT)/bin/sample $(SAMPLE_OUT_ROOT)/burn/sample.bin
	$(OBJDUMP) -d $(SAMPLE_OUT_ROOT)//bin/sample >$(SAMPLE_OUT_ROOT)/bin/sample.asm
	chmod u+x $(LITEOSTOPDIR)/tools/scripts/scatter_sr/scatter_size.sh 
	$(LITEOSTOPDIR)/tools/scripts/scatter_sr/scatter_size.sh    $(SAMPLE_OUT_ROOT)/bin/sample
	

liteos_image:
	@chmod u+x $(SAMPLE_TOP_ROOT)/script/gen_image.sh
	@$(SAMPLE_TOP_ROOT)/script/gen_image.sh

liteos_image_clean: clean
	@cp $(SAMPLE_SCRIPT_ROOT)/wow_orignal.ld    $(LITEOSTOPDIR)/tools/scripts/ld/wow.ld   -f
	@cp $(SAMPLE_SCRIPT_ROOT)/scatter_orignal.ld     $(LITEOSTOPDIR)/tools/scripts/ld/scatter.ld  -f
	@if [[ -f  $(LITEOSTOPDIR)/tools/scripts/scatter_sr/liblist.sh.bak ]]; then \
		rm $(LITEOSTOPDIR)/tools/scripts/scatter_sr/liblist.sh; \
		mv $(LITEOSTOPDIR)/tools/scripts/scatter_sr/liblist.sh.bak $(LITEOSTOPDIR)/tools/scripts/scatter_sr/liblist.sh;\
	fi	
