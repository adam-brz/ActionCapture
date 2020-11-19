#ifndef GLOBALKEYCAPTURE_H
#define GLOBALKEYCAPTURE_H

#include <list>
#include "KeyInfo.h"

class GlobalKeyCapture
{
private:
    std::list<KeyInfo> keyQueue;
    unsigned maxSize;

public:
    GlobalKeyCapture(unsigned queueSize = 16);
    virtual ~GlobalKeyCapture() = default;

    KeyInfo popKey();
    bool isQueueEmpty() const;
    void clearQueue();

    const std::list<KeyInfo> &getQueue() const;

protected:
    virtual void storeKey(const KeyInfo &key);
};

#endif // GLOBALKEYCAPTURE_H
