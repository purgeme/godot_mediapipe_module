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

int Mediapipe::create_observer(String name, String type){
    auto* observer = gmod->create_observer(name.ascii().get_data());
    mob tmp;
    tmp.observer = observer;
    tmp.type = type;
    observers.push_back(tmp);
    return observers.size() - 1;
}

void Mediapipe::add_callbacks(){
    std::cout << "1" << std::endl;
    std::cout << "observers: " << observers.size() << std::endl;
    _data.resize(observers.size());
    _presence.resize(observers.size());

    for (int i=0; i<observers.size(); i++){
        std::cout << "2" << std::endl;
        if(observers[i].type == "NormalizedLandmarkList"){
            observers[i].observer->SetPresenceCallback([this, i](class IObserver* observer, bool present){
                std::cout << "3" << std::endl;
                _presence.set(i, present);
            });
            observers[i].observer->SetPacketCallback([this, i](class IObserver* observer){
                const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData());
                int size = (int)data->landmark_size();
                Array current_array;
                current_array.resize(size);
                // size_t message_type = observer->GetMessageType();
                std::cout << "4" << std::endl;
                mx.lock();
                for ( int u=0; u < size; ++u){
                    const mediapipe::NormalizedLandmark& landmark = data->landmark(u);
                    Vector3 y;
                    y.x = landmark.x();
                    y.y = landmark.y();
                    y.z = landmark.z();
                    current_array.set(u, y);
                }
                _data.set(i, current_array);
                mx.unlock();
            });
        }
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
    ClassDB::bind_method(D_METHOD("add_callbacks"), &Mediapipe::add_callbacks);
    ClassDB::bind_method(D_METHOD("get_data", "index"), &Mediapipe::get_data);

    ClassDB::bind_method(D_METHOD("start", "graph_file_name"), &Mediapipe::start);
    ClassDB::bind_method(D_METHOD("stop"), &Mediapipe::stop);
}

Mediapipe::Mediapipe() {
    gmod = CreateGMOD();
}
