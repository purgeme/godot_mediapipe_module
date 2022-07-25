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

void Mediapipe::toggle_part(bool x, String part){
    if(part=="face"){
        toggle_face(x);
    }
    if(part=="hand_right"){
        toggle_hand_right(x);
    }
    if(part=="hand_left"){
        toggle_hand_left(x);
    }
    if(part=="pose"){
        toggle_pose(x);
    }
    if(part=="camera"){
        toggle_camera(x);
    }
    if(part=="detection"){
        toggle_detection(x);
    }
}

Array Mediapipe::get_face_tracking_data() {
    // double** tmp = return_face_trackers();
    // // List<float> *E=tmp;
    // // for(int i=0;E;E=E->next()) {
    // //     print_line(E->get()); // print the element
    // // }
    // printf("%f", tmp[0][0]);
    // int x = tmp[0][0]*100;
    // return x;
    double** tmp = return_face_trackers();
    Array x;
    for(int i=0; i<468; i++){
        Array y;
        y.push_back(tmp[i][0]);
        y.push_back(tmp[i][1]);
        y.push_back(tmp[i][2]);
        x.push_back(y);
    }
    return x;
}

void Mediapipe::_bind_methods() {
    ClassDB::bind_method(D_METHOD("toggle_part", "bool", "part_name"), &Mediapipe::toggle_part);
    ClassDB::bind_method(D_METHOD("get_face_tracking_data"), &Mediapipe::get_face_tracking_data);
    ClassDB::bind_method(D_METHOD("tracking_start", "graph_name"), &Mediapipe::tracking_start);
    ClassDB::bind_method(D_METHOD("tracking_stop"), &Mediapipe::tracking_stop);
    ClassDB::bind_method(D_METHOD("sayhi"), &Mediapipe::sayhi);
}

Mediapipe::Mediapipe() {
    x = 0;
}