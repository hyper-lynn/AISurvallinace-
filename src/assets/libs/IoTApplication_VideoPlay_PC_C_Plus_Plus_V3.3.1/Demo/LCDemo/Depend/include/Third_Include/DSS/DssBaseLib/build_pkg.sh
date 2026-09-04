#!/bin/bash

# Usage : build_pkg.sh [target_type]

# NOTE : SHOULD ONLY MODIFY CUSTOM SECTION !


# <1> Set Build Target and Option

SP_TARGETS[1]="linux32-centos6-gcc-debug"
SP_TARGETS[2]="linux32-centos6-gcc-release"
SP_TARGETS[3]="linux32-centos5-gcc-debug"
SP_TARGETS[4]="linux32-centos5-gcc-release"
SP_TARGETS[5]="mac32-llvmgcc42-debug"
SP_TARGETS[6]="mac32-llvmgcc42-release"
SP_TARGETS[7]="linux64-centos6-gcc-debug"
SP_TARGETS[8]="linux64-centos6-gcc-release"
SP_TARGETS[9]="linux64-centos5-gcc-debug"
SP_TARGETS[10]="linux64-centos5-gcc-release"
SP_TARGETS[11]="sh4-linux-uclibc-gcc-debug"
SP_TARGETS[12]="sh4-linux-uclibc-gcc-release"
SP_TARGETS[13]="mac32-xcode5-debug"
SP_TARGETS[14]="mac32-xcode5-release"
SP_TARGETS[15]="mac-armv7-xcode5-debug"
SP_TARGETS[16]="mac-armv7-xcode5-release"
SP_TARGETS[17]="android-arm-gcc46-debug"
SP_TARGETS[18]="android-arm-gcc46-release"
SP_TARGETS[19]="mac-arm64-xcode5-debug"
SP_TARGETS[20]="mac-arm64-xcode5-release"
SP_TARGETS[21]="android-arm64-gcc49-debug"
SP_TARGETS[22]="android-arm64-gcc49-release"
SP_TARGETS[23]="aarch64-linux-gcc483-debug"
SP_TARGETS[24]="aarch64-linux-gcc483-release"
SP_TARGETS_NUM=24

TARGET_TYPE=$1
if [ -z "$TARGET_TYPE" ] ; then
	for (( i = 1 ; i <= $SP_TARGETS_NUM ; i++ )) ; do
		echo "$i : ${SP_TARGETS[$i]}"
	done
	echo "Please choose target :"
	read idx
	TARGET_TYPE=${SP_TARGETS[$idx]}
	if [ -z "$TARGET_TYPE" ] ; then
		echo "ERR : bad choose"
		exit 1
	fi
fi

valid=0
for (( i = 1 ; i <= $SP_TARGETS_NUM ; i++ )) ; do
	if [ "$TARGET_TYPE" == "${SP_TARGETS[$i]}" ] ; then
		valid=1
	fi
done
if [ "$valid" == "0" ] ; then
	echo "Usage: build_pkg.sh <target_type>"
	exit 1
fi

set -x

FN_D=""
if [ ${TARGET_TYPE:(-5)} == "debug" ] ; then
	FN_D="_d"
fi

export DSL_BUILD_TARGET=$TARGET_TYPE

if [ -z "$MAKE_OPT" ] ; then
	MAKE_OPT="-j 4 -l 4"
fi


NEED_STATIC_LIB=1
#if [ ${TARGET_TYPE:8:6} == "centos" ] ; then
#	NEED_STATIC_LIB=0
#fi

if [ ${TARGET_TYPE:8:7} == "centos6" ] ; then
	BUILD_OPT="$BUILD_OPT DSL_ZLIB_ASM=1"
fi


# <2> Build Target From Source

export LC_ALL=C
echo build at $(date)

#######################################
####	Custom Section Begin
#######################################

make -C .. clean
make -C .. $MAKE_OPT
if [ $? -ne 0 ] ; then
	echo "ERR : build failed"
	exit 1
fi

# <3> Package Target

DST_DIR=DssBaseLib${FN_D}
rm -rf $DST_DIR ${DST_DIR}.tar.gz

