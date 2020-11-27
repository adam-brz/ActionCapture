#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action
{
public:
    virtual ~Action() = default;
    virtual std::string name() const = 0;
    virtual void run() = 0;
};

#endif // ACTION_H
