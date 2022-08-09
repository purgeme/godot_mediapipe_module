/* mediapipe.h */

#ifndef MEDIAPIPE_H
#define MEDIAPIPE_H

#include "core/reference.h"
#include <string>
#include <vector>
#include "gmod_api.h"
#include "mediapipe/framework/formats/landmark.pb.h"

class Mediapipe : public Reference {
    GDCLASS(Mediapipe, Reference);

    IGMOD* gmod;

    IObserver* face_tracker;
    Array face_tracking_data;
    IObserver* right_hand_tracker;
    Array right_hand_tracking_data;
    IObserver* left_hand_tracker;
    Array left_hand_tracking_data;
    IObserver* pose_tracker;
    Array pose_tracking_data;

    std::mutex mx;

    std::vector<class IObserver*> observers = {};

protected:
    static void _bind_methods();

    bool get_camera();
    void set_camera(bool x);
    bool get_overlay();
    void set_overlay(bool x);
    void set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps);
    void track_face(bool toggle);
    void track_right_hand(bool toggle);
    void track_left_hand(bool toggle);
    void track_pose(bool toggle);
    Vector3 get_face_tracking_data(int indx);
    Vector3 get_right_hand_tracking_data(int indx);
    Vector3 get_left_hand_tracking_data(int indx);
    Vector3 get_pose_tracking_data(int indx);
    void start(String filename);
    void stop();

public:

    Mediapipe();
};

#endif // MEDIAPIPE_H