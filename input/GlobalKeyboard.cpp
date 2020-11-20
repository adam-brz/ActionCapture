#include "GlobalKeyboard.h"

#ifdef _WIN32
    #include "input/win/GlobalWinKeyboard.h"
#else
    #error "UNSUPPORTEDD TARGET PLATFORM"
#endif

GlobalKeyboard *GlobalKeyboard::instance()
{
#ifdef _WIN32
    return GlobalWinKeyboard::instance();
#endif
}

void GlobalKeyboard::removeInstance()
{
#ifdef _WIN32
    GlobalWinKeyboard::removeInstance();
#endif
}
