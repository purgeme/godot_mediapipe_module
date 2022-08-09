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

# Download protobuf 3.19.1
cd mediapipe_module/
wget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.zip
unzip protobuf-cpp-3.19.1.zip
cd ..

# Copy module files to modules directory
mkdir godot/modules/mediapipe
\cp -r mediapipe_module/* godot/modules/mediapipe/

# Copy required files to module
# mediapipe files
mkdir godot/modules/mediapipe/mediapipe
\cp -r MediapipeModule_library/mediapipe/mediapipe/* godot/modules/mediapipe/mediapipe/
# library 
mkdir godot/modules/mediapipe/libpath
\cp -r libraries/libgmod.so godot/modules/mediapipe/libpath/
chmod +w godot/modules/mediapipe/libpath/libgmod.so