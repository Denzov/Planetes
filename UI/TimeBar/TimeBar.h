#ifndef _TIME_BAR_H_
#define _TIME_BAR_H_

#include <raylib.h>
#include <string>
#include <format>

#include "../../Simulation/TimeHandler/TimeHandler.h"

class TimeBar{
public:
    void draw(){
        const float sim_time = PhysTimeHandler::getInstance()->getTime();
        const float time_scale = RealTimeHandler::getInstance()->getTimeScale();

        const std::string sim_time_s = std::format("{:.2f}", sim_time);
        const std::string time_scale_s = std::format("{:.2f}", time_scale);

        
    }

private:
    static constexpr float _text_sim_y_ratio = 0.9f;
    static constexpr Color _text_color = {255, 255, 255, 255};
    static constexpr int _font_size = 20;
};

#endif // !_TIME_BAR_H_