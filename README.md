# MediapipeModule_module

This project is a module for Godot game engine. It provides different types of tracking using mediapipe project from google.
Currently this project has only been made to work on linux.

## Setting up and building the module

### setup.sh:

Downloads the MediapipeModule_library repo, sets it up and builds the library.
Downloads Godot source code and sets it up with the module and the built library.

### build.sh:

Builds the godot engine module.
The generated binary is in `godot/bin/`.
Before running the binary make sure to run:
`source envs`
to setup the environment variables so that the binary is able to find the library.

You can also move the library anywhere else and add the directory to the `LD_LIBRARY_PATH` variable.

## Using the module

To use the module, just create a godot project and add a script to a node.
All the methods are available under the Mediapipe class.

Sample code:
```
extends Node2D

var s = Mediapipe.new()
var thread

func _ready():

	thread = Thread.new()
	thread.start(self, "_thread_function")

func _thread_function(userdata):
	s.sayhi()
	s.tracking_start("/home/test/Projects/MediapipeModule_module/MediapipeModule_library/mediapipe/mediapipe/graphs/holistic_tracking/holistic_tracking_cpu.pbtxt") # The path to the graph file as string in brackets

func _process(delta):
	var x = s.get_face_tracking_data()
	pass

func _exit_tree():
	thread.wait_to_finish()
```

It is important to use multiple threads as the mediapipe library uses a while loop and since by defaul everything is run on single thread, it freezes the game and essentially makes it unusable. To avoid freezing we run the tracking_start() method on a new thread but the data can be accessed on the main thread with methods like get_face_tracking_data().

## Issues:

For now the tracking works and the module can get the data, but there are no methods to access that data inside godot. Once these methods are put in place, I will also create the documentation.

The path for the graph file is also hard coded inside the module.