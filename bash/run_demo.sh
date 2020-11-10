#!/usr/bin/env bash
SNPE_LIB=build_android_aarch64/armv8a-release/test_demo

adb push $SNPE_LIB /data/local/tmp/
bin_path="/data/local/tmp/test_demo/"
adb shell "chmod +x ${bin_path}"
adb shell "cd ${bin_path} \
       && export LD_LIBRARY_PATH=${bin_path}:${LD_LIBRARY_PATH} \
       && ./test_task "


