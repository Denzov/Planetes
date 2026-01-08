#ifndef _MAIN_CAMERA_2D_HANDLER_H_
#define _MAIN_CAMERA_2D_HANDLER_H_

#include "MCameraExecutor.h"

class MCamera2DHandler{
public:
    static MCamera2DHandler* getInstance(){
        static MCamera2DHandler instance;
        return &instance;
    }

    void init(){
        _camera.offset = {GetRenderWidth() / 2.f, GetRenderHeight() / 2.f};
    }

    void addCommand(CameraCommand cmd){
        _commands.push(cmd);
    }

    void process(){
        processCamera(_camera, _commands);
    }

    Camera2D getData(){
        return _camera;
    }

    MCamera2DHandler(const MCamera2DHandler&) = delete;
    MCamera2DHandler& operator=(const MCamera2DHandler&) = delete;
private:
    MCamera2DHandler(){}
    ~MCamera2DHandler(){}

private:
    Camera2D _camera{
        .offset = {0.f, 0.f},
        .target = {0.f, 0.f},
        .rotation = 0.f,
        .zoom = 1.f
    };

    std::queue<CameraCommand> _commands;
};

#endif // !_MAIN_CAMERA_2D_HANDLER_H_