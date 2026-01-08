#ifndef _UI_PARAMS_H_
#define _UI_PARAMS_H_

#include <unordered_map>
#include <string>
#include <any>

class UIParams{
public:
    static UIParams* getInstance(){
        static UIParams ui_params;
        return &ui_params;
    }

    void setField(std::string name, std::any val){
        _settings[name] = val;        
    }

    std::any getField(std::string name){
        return _settings.at(name);
    }

    int getSize(){
        return _settings.size();
    }

    const std::unordered_map<std::string, std::any>& getRaw(){
        return _settings;
    }
private:
    UIParams(){}
    ~UIParams(){}

private:
    std::unordered_map<std::string, std::any> _settings;
};

#endif // !_UI_PARAMS_H_