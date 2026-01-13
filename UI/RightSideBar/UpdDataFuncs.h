#ifndef _RIGHT_SIDE_BAR_UPD_DATA_FUNCS_H_
#define _RIGHT_SIDE_BAR_UPD_DATA_FUNCS_H_

#include <raylib.h>
#include <format>
#include <string>
#include <cmath>

#include <sstream>
#include <iomanip>

#include "Block.h"

inline std::string get_void(){
    return "";
}

inline std::string get_fps(){
    std::string fps = std::to_string(GetFPS());
    return fps;
}

inline std::string get_sim_time(){
    const double raw_time_s = PhysTimeHandler::getInstance()->getTime();

    const int time_ms = static_cast<int>((raw_time_s - std::floor(raw_time_s)) * 1000);
    const int time_h  = static_cast<int>( raw_time_s / 3600);
    const int time_m  = static_cast<int>((raw_time_s - time_h * 3600) / 60);
    const int time_s  = static_cast<int>( raw_time_s - time_h * 3600 - time_m * 60);

    const std::string out_time_format = std::format("{:02}:{:02}:{:02}.{:03}", time_h, time_m, time_s, time_ms);
    return out_time_format;
}

inline std::string get_time_scale(){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << (float)RealTimeHandler::getInstance()->getTimeScale();
    return oss.str();
}

#endif // !_RIGHT_SIDE_BAR_UPD_DATA_FUNCS_H_