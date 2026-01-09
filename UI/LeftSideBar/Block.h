#ifndef _LEFT_SIDE_BAR_BLOCK_H_
#define _LEFT_SIDE_BAR_BLOCK_H_

#include <raylib.h>
#include <string>
#include <memory>

#include "LeftSideBarTasks.h"

class LeftSideBarBlock{
public:
    LeftSideBarBlock(
        Vector2 base, Vector2 size,
        std::string title,
        std::unique_ptr<ILeftSideBarTask> task_on_click):
            _base(base), 
            _size(size),
            _title(title), 
            _task_on_click(std::move(task_on_click)){}

    void draw(){
        _draw_main_body();
        _draw_border();
        _draw_title();
    }

    void handle(){
        const bool mouse_in_block = _mouse_in_block_signal();

        if(mouse_in_block){
            state = State::WAIT;
            const auto& down_events = MouseHandler::getInstance()->getDownPerFrame();
            
            const bool is_right_down = 
                std::find(
                    down_events.begin(), down_events.end(), 
                    MouseHandler::TypeEvent::LEFT) != down_events.end();

            const bool back_front = _prev_is_right_down && !is_right_down;
            
            if(back_front){
                _task_on_click->exec();
            }
            
            if(is_right_down){
                state = State::ON;
            }
            
            _prev_is_right_down = is_right_down;
        }
        else{
            state = State::OFF;
            _prev_is_right_down = false;
        }
    }

private:
    bool _mouse_in_block_signal(){
        const Vector2 mouse_pos = MouseHandler::getInstance()->getMousePos();

        const bool mouse_in_block = 
            mouse_pos.x > _base.x && 
            mouse_pos.x < _base.x + _size.x &&
            mouse_pos.y > _base.y && 
            mouse_pos.y < _base.y + _size.y;

        return mouse_in_block;
    }

    void _draw_main_body(){
        switch(state){
        case State::ON:
            DrawRectangle(
                _base.x,
                _base.y,
                _size.x,
                _size.y,
                _block_color_bg_on
            );
            break;
        case State::WAIT:
            DrawRectangle(
                _base.x,
                _base.y,
                _size.x,
                _size.y,
                _blcok_color_bg_wait_on
            );
            break;
        case State::OFF:
            DrawRectangle(
                _base.x,
                _base.y,
                _size.x,
                _size.y,
                _block_color_bg_off
            );
            break;
        }
    }

    void _draw_border(){
        DrawRectangleLines(
            _base.x,
            _base.y,
            _size.x,
            _size.y,
            _block_color_border
        );
    }

    void _draw_title(){
        const Vector2 title_offset = {
            _title_offset_ratio.x * _size.x,
            _title_offset_ratio.y * _size.y,
        };
                
        DrawText(
            _title.c_str(), 
            _base.x + title_offset.x,
            _base.y + title_offset.y,
            _target_font_size,
            BLACK
        );
    }

private:
    bool _prev_is_right_down = false;

    static constexpr int _target_font_size = 30;

    static constexpr float _block_width = 150.f;
    static constexpr float _block_height = 75.f;

    static constexpr Vector2 _title_offset_ratio = {
        0.025f,
        0.025f
    };

    static constexpr Vector2 _text_offset_ratio = { 
        0.05f,
        0.5f
    };

    enum class State{
        ON,
        WAIT,
        OFF
    } state = State::OFF;

    static constexpr Color _block_color_bg_on = {192, 214, 210, 78};
    static constexpr Color _blcok_color_bg_wait_on = {192, 214, 210, 100};
    static constexpr Color _block_color_bg_off = {192, 214, 210, 128};

    static constexpr Color _block_color_border = {128, 158, 74, 255};

    const Vector2 _base;
    const Vector2 _size;
    const std::string _title;

    std::unique_ptr<ILeftSideBarTask> _task_on_click;
};

#endif // !_LEFT_SIDE_BAR_BLOCK_H_