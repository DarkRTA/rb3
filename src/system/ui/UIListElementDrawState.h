#ifndef UI_UILISTELEMENTDRAWSTATE_H
#define UI_UILISTELEMENTDRAWSTATE_H
#include "math/Vec.h"
#include "ui/UIEnums.h"
#include "ui/UIComponent.h"

class UIListElementDrawState {
public:
    // got this entirely from bank 5 - courtesy of UIListSubList::Draw, we know the size of this is 0x28 total
    Vector3 mPos; // 0x0
    float mAlpha; // 0xc
    UIListWidgetState mElementState; // 0x10
    UIComponent::State mComponentState; // 0x14
    int mDisplay; // 0x18
    int mShowing; // 0x1c
    int mData; // 0x20
    int unk24; // 0x24
};

#endif
