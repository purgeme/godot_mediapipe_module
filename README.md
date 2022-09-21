# MediapipeModule_module

This is a module for Godot. It provides access to this mediapipe library inside godot as a module.
This provides different types of tracking/solutions from mediapipe inside godot.

The way things are set up, it can run other graphs but expects output stream of `NormalizedLandmarkList` type.
Only the graph file `holistic_tracking_cpu.pbtxt` has been tested and works for now. The observer names are the output streams in the graph.
The supported observer names for holistic tracking:
- "face_landmarks" -> Get face tracking data
- "right_hand_landmarks" -> Get right hand tracking data
- "left_hand_landmarks" -> Get left hand tracking data
- "pose_landmarks" -> Get pose tracking data

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
	s.create_observer("face_landmarks", "NormalizedLandmarkList") # Create observer to track face, we also pass the data type for this stream name
	# The data type is that which is used in the graph for this stream.
	s.create_observer("pose_landmarks", "NormalizedLandmarkList") # Create observer to track pose
	s.add_callbacks() # Add callbacks for all observers
	s.tracking_start("mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt") # The path to the graph file as string in brackets

func _process(delta):
	# Get data at 0, face was first so index 0
	var face = s.get_data(0) # get_data returns an array of tracked landmarks
	# Get data at 1, pose was second so index 1
 	var pose = s.get_data(1)
	# Similarly for more observers added, the index will be incremented
	
	print(face) # Print the data
```

