#ifndef GLOBALWINKEYBOARD_H
#define GLOBALWINKEYBOARD_H

#include "input/GlobalKeyboard.h"
#include <windows.h>

class GlobalWinKeyboard : public GlobalKeyboard
{
private:
    static GlobalWinKeyboard *uniqueInstance;
    HHOOK hook;

public:
    static GlobalWinKeyboard *instance();
    static void removeInstance();

    ~GlobalWinKeyboard();

protected:
    GlobalWinKeyboard();
};

#endif // GLOBALWINKEYBOARD_H
