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
    void toggle_part(bool x, String part);

    Array get_face_tracking_data();

    void tracking_start(String graph_name);
    void tracking_stop();

    void sayhi();

    Mediapipe();
};

#endif // MEDIAPIPE_H