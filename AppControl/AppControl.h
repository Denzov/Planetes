#ifndef _APP_CONTROL_H_
#define _APP_CONTROL_H_

#include <raylib.h>
#include <cmath>

#include "../AppParams/MainWindow/MWindowHandler.h"
#include "../AppParams/MainCamera2D/MCamera2DHandler.h"
#include "../Input/KeyboardHandle/KeyboardHandler.h"
#include "../Input/MouseHandle/MouseHanlder.h"
#include "../UI/GUIHandler.h"

class AppControl{
public:
    static void init(){
        MWindowHandler::getInstance()->init();
        MCamera2DHandler::getInstance()->init();

        GUIHandler::getInstance()->init();
    }

    static void inputHandle(){
        KeyboardHandler::getInstance()->handle();
        MouseHandler::getInstance()->handle();

        MWindowHandler::getInstance()->process();
        MCamera2DHandler::getInstance()->process();

        Mouse::handle();
    }

private:
    struct Mouse{
        static constexpr float sensitivity = 0.2f;

        enum Cmd{
            MOVE_SCREEN = MOUSE_BUTTON_LEFT
        };

        static void handle(){
            MCamera2DHandler::getInstance()->addCommand(
                MCExecutor::ImpactZoom{GetMouseWheelMove() * sensitivity}
            );

            if(IsMouseButtonDown(MOVE_SCREEN)){
                Vector2 dtarget = GetMouseDelta();

                MCamera2DHandler::getInstance()->addCommand(
                    MCExecutor::AddTarget{
                        .x = -dtarget.x,
                        .y = -dtarget.y
                    }
                );
            }
        }

        Mouse() = delete;
        ~Mouse() = delete;
    };
};

#endif // !_APP_CONTROL_H_