#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "toolbox/Savable.h"

class Action : public Savable
{
    unsigned startTime = 0;

public:
    virtual ~Action() = default;
    virtual std::string name() const = 0;
    virtual void run() = 0;

    unsigned getStartTime() const;
    void setStartTime(unsigned value);

    virtual SavableData *save() const override;
    virtual bool restore(SavableData *data) override;
};

#endif // ACTION_H
