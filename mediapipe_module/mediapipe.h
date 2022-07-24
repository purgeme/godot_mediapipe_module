/* mediapipe.h */

#ifndef MEDIAPIPE_H
#define MEDIAPIPE_H

#include "core/reference.h"
#include <string>

class Mediapipe : public Reference {
    GDCLASS(Mediapipe, Reference);

    int x;

protected:
    static void _bind_methods();

public:
    void sayhi();
    void tracking_start(String graph_name);
    void tracking_stop();
    int get_face_tracking_data();
    Mediapipe();
};

#endif // MEDIAPIPE_H