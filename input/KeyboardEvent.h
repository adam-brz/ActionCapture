#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

typedef int Key;

enum class KeyStatus
{
    UP = 0,
    DOWN,
};

struct KeyboardEvent
{
    Key code = 0;
    KeyStatus status = KeyStatus::UP;
    int time = 0;
};

#endif // KEYBOARDEVENT_H
