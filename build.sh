#!/bin/bash
source envs

cores=$(lscpu | grep socket | awk '{print$4}')
threads=$(lscpu | grep core | awk '{print$4}')
jobs=$(expr $cores \* $threads)

# Build Godot engine
cd godot
scons -j$jobs platform=x11