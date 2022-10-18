#pragma once
#include<string>
#include<functional>

class IObserver
{
    public:
        virtual void SetPresenceCallback(std::function<void(class IObserver*, bool)> in_presence_callback)=0;
        virtual void SetPacketCallback(std::function<void(class IObserver*)> in_packet_callback)=0;
        virtual std::string GetMessageType()=0;
        virtual const void* const GetData()=0;
};

class IGMOD
{
    public:
        virtual bool get_camera() = 0;
        virtual void set_camera(bool x) = 0;
        virtual bool get_overlay() = 0;
        virtual void set_overlay(bool x) = 0;

        virtual void set_camera_props(int cam_id, int cam_resx, int cam_resy, int cam_fps) = 0;

        virtual IObserver* create_observer(const char* stream_name) = 0;

        virtual bool is_loaded() = 0;

        virtual void start(const char* filename) = 0;
        virtual void stop() = 0;
};

IGMOD* CreateGMOD();