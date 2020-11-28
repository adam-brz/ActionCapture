#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action
{
    unsigned startTime = 0;

public:
    virtual ~Action() = default;
    virtual std::string name() const = 0;
    virtual void run() = 0;

    unsigned getStartTime() const;
    void setStartTime(unsigned value);
};

#endif // ACTION_H
