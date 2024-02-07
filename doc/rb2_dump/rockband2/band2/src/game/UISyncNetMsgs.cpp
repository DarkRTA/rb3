/*
    Compile unit: C:\rockband2\band2\src\game\UISyncNetMsgs.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80097514 -> 0x800988E0
*/
class Symbol t; // size: 0x4, address: 0x80A4A13C
class Symbol t; // size: 0x4, address: 0x80A4A144
class Symbol t; // size: 0x4, address: 0x80A4A14C
class ComponentFocusNetMsg : public NetMessage {
    // total size: 0x14
    int mPlayerNum; // offset 0x4, size 0x4
    class String mComponentName; // offset 0x8, size 0xC
};
// Range: 0x80097514 -> 0x8009756C
void ComponentFocusNetMsg::Save(const class ComponentFocusNetMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8009756C -> 0x800975BC
void ComponentFocusNetMsg::Load(class ComponentFocusNetMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

class NetComponentFocusMsg : public Message {
    // total size: 0x8
};
static class NetComponentFocusMsg netFocus; // size: 0x8, address: 0x80977878
// Range: 0x800975BC -> 0x80097998
void ComponentFocusNetMsg::Dispatch(class ComponentFocusNetMsg * const this /* r30 */) {
    // Local variables
    class DataNode ret; // r1+0x40
    class UIPanel * p; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class UIManager TheUI;
    // -> class UserMgr * TheUserMgr;
    // -> struct [anonymous] __vt__20NetComponentFocusMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class NetComponentFocusMsg netFocus;
    // -> class NetSync * TheNetSync;
}

class ComponentSelectNetMsg : public NetMessage {
    // total size: 0x18
    int mPlayerNum; // offset 0x4, size 0x4
    class String mComponentName; // offset 0x8, size 0xC
    unsigned char mShowSelect; // offset 0x14, size 0x1
};
// Range: 0x80097998 -> 0x80097A48
void * ComponentSelectNetMsg::ComponentSelectNetMsg(class ComponentSelectNetMsg * const this /* r28 */, int playerNum /* r29 */, class UIComponent * c /* r30 */, unsigned char show_select /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__21ComponentSelectNetMsg;
}

// Range: 0x80097A48 -> 0x80097AB8
void ComponentSelectNetMsg::Save(const class ComponentSelectNetMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x80097AB8 -> 0x80097B2C
void ComponentSelectNetMsg::Load(class ComponentSelectNetMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

class NetComponentSelectMsg : public Message {
    // total size: 0x8
};
static class NetComponentSelectMsg msg; // size: 0x8, address: 0x80977890
// Range: 0x80097B2C -> 0x80097F08
void ComponentSelectNetMsg::Dispatch(class ComponentSelectNetMsg * const this /* r30 */) {
    // Local variables
    class DataNode ret; // r1+0x40
    class UIComponent * c; // r0

    // References
    // -> class UIManager TheUI;
    // -> class UserMgr * TheUserMgr;
    // -> struct [anonymous] __vt__21NetComponentSelectMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class NetComponentSelectMsg msg;
    // -> class NetSync * TheNetSync;
}

class ComponentScrollNetMsg : public NetMessage {
    // total size: 0x1C
    int mPlayerNum; // offset 0x4, size 0x4
    class String mComponentName; // offset 0x8, size 0xC
    int mPosition; // offset 0x14, size 0x4
    int mFirstShowing; // offset 0x18, size 0x4
};
class ScrollSelect {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    unsigned char mNeedSelect; // offset 0x4, size 0x1
private:
    int mSelectedIndex; // offset 0x8, size 0x4
};
enum ListShowing {
    kListAlways = 0,
    kListOnlyFocused = 1,
    kListNever = 2,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ListElement * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ListElement * * _M_start; // offset 0x0, size 0x4
    class ListElement * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Box {
    // total size: 0x20
public:
    class Vector3 mMin; // offset 0x0, size 0x10
    class Vector3 mMax; // offset 0x10, size 0x10
};
class ListDisplay {
    // total size: 0x60
    unsigned char mDirty; // offset 0x0, size 0x1
    unsigned char mVertical; // offset 0x1, size 0x1
    float mSpacing; // offset 0x4, size 0x4
    float mArrowOffset; // offset 0x8, size 0x4
    enum ListShowing mArrowShowing; // offset 0xC, size 0x4
    unsigned char mArrowOnlyScroll; // offset 0x10, size 0x1
    unsigned char mArrowsOnHighlight; // offset 0x11, size 0x1
    enum ListShowing mHighlightShowing; // offset 0x14, size 0x4
    class DataArray * mHighlightColors; // offset 0x18, size 0x4
    unsigned char mHighlightFirst; // offset 0x1C, size 0x1
    int mFadeOffset; // offset 0x20, size 0x4
    class DataArray * mSlots; // offset 0x24, size 0x4
    class UIList * mList; // offset 0x28, size 0x4
    class RndMesh * mBackArrow; // offset 0x2C, size 0x4
    class RndMesh * mNextArrow; // offset 0x30, size 0x4
    class RndMesh * mHighlight; // offset 0x34, size 0x4
    class vector mElements; // offset 0x38, size 0xC
    class vector mDisplays; // offset 0x44, size 0xC
    class ListElement * mNext; // offset 0x50, size 0x4
    int mDirection; // offset 0x54, size 0x4
    float mTotalGap; // offset 0x58, size 0x4
    float mHighlightGap; // offset 0x5C, size 0x4
};
struct ScrollState {
    // total size: 0x8
    int mTarget; // offset 0x0, size 0x4
    int mSelected; // offset 0x4, size 0x4
};
class ListState : public MsgSource {
    // total size: 0x88
protected:
    unsigned char mCircular; // offset 0x1C, size 0x1
    int mNumDisplay; // offset 0x20, size 0x4
    float mSpeed; // offset 0x24, size 0x4
    int mMinDisplay; // offset 0x28, size 0x4
    unsigned char mScrollPastMinDisplay; // offset 0x2C, size 0x1
    int mMaxDisplay; // offset 0x30, size 0x4
    unsigned char mScrollPastMaxDisplay; // offset 0x34, size 0x1
    class ListProvider * mProvider; // offset 0x38, size 0x4
    class vector mHiddenData; // offset 0x3C, size 0xC
    int mFirstShowing; // offset 0x48, size 0x4
    int mTargetShowing; // offset 0x4C, size 0x4
    int mSelectedDisplay; // offset 0x50, size 0x4
    float mStepPercent; // offset 0x54, size 0x4
    float mStepTime; // offset 0x58, size 0x4
};
class DataProvider : public ListProvider {
    // total size: 0x14
    class DataArray * mData; // offset 0x4, size 0x4
    int mOffset; // offset 0x8, size 0x4
    class list mDisabled; // offset 0xC, size 0x8
};
class ListScrollStartMsg : public Message {
    // total size: 0x8
};
class ListScrollMsg : public Message {
    // total size: 0x8
};
class UIList : public UIComponent, public ListProvider, public ScrollSelect {
    // total size: 0x2A0
public:
    class String printMsg; // offset 0x140, size 0xC
protected:
    class ListDisplay mDisplay; // offset 0x14C, size 0x60
    class ListState mListState; // offset 0x1AC, size 0x88
private:
    class DataProvider * mDataProvider; // offset 0x234, size 0x4
    int mDummyNumData; // offset 0x238, size 0x4
    unsigned char mPaginate; // offset 0x23C, size 0x1
    class User * mUser; // offset 0x240, size 0x4
    class UIList * mParent; // offset 0x244, size 0x4
    float mAutoScrollPause; // offset 0x248, size 0x4
    int mAutoScrollDirection; // offset 0x24C, size 0x4
    unsigned char mAutoScrolling; // offset 0x250, size 0x1
    float mNextScrollTime; // offset 0x254, size 0x4
    int mLastScrollDirection; // offset 0x258, size 0x4
};
class UISlider : public UIComponent, public ScrollSelect {
    // total size: 0x180
    int mCurrent; // offset 0x13C, size 0x4
    int mNumSteps; // offset 0x140, size 0x4
    unsigned char mVertical; // offset 0x144, size 0x1
};
// Range: 0x80097F8C -> 0x80098098
void * ComponentScrollNetMsg::ComponentScrollNetMsg(class ComponentScrollNetMsg * const this /* r27 */, int playerNum /* r29 */, class UIComponent * c /* r28 */) {
    // Local variables
    class UIList * list; // r29
    class UISlider * slider; // r0

    // References
    // -> struct [anonymous] __RTTI__8UISlider;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__21ComponentScrollNetMsg;
}

// Range: 0x80098098 -> 0x80098120
void ComponentScrollNetMsg::Save(const class ComponentScrollNetMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x80098120 -> 0x80098190
void ComponentScrollNetMsg::Load(class ComponentScrollNetMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

class NetComponentScrollMsg : public Message {
    // total size: 0x8
};
static class NetComponentScrollMsg msg; // size: 0x8, address: 0x809778A8
// Range: 0x80098190 -> 0x8009873C
void ComponentScrollNetMsg::Dispatch(class ComponentScrollNetMsg * const this /* r30 */) {
    // Local variables
    class DataNode ret; // r1+0x60
    class UIPanel * p; // r0
    class UIComponent * c; // r28
    class UIList * list; // r0
    class UISlider * slider; // r0

    // References
    // -> struct [anonymous] __RTTI__8UISlider;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UIManager TheUI;
    // -> class UserMgr * TheUserMgr;
    // -> struct [anonymous] __vt__21NetComponentScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class NetComponentScrollMsg msg;
    // -> class NetSync * TheNetSync;
}

struct {
    // total size: 0x8
} __RTTI__8UISlider; // size: 0x8, address: 0x8087A4C8
struct {
    // total size: 0x8
} __RTTI__6UIList; // size: 0x8, address: 0x8087A528
struct {
    // total size: 0x8
} __RTTI__12ScrollSelect; // size: 0x8, address: 0x8087A540
struct {
    // total size: 0x8
} __RTTI__11UIComponent; // size: 0x8, address: 0x8087A588
struct {
    // total size: 0xC
} __vt__21NetComponentScrollMsg; // size: 0xC, address: 0x8087A590
struct {
    // total size: 0x8
} __RTTI__21NetComponentScrollMsg; // size: 0x8, address: 0x8087A5C0
struct {
    // total size: 0x28
} __vt__21ComponentScrollNetMsg; // size: 0x28, address: 0x8087A5C8
struct {
    // total size: 0x8
} __RTTI__21ComponentScrollNetMsg; // size: 0x8, address: 0x8087A618
struct {
    // total size: 0xC
} __vt__21NetComponentSelectMsg; // size: 0xC, address: 0x8087A620
struct {
    // total size: 0x8
} __RTTI__21NetComponentSelectMsg; // size: 0x8, address: 0x8087A650
struct {
    // total size: 0x28
} __vt__21ComponentSelectNetMsg; // size: 0x28, address: 0x8087A658
struct {
    // total size: 0x8
} __RTTI__21ComponentSelectNetMsg; // size: 0x8, address: 0x8087A6A8
struct {
    // total size: 0xC
} __vt__20NetComponentFocusMsg; // size: 0xC, address: 0x8087A6B0
struct {
    // total size: 0x8
} __RTTI__20NetComponentFocusMsg; // size: 0x8, address: 0x8087A6E0
struct {
    // total size: 0x28
} __vt__20ComponentFocusNetMsg; // size: 0x28, address: 0x8087A6E8
struct {
    // total size: 0x8
} __RTTI__20ComponentFocusNetMsg; // size: 0x8, address: 0x8087A738

