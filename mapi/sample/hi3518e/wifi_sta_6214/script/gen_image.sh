#!/bin/sh

set -e

cur_dir=`pwd`

dir_code=${cur_dir}
dir_scatter=${LITEOSTOPDIR}/tools/scripts/scatter_sr
dir_ld=${dir_scatter}/../ld


echo "select the image you want to make:"
echo "			1:wifi sta image"
echo "			2:wifi ap  image"


read image_type

echo $image_type
if [[ "$image_type" != 1  && "$image_type" != 2  ]];then
	echo "please enter right choice"
	exit 1
fi

export CFG_SCATTER_FLAG=yes

export image_type


if [[ "$image_type" = "1" ]];then
	export CFG_WIFI_IMAGE=yes
	export CFG_SUPPORT_WIFI_WAKEUP=yes
	export CFG_SUPPORT_WIFI_AP=no
elif [[ "$image_type" = "2" ]];then
	export CFG_WIFI_IMAGE=yes
	export CFG_SUPPORT_WIFI_WAKEUP=yes
	export CFG_SUPPORT_WIFI_AP=yes
fi




# step 1
cp ${dir_code}/script/wow_orignal.ld    ${dir_ld}/wow.ld   -f
cp ${dir_code}/script/scatter_orignal.ld     ${dir_ld}/scatter.ld  -f

cd ${dir_code}; make clean; make ;cd -


# step 2
cd ${dir_scatter}

chmod -R 777 *

rm -f lib_list.wow.*
rm -f lib_list.scatter.*
rm -f symbol_list.wow.*
rm -f symbol_list.scatter.*


if [[ "$image_type" = "1" ]];then
	./liblist.sh  hi3518ev200  wow   ${dir_code}/out/bin/sample  ${dir_code}/out/bin/sample.map   ${dir_scatter}    ${dir_code}/out/lib
elif [[ "$image_type" = "2" ]];then
	./liblist.sh  hi3518ev200  wow   ${dir_code}/out/bin/sample  ${dir_code}/out/bin/sample.map   ${dir_scatter}    ${dir_code}/out/lib
fi

cd -


# step 3

if [[ "$image_type" = "1" ]];then
	export CFG_WIFI_IMAGE=no
elif [[ "$image_type" = "2" ]];then
	export CFG_WIFI_IMAGE=no
fi



cd ${dir_code}; make clean; make;cd - 


