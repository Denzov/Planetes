#ifndef _LEFT_SIDE_BAR_TASKS_H_
#define _LEFT_SIDE_BAR_TASKS_H_

#include <raylib.h>

#include "../../AppParams/MainWindow/MWindowHandler.h"
#include "../../Simulation/Planet/PlanetHolder.h"


#define PASTE(a,b) a##b
#define EXP_AND_PASTE(a,b) PASTE(a,b)

// Side bar task
#define TASK_NAME(NAME) PASTE(SB_TASK_, NAME) 

class ILeftSideBarTask
{
public:
    virtual void exec() = 0;
};

#define LEFT_SIDE_BAR_TASK_BEGIN(NAME) \
    class TASK_NAME(NAME) : public ILeftSideBarTask { \
    public: \
        void exec() override {

#define LEFT_SIDE_BAR_TASK_END } };

LEFT_SIDE_BAR_TASK_BEGIN(NONE)
LEFT_SIDE_BAR_TASK_END

LEFT_SIDE_BAR_TASK_BEGIN(TOGGLE_FULLSCREEN)
    MWindowHandler::getInstance()->addCommand(
        MWExecutor::ToggleFullscreen{}
    );
LEFT_SIDE_BAR_TASK_END

LEFT_SIDE_BAR_TASK_BEGIN(EXIT)
    CloseWindow();
LEFT_SIDE_BAR_TASK_END

LEFT_SIDE_BAR_TASK_BEGIN(SPAWN_DEFAULT_WITHOUT_MASS)
LEFT_SIDE_BAR_TASK_END

#endif // !_LEFT_SIDE_BAR_TASKS_H_   