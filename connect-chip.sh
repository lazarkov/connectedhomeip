#!/bin/bash

echo "******************************************"
echo "** connecting to your TV from chip tool **"
echo "******************************************"

# adb connect 10.78.130.166
adb shell iptables -A INPUT -i wlan0 -p udp --dport 11097 -j ACCEPT
./out/debug/standalone/chip-tool pairing onnetwork 0 20202021 3840 10.78.130.161 11097

echo "***************************************"
echo "** Now CHIP will turn on off your TV **"
echo "***************************************"

sleep 3
./out/debug/standalone/chip-tool onoff on 1
