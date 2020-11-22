#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "Key.h"

enum class KeyStatus
{
    UP = 0,
    DOWN,
};

struct KeyboardEvent
{
    Key code = 0;
    KeyStatus status = KeyStatus::UP;
};

#endif // KEYBOARDEVENT_H
