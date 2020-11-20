#ifndef KEYINFO_H
#define KEYINFO_H

#include "Key.h"

enum class KeyStatus
{
    UP = 0,
    DOWN
};

struct KeyInfo
{
    Key code = 0;
    KeyStatus status = KeyStatus::UP;
    int time = 0;
};

#endif // KEYINFO_H
