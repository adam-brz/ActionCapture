#include "GlobalMouse.h"

#ifdef _WIN32
    #include "input/win/GlobalWinMouse.h"
#else
    #error "UNSUPPORTEDD TARGET PLATFORM"
#endif

GlobalMouse *GlobalMouse::instance()
{
#ifdef _WIN32
    return GlobalWinMouse::instance();
#endif
}

void GlobalMouse::removeInstance()
{
#ifdef _WIN32
    GlobalWinMouse::removeInstance();
#endif
}
