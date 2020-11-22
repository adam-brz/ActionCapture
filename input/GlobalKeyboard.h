#ifndef GLOBALKEYBOARD_H
#define GLOBALKEYBOARD_H

#include "KeyboardEvent.h"
#include <functional>

class GlobalKeyboard
{
    std::function<void(const KeyboardEvent&)> callback;

public:
    virtual ~GlobalKeyboard() = default;

    void setCallback(std::function<void(const KeyboardEvent&)> newCallback);
    void invokeCallback(const KeyboardEvent& event);
};

#endif // GLOBALKEYBOARD_H
