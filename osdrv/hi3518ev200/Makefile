
export OSDRV_DIR:=$(shell pwd)
export OSDRV_CROSS?=arm-hisiv500-linux

UBOOT_HI3518EV200:=u-boot-hi3518ev200.bin
UBOOT_HI3516CV200:=u-boot-hi3516cv200.bin
UBOOT_HI3518EV201:=u-boot-hi3518ev201.bin

UBOOT_REG_BIN_HI3518EV200:=reg_info_hi3518ev200.bin
UBOOT_REG_BIN_HI3516CV200:=reg_info_hi3516cv200.bin
UBOOT_REG_BIN_HI3518EV201:=reg_info_hi3518ev201.bin

UBOOT_HI3518EV200_CONFIG:=hi3518ev200_config
UBOOT_HI3516CV200_CONFIG:=hi3516cv200_config
UBOOT_HI3518EV201_CONFIG:=hi3518ev201_config

YAFFS_TOOL:=mkyaffs2image100

all: prepare hiboot liteos hitools build_done

clean: hiboot_clean liteos_clean hitools_clean

distclean: clean pub_clean clean_done

##task [0] prepare pub directory
prepare:
	@echo "------- task [0] prepare pub dir -------"
	mkdir $(OSDRV_DIR)/pub/boot -p
	mkdir $(OSDRV_DIR)/pub/tools -p

##task [1] make u-boot
hiboot:
	@echo "------- task [1] build u-boot -------"
	rm $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 -rf
	tar xzf $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06.tgz -C $(OSDRV_DIR)/opensource/u-boot
	find $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 | xargs touch
	cp $(OSDRV_DIR)/tools/pc/uboot_tools/mkboot.sh $(OSDRV_DIR)/pub/boot	
	chmod 777 $(OSDRV_DIR)/pub/boot/mkboot.sh

	make -C $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- $(UBOOT_HI3518EV200_CONFIG)
	pushd $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06;make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- -j 20 >/dev/null;popd
	cp $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06/u-boot.bin $(OSDRV_DIR)/pub/boot
	cp $(OSDRV_DIR)/tools/pc/uboot_tools/$(UBOOT_REG_BIN_HI3518EV200) $(OSDRV_DIR)/pub/boot	
	pushd $(OSDRV_DIR)/pub/boot;./mkboot.sh $(UBOOT_REG_BIN_HI3518EV200) $(UBOOT_HI3518EV200);popd
	
	make -C $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- distclean
	make -C $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- $(UBOOT_HI3516CV200_CONFIG)
	pushd $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06;make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- -j 20 >/dev/null;popd
	cp $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06/u-boot.bin $(OSDRV_DIR)/pub/boot
	cp $(OSDRV_DIR)/tools/pc/uboot_tools/$(UBOOT_REG_BIN_HI3516CV200) $(OSDRV_DIR)/pub/boot
	pushd $(OSDRV_DIR)/pub/boot;./mkboot.sh $(UBOOT_REG_BIN_HI3516CV200) $(UBOOT_HI3516CV200);popd
	
	make -C $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- distclean
	make -C $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- $(UBOOT_HI3518EV201_CONFIG)
	pushd $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06;make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- -j 20 >/dev/null;popd
	cp $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06/u-boot.bin $(OSDRV_DIR)/pub/boot
	cp $(OSDRV_DIR)/tools/pc/uboot_tools/$(UBOOT_REG_BIN_HI3518EV201) $(OSDRV_DIR)/pub/boot
	pushd $(OSDRV_DIR)/pub/boot;./mkboot.sh $(UBOOT_REG_BIN_HI3518EV201) $(UBOOT_HI3518EV201);popd
	
	rm $(OSDRV_DIR)/pub/boot/u-boot.bin
	rm $(OSDRV_DIR)/pub/boot/mkboot.sh
	rm $(OSDRV_DIR)/pub/boot/$(UBOOT_REG_BIN_HI3518EV200)
	rm $(OSDRV_DIR)/pub/boot/$(UBOOT_REG_BIN_HI3516CV200)
	rm $(OSDRV_DIR)/pub/boot/$(UBOOT_REG_BIN_HI3518EV201)


hiboot_clean:
	rm $(OSDRV_DIR)/opensource/u-boot/u-boot-2010.06 -rf

##task [2] make liteos
liteos:
	echo "------- task [2] build liteos -------"
	# uncompress source code
	rm $(OSDRV_DIR)/opensource/liteos/liteos -rf
	tar -xzf $(OSDRV_DIR)/opensource/liteos/liteos.tgz -C $(OSDRV_DIR)/opensource/liteos
	cd $(OSDRV_DIR)/opensource/liteos/liteos;lib/cxxstl/cxx_copy.sh $(OSDRV_CROSS) 4.9.4;cd $(OSDRV_DIR)
	pushd $(OSDRV_DIR)/opensource/liteos/liteos;make >/dev/null;popd

liteos_clean:
	rm $(OSDRV_DIR)/opensource/liteos/liteos/ -rf

hitools:
	@echo "---------task [3] build tools run on pc"
	make -C $(OSDRV_DIR)/tools/pc/mkyaffs2image/
	cp $(OSDRV_DIR)/tools/pc/mkyaffs2image/bin/$(YAFFS_TOOL) $(OSDRV_DIR)/pub/tools
	make -C $(OSDRV_DIR)/tools/pc/jffs2_tool/
	cp $(OSDRV_DIR)/tools/pc/jffs2_tool/mkfs.jffs2 $(OSDRV_DIR)/pub/tools

hitools_clean:
	make -C $(OSDRV_DIR)/tools/pc/mkyaffs2image clean
	make -C $(OSDRV_DIR)/tools/pc/jffs2_tool distclean

pub_clean:
	rm $(OSDRV_DIR)/pub/* -rf

build_done:
	@echo "------- osdrv build done -------"

clean_done:
	@echo "------- clean done -------"

