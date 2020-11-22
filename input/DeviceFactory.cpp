#include "DeviceFactory.h"

#ifdef _WIN32
    #include "input/win/GlobalWinMouse.h"
    #include "input/win/GlobalWinKeyboard.h"
#else
    #error "UNSUPPORTEDD TARGET PLATFORM"
#endif

GlobalKeyboard *DeviceFactory::makeKeyboard()
{
#ifdef _WIN32
    return GlobalWinKeyboard::instance();
#endif
}

GlobalMouse *DeviceFactory::makeMouse()
{
#ifdef _WIN32
    return GlobalWinMouse::instance();
#endif
}

void DeviceFactory::removeInstances()
{
#ifdef _WIN32
    GlobalWinMouse::removeInstance();
    GlobalWinKeyboard::removeInstance();
#endif
}
