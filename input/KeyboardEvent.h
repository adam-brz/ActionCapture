#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include "Key.h"
#include <string>
#include <list>

enum class KeyStatus
{
    UP = 0,
    DOWN,
};

std::string to_string(const KeyStatus& eventType);
KeyStatus to_keyStatus(const std::string& eventName);

std::list<std::string> keyboardActions();

struct KeyboardEvent
{
    Key code = 0;
    KeyStatus status = KeyStatus::UP;
};

#endif // KEYBOARDEVENT_H
