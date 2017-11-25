make ARCH=arm CROSS_COMPILE=arm-hisiv500-linux-  hi3516cv200_config 
make ARCH=arm CROSS_COMPILE=arm-hisiv500-linux-

将生成的u-boot.bin 复制到osdrv/tools/pc/uboot_tools/目录下
运行./mkboot.sh reg_info.bin u-boot-ok.bin
生成的u-boot-ok.bin即为可用的u-boot镜像



