#!/bin/bash

# Setup MediapipeModule_library
git clone https://github.com/purgeme/MediapipeModule_library.git
cd MediapipeModule_library
./setup.sh
./build.sh

# Copy libary file
mkdir ../libraries
cp library/libgmod.so ../libraries/
cd ..

# Download godot source code
git clone https://github.com/godotengine/godot.git -b 3.4

# Copy module files to modules directory
mkdir godot/modules/mediapipe
\cp -r mediapipe_module/* godot/modules/mediapipe/

# Copy required files to module
# mediapipe files
mkdir godot/modules/mediapipe/mediapipe
\cp -r MediapipeModule_library/mediapipe/mediapipe/* godot/modules/mediapipe/mediapipe/
# header file
\cp MediapipeModule_library/godot/gmod_core.h godot/modules/mediapipe/
# library 
mkdir godo/modules/mediapipe/libpath
\cp -r libraries/libgmod.so godot/modules/mediapipe/libpath/
chmod +w godot/modules/mediapipe/libpath/libgmod.so