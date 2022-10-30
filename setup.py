#!/usr/bin/python

from genericpath import isdir
import os
import subprocess
import sys
import shutil
import requests
from zipfile import ZipFile

current_dir = os.path.dirname(__file__)
mediapipe_module_dir = os.path.join(current_dir, "mediapipe_module")

mediapipe_cpp_lib = os.path.join(current_dir, "mediapipe_cpp_lib")

library_src = os.path.join(mediapipe_cpp_lib, "library/libgmod.so")
library_dst = os.path.join(mediapipe_module_dir, "libpath/libgmod.so")

mediapipe_models_src = os.path.join(mediapipe_cpp_lib, "mediapipe_models")
mediapipe_models_dst = os.path.join(current_dir, "mediapipe_models")

mediapipe_graphs_src = os.path.join(mediapipe_cpp_lib, "mediapipe_graphs")
mediapipe_graphs_dst = os.path.join(current_dir, "mediapipe_graphs")

import_files_src = os.path.join(mediapipe_cpp_lib, "import_files")
import_files_dst = os.path.join(mediapipe_module_dir, "mediapipe")

# protobuf_dst = os.path.join(mediapipe_module_dir, "protobuf-3.19.1")
protobuf_dst = mediapipe_module_dir

godot_dir = os.path.join(current_dir, "godot")
module_files_src = mediapipe_module_dir
module_files_dst = os.path.join(godot_dir, "modules/mediapipe_module")

def copy2dir( src, dst ):
    if os.path.isdir(dst):
        inp = input ("Destination already exists, do you wish to replace it ? [N/y]: ")
        if inp == "y" or inp == "Y":
            shutil.rmtree(dst)
            shutil.copytree(src, dst)
            return
        else:
            return
    else:
        shutil.copytree(src, dst)

os.chdir(mediapipe_cpp_lib)

print("##########")
print("Setting up cpp library...")
subprocess.run(mediapipe_cpp_lib+"/setup.py")
print("Cpp library setup!")
print("##########")

print("\n##########")
print("Building cpp library...")
subprocess.run(mediapipe_cpp_lib+"/build.py")
print("Cpp library setup!")
print("##########")

print("\n##########")
print("Downloading mediapipe models...")
subprocess.run(os.path.join(mediapipe_cpp_lib, "download_models.py"))
print("Models Downloaded!")
print("##########")

print("\n##########")
print("Extracting mediapipe graphs...")
subprocess.run(os.path.join(mediapipe_cpp_lib, "extract_graphs.py"))
print("Graphs extracted!")
print("##########")

os.chdir(current_dir)

print("\n##########")
print("Copying library...")
os.chdir(mediapipe_module_dir)
if os.path.isdir("libpath") == False:
    os.mkdir("libpath")
os.chdir(current_dir)
shutil.copyfile(library_src, library_dst)
print("Library copied!")
print("##########")

print("\n##########")
print("Copying mediapipe models...")
copy2dir(mediapipe_models_src, mediapipe_models_dst)
print("Models copied!")
print("##########")

print("\n##########")
print("Copying mediapipe graphs...")
copy2dir(mediapipe_graphs_src, mediapipe_graphs_dst)
print("Graphs copied!")
print("##########")

print("\n##########")
print("Copying import files...")
copy2dir(import_files_src, import_files_dst)
print("Import files copied!")
print("##########")

print("\n##########")
print("Downloading protobuf...")
if os.path.isfile(os.path.join(current_dir, "protobuf-cpp-3.19.1.zip")):
    print("Protobuf is already downloaded!")
else:
    response = requests.get("https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.zip")
    file = open("protobuf-cpp-3.19.1.zip", "wb")
    file.write(response.content)
    file.close()
if os.path.isdir(os.path.join(protobuf_dst, "protobuf-cpp-3.19.1")):
    print("Protobuf is already extracted!")
else:
    print("Extracting protobuf...")
    with ZipFile("protobuf-cpp-3.19.1.zip", 'r') as zip:
        print("Extracting to: " + protobuf_dst)
        zip.extractall(protobuf_dst)
print("Protobuf placed!")
print("##########")

print("\n##########")
print("Copying module files...")
copy2dir(module_files_src, module_files_dst)
print("Module files copied!")
print("##########")