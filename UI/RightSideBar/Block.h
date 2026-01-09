#ifndef _RIGHT_SIDE_BAR_BLOCK_H_
#define _RIGHT_SIDE_BAR_BLOCK_H_

#include <raylib.h>
#include <string>

class RightSideBarBlock{
public:
    using upd_data_func = std::string (*)();

    RightSideBarBlock(
        Vector2 base,
        std::string description,
        upd_data_func upd_data_func
    ):
        _base(base),
        _description(description),
        _upd_data_func(upd_data_func){}

    void draw(){
        const std::string data = _upd_data_func();
        std::string drawable = data + _description;

        DrawText(
            drawable.c_str(),
            _base.x,
            _base.y,
            20,
            BLACK
        );

    }
private:
    const Vector2 _base;
    const std::string _description;
    upd_data_func _upd_data_func;
};

#endif // !_RIGHT_SIDE_BAR_BLOCK_H_