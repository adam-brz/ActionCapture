#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Point.h"
#include "Key.h"

enum class MouseEventType
{
    MOVE = 0,
    UP,
    DOWN
};

struct MouseEvent
{
    Point point;
    Key key = 0;
    MouseEventType type = MouseEventType::MOVE;
};

#endif // MOUSEEVENT_H
