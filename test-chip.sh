#!/bin/bash

echo "***************************************"
echo "** Now CHIP will turn on off your TV **"
echo "***************************************"

./out/debug/standalone/chip-tool onoff off 1
sleep 5
./out/debug/standalone/chip-tool onoff on 1

echo "***************************************"
echo "** Now CHIP will mute unmute your TV **"
echo "***************************************"

./out/debug/standalone/chip-tool onoff off 2
sleep 2
./out/debug/standalone/chip-tool onoff on 2

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
