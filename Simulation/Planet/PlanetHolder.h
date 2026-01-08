#ifndef _PLANET_HOLDER_H_
#define _PLANET_HOLDER_H_

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "Planet.h"
#include "../../Util/all.h"

class PlanetHolder{
public:
    PlanetHolder(const PlanetHolder&) = delete;
    PlanetHolder& operator=(const PlanetHolder&) = delete;

    static PlanetHolder* getInstance(){
        static PlanetHolder instance;
        return &instance;
    }

    void init(int32_t planet_count){
        _planets.reserve(planet_count);
    }

    void addPlanet(PlanetData data){
        _planets.push_back(Planet(data));
    }

    void addPlanet(Planet& planet){
        _planets.push_back(planet);
    }

    void delPlanet(Planet& planet){
        _planets.erase(
            std::remove_if(_planets.begin(), _planets.end(), 
            [&](Planet& p){
                return p.getId() == planet.getId();
            })
        );
    }

    void handle(){        
        const float real_time = RealTimeHandler::getInstance()->getTime();

        RealTimeHandler::getInstance()->getDeltaTime();

        while (real_time > PhysTimeHandler::getInstance()->getTime()) {
            PhysTimeHandler::getInstance()->timeStep();
            for (size_t i = 0; i < _planets.size(); i++) {
                for (size_t j = i + 1; j < _planets.size(); j++) {
                    auto& first = _planets[i];
                    auto& second = _planets[j];

                    const Vector2 diff = 
                        umath::sub(first.getPosition(), second.getPosition());
                                    
                    const float dist_sq = umath::dot(diff, diff);
                    const float sum_radius = first.getRadius() + second.getRadius();

                    const bool collision_cond = dist_sq < sum_radius * sum_radius;

                    // if (collision_cond){
                    //     first.markCollided();
                    //     second.markCollided();
                    //     continue;
                    // }

                    const float dist = sqrt(dist_sq);
                    const Vector2 normalized_diff = umath::normalize(diff, dist);

                    const Vector2 first_temp_accel = 
                        _resolve_gravity_accel({
                            .normalized_diff = umath::mult(normalized_diff, -1),
                            .dist = dist,
                            .mass = second.getMass()
                        });

                    const Vector2 second_temp_accel = 
                        _resolve_gravity_accel({
                            .normalized_diff = normalized_diff,
                            .dist = dist, 
                            .mass = first.getMass()
                        });

                    first.addAccel(first_temp_accel);
                    second.addAccel(second_temp_accel);
                }
            }

            _upd_position();
        }
    }

    void draw(){
        for(auto& planet: _planets){
            DrawCircleV(planet.getPosition(), planet.getRadius(), RED);
        }
    }

private:
    PlanetHolder(){}
    ~PlanetHolder(){}

    void _upd_position(){
        for(auto& planet: _planets){
            planet.update();
        }
    }
private:
    Vector2 _resolve_collision_accel(){

    }

    struct ResolveGravityAccelArgs{
        Vector2 normalized_diff;
        float dist;
        float mass;
    };

    Vector2 _resolve_gravity_accel(ResolveGravityAccelArgs args){
        const float common_inv_dist_sq = 1.0f / (args.dist * args.dist);

        const float scalar_temp_accel = common_inv_dist_sq * args.mass;

        const Vector2 vec_temp_accel = 
            umath::mult(args.normalized_diff, scalar_temp_accel);
            
        return vec_temp_accel;
    }

private:
    std::vector<Planet> _planets;
};
#endif // !_PLANET_HOLDER_H_
