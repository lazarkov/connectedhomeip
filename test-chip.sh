#!/bin/bash

adb push chip_server_kvs.tmp /tmp/chip_server_kvs.tmp

echo "***************************************"
echo "** Now CHIP pair with your TV        **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool pairing onnetwork 0 20202021 3840 10.78.130.161 11097
sleep 5

echo "***************************************"
echo "** Now CHIP will turn on off your TV **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool onoff toggle 1
sleep 5
./out/debug/standalone/chip-tool onoff toggle 1
sleep 5

echo "***************************************"
echo "** Now CHIP will mute unmute your TV **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool onoff toggle 2
sleep 5
./out/debug/standalone/chip-tool onoff toggle 2

sleep 5
echo "***************************************"
echo "** Now CHIP will set TV to low power **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool lowpower sleep 1

echo "***************************************"
echo "** Now CHIP will turn on     your TV **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool onoff toggle 1

echo "***************************************"
echo "** Now CHIP will volume up TV        **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool levelcontrol step 0 2 0 0 0 2

echo "***************************************"
echo "** Now CHIP will volume down TV        **"
echo "***************************************"
sleep 5
./out/debug/standalone/chip-tool levelcontrol step 1 2 0 0 0 2

sleep 5
echo "***************************************"
echo "** Now CHIP navigate through fire TV **"
echo "***************************************"
./out/debug/standalone/chip-tool keypadinput send-key 4 1
./out/debug/standalone/chip-tool keypadinput send-key 4 1
./out/debug/standalone/chip-tool keypadinput send-key 4 1
./out/debug/standalone/chip-tool keypadinput send-key 4 1
./out/debug/standalone/chip-tool keypadinput send-key 2 1
./out/debug/standalone/chip-tool keypadinput send-key 2 1
./out/debug/standalone/chip-tool keypadinput send-key 0 1
