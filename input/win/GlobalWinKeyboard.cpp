#include "GlobalWinKeyboard.h"
#include "input/KeyboardEvent.h"

GlobalWinKeyboard *GlobalWinKeyboard::uniqueInstance = nullptr;

void processKeyboardAction(WPARAM wParam, LPARAM lParam)
{
    KeyboardEvent event;
    PKBDLLHOOKSTRUCT action = (PKBDLLHOOKSTRUCT)lParam;

    if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        event.status = KeyStatus::DOWN;
    else
        event.status = KeyStatus::UP;

    event.code = action->vkCode;
    GlobalWinKeyboard::instance()->invokeCallback(event);
}

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode == HC_ACTION) {
        processKeyboardAction(wParam, lParam);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

GlobalWinKeyboard *GlobalWinKeyboard::instance()
{
    if(uniqueInstance == nullptr)
        uniqueInstance = new GlobalWinKeyboard;
    return uniqueInstance;
}

void GlobalWinKeyboard::removeInstance()
{
    delete uniqueInstance;
    uniqueInstance = nullptr;
}

GlobalWinKeyboard::GlobalWinKeyboard()
{
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, 0, 0);
}

GlobalWinKeyboard::~GlobalWinKeyboard()
{
    UnhookWindowsHookEx(hook);
}
