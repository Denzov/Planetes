#ifndef _LEFT_SIDE_BAR_H_
#define _LEFT_SIDE_BAR_H_

#include <raylib.h>
#include <string>

#include "Block.h"
#include "../../AppParams/MainCamera2D/MCamera2DHandler.h"
#include "../UI.params.h"

class LeftSideBar{
public:
    void init(){
        pushOnNextPlace("EXIT", std::make_unique<SB_TASK_EXIT>());
        pushOnNextPlace("TOGGLE\nFS", std::make_unique<SB_TASK_TOGGLE_FULLSCREEN>());
        pushOnNextPlace("SPAWN\nPLANET", std::make_unique<SB_TASK_NONE>());
    }

    void pushOnNextPlace(
        std::string title, 
        std::unique_ptr<ILeftSideBarTask> task){

        const Vector2 pos = {
            .x = _side_bar_pos.x,
            .y = _side_bar_pos.y + _block_section_height * _blocks.size()
        };

        _blocks.push_back(
            LeftSideBarBlock(
                pos,
                {_side_bar_width, _block_section_height},
                title,
                std::move(task)
            )
        );
    }

    void handle(){
        _update_blocks();
        _draw_blocks();
    }

    void setPosition(Vector2 pos){
        _side_bar_pos = pos;
    }

    void addPosition(Vector2 pos){
        _side_bar_pos.x += pos.x;
        _side_bar_pos.y += pos.y;
    }

private:
    void _update_blocks(){
        for(auto& block: _blocks){
            block.handle();
        }
    }


    void _draw_blocks(){
        for(auto& block: _blocks){
            block.draw();
        }
    }

private:
    static constexpr int _target_font_size = 25;

    static constexpr float _side_bar_width = 150.f;
    static constexpr float _block_section_height = 75.f;

    Vector2 _side_bar_pos {.x = 0.f, .y = 10.f};

    
    std::vector<LeftSideBarBlock> _blocks;
};

#endif // !_LEFT_SIDE_BAR_H_