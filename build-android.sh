#!/bin/bash

cd examples/tv-app/linux/
gn gen out/android_arm --args='target_os="android" target_cpu="arm" chip_build_tests=false chip_device_platform="linux" chip_mdns="none" chip_enable_openthread=false chip_enable_wifi=false android_ndk_root="/Users/lkovacic/Library/Android/sdk/ndk-bundle" android_sdk_root="/Users/lkovacic/Library/Android/sdk"'
ninja -C out/android_arm all
