#include "GlobalKeyCapture.h"

KeyInfo GlobalKeyCapture::popKey()
{
    KeyInfo result;

    if(!isQueueEmpty()) {
        result = keyQueue.back();
        keyQueue.pop_back();
    }

    return result;
}

bool GlobalKeyCapture::isQueueEmpty() const
{
    return keyQueue.size() > 0;
}

void GlobalKeyCapture::clearQueue()
{
    keyQueue.clear();
}

const std::list<KeyInfo> &GlobalKeyCapture::getQueue() const
{
    return keyQueue;
}
