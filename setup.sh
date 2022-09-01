#!/bin/bash

# Build mediapipe library
###################################
git clone https://github.com/purgeme/MediapipeModule_library.git
cd MediapipeModule_library
# Setup MediapipeModule_library
./setup.sh
# Build library
./build.sh
# Download model files
./download_models.sh
# Download graph files
./extract_graphs.sh
###################################

# Move/Copy files into locations
###################################
# Copy libary file
mkdir ../library
cp library/libgmod.so ../library/
# Copy model files
mv mediapipe_models ../mediapipe_models
# Copy graph files
mv mediapipe_graphs ../mediapipe_graphs
# Copy import files
mv import_files ../import_files
# Copy import files
mv import_files/mediapipe ../mediapipe_module/mediapipe
cd ..
cd mediapipe_module/
mkdir libpath
\cp -r ../library/libgmod.so libpath/libgmod.so
chmod +w godot/modules/mediapipe/libpath/libgmod.so
# Download protobuf 3.19.1
wget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.zip
unzip protobuf-cpp-3.19.1.zip
cd ..
###################################

# Download godot source code
git clone https://github.com/godotengine/godot.git -b 3.4
# Copy module files to modules directory
mkdir godot/modules/mediapipe
\cp -r mediapipe_module/* godot/modules/mediapipe/
