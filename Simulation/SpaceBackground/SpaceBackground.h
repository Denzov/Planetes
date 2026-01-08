#ifndef _SPACE_BACKGROUND_H_
#define _SPACE_BACKGROUND_H_

#include <raylib.h>
#include <vector>
#include <cmath>

#include "../../AppParams/MainCamera2D/MCamera2DHandler.h"

class SpaceBackground{
public:
    struct Star {
        Vector2 pos;      
        float radius;     
        float brightness; 
        float speed;      
        float phase;      
    };

    SpaceBackground(const SpaceBackground&) = delete;
    SpaceBackground& operator=(const SpaceBackground&) = delete;

    static SpaceBackground* getInstance(){
        static SpaceBackground instance;
        return &instance;
    }

    void init(){
        _stars.reserve(_count);

        for (int i = 0; i < _count; i++) {
            Star s;

            s.pos = {
                static_cast<float>(GetRandomValue(-_spread, _spread)),
                static_cast<float>(GetRandomValue(-_spread, _spread))
            };
            
            s.radius = GetRandomValue(1, 2);
            s.brightness = GetRandomValue(50, 100) / 100.f;
            s.speed = GetRandomValue(10, 40) / 350.f;
            s.phase = GetRandomValue(0, 1000) / 100.f;

            _stars.push_back(s);
        }
    }

    void draw(float time){
        ClearBackground(_bg_color);

        for (const Star& s : _stars) {
            const Camera2D cam = MCamera2DHandler::getInstance()->getData();

            const Vector2 screen_pos = {
                s.pos.x / cam.zoom + cam.target.x * (1 - s.speed),
                s.pos.y / cam.zoom + cam.target.y * (1 - s.speed)
            };

            float twinkle = 0.6f + 0.3f * sinf(time * 2.5 + s.phase);

            unsigned char c = (unsigned char)(200 * s.brightness * twinkle);

            DrawCircleV(screen_pos, s.radius / cam.zoom, {c, c, c, 255});
        }
    }

private:
    SpaceBackground(){}
    ~SpaceBackground(){}

private:
    std::vector<Star> _stars;

    static constexpr Color _bg_color = {5, 5, 15, 255};
    static constexpr int _count = 300;
    static constexpr int _spread = 2000;

};

#endif // !_SPACE_BACKGROUND_H_