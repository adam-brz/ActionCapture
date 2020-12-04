#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Point.h"
#include "Key.h"

#include <string>
#include <list>

enum class MouseEventType
{
    MOVE = 0,
    UP,
    DOWN
};

std::string to_string(const MouseEventType& eventType);
MouseEventType to_mouseEvent(const std::string& eventName);

std::list<std::string> mouseActions();

struct MouseEvent
{
    Point point;
    Key key = 0;
    MouseEventType type = MouseEventType::MOVE;
};

#endif // MOUSEEVENT_H
