#ifndef _PLANET_H_
#define _PLANET_H_

#include <raylib.h>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include "../TimeHandler/TimeHandler.h"
#include "../../Util/all.h"

struct PlanetData{
    float radius;
    float mass;
    Vector2 position;
    Vector2 speed0;
    Vector2 old_position = {0.f, 0.f};
    Vector2 accel = {0.f, 0.f};
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

    Vector2 getPosition() const{
        return _data.position;
    }

    float getMass() const{
        return _data.mass;
    }

    uint64_t getId() const{
        return _id;
    }

    Vector2 getTempAccel() const{
        return _data.accel;
    }

    void setPosition(Vector2 pos){
        _data.position = pos;
    }

    void addPosition(Vector2 dpos){
        _data.position = umath::add(_data.position, dpos);
    }

    void setSpeed(Vector2 speed){
        const float dt = PhysTimeHandler::getInstance()->getTimeStep(); 
        _data.old_position = umath::sub(_data.position, umath::mult(speed, dt));
    }
    
    void addSpeed(Vector2 dspeed){
        const float dt = PhysTimeHandler::getInstance()->getTimeStep(); 
        const Vector2 shift = umath::mult(dspeed, dt);
        _data.old_position = umath::sub(_data.old_position, shift);
    }

    void setAccel(Vector2 accel){
        _data.accel = accel;
    }

    void addAccel(Vector2 accel){
        _data.accel = umath::add(_data.accel, accel);
    }

    void markCollided(){
        _data.is_collided = true;
    }

    void update(){
        const float dtime = PhysTimeHandler::getInstance()->getTimeStep();
        
        const Vector2 temp_pos = _data.position;

        const Vector2 velocity_term =
            umath::sub(_data.position, _data.old_position);

        const Vector2 accel_term = 
            umath::mult(_data.accel, dtime * dtime);

            
        // std::cout << _id << ": " << accel_term.x << ", " << accel_term.y << std::endl;

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