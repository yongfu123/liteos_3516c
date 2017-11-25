=========================================================================
*********************LiteOS小系统环境使用说明****************************
=========================================================================

------------------------------目录介绍-----------------------------------

opensource:	存放U-boot、LiteOS源码
pub:		存放输出镜像
toolchain:	存放编译工具链
tools:		存放其他工具

----------------------------工具链安装-----------------------------------
toolchain目录下有arm-hisiv500-linux.tar.bz2 和 arm-hisiv500-linux.install两个文件，其中
arm-hisiv500-linux.tar.bz2 是安装包，arm-hisiv500-linux.install 是  x86_64-linux-gnu
服务器上的安装脚本。
安装方法：
1. 将arm-hisiv500-linux.tar.bz2 和 arm-hisiv500-linux.install放在同一级目录下；
2. ./arm-hisiv500-linux.install
  执行完以上命令即完成安装。
注意，如果服务器已经安装好了arm-hisiv500-linux- 工具链，不必重新安装。

---------------------------u-boot单独编译--------------------------------
对于demo板：
cd osdrv/opensource/u-boot/
tar -xf arm-hisiv500-linux.tar.bz2
cd arm-hisiv500-linux
make ARCH=arm CROSS_COMPILE=arm-hisiv500-linux- hi3518ev200_config
make ARCH=arm CROSS_COMPILE=arm-hisiv500-linux-
cp osdrv/tools/pc/uboot_tools/mkboot.sh .
cp osdrv/tools/pc/uboot_tools/reg_info_hi3518ev200.bin .
./mkboot.sh reg_info_hi3518ev200.bin u-boot-final.bin
完成以上命令之后，当前目录下会生成 u-boot-final.bin 文件，u-boot-final.bin
即为可用的u-boot镜像
对dv板的 u-boot，请参加源码包的readme。
