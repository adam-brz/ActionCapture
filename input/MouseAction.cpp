#include "MouseAction.h"
#include "toolbox/SavableData.h"

MouseAction::MouseAction(GlobalMouse *mouse) :
    mouse(mouse)
{

}

MouseAction::MouseAction(GlobalMouse *mouse, const MouseEvent &event) :
    mouse(mouse),
    event(event)
{

}

const MouseEvent &MouseAction::readEvent() const
{
    return event;
}

std::string MouseAction::name() const
{
    std::string description = "Mouse ";

    description += std::to_string(event.key);

    switch (event.type) {
        case MouseEventType::MOVE:
            description += " move ";
            break;
        case MouseEventType::UP:
            description += " up ";
            break;
        case MouseEventType::DOWN:
            description += " down ";
            break;
    }

    description += std::to_string(event.point.x) + ", "
                    + std::to_string(event.point.y);

    return description;
}

void MouseAction::run()
{
    mouse->sendInput(event);
}

unsigned char MouseAction::typeID() const
{
    return MOUSE_ACTION_ID;
}

SavableData *MouseAction::save() const
{
    SavableData *data = Action::save();
    data->add(RawBytesConst(&event), sizeof(event));

    return data;
}

bool MouseAction::restore(SavableData *data)
{
    if(!Action::restore(data))
        return false;

    data->read(RawBytes(&event), sizeof(event));
    return true;
}
