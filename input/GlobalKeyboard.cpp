#include "GlobalKeyboard.h"

void GlobalKeyboard::setCallback(std::function<void (const KeyboardEvent &)> newCallback)
{
    callback = newCallback;
}

void GlobalKeyboard::invokeCallback(const KeyboardEvent &event)
{
    if(callback) {
        callback(event);
    }
}
