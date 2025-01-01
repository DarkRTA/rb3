#pragma once
#include "utl/Str.h"

// as of bank 5
class Friend {
public:
    String mName; // 0x0
    bool mOnline; // 0xc
    String mGame; // 0x10
    unsigned long long mFriendKey; // 0x1c
};