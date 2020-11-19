#ifndef GLOBALWINMOUSE_H
#define GLOBALWINMOUSE_H

#include "../GlobalMouse.h"
#include <windows.h>

class GlobalWinMouse : public GlobalMouse
{
public:
    GlobalWinMouse();
    ~GlobalWinMouse();

    Point getPos() const override;
    void setPos(Point &pos) const override;

    void move(int dx, int dy, int time) override;
};

#endif // GLOBALWINMOUSE_H