mkdir $DST_DIR
cd $DST_DIR
mkdir AX_API
mkdir HTTP
mkdir RTP
mkdir RTSP
mkdir tinyxml
mkdir TPLayer
mkdir Utils
mkdir libdsl
mkdir libdsl/ESB
mkdir jsondsl
mkdir pugixmldsl
mkdir sqlitedsl
mkdir zlibdsl
mkdir curl
mkdir log4cplus
mkdir html
mkdir html/jstree
cd ..

cp ../DOAXBase/AX_API/*.h $DST_DIR/AX_API
cp ../DOAXBase/AX_API/*.inl $DST_DIR/AX_API
cp ../DOAXBase/HTTP/*.h $DST_DIR/HTTP
cp ../DOAXBase/RTP/*.h $DST_DIR/RTP
cp ../DOAXBase/RTSP/*.h $DST_DIR/RTSP
cp ../DOAXBase/tinyxml/*.h $DST_DIR/tinyxml
cp ../DOAXBase/TPLayer/*.h $DST_DIR/TPLayer
cp ../DOAXBase/Utils/*.h $DST_DIR/Utils
cp ../libdsl/*.h $DST_DIR/libdsl
cp ../libdsl/jsondsl/*.h $DST_DIR/jsondsl
cp ../libdsl/pugixmldsl/*.h* $DST_DIR/pugixmldsl
cp ../libdsl/ESB/*.h* $DST_DIR/libdsl/ESB
cp ../dslalien/dslalien.h $DST_DIR
cp ../dslalien/sqlitedsl/*.h $DST_DIR/sqlitedsl
cp ../dslalien/zlibdsl/zconf.h $DST_DIR/zlibdsl
cp ../dslalien/zlibdsl/zlib.h $DST_DIR/zlibdsl
cp ../dslalien/curl/include/curl/*.h $DST_DIR/curl
cp ../dslalien/curl/ftp_opt.h $DST_DIR/curl
cp -rf ../dslalien/log4cplus/include/log4cplus/* $DST_DIR/log4cplus
cp ../libdsl_ssl/DSHA.h $DST_DIR/libdsl
cp ../libdsl_ssl/AESCryption.h $DST_DIR/libdsl
cp ../libdsl_ssl/RSACryption.h $DST_DIR/libdsl
cp ../libdsl_ssl/DSecureUtil.h $DST_DIR/libdsl

rm -f $DST_DIR/libdsl/StdAfx.h
rm -f $DST_DIR/libdsl/svn_version.h

cp ../DOAXBase/libDOAXBase${FN_D}.a $DST_DIR
cp ../libdsl/libdsl${FN_D}.so $DST_DIR
cp ../dslalien/libdslalien${FN_D}.so $DST_DIR
cp ../libdsl_ssl/libdsl_ssl${FN_D}.a $DST_DIR

if [ $NEED_STATIC_LIB == 1 ] ; then
	cp ../libdsl/libdsl_static${FN_D}.a $DST_DIR
	cp ../dslalien/libdslalien_static${FN_D}.a $DST_DIR
fi

# status server html
cp ../demo/html/*.html $DST_DIR/html
cp ../demo/html/jstree/*.* $DST_DIR/html/jstree

# put these in release package as example for other module
cp ../Makefile.template $DST_DIR
cp ../Makefile.template.qt $DST_DIR
cp ../Makefile $DST_DIR/Makefile_sample_for_root_dir
cp ../libdsl/Makefile $DST_DIR/Makefile_sample_for_sub_dir
cp ../test/Makefile $DST_DIR/Makefile_sample_for_test_dir

cp build_pkg*.* $DST_DIR
cp test_pkg*.* $DST_DIR
cp upload_pkg*.* $DST_DIR
cp gen_svninfo_header.bat $DST_DIR
cp ../Depend/build_depend*.* $DST_DIR
cp ../Depend/update_depend*.* $DST_DIR


#Lint配置目录
TOPDIR=$(pwd)/..

make -C .. flintclean
make -C .. flint

#lint报告
LINT_DIR=lint-report
mkdir $LINT_DIR
cp -rf ../flexelint/report/* $LINT_DIR

########################################
####	Custom Section End
########################################

cp ../Depend/Version.xml $DST_DIR

tar czf ${DST_DIR}.tar.gz $DST_DIR

#打包lint报告
tar zcf $LINT_DIR.tar.gz $LINT_DIR

