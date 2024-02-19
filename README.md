# Status
Though I have been working on this project on my machine, porting it to gdextensions and adding new features, development on the library has been halted for now, same goes for this repo as well. Reasons given in the mediapipe_cpp_lib repo.

---

# MediapipeModule_module

This is a module for Godot. It provides access to this mediapipe library inside godot as a module.
This provides different types of tracking/solutions from mediapipe inside godot.

The way things are set up, it can run other graphs but only output stream of `mediapipe::NormalizedLandmarkList` type is supported for now.
Support for more data types such as Images is coming...

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
	s.create_observer("face_landmarks") # Create observer to track face, we also pass the data type for this stream name
	# The data type is that which is used in the graph for this stream.
	s.create_observer("pose_landmarks") # Create observer to track pose
	s.tracking_start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt") # The path to the graph file as string in brackets

func _process(delta):
	# Get data at 0, face was first so index 0
	var face = s.get_data(0) # get_data returns an array of tracked landmarks
	# Get data at 1, pose was second so index 1
 	var pose = s.get_data(1)
	# Similarly for more observers added, the index will be incremented
	
	print(face) # Print the data
```

## TODO:

- [ ] Faster way to compare data type in callback
- [ ] Add images to available data types
