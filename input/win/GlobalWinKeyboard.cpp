#include "GlobalWinKeyboard.h"

#include <stdio.h>

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    static int last;
    BOOL letter = 1;

    if(nCode == HC_ACTION) {
        if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
            int code = p->vkCode;
            if(code == 0xA2) { // LCTRL or first signal of RALT
                last = code;
                return CallNextHookEx(NULL, nCode, wParam, lParam);
            }
            if(last == 0xA2 && code == 0xA5) { // RALT
                printf("%s", "<RALT>");
                letter = 0;
            } else if(last == 0xA2 && code != 0xA5) {
                printf("%s", "<LCTRL>");
            }
            if(code == 0xA3) {
                letter = 0;
                printf("%s", "<RCTRL>");
            }
            if(code == 0xA4) {
                letter = 0;
                printf("%s", "<LALT>");
            }
            if(code == 0xA0) {
                letter = 0;
                printf("%s", "<LSHIFT>");
            }
            if(code == 0xA1) {
                letter = 0;
                printf("%s", "<RSHIFT>");
            }
            if(code == 0x08) {
                letter = 0;
                printf("%s", "<ESC>");
            }
            if(code == 0x0D) {
                letter = 0;
                printf("\n");
            }
            last = code;
            if(letter) {
                printf("%c, %d", code, code);
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

GlobalWinKeyboard::GlobalWinKeyboard()
{
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, 0, 0);
}

GlobalWinKeyboard::~GlobalWinKeyboard()
{
    UnhookWindowsHookEx(hook);
}
