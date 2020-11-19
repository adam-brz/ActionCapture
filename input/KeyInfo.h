#ifndef KEYINFO_H
#define KEYINFO_H

#include "Key.h"

struct KeyInfo
{
    Key code = 0;
    int status = 0; // Pressed/released
    int time = 0;
};

#endif // KEYINFO_H
