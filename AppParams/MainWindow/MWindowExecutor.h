#ifndef _MAIN_WINDOW_EXECUTOR_H_
#define _MAIN_WINDOW_EXECUTOR_H_

#include <raylib.h>
#include <variant>
#include <queue>

#include "../../AppParams/MainCamera2D/MCamera2DHandler.h"

namespace MWExecutor{
    struct SetWidth{ int width; };
    struct SetHeight{ int height; };
    struct SetFps{ int fps; };
    struct SetFullscreen{ bool fullscreen; };
    struct ToggleFullscreen{};
};

struct MWindowExecutor{
    void operator()(const MWExecutor::SetWidth& w){
        SetWindowSize(w.width, GetRenderHeight());
    }

    void operator()(const MWExecutor::SetHeight& h){
        SetWindowSize(GetRenderWidth(), h.height);
    }

    void operator()(const MWExecutor::SetFps& fps){
        SetTargetFPS(fps.fps);
    }

    void operator()(const MWExecutor::SetFullscreen& fs){
        if(fs.fullscreen == IsWindowFullscreen()) return;
            
        int monitor_id = GetCurrentMonitor();
        float monitor_width = GetMonitorWidth(monitor_id);
        float monitor_height = GetMonitorHeight(monitor_id);

        ToggleFullscreen();

        if(IsWindowFullscreen()){
            MCamera2DHandler::getInstance()->addCommand(
                MCExecutor::SetOffset{
                    .x = monitor_width / 2.f, 
                    .y = monitor_height / 2.f
                }
            );
        }
        else{
            MCamera2DHandler::getInstance()->addCommand(
                MCExecutor::SetOffset{
                    .x = GetScreenWidth() / 2.f, 
                    .y = GetScreenHeight() / 2.f
                }
            );
        }
    }

    void operator()(const MWExecutor::ToggleFullscreen&){
        int monitor_id = GetCurrentMonitor();
        float monitor_width = GetMonitorWidth(monitor_id);
        float monitor_height = GetMonitorHeight(monitor_id);

        ToggleFullscreen();

        if(IsWindowFullscreen()){
            MCamera2DHandler::getInstance()->addCommand(
                MCExecutor::SetOffset{
                    .x = monitor_width / 2.f, 
                    .y = monitor_height / 2.f
                }
            );
        }
        else{
            MCamera2DHandler::getInstance()->addCommand(
                MCExecutor::SetOffset{
                    .x = GetScreenWidth() / 2.f, 
                    .y = GetScreenHeight() / 2.f
                }
            );
        }
    }
};

using MWindowCommand = std::variant<
    MWExecutor::SetWidth,
    MWExecutor::SetHeight,
    MWExecutor::SetFps,
    MWExecutor::SetFullscreen,
    MWExecutor::ToggleFullscreen
>;

inline void processMWindow(std::queue<MWindowCommand>& cmds){
    if(cmds.empty()){
        return;
    }

    while (!cmds.empty()) {
        const MWindowCommand cmd = std::move(cmds.front());
        MWindowExecutor exec;
        
        std::visit(exec, cmd);
        cmds.pop();
    }
}

#endif // !_MAIN_WINDOW_EXECUTOR_H_