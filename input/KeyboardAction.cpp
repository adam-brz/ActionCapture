#include "KeyboardAction.h"
#include "toolbox/SavableData.h"

KeyboardAction::KeyboardAction(GlobalKeyboard *keyboard) :
    keyboard(keyboard)
{

}

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

unsigned char KeyboardAction::typeID() const
{
    return KEYBOAD_ACTION_ID;
}

SavableData *KeyboardAction::save() const
{
    SavableData *data = Action::save();
    data->add(RawBytesConst(&event), sizeof(event));
    return data;
}

bool KeyboardAction::restore(SavableData *data)
{
    if(!Action::restore(data))
        return false;

    data->read(RawBytes(&event), sizeof(event));
    return true;
}

