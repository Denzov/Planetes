#ifndef _FPS_BAR_H_
#define _FPS_BAR_H_

#include <raylib.h>
#include <string>

class FpsBar{
public:
    void draw(){
        const std::string fps_text = std::to_string(GetFPS()) + " FPS ";
        const float text_width = static_cast<float>(MeasureText(fps_text.c_str(), _font_size));

        const Vector2 position = {
            .x = GetRenderWidth() - text_width,
            .y = GetRenderHeight() * _text_pos_ratio.y
        };

        DrawText(fps_text.c_str(), position.x, position.y, _font_size, _text_color);

        // std::cout << GetRenderWidth() << " " << GetRenderHeight() << std::endl;
    }

private:
    static constexpr Vector2 _text_pos_ratio = {0.99f, 0.95f};
    static constexpr Color _text_color = {255, 255, 255, 255};
    static constexpr int _font_size = 20;
};

#endif // !_FPS_BAR_H_