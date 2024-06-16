#include "ui/UIListDir.h"

UIListDir::UIListDir() : mOrientation(kUIListVertical), mFadeOffset(0), mElementSpacing(50.0f), mScrollHighlightChange(0.5f),
    mTestMode(0), mTestState(this, this), mTestNumData(100), mTestGapSize(0.0f), mTestComponentState(UIComponent::kFocused),
    mTestDisableElements(0), unk1fc(), unk204(0) {
    mTestState.SetNumDisplay(5, true);
    mTestState.SetGridSpan(1, true);
    mTestState.SetSelected(0, -1, true);
}

UIListDir::~UIListDir(){

}

UIListOrientation UIListDir::Orientation() const { return mOrientation; }
float UIListDir::ElementSpacing() const { return mElementSpacing; }