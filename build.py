#!/usr/bin/python
from dbm.ndbm import library
import os
import sys
import shutil
import subprocess

current_dir = os.path.dirname(__file__)
godot_dir = os.path.join(current_dir, "godot")

os.chdir(godot_dir)
os.system("scons -j"+str(os.cpu_count())+" platform=x11")