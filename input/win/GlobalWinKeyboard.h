#ifndef GLOBALWINKEYBOARD_H
#define GLOBALWINKEYBOARD_H

#include "input/GlobalKeyboard.h"
#include <windows.h>

class GlobalWinKeyboard : public GlobalKeyboard
{
private:
    static GlobalWinKeyboard *uniqueInstance;
    HHOOK hook;
    INPUT input;

public:
    static GlobalWinKeyboard *instance();
    static void removeInstance();

    ~GlobalWinKeyboard();
    virtual void sendInput(const KeyboardEvent& event) override;

protected:
    GlobalWinKeyboard();
};

#endif // GLOBALWINKEYBOARD_H
