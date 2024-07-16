#ifndef UI_UILISTELEMENTDRAWSTATE_H
#define UI_UILISTELEMENTDRAWSTATE_H
#include "math/Vec.h"
#include "ui/UIEnums.h"
#include "ui/UIComponent.h"

class UIListElementDrawState {
public:
    // got this entirely from bank 5 - courtesy of UIListSubList::Draw, we know the size of this is 0x28 total
    bool unk0; // 0x0
    Vector3 mPos; // 0x4
    float mAlpha; // 0x10
    UIListWidgetState mElementState; // 0x14
    UIComponent::State mComponentState; // 0x18
    int mDisplay; // 0x1c
    int mShowing; // 0x20
    int mData; // 0x24
};

#endif
