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
    KeyboardAction(GlobalKeyboard *keyboard = nullptr);
    KeyboardAction(GlobalKeyboard *keyboard, const KeyboardEvent &event);

    virtual std::string name() const override;
    virtual void run() override;

    virtual unsigned char typeID() const override;
    virtual SavableData *save() const override;
    virtual bool restore(SavableData *data) override;
};

#endif // KEYBOARDACTION_H
