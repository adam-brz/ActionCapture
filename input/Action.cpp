#include "Action.h"
#include "toolbox/SavableData.h"

unsigned Action::getStartTime() const
{
    return startTime;
}

void Action::setStartTime(unsigned value)
{
    startTime = value;
}

SavableData *Action::save() const
{
    SavableData* data = Savable::save();
    data->add(RawBytesConst(&startTime), sizeof(startTime));
    return data;
}

bool Action::restore(SavableData *data)
{
    if(!Savable::restore(data))
        return false;

    data->read(RawBytes(&startTime), sizeof(startTime));
    return true;
}
