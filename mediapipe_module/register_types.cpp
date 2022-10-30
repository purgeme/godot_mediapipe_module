/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "mediapipe_module.h"

void register_mediapipe_module_types() {
    ClassDB::register_class<Mediapipe>();
}

void unregister_mediapipe_module_types() {
}