#ifndef GLOBALWINKEYBOARD_H
#define GLOBALWINKEYBOARD_H

#include "../GlobalKeyCapture.h"
#include <windows.h>

class GlobalWinKeyboard : public GlobalKeyCapture
{
private:
    HHOOK hook;

public:
    GlobalWinKeyboard();
    ~GlobalWinKeyboard();
};

#endif // GLOBALWINKEYBOARD_H
