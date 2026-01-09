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
        const double real_dt = static_cast<double>(RealTimeHandler::getInstance()->getScaledDeltaTime());
        
        double phys_temp_time = 0.f;

        // std::cout << real_dt << std::endl;

        while (std::abs(real_dt) > phys_temp_time) {
            phys_temp_time += PhysTimeHandler::getInstance()->getTimeStep();

            for (size_t i = 0; i < _planets.size(); i++) {
                for (size_t j = i + 1; j < _planets.size(); j++) {
                    auto& first = _planets[i];
                    auto& second = _planets[j];

                    const Vec2Double diff = 
                        umath::sub(first.getPosition(), second.getPosition());
                                    
                    const double dist_sq = umath::dot(diff, diff);
                    const double sum_radius = first.getRadius() + second.getRadius();

                    const double collision_cond = dist_sq < sum_radius * sum_radius;

                    // if (collision_cond){
                    //     first.markCollided();
                    //     second.markCollided();
                    //     continue;
                    // }

                    const double dist_raw = sqrt(dist_sq);
                    const double dist = dist_raw * _distance_factor;
                    const Vec2Double normalized_diff = umath::normalize(diff, dist_raw);

                    const Vec2Double first_temp_accel = 
                        _resolve_gravity_accel({
                            .normalized_diff = umath::mult(normalized_diff, -1),
                            .dist = dist,
                            .mass = second.getMass()
                        });

                    const Vec2Double second_temp_accel = 
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
            DrawCircleV(planet.getPositionRb(), planet.getRadiusRb(), RED);
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
    // Vec2Double _resolve_collision_accel(){

    // }

    struct ResolveGravityAccelArgs{
        Vec2Double normalized_diff;
        double dist;
        double mass;
    };

    Vec2Double _resolve_gravity_accel(ResolveGravityAccelArgs args){
        const double common_inv_dist_sq = 1.0f / (args.dist * args.dist);

        const double scalar_temp_accel = common_inv_dist_sq * args.mass;

        const Vec2Double vec_temp_accel = 
            umath::mult(args.normalized_diff, scalar_temp_accel);
            
        return vec_temp_accel;
    }

private:
    std::vector<Planet> _planets;
    const float _distance_factor = 0.01f;
};
#endif // !_PLANET_HOLDER_H_
