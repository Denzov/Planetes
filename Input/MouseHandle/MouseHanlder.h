#ifndef _MOUSE_HANDLER_H_
#define _MOUSE_HANDLER_H_

#include <raylib.h>
#include <vector>
#include <algorithm>

class MouseHandler{
public:
    enum class TypeEvent{
        LEFT = MOUSE_BUTTON_LEFT,
        RIGHT = MOUSE_BUTTON_RIGHT,
        MIDDLE = MOUSE_BUTTON_MIDDLE
    };

    static MouseHandler* getInstance(){
        static MouseHandler instance;
        return &instance;
    }

    Vector2 getMousePos(){
        return _mouse_pos;
    }

    void handle(){
        _pressed_per_frame.clear();
        _down_per_frame.clear();

        _mouse_pos = GetMousePosition();

        for(auto& event : _all_events){
            if(IsMouseButtonDown(static_cast<int>(event))){
                _down_per_frame.push_back(event);

                if(IsMouseButtonPressed(static_cast<int>(event))){
                    _pressed_per_frame.push_back(event);
                }   
            }
        }
    }

    const std::vector<TypeEvent>& getPressedPerFrame(){
        return _pressed_per_frame;
    }

    const std::vector<TypeEvent>& getDownPerFrame(){
        return _down_per_frame;
    }

    MouseHandler(const MouseHandler&) = delete;
    MouseHandler& operator=(const MouseHandler&) = delete;

private:
    MouseHandler(){}
    ~MouseHandler(){}

private:
    static constexpr TypeEvent _all_events[] = {
        TypeEvent::LEFT,
        TypeEvent::RIGHT,
        TypeEvent::MIDDLE
    };


    std::vector<TypeEvent> _pressed_per_frame;
    std::vector<TypeEvent> _down_per_frame;
    Vector2 _mouse_pos;
};

#endif // !_MOUSE_HANDLER_H_