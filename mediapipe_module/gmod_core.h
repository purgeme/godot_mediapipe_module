#pragma once

#if defined(_MSC_VER) // M$VS
    #define DLL_EXPORT __declspec(dllexport)
    #define DLL_IMPORT __declspec(dllimport)
#elif defined(__GNUC__) // GCC
    #define DLL_EXPORT __attribute__((visibility("default")))
    #define DLL_IMPORT
#else
    #define DLL_EXPORT
    #define DLL_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#if defined(UMP_EXPORTS)
	#define UMP_API DLL_EXPORT
#elif defined(UMP_IMPORTS)
	#define UMP_API DLL_IMPORT
#else
	#define UMP_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//C code goes here

double ** return_face_trackers();
double ** return_hand_right_trackers();
double ** return_hand_left_trackers();
double ** return_pose_trackers();

void toggle_face(bool x);
void toggle_hand_right(bool x);
void toggle_hand_left(bool x);
void toggle_pose(bool x);
void toggle_camera(bool x);
void toggle_detection(bool x);

int start(const char* filename);
void stop();

void hello();

#ifdef __cplusplus
} // extern "C"
#endif