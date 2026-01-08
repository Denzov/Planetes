#ifndef _SIDE_BAR_TASKS_H_
#define _SIDE_BAR_TASKS_H_

#include <raylib.h>

#include "../../AppParams/MainWindow/MWindowHandler.h"
#include "../../Simulation/Planet/PlanetHolder.h"


#define PASTE(a,b) a##b
#define EXP_AND_PASTE(a,b) PASTE(a,b)

// Side bar task
#define TASK_NAME(NAME) PASTE(SB_TASK_, NAME) 

class ISideBarTask
{
public:
    virtual void exec() = 0;
};

#define SIDE_BAR_TASK_BEGIN(NAME) \
    class TASK_NAME(NAME) : public ISideBarTask { \
    public: \
        void exec() override {

#define SIDE_BAR_TASK_END } };

SIDE_BAR_TASK_BEGIN(NONE)
SIDE_BAR_TASK_END

SIDE_BAR_TASK_BEGIN(TOGGLE_FULLSCREEN)
    MWindowHandler::getInstance()->addCommand(
        MWExecutor::ToggleFullscreen{}
    );
SIDE_BAR_TASK_END

SIDE_BAR_TASK_BEGIN(EXIT)
    CloseWindow();
SIDE_BAR_TASK_END

SIDE_BAR_TASK_BEGIN(SPAWN_DEFAULT_WITHOUT_MASS)
SIDE_BAR_TASK_END

#endif // !_SIDE_BAR_TASKS_H_   