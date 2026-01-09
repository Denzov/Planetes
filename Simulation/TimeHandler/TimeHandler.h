#ifndef _TIME_HANDLER_H_
#define _TIME_HANDLER_H_

#include <raylib.h>

#include "../../Util/lerp.h"

class RealTimeHandler{
public:
    static RealTimeHandler* getInstance() {
        static RealTimeHandler instance;
        return &instance;
    }

    float getTime() const { return GetTime(); }

    float getDeltaTime() const { return GetFrameTime(); }

    float getScaledDeltaTime() const { 
        const float dt = GetFrameTime();
        return _time_scale * dt; 
    }
    float getTimeScale() const { return _time_scale; }
    
    void setTimeScaleByLerp(float target, float lerp_t) {
        _time_scale = umath::lerp(_time_scale, target, lerp_t); 
    }

    void setTimeScale(float scale) { _time_scale = scale; }
    void resetTimeScale() { _time_scale = 1.0f; }
    void addTimeScale(float scale) { _time_scale += scale; }
    void mulTimeScale(float scale) { _time_scale *= scale; }

    bool isReverse() const { return _time_scale < 0.f; }
    bool isReverseFront() const {
        static bool prev_is_reverse = false;
        const bool is_reverse = isReverse();

        const bool front = prev_is_reverse != is_reverse;

        prev_is_reverse = is_reverse;
        return front;
    }

private:
    RealTimeHandler() = default;
    ~RealTimeHandler() = default;

    RealTimeHandler(const RealTimeHandler&) = delete;
    RealTimeHandler& operator=(const RealTimeHandler&) = delete;
    
private:
    float _time_scale = 1.0f;
};

class PhysTimeHandler{
public:
    static PhysTimeHandler* getInstance() {
        static PhysTimeHandler instance;
        return &instance;
    }

    float getTimeStep() const { return _TIME_STEP; }

    void timeStep(){
        _time += _TIME_STEP;
    }

    double getTime() const { return _time; }

    PhysTimeHandler(const PhysTimeHandler&) = delete;
    PhysTimeHandler& operator=(const PhysTimeHandler&) = delete;

private:
    PhysTimeHandler() = default;
    ~PhysTimeHandler() = default;

private:
    static constexpr double _TIME_STEP = 0.00005f;
    double _time = 0.f;

};


#endif // !_TIME_HANDLER_H_