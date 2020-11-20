#include "InputDevice.h"

void InputDevice::setCallback(std::function<void (const KeyInfo &)> newCallback)
{
    callback = newCallback;
}

void InputDevice::invokeCallback(const KeyInfo &keyInfo)
{
   if(callback)
       callback(keyInfo);
}
