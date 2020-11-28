#ifndef SAVABLE_H
#define SAVABLE_H

class SavableData;

class Savable
{
public:
    virtual unsigned char typeID() const = 0;
    virtual SavableData *save() const;
    virtual bool restore(SavableData *data);
};


#endif // SAVABLE_H
