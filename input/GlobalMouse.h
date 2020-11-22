#ifndef GLOBALMOUSE_H
#define GLOBALMOUSE_H

#include "Point.h"
#include "input/InputDevice.h"

class GlobalMouse : public InputDevice
{
public:
    virtual ~GlobalMouse() = default;

    virtual Point getPos() const = 0;
    virtual void setPos(Point &pos) const = 0;

    virtual void move(int dx, int dy, int time) = 0;
};

#endif // GLOBALMOUSE_H
