#ifndef _I_KEY_HANDLE_H_
#define _I_KEY_HANDLE_H_

#include <memory>
#include <vector>

class IKeyHandle{
public:
    using UPtr = std::unique_ptr<IKeyHandle>;
    using vector = std::vector<UPtr>;

    virtual void handle() = 0;
};

#endif // !_I_KEY_HANDLE_H_