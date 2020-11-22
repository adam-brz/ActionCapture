#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "GlobalKeyboard.h"
#include "GlobalMouse.h"

class DeviceFactory
{
public:
    static GlobalKeyboard *makeKeyboard();
    static GlobalMouse *makeMouse();
    static void removeInstances();
};

#endif // DEVICEFACTORY_H
