#ifndef _RIGHT_SIDE_BAR_H_
#define _RIGHT_SIDE_BAR_H_

#include <raylib.h>
#include <vector>

#include "Block.h"
#include "UpdDataFuncs.h"

class RightSideBar{
public:
    void init(){
        pushBack("", 30, get_sim_time);
        pushBack("X", 25, get_time_scale);
        pushBackVoid(60);
        pushBack(" FPS", 20, get_fps);
    }

    void pushBackVoid(const float offset){
        const float font_size = offset;
        pushBack("", font_size, get_void);
    }

    void pushBack(std::string title, const float font_size, RightSideBarBlock::updDataFunc upd_data_func){
        const float base_ratio = static_cast<float>(font_size) / GetRenderHeight();
        const float ratio = ratio_counter - base_ratio;
        
        _blocks.push_back(
            RightSideBarBlock(
                ratio,
                font_size,
                title,
                upd_data_func
            )
        );
        
        ratio_counter -= base_ratio;
    }

    void handle(){
        for(auto& block: _blocks){
            block.draw();
        }
    }   

private:
    float ratio_counter = 0.95f;
    std::vector<RightSideBarBlock> _blocks;
};

#endif // !_RIGHT_SIDE_BAR_H_