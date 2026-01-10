#ifndef _RIGHT_SIDE_BAR_UPD_DATA_FUNCS_H_
#define _RIGHT_SIDE_BAR_UPD_DATA_FUNCS_H_

#include <raylib.h>
#include <format>
#include <string>

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
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << (float)PhysTimeHandler::getInstance()->getTime();
    return oss.str();
}

inline std::string get_time_scale(){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << (float)RealTimeHandler::getInstance()->getTimeScale();
    return oss.str();
}

#endif // !_RIGHT_SIDE_BAR_UPD_DATA_FUNCS_H_