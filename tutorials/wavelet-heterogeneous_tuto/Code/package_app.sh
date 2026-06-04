#!/bin/sh

FOLDER=${1%/} # %/ removes potential trailing "/"
PACKAGE=PACKAGE_"${FOLDER/generated_/}"/ # remove "generated" from folder name
DEST=${2}

if [ -z ${FOLDER} ]; then
	echo "usage : bash setup_package.sh <generated_folder>"
	exit 1
fi

rm -rf $PACKAGE
mkdir $PACKAGE
cp $FOLDER/vitis_platform/dtbo_output/pl.dtbo $PACKAGE

cp $FOLDER/system_project/app_component/build/hw/app_component $PACKAGE
chmod +x $PACKAGE/app_component

cp $FOLDER/system_project/system_project/build/hw/hw_link/*.xclbin $PACKAGE/container.xclbin
cp $PACKAGE/container.xclbin $PACKAGE/container.bin

cp akiyo_cif.yuv $PACKAGE

echo '{\n  "shell_type" : "XRT_FLAT",\n  "num_slots": "1"\n}' > $PACKAGE/shell.json

cp $FOLDER/system_project/system_project/build/hw/hw_link/container/reports/container/imp/impl_1_full_util_placed.rpt $PACKAGE

if ! [ -z ${DEST} ]; then
	cp -r ${PACKAGE} ${DEST}
fi

echo "setup done !"
