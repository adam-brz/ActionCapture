#include "GlobalKeyCapture.h"

GlobalKeyCapture::GlobalKeyCapture(unsigned queueSize) :
    maxSize(queueSize)
{

}

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

void GlobalKeyCapture::storeKey(const KeyInfo &key)
{
    keyQueue.push_back(key);
    if(keyQueue.size() >= maxSize)
        keyQueue.pop_front();
}
