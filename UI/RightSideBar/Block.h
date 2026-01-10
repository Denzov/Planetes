#ifndef _RIGHT_SIDE_BAR_BLOCK_H_
#define _RIGHT_SIDE_BAR_BLOCK_H_

#include <raylib.h>
#include <string>

class RightSideBarBlock{
public:
    using updDataFunc = std::string (*)();

    RightSideBarBlock(
        const float y_offset_ratio,
        const float font_size,
        std::string description,
        updDataFunc upd_data_func
    ):
        _y_offset_ratio(y_offset_ratio),
        _font_size(font_size),
        _description(description),
        _upd_data_func(upd_data_func){}

    void draw(){
        const std::string data = _upd_data_func();
        std::string drawable = data + _description;

        const float text_width = static_cast<float>(MeasureText(drawable.c_str(), _font_size));
        
        const float x_offset = GetRenderWidth() * _x_offset_ratio - text_width;
        const float y_offset = GetRenderHeight() * _y_offset_ratio;

        // std::cout << x_offset << " " << y_offset << " " << _y_offset_ratio<< std::endl;

        DrawText(
            drawable.c_str(),
            x_offset,
            y_offset,
            _font_size,
            WHITE
        );
    }
private:
    static constexpr float _x_offset_ratio = 0.99f;

    const float _font_size;
    const float _y_offset_ratio;
    const std::string _description;    
    updDataFunc _upd_data_func;

};

#endif // !_RIGHT_SIDE_BAR_BLOCK_H_