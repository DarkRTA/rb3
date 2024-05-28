#ifndef UI_UILISTSTATE_H
#define UI_UILISTSTATE_H

class UIListState {
public:
    UIListState(class UIListProvider*, class UIListStateCallback*);

    bool mCircular;
    int mNumDisplay;
    int mGridSpan;
    // TODO: fill out the rest
};

#endif
