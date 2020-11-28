#include "SavableData.h"

SavableData::SavableData(unsigned reserveSize)
{
    this->reserve(reserveSize);
}

void SavableData::reserve(unsigned length)
{
    data.reserve(length);
}

void SavableData::add(const unsigned char *newData, unsigned size)
{
    for(unsigned i = 0; i < size; ++i)
        data.push_back(newData[i]);
}

void SavableData::add(unsigned char byte)
{
    data.push_back(byte);
}

void SavableData::add(const SavableData &other)
{
    this->reserve(this->size() + other.size());
    this->add(other.getRaw(), other.size());
}

const unsigned char *SavableData::getRaw() const
{
    return data.data();
}

unsigned char SavableData::read()
{
    if(atEnd())
        return data.back();
    return data[cursor++];
}

unsigned SavableData::read(unsigned char *destination, int maxAmount)
{
    unsigned readAmount = 0;

    while(maxAmount-- && !atEnd())
        destination[readAmount++] = data[cursor++];

    return readAmount;
}

unsigned SavableData::pos() const
{
    return cursor;
}

void SavableData::seek(unsigned pos)
{
    cursor = pos;
}

bool SavableData::atEnd() const
{
    return !(cursor < size());
}

unsigned SavableData::size() const
{
    return data.size();
}

void SavableData::clear()
{
    cursor = 0;
    data.clear();
}
