#ifndef UI_UILISTSTATE_H
#define UI_UILISTSTATE_H
#include "ui/UIListProvider.h"
#include "types.h"
#include <vector>

class UIListStateCallback;

class UIListState { // 0x48
public:
    UIListState(class UIListProvider*, UIListStateCallback*);

    int Display2Showing(int) const;
    int Display2Data(int) const;
    int Showing2Data(int) const;
    int SelectedDisplay() const;
    bool IsScrolling() const;
    int MinDisplay() const;
    int MaxDisplay() const;
    float Speed() const;
    bool ScrollPastMinDisplay() const;
    bool ScrollPastMaxDisplay() const;
    bool CanScrollBack(bool) const;
    bool CanScrollNext(bool) const;
    float StepPercent() const;
    UIListProvider* Provider();
    UIListProvider* Provider() const;
    int WrapShowing(int) const;
    int NumDisplayWithData() const;
    void SetScrollPastMinDisplay(bool);
    void SetScrollPastMaxDisplay(bool);
    void SetMinDisplay(int);
    void SetMaxDisplay(int);
    int Selected() const;
    int SelectedData() const;
    void SetNumDisplay(int, bool);
    void SetGridSpan(int, bool);
    void SetSelected(int, int, bool);
    void SetCircular(bool, bool);
    void SetSpeed(float);
    void SetSelectedSimulateScroll(int);
    void SetProvider(UIListProvider*, RndDir*);
    void Scroll(int, bool);

    int NumShowing() const { return mProvider->NumData() - mHiddenData.size(); }

    bool mCircular; // 0x0
    int mNumDisplay; // 0x4
    int mGridSpan; // 0x8
    float mSpeed; // 0xc
    int mMinDisplay; // 0x10
    bool mScrollPastMinDisplay; // 0x14
    int mMaxDisplay; // 0x18
    bool mScrollPastMaxDisplay; // 0x1c
    UIListProvider* mProvider; // 0x20
    std::vector<int> mHiddenData; // 0x24
    int mFirstShowing; // 0x2c
    int mTargetShowing; // 0x30
    int mSelectedDisplay; // 0x34
    float mStepPercent; // 0x38
    float mStepTime; // 0x3c
    UIListStateCallback* mCallback; // 0x40
};

class UIListStateCallback {
public:
    UIListStateCallback() {}
    virtual ~UIListStateCallback() {}
    virtual void StartScroll(const UIListState&, int, bool) = 0;
    virtual void CompleteScroll(const UIListState&) = 0;
};

#endif
