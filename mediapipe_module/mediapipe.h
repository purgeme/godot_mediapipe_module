/* mediapipe.h */

#ifndef MEDIAPIPE_H
#define MEDIAPIPE_H

#include "core/reference.h"
#include <string>
#include <vector>
#include <list>
#include "gmod_api.h"
#include "mediapipe/framework/formats/landmark.pb.h"

class Mediapipe : public Reference {
    GDCLASS(Mediapipe, Reference);

    IGMOD* gmod;

    struct mob {
        IObserver* observer;
        String type;
    };

    std::vector<struct mob> observers = {};
    Array _presence;
    Array _data;

    std::mutex mx;

protected:
    static void _bind_methods();


    void set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps);

    bool get_camera();
    void set_camera(bool x);

    bool get_overlay();
    void set_overlay(bool x);

    int create_observer(String name, String type);
    void add_callbacks();
    Array get_data(int index);

    void start(String filename);
    void stop();

public:

    Mediapipe();
};

#endif // MEDIAPIPE_H
