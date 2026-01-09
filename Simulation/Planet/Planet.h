#ifndef _PLANET_H_
#define _PLANET_H_

#include <raylib.h>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include "../TimeHandler/TimeHandler.h"
#include "../../Util/all.h"

struct Vec2Double{
    double x;
    double y;
};

struct PlanetData{
    double radius;
    double mass;
    Vec2Double position;
    Vec2Double speed0;
    Vec2Double old_position = {0.f, 0.f};
    Vec2Double accel = {0.f, 0.f};
    bool is_collided = false;
};

class Planet{
public:
    Planet(PlanetData data):
        _data(data),
        _id(_id_counter++)
    {
        setSpeed(data.speed0);
    }

    float getRadius() const{
        return _data.radius;
    }

    double getRadiusRb() const{
        return static_cast<float>(_data.radius);
    }

    Vec2Double getPosition() const{
        return _data.position;
    }

    Vector2 getPositionRb() const{
        return Vector2{
            .x = static_cast<float>(_data.position.x),
            .y = static_cast<float>(_data.position.y)
        };
    }

    float getMass() const{
        return _data.mass;
    }

    uint64_t getId() const{
        return _id;
    }

    Vec2Double getTempAccel() const{
        return _data.accel;
    }

    void setPosition(Vec2Double pos){
        _data.position = pos;
    }

    void addPosition(Vec2Double dpos){
        _data.position = umath::add(_data.position, dpos);
    }

    void setSpeed(Vec2Double speed){
        const float dt = PhysTimeHandler::getInstance()->getTimeStep(); 
        _data.old_position = umath::sub(_data.position, umath::mult(speed, dt));
    }
    
    void addSpeed(Vec2Double dspeed){
        const float dt = PhysTimeHandler::getInstance()->getTimeStep(); 
        const Vec2Double shift = umath::mult(dspeed, dt);
        _data.old_position = umath::sub(_data.old_position, shift);
    }

    void setAccel(Vec2Double accel){
        _data.accel = accel;
    }

    void addAccel(Vec2Double accel){
        _data.accel = umath::add(_data.accel, accel);
    }

    void markCollided(){
        _data.is_collided = true;
    }

    void update(){
        const float real_dtime = RealTimeHandler::getInstance()->getScaledDeltaTime();
        const double phys_dtime = PhysTimeHandler::getInstance()->getTimeStep();
        
        const Vec2Double temp_pos = _data.position;

        const Vec2Double velocity_term =
            umath::sub(_data.position, _data.old_position);

        const Vec2Double accel_term = 
            umath::mult(_data.accel, phys_dtime * phys_dtime);

        _data.position =
            umath::add(_data.position, umath::add(velocity_term, accel_term));

        _data.old_position = temp_pos;

        _data.is_collided = false;
        _data.accel = {0.f, 0.f};
    }
     
private:
    inline static uint64_t _id_counter = 0;

    uint64_t _id;
    PlanetData _data;
};

#endif // !_PLANET_H_