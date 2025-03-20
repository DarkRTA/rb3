#pragma once
#include "os/JoypadMsgs.h"
#include "rndobj/Mesh.h"
#include "ui/UIComponent.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"

class MultiSelectListPanel : public UIPanel {
public:
    MultiSelectListPanel();
    OBJ_CLASSNAME(MultiSelectListPanel);
    OBJ_SET_TYPE(MultiSelectListPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~MultiSelectListPanel() {}
    virtual void Unload();
    virtual void FinishLoad();

    void ResetSelectRect(int);
    void FakeComponentSelect();
    void FakeComponentScroll();
    void UnChoose();
    DataNode OnMsg(const UIComponentSelectMsg &);
    DataNode OnMsg(const UIComponentScrollMsg &);
    DataNode OnMsg(const ButtonDownMsg &);

    RndMesh *mSelectionMesh; // 0x38
    UIList *mScrollList; // 0x3c
    int mStartSection; // 0x40
    float mSpacing; // 0x44
    float mHeightMultiplier; // 0x48
    Vector3 mSelectionStart; // 0x4c
};