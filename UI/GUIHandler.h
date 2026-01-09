#ifndef _GUI_HANDLER_H_
#define _GUI_HANDLER_H_

#include "LeftSideBar/LeftSideBar.h"
// #include "FpsBar/FpsBar.h"
// #include "TimeBar/TimeBar.h"

#include "UI.params.h"

class GUIHandler{
public:
    GUIHandler(const GUIHandler&) = delete;
    GUIHandler& operator=(const GUIHandler&) = delete;

    static GUIHandler* getInstance(){
        static GUIHandler gui_handler;
        return &gui_handler;
    }

    void init(){
        UIParams::getInstance()->setField("is_fullscreen", false);
        UIParams::getInstance()->setField("is_close_side_bar", false);
        UIParams::getInstance()->setField("is_close_fps_bar", false);
        UIParams::getInstance()->setField("is_close_time_bar", false);
        UIParams::getInstance()->setField("is_debug", false);

        _left_side_bar.init();
    }

    void draw(){
        const bool is_close_side_bar =
            std::any_cast<bool>(UIParams::getInstance()->getField("is_close_side_bar"));

        if(!is_close_side_bar){
            _left_side_bar.handle();
        }

        const bool is_close_fps_bar =
            std::any_cast<bool>(UIParams::getInstance()->getField("is_close_fps_bar"));

        if(!is_close_fps_bar){
            // _fps_bar.draw();
        }

        const bool is_close_time_bar =
            std::any_cast<bool>(UIParams::getInstance()->getField("is_close_time_bar"));

        if(!is_close_time_bar){
            // _time_bar.draw();
        }
    }
    
private:
    GUIHandler(){}
    ~GUIHandler(){}
private:
    LeftSideBar _left_side_bar;
    // FpsBar _fps_bar;
    // TimeBar _time_bar;
};

#endif // !_GUI_HANDLER_H_