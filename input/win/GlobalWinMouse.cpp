#include "GlobalWinMouse.h"
#include <stdio.h>

GlobalWinMouse *GlobalWinMouse::uniqueInstance = nullptr;

void processMouseAction(WPARAM wParam, LPARAM lParam)
{
    KeyInfo info;
    PKBDLLHOOKSTRUCT action = (PKBDLLHOOKSTRUCT)lParam;

    if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        info.status = KeyStatus::DOWN;
    else
        info.status = KeyStatus::UP;

    info.time = action->time;
    info.code = action->vkCode;

    GlobalWinMouse::instance()->invokeCallback(info);
}

LRESULT CALLBACK MouseHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode == HC_ACTION) {
        processMouseAction(wParam, lParam);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

GlobalWinMouse *GlobalWinMouse::instance()
{
    if(uniqueInstance == nullptr)
        uniqueInstance = new GlobalWinMouse;
    return uniqueInstance;
}

void GlobalWinMouse::removeInstance()
{
    delete uniqueInstance;
    uniqueInstance = nullptr;
}

GlobalWinMouse::GlobalWinMouse()
{
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, MouseHook, 0, 0);
}

GlobalWinMouse::~GlobalWinMouse()
{
    UnhookWindowsHookEx(hook);
}

Point GlobalWinMouse::getPos() const
{
    return Point();
}

void GlobalWinMouse::setPos(Point &pos) const
{

}

void GlobalWinMouse::move(int dx, int dy, int time)
{

}
