#!/bin/bash

# Usage : test_pkg.sh [target_type]

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
SP_TARGETS_NUM=12

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
	echo "Usage: test_pkg.sh <target_type>"
	exit 1
fi

set -x

BUILD_OPT=""
FN_D=""
if [ ${TARGET_TYPE:(-5)} == "debug" ] ; then
	BUILD_OPT="$BUILD_OPT D=1"
	FN_D="_d"
fi
if [ ${TARGET_TYPE:0:3} == "mac" ] ; then
	BUILD_OPT="$BUILD_OPT MAC=1"
fi
if [ ${TARGET_TYPE:0:17} == "sh4-linux-uclibc-" ] ; then
	BUILD_OPT="$BUILD_OPT CROSS=sh4-linux-uclibc-"
fi

if [ -z "$MAKE_OPT" ] ; then
	MAKE_OPT="-j 4"
fi

# <2> Build Test Target

export LC_ALL=C
echo build at $(date)

#######################################
####	Custom Section Begin
#######################################

make -C .. test_clean $BUILD_OPT
make -C .. $MAKE_OPT test $BUILD_OPT
if [ $? -ne 0 ] ; then
	echo "ERR : build test failed"
	exit 1
fi

# <3> Run Test

ls -l ../test/test${FN_D}.exe
../test/test${FN_D}.exe
if [ $? -ne 0 ] ; then
	echo "ERR : test run failed"
	exit 1
fi

########################################
####	Custom Section End
########################################

