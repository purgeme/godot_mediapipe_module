/* mediapipe.cpp */

#include "mediapipe.h"

///////////////////////////////////////////////////////////

bool Mediapipe::get_camera(){
    return gmod->get_camera();
};

void Mediapipe::set_camera(bool x){
    gmod->set_camera(x);
};

bool Mediapipe::get_overlay(){
    return gmod->get_overlay();
};

void Mediapipe::set_overlay(bool x){
    gmod->set_overlay(x);
};

void Mediapipe::set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps){
    gmod->set_camera_props(cam_id, cam_resx, cam_resy, cam_fps);
};

///////////////////////////////////////////////////////////

int Mediapipe::create_observer(String x){
    auto* observer = gmod->create_observer(x.ascii().get_data());
    observers.push_back(observer);
    return observers.size() - 1;
}

void Mediapipe::add_callbacks(){
    for(int i=0; i<observers.size(); i++){
        _presence.push_back(0);
        Array x;
        _data.push_back(x);
    }
    for (int i=0; i<observers.size(); i++){
        observers[i]->SetPresenceCallback([this, i](class IObserver* observer, bool present){
            _presence[i] = present;
        });
        observers[i]->SetPacketCallback([this, i](class IObserver* observer){
            const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData());
            Array current_array = std::ref(_data[i]);
            if (current_array.size() != data->landmark_size()){
                current_array.resize(data->landmark_size());
            }
            // size_t message_type = observer->GetMessageType();
            mx.lock();
            for ( int u=0; u < data->landmark_size(); ++u){
                const mediapipe::NormalizedLandmark& landmark = data->landmark(u);
                Vector3 y;
                y.x = landmark.x();
                y.y = landmark.y();
                y.z = landmark.z();
                current_array.set(u, y);
            }
            mx.unlock();
        });
    }
}

Array Mediapipe::get_data(int index){
    return _data[index];
}

///////////////////////////////////////////////////////////


void Mediapipe::start(String filename){
    gmod->start(filename.ascii().get_data());
};

void Mediapipe::stop(){
    gmod->stop();
};

///////////////////////////////////////////////////////////

void Mediapipe::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_camera_props", "cam_id", "cam_resx", "cam_resy", "cam_fps"), &Mediapipe::set_camera_props);

    ClassDB::bind_method(D_METHOD("get_camera"), &Mediapipe::get_camera);
    ClassDB::bind_method(D_METHOD("set_camera", "bool"), &Mediapipe::set_camera);

    ClassDB::bind_method(D_METHOD("get_overlay"), &Mediapipe::get_overlay);
    ClassDB::bind_method(D_METHOD("set_overlay", "bool"), &Mediapipe::set_overlay);

    ClassDB::bind_method(D_METHOD("create_observer", "observer name"), &Mediapipe::create_observer);
    ClassDB::bind_method(D_METHOD("set_callbacks"), &Mediapipe::set_callbacks);
    ClassDB::bind_method(D_METHOD("get_data"), &Mediapipe::get_data);

    ClassDB::bind_method(D_METHOD("start", "graph_file_name"), &Mediapipe::start);
    ClassDB::bind_method(D_METHOD("stop"), &Mediapipe::stop);
}

Mediapipe::Mediapipe() {
    gmod = CreateGMOD();
    face_tracking_data.resize(468);
    right_hand_tracking_data.resize(21);
    left_hand_tracking_data.resize(21);
    pose_tracking_data.resize(33);
}
