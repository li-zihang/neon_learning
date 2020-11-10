#!/bin/bash
if [ $# -eq 1 ]; then
  export INSTALL_PREFIX=$1

else
  echo "Please specifiy the install path"
  echo "$0 install_path"
  exit -1

fi

if [ ! -d build_android_aarch64 ]; then
    mkdir -p build_android_aarch64
fi
cd build_android_aarch64


BUILD_DIR="armv8a-release"
if [ ! -d $BUILD_DIR ]; then
    mkdir -p $BUILD_DIR
fi
cd $BUILD_DIR


export ANDROID_NDK="./3rdparty/android-ndk-r17c"
echo "ANDROID_NDK=====>:${ANDROID_NDK}"


if [ "$ANDROID_NDK" = "" ]; then
    echo "ERROR: Please set ANDROID_NDK_HOME environment"
    exit
fi


cmake ../.. \
 -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
 -D__ARM_NEON=ON \
 -DANDROID_ABI="arm64-v8a" \
 -DANDROID_PLATFORM=android-21 \

make -j4 VERBOSE=1

cd ../../
DEMO_DIR=build_android_aarch64/$BUILD_DIR/test_demo
if [ ! -d $DEMO_DIR ]; then
    mkdir -p $DEMO_DIR
fi


echo "build_dir:$BUILD_DIR"
cp -rf build_android_aarch64/$BUILD_DIR/test_task $DEMO_DIR
