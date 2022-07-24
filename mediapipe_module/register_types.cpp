/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "mediapipe.h"

void register_mediapipe_types() {
    ClassDB::register_class<Mediapipe>();
}

void unregister_mediapipe_types() {
}