#ifndef GLOBALMOUSE_H
#define GLOBALMOUSE_H

#include "GlobalKeyCapture.h"
#include "Point.h"

class GlobalMouse : public GlobalKeyCapture
{
public:
    ~GlobalMouse() = default;

    virtual Point getPos() const = 0;
    virtual void setPos(Point &pos) const = 0;

    virtual void move(int dx, int dy, int time) = 0;

protected:
    virtual void storeKey(const KeyInfo &key) = 0;
};

#endif // GLOBALMOUSE_H
