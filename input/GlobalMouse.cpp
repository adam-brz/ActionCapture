#include "GlobalMouse.h"

#include <QApplication>
#include <QScreen>
#include <QCursor>

void GlobalMouse::setCallback(std::function<void (const MouseEvent &)> newCallback)
{
    callback = newCallback;
}

void GlobalMouse::invokeCallback(const MouseEvent &event)
{
    if(callback) {
        callback(event);
    }
}

Point GlobalMouse::getPos() const
{
    QScreen *screen = QApplication::primaryScreen();
    QCursor *cursor = new QCursor;
    QPoint pos = cursor->pos(screen);

    return Point{pos.x(), pos.y()};
}

void GlobalMouse::setPos(Point &pos) const
{
    QScreen *screen = QApplication::primaryScreen();
    QCursor *cursor = new QCursor;

    cursor->setPos(screen, pos.x, pos.y);
}
