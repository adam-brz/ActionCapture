#ifndef KEYBOARDACTION_H
#define KEYBOARDACTION_H

#include "Action.h"
#include "GlobalKeyboard.h"
#include "KeyboardEvent.h"

class KeyboardAction : public Action
{
    GlobalKeyboard *keyboard;
    KeyboardEvent event;

public:
    KeyboardAction(GlobalKeyboard *keyboard, const KeyboardEvent &event);

    virtual std::string name() const override;
    virtual void run() override;
};

#endif // KEYBOARDACTION_H
