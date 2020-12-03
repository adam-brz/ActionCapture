#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include "MouseEvent.h"
#include "KeyboardEvent.h"

struct EventFilter {
    bool printable;
    bool nonprintable;
    bool mouseMove;
    bool mousePress;

    bool isGoodEvent(const MouseEvent& event) {
        return ((event.type == MouseEventType::MOVE) && mouseMove) ||
                ((event.type != MouseEventType::MOVE) && mousePress);
    }

    bool isGoodEvent(const KeyboardEvent &event) {
        return ((0x30 <= event.code && event.code <= 0x5A) && printable) ||
                ((event.code < 0x30  || event.code > 0x5A) && nonprintable);
    }
};

#endif // EVENTFILTER_H
