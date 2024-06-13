#ifndef UI_UILISTSTATE_H
#define UI_UILISTSTATE_H

#include "types.h"
#include <vector>
class UIListStateCallback {
    public:
    UIListStateCallback() {}
    virtual ~UIListStateCallback() {}
};

class UIListState { // 0x48
public:
    UIListState(class UIListProvider*, UIListStateCallback*);

    bool CanScrollBack(bool) const;
    bool CanScrollNext(bool) const;

    bool mCircular; // 0x0
    int mNumDisplay; // 0x4
    int mGridSpan; // 0x8
    float unk_0xC;
    int unk_0x10;
    u8 unk_0x14;
    int unk_0x18;
    u8 unk_0x1C;
    int unk_0x20;
    std::vector<int> unk_0x24;
    int unk_0x2C, unk_0x30, unk_0x34;
    float unk_0x38, unk_0x3C;
    int unk_0x40;
    // TODO: fill out the rest
};

#endif
