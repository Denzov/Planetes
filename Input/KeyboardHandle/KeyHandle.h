#ifndef _KEY_HANDLE_H_
#define _KEY_HANDLE_H_

#include <raylib.h>
#include <iostream>

#include "IKeyHandle.h"

#include "../../AppParams/MainCamera2D/MCamera2DHandler.h"
#include "../../AppParams/MainWindow/MWindowHandler.h"

#include "../../UI/UI.params.h"

#define PASTE(a,b) a##b
#define EXP_AND_PASTE(a,b) PASTE(a,b)

#define HANDLE_KEY_NAME(a) PASTE(HKey_, a)
#define RBKEY_NAME(a) PASTE(KEY_, a)

#define HANDLE_KEY_BEGIN(KEY_NAME) \
    class HANDLE_KEY_NAME(KEY_NAME): public IKeyHandle{ \
        void handle() override { 

#define HANDLE_KEY_END } };

constexpr float CAMERA_SPEED = 7.5;

HANDLE_KEY_BEGIN(A)
    if(IsKeyDown(RBKEY_NAME(A))){

        const Vector2 speed = { -CAMERA_SPEED, 0.f };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(W)
    if(IsKeyDown(RBKEY_NAME(W))){
        const Vector2 speed = { 0.f, -CAMERA_SPEED };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(S)
    if(IsKeyDown(RBKEY_NAME(S))){
        const Vector2 speed = { 0.f, CAMERA_SPEED };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(D)
    if(IsKeyDown(RBKEY_NAME(D))){
        const Vector2 speed = { CAMERA_SPEED, 0.f };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(LEFT)
    if(IsKeyDown(RBKEY_NAME(LEFT))){
        const Vector2 speed = { -CAMERA_SPEED, 0.f };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(UP)
    if(IsKeyDown(RBKEY_NAME(UP))){
        const Vector2 speed = { 0.f, -CAMERA_SPEED };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(DOWN)
    if(IsKeyDown(RBKEY_NAME(DOWN))){
        const Vector2 speed = { 0.f, CAMERA_SPEED };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(RIGHT)
    if(IsKeyDown(RBKEY_NAME(RIGHT))){
        const Vector2 speed = { CAMERA_SPEED, 0.f };

        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::AddTarget{.x = speed.x, .y = speed.y}
        );
    }
HANDLE_KEY_END  

HANDLE_KEY_BEGIN(EQUAL)
    if(IsKeyDown(RBKEY_NAME(EQUAL))){
        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::ImpactZoom(0.05f)
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(MINUS)
    if(IsKeyDown(RBKEY_NAME(MINUS))){
        MCamera2DHandler::getInstance()->addCommand(
            MCExecutor::ImpactZoom(-0.05f)
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(F11)
    if(IsKeyPressed(RBKEY_NAME(F11))){
        bool fullscreen = std::any_cast<bool>(UIParams::getInstance()->getField("is_fullscreen"));
        UIParams::getInstance()->setField("is_fullscreen", !fullscreen);

        MWindowHandler::getInstance()->addCommand(
            MWExecutor::ToggleFullscreen{}
        );
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(TAB)
    if(IsKeyPressed(RBKEY_NAME(TAB))){
        bool is_close_side_bar = std::any_cast<bool>(UIParams::getInstance()->getField("is_close_side_bar"));
        UIParams::getInstance()->setField("is_close_side_bar", !is_close_side_bar);
    }
HANDLE_KEY_END

HANDLE_KEY_BEGIN(F)
    if(IsKeyPressed(RBKEY_NAME(F))){
        bool is_fullscreen = std::any_cast<bool>(UIParams::getInstance()->getField("is_fullscreen"));
        UIParams::getInstance()->setField("is_fullscreen", !is_fullscreen);

        MWindowHandler::getInstance()->addCommand(
            MWExecutor::ToggleFullscreen{}
        );
    }
HANDLE_KEY_END

#endif // !_KEY_HANDLE_H_