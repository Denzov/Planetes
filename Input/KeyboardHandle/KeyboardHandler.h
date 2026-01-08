#ifndef _KEYBOARD_HANDLER_H_
#define _KEYBOARD_HANDLER_H_

#include <raylib.h>

#include "KeyHandle.h"

class KeyboardHandler{
public:
    static KeyboardHandler* getInstance(){
        static KeyboardHandler instance;
        return &instance;
    }   

    void handle(){
        for(auto& key: _all_keys){
            key->handle();
        }
    }
    
    KeyboardHandler(const KeyboardHandler&) = delete;
    KeyboardHandler& operator=(const KeyboardHandler&) = delete;

private:
    KeyboardHandler(){
        _all_keys.push_back(std::make_unique<HKey_A>());
        _all_keys.push_back(std::make_unique<HKey_W>());
        _all_keys.push_back(std::make_unique<HKey_S>());
        _all_keys.push_back(std::make_unique<HKey_D>());

        _all_keys.push_back(std::make_unique<HKey_UP>());
        _all_keys.push_back(std::make_unique<HKey_DOWN>());
        _all_keys.push_back(std::make_unique<HKey_RIGHT>());
        _all_keys.push_back(std::make_unique<HKey_LEFT>());

        _all_keys.push_back(std::make_unique<HKey_EQUAL>());
        _all_keys.push_back(std::make_unique<HKey_MINUS>());

        _all_keys.push_back(std::make_unique<HKey_F11>());
        _all_keys.push_back(std::make_unique<HKey_TAB>());
        _all_keys.push_back(std::make_unique<HKey_F>());
    }
    ~KeyboardHandler(){}

    IKeyHandle::vector _all_keys;
};

#endif // !_KEYBOARD_HANDLER_H_