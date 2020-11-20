#ifndef GLOBALKEYBOARD_H
#define GLOBALKEYBOARD_H

#include "input/InputDevice.h"

class GlobalKeyboard : public InputDevice
{
public:
    virtual ~GlobalKeyboard() = default;

    static GlobalKeyboard *instance();
    static void removeInstance();

protected:
    GlobalKeyboard() = default;
};

#endif // GLOBALKEYBOARD_H
