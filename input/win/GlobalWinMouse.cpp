#include "GlobalWinMouse.h"
#include "input/MouseEvent.h"

GlobalWinMouse *GlobalWinMouse::uniqueInstance = nullptr;

void saveEventKeyAndType(WPARAM wParam, MouseEvent &event);

void processMouseAction(WPARAM wParam, LPARAM lParam)
{
    MouseEvent event;
    LPMOUSEHOOKSTRUCT action = (LPMOUSEHOOKSTRUCT)lParam;

    event.point.x = action->pt.x;
    event.point.y = action->pt.y;

    saveEventKeyAndType(wParam, event);
    GlobalWinMouse::instance()->invokeCallback(event);
}

void saveEventKeyAndType(WPARAM wParam, MouseEvent &event){
    switch(wParam) {
    case WM_LBUTTONDOWN:
        event.key = 0;
        event.type = MouseEventType::DOWN;
        break;
    case WM_LBUTTONUP:
        event.key = 0;
        event.type = MouseEventType::UP;
        break;
    case WM_RBUTTONDOWN:
        event.key = 1;
        event.type = MouseEventType::DOWN;
        break;
    case WM_RBUTTONUP:
        event.key = 1;
        event.type = MouseEventType::UP;
        break;
    case WM_MBUTTONDOWN:
        event.key = 2;
        event.type = MouseEventType::DOWN;
        break;
    case WM_MBUTTONUP:
        event.key = 2;
        event.type = MouseEventType::UP;
        break;
    default:
        event.key = 0;
        event.type = MouseEventType::MOVE;
    }
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

void GlobalWinMouse::sendInput(const MouseEvent &event)
{
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;

    input.mi.dx = event.point.x;
    input.mi.dy = event.point.y;

    if(event.type == MouseEventType::MOVE) {
         input.mi.dwFlags |= MOUSEEVENTF_MOVE;
    }
    else if(event.type == MouseEventType::UP) {
        if(event.key == 0)
            input.mi.dwFlags |= MOUSEEVENTF_LEFTUP;
        else if(event.key == 1)
            input.mi.dwFlags |= MOUSEEVENTF_RIGHTUP;
        else if(event.key == 2)
            input.mi.dwFlags |= MOUSEEVENTF_MIDDLEUP;
    }
    else if(event.type == MouseEventType::DOWN) {
        if(event.key == 0)
            input.mi.dwFlags |= MOUSEEVENTF_LEFTDOWN;
        else if(event.key == 1)
            input.mi.dwFlags |= MOUSEEVENTF_RIGHTDOWN;
        else if(event.key == 2)
            input.mi.dwFlags |= MOUSEEVENTF_MIDDLEDOWN;
    }

    SendInput(1, &input, sizeof(INPUT));
}

GlobalWinMouse::GlobalWinMouse()
{
    hook = SetWindowsHookEx(WH_MOUSE_LL, MouseHook, 0, 0);
}

GlobalWinMouse::~GlobalWinMouse()
{
    UnhookWindowsHookEx(hook);
}
