#ifndef _MAIN_WINDOW_HANDLER_H_
#define _MAIN_WINDOW_HANDLER_H_

#include <string>
#include "MWindowExecutor.h"

class MWindowHandler{
public:
    struct DefaultData {
        static constexpr std::string title = "Planetes";
        static constexpr int width = 1000;
        static constexpr int height = 1000;
        static constexpr int fps = 60;
    };

    static MWindowHandler* getInstance(){
        static MWindowHandler instance;
        return &instance;
    }

    void init(){
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(DefaultData::width, DefaultData::height, DefaultData::title.c_str());
        SetTargetFPS(DefaultData::fps);
    }

    void addCommand(MWindowCommand cmd){
        _commands.push(cmd);
    }

    // only for mainthread use 
    void process(){
        processMWindow(_commands);
    }

    MWindowHandler(const MWindowHandler&) = delete;
    MWindowHandler& operator=(const MWindowHandler&) = delete;

private:
    MWindowHandler(){}
    ~MWindowHandler(){}

private:
    std::string _title;
    std::queue<MWindowCommand> _commands;
};

#endif // !_MAIN_WINDOW_HANDLER_H_