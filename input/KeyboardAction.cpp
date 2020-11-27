#include "KeyboardAction.h"

KeyboardAction::KeyboardAction(GlobalKeyboard *keyboard, const KeyboardEvent &event) :
    keyboard(keyboard),
    event(event)
{

}

std::string KeyboardAction::name() const
{
    std::string description = "Key ";
    description += std::to_string(event.code);

    if(event.status == KeyStatus::DOWN)
        return description + " Down";
    return description + " Up";
}

void KeyboardAction::run()
{
    keyboard->sendInput(event);
}

