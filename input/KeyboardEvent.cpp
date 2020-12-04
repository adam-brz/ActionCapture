#include "KeyboardEvent.h"

std::string to_string(const KeyStatus &eventType)
{
    if(eventType == KeyStatus::DOWN)
        return "Down";

    return "Up";
}

KeyStatus to_keyStatus(const std::string &eventName)
{
    if(eventName == "Down")
        return KeyStatus::DOWN;

    return KeyStatus::UP;
}

std::list<std::string> keyboardActions()
{
    return {"Up", "Down"};
}
