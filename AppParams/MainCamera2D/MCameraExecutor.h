#ifndef _MCAMERA_EXECUTOR_H_
#define _MCAMERA_EXECUTOR_H_

#include <raylib.h>
#include <queue>
#include <variant>

namespace MCExecutor{
    struct SetTarget{
        const float x;
        const float y;
    };

    struct AddTarget{
        const float x;
        const float y;
    };

    struct SetOffset{
        const float x;
        const float y;
    };

    struct AddOffset{
        const float x;
        const float y;
    };

    struct SetRotation{
        const float rotation;
    };

    struct AddRotation{
        const float rotation;
    };
    
    struct SetZoom{
        const float zoom;
    };

    struct AddZoom{
        const float dzoom;
    }; 

    struct ImpactZoom{
        const float dzoom;
    };

};

struct MCameraExecutor{
    Camera2D& camera;

    void operator()(const MCExecutor::SetTarget& t){
        camera.target = {t.x, t.y};
    }

    void operator()(const MCExecutor::AddTarget& t){
        camera.target.x += t.x / camera.zoom;
        camera.target.y += t.y / camera.zoom;
    }

    void operator()(const MCExecutor::SetOffset& t){
        camera.offset = {t.x, t.y}; 
    }

    void operator()(const MCExecutor::AddOffset& t){
        camera.offset.x += t.x;
        camera.offset.y += t.y;
    }

    void operator()(const MCExecutor::SetRotation& t){
        camera.rotation = t.rotation;
    }

    void operator()(const MCExecutor::AddRotation& t){
        camera.rotation += t.rotation;
    }

    void operator()(const MCExecutor::SetZoom& t){
        camera.zoom = t.zoom;

    }

    void operator()(const MCExecutor::AddZoom& t){
        camera.zoom += t.dzoom;
    }

    void operator()(const MCExecutor::ImpactZoom& t){
        Vector2 screen_center = {
            GetRenderWidth() / 2.f, 
            GetRenderHeight() / 2.f
        };

        const Vector2 before = GetScreenToWorld2D(screen_center, camera);
        camera.zoom += camera.zoom * t.dzoom;
        const Vector2 after  = GetScreenToWorld2D(screen_center, camera);

        camera.target.x += before.x - after.x;
        camera.target.y += before.y - after.y;
    }
};

using CameraCommand = std::variant<
    MCExecutor::SetTarget,
    MCExecutor::AddTarget,
    MCExecutor::SetOffset,
    MCExecutor::AddOffset,
    MCExecutor::SetRotation,
    MCExecutor::AddRotation,
    MCExecutor::SetZoom,
    MCExecutor::AddZoom,
    MCExecutor::ImpactZoom
>;

inline void processCamera(Camera2D& cam, std::queue<CameraCommand>& cmds){
    if(cmds.empty()){
        return;
    }
    
    MCameraExecutor exec{cam};
    while (!cmds.empty()) {
        const CameraCommand cmd = std::move(cmds.front());
        std::visit(exec, cmd);
        cmds.pop();
    }
}
#endif // !_MCAMERA_EXECUTOR_H_