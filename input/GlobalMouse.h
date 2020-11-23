#ifndef GLOBALMOUSE_H
#define GLOBALMOUSE_H

#include "Point.h"
#include "MouseEvent.h"

#include <functional>

class GlobalMouse
{
    std::function<void(const MouseEvent&)> callback;

public:
    virtual ~GlobalMouse() = default;

    virtual Point getPos() const;
    virtual void setPos(Point &pos) const;

    virtual void sendInput(const MouseEvent& event) = 0;

    void setCallback(std::function<void(const MouseEvent&)> newCallback);
    void invokeCallback(const MouseEvent& event);
};

#endif // GLOBALMOUSE_H
