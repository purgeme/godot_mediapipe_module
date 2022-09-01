# MediapipeModule_module

This is a module for Godot. It provides access to this mediapipe library inside godot as a module.
This provides different types of tracking/solutions from mediapipe inside godot.

`Currently the library does not have gpu support`

## Getting started:

### Step 1: setup.sh

Run `setup.sh`

Downloads the MediapipeModule_library repo, sets it up and builds the library.
Downloads Godot source code and sets it up with the module and the built library.

### Step 2: build.sh

Run `build.sh`

Builds the godot engine module.
The generated binary is in `godot/bin/`.

Before running the binary make sure to run:
`source envs`
to setup the environment variables so that the binary is able to find the library.

You can also move the library anywhere else and add the directory to the `LD_LIBRARY_PATH` environment variable.

Any exported projects built in godot would also require this library as well as mediapipe repo one directory above that of the executable.

( mediapipe repo is required to be one directory above to avoid importing it into godot )

## Using the module

To use the module, just create a godot project and add a script to a node.
All the methods are available under the Mediapipe class.

Sample code:
```
extends Node2D

var s = Mediapipe.new()

func _ready():
	s.set_camera_props(1, 640, 480, 30);
	s.set_camera(true) # Show camera output
	s.set_overlay(true) # Show overlay
	s.track_face(true) # Track face
	s.tracking_start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt") # The path to the graph file as string in brackets

func _process(delta):
	var x = s.get_face_tracking_data(0) # Get position of landmark with index 0
	print(x) # Print the data
	pass
```

Only the graph file `holistic_tracking_cpu.pbtxt` has been tested.
