#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <functional>
#include "KeyInfo.h"

class InputDevice
{
    std::function<void(const KeyInfo&)> callback;

public:
    virtual ~InputDevice() = default;

    void setCallback(std::function<void(const KeyInfo&)> newCallback);
    void invokeCallback(const KeyInfo &keyInfo);
};

#endif // INPUTDEVICE_H
