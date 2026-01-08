#ifndef _GUI_HANDLER_H_
#define _GUI_HANDLER_H_

#include "SideBar/SideBar.h"
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
        UIParams::getInstance()->setField("is_debug", false);

        _side_bar.init();
    }

    void draw(){
        if(!std::any_cast<bool>(UIParams::getInstance()->getField("is_close_side_bar"))){
            _side_bar.handle();
        }
    }
    
private:
    GUIHandler(){}
    ~GUIHandler(){}
private:
    SideBar _side_bar;
};

#endif // !_GUI_HANDLER_H_