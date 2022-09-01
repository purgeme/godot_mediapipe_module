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

void Mediapipe::track_face(bool toggle){
    if(toggle){
        face_tracker = gmod->create_observer("face_landmarks");
        face_tracker->SetPresenceCallback([this](class IObserver* observer, bool present){
            face_present = present;
        });
        face_tracker->SetPacketCallback([this](class IObserver* observer){ 
            const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
            // size_t message_type = observer->GetMessageType();
            mx.lock();
            for ( int i=0; i < 468; ++i){
                const mediapipe::NormalizedLandmark& landmark = data->landmark(i);
                Vector3 y;
                y.x = landmark.x();
                y.y = landmark.y();
                y.z = landmark.z();
                face_tracking_data.set(i, y);
            }
            mx.unlock();
        });
    } else {
        face_tracker = nullptr;
    }
};

Vector3 Mediapipe::get_face_tracking_data(int indx){
    return face_tracking_data[indx];
}

bool Mediapipe::get_face_present(){
    return face_present;
};

void Mediapipe::track_right_hand(bool toggle){
    if(toggle){
        right_hand_tracker = gmod->create_observer("right_hand_landmarks");
        right_hand_tracker->SetPresenceCallback([this](class IObserver* observer, bool present){
            right_hand_present = present;
        });
        right_hand_tracker->SetPacketCallback([this](class IObserver* observer){ 
            const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
            // size_t message_type = observer->GetMessageType();
            mx.lock();
            for ( int i=0; i < 21; ++i){
                const mediapipe::NormalizedLandmark& landmark = data->landmark(i);
                Vector3 y;
                y.x = landmark.x();
                y.y = landmark.y();
                y.z = landmark.z();
                right_hand_tracking_data.set(i, y);
            }
            mx.unlock();
        });
    } else {
        right_hand_tracker = nullptr;
    }
};

Vector3 Mediapipe::get_right_hand_tracking_data(int indx){
    return right_hand_tracking_data[indx];
}

bool Mediapipe::get_right_hand_present(){
    return right_hand_present;
};

void Mediapipe::track_left_hand(bool toggle){
    if(toggle){
        left_hand_tracker = gmod->create_observer("left_hand_landmarks");
        left_hand_tracker->SetPresenceCallback([this](class IObserver* observer, bool present){
            left_hand_present = present;
        });
        left_hand_tracker->SetPacketCallback([this](class IObserver* observer){ 
            const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
            // size_t message_type = observer->GetMessageType();
            mx.lock();
            for ( int i=0; i < 21; ++i){
                const mediapipe::NormalizedLandmark& landmark = data->landmark(i);
                Vector3 y;
                y.x = landmark.x();
                y.y = landmark.y();
                y.z = landmark.z();
                left_hand_tracking_data.set(i, y);
            }
            mx.unlock();
        });
    } else {
        left_hand_tracker = nullptr;
    }
};

Vector3 Mediapipe::get_left_hand_tracking_data(int indx){
    return left_hand_tracking_data[indx];
}

bool Mediapipe::get_left_hand_present(){
    return left_hand_present;
};

void Mediapipe::track_pose(bool toggle){
    if(toggle){
        pose_tracker = gmod->create_observer("pose_landmarks");
        pose_tracker->SetPresenceCallback([this](class IObserver* observer, bool present){
            pose_present = present;
        });
        pose_tracker->SetPacketCallback([this](class IObserver* observer){ 
            const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
            // size_t message_type = observer->GetMessageType();
            mx.lock();
            for ( int i=0; i < 33; ++i){
                const mediapipe::NormalizedLandmark& landmark = data->landmark(i);
                Vector3 y;
                y.x = landmark.x();
                y.y = landmark.y();
                y.z = landmark.z();
                pose_tracking_data.set(i, y);
            }
            mx.unlock();
        });
    } else {
        pose_tracker = nullptr;
    }
};

Vector3 Mediapipe::get_pose_tracking_data(int indx){
    return pose_tracking_data[indx];
}

bool Mediapipe::get_pose_present(){
    return pose_present;
};

///////////////////////////////////////////////////////////

void Mediapipe::start(String filename){
    gmod->start(filename.ascii().get_data());
};

void Mediapipe::stop(){
    gmod->stop();
};

///////////////////////////////////////////////////////////

void Mediapipe::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_camera"), &Mediapipe::get_camera);
    ClassDB::bind_method(D_METHOD("set_camera", "bool"), &Mediapipe::set_camera);
    ClassDB::bind_method(D_METHOD("get_overlay"), &Mediapipe::get_overlay);
    ClassDB::bind_method(D_METHOD("set_overlay", "bool"), &Mediapipe::set_overlay);
    ClassDB::bind_method(D_METHOD("set_camera_props", "cam_id", "cam_resx", "cam_resy", "cam_fps"), &Mediapipe::set_camera_props);
    ClassDB::bind_method(D_METHOD("track_face", "bool"), &Mediapipe::track_face);
    ClassDB::bind_method(D_METHOD("get_face_tracking_data"), &Mediapipe::get_face_tracking_data);
    ClassDB::bind_method(D_METHOD("get_face_present"), &Mediapipe::get_face_present);
    ClassDB::bind_method(D_METHOD("track_right_hand", "bool"), &Mediapipe::track_right_hand);
    ClassDB::bind_method(D_METHOD("get_right_hand_tracking_data"), &Mediapipe::get_right_hand_tracking_data);
    ClassDB::bind_method(D_METHOD("get_right_hand_present"), &Mediapipe::get_right_hand_present);
    ClassDB::bind_method(D_METHOD("track_left_hand", "bool"), &Mediapipe::track_left_hand);
    ClassDB::bind_method(D_METHOD("get_left_hand_tracking_data"), &Mediapipe::get_left_hand_tracking_data);
    ClassDB::bind_method(D_METHOD("get_left_hand_present"), &Mediapipe::get_left_hand_present);
    ClassDB::bind_method(D_METHOD("track_pose", "bool"), &Mediapipe::track_pose);
    ClassDB::bind_method(D_METHOD("get_pose_tracking_data"), &Mediapipe::get_pose_tracking_data);
    ClassDB::bind_method(D_METHOD("get_pose_present"), &Mediapipe::get_pose_present);
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