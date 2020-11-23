#ifndef GLOBALWINMOUSE_H
#define GLOBALWINMOUSE_H

#include "../GlobalMouse.h"
#include <windows.h>

class GlobalWinMouse : public GlobalMouse
{
private:
    static GlobalWinMouse *uniqueInstance;
    HHOOK hook;

public:
    static GlobalWinMouse *instance();
    static void removeInstance();

    virtual ~GlobalWinMouse();

protected:
    GlobalWinMouse();
};

#endif // GLOBALWINMOUSE_H
