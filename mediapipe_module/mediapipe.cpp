/* mediapipe.cpp */

#include "mediapipe.h"
#include "gmod_core.h"

void Mediapipe::sayhi() {
    hello();
}

void Mediapipe::tracking_start(String graph_name) {
    start(graph_name.ascii().get_data());
}

void Mediapipe::tracking_stop() {
    stop();
}

int Mediapipe::get_face_tracking_data() {
    double** tmp = return_face_trackers();
    // List<float> *E=tmp;
    // for(int i=0;E;E=E->next()) {
    //     print_line(E->get()); // print the element
    // }
    printf("%f", tmp[0][0]);
    int x = tmp[0][0]*100;
    return x;
}

void Mediapipe::_bind_methods() {
    ClassDB::bind_method(D_METHOD("sayhi"), &Mediapipe::sayhi);
    ClassDB::bind_method(D_METHOD("tracking_start", "graph_name"), &Mediapipe::tracking_start);
    ClassDB::bind_method(D_METHOD("tracking_stop"), &Mediapipe::tracking_stop);
    ClassDB::bind_method(D_METHOD("get_face_tracking_data"), &Mediapipe::get_face_tracking_data);
}

Mediapipe::Mediapipe() {
    x = 0;
}