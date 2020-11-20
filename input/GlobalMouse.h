#ifndef GLOBALMOUSE_H
#define GLOBALMOUSE_H

#include "KeyQueue.h"
#include "Point.h"

#include "input/InputDevice.h"

class GlobalMouse : public InputDevice
{
private:
    KeyQueue queue;

public:
    static GlobalMouse *instance();
    static void removeInstance();

    virtual ~GlobalMouse() = default;

    virtual Point getPos() const = 0;
    virtual void setPos(Point &pos) const = 0;

    virtual void move(int dx, int dy, int time) = 0;

protected:
    GlobalMouse() = default;
};

#endif // GLOBALMOUSE_H
