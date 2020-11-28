#include "Savable.h"
#include "SavableData.h"

SavableData *Savable::save() const
{
    SavableData *data = new SavableData;
    data->add(typeID());
    return data;
}

bool Savable::restore(SavableData *data)
{
    if(data->read() != typeID())
        return false;
    return true;
}
