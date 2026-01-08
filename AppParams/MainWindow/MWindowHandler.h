#ifndef _MAIN_WINDOW_HANDLER_H_
#define _MAIN_WINDOW_HANDLER_H_

#include <string>
#include "MWindowExecutor.h"

class MWindowHandler{
public:
    struct Data {
        std::string title = "Planetes";
        int width = 1000;
        int height = 1000;
        int fps = 60;
    };

    static MWindowHandler* getInstance(){
        static MWindowHandler instance;
        return &instance;
    }

    void init(){
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(data.width, data.height, data.title.c_str());
        SetTargetFPS(data.fps);
    }

    void addCommand(MWindowCommand cmd){
        _commands.push(cmd);
    }

    // only for mainthread use 
    void process(){
        processMWindow(_commands);
    }

    MWindowHandler::Data getData(){
        return data;
    }

    MWindowHandler(const MWindowHandler&) = delete;
    MWindowHandler& operator=(const MWindowHandler&) = delete;

private:
    MWindowHandler(){}
    ~MWindowHandler(){}

private:
    Data data;

    std::string _title;
    std::queue<MWindowCommand> _commands;
};

#endif // !_MAIN_WINDOW_HANDLER_H_