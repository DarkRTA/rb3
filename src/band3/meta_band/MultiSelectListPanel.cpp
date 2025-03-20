#include "meta_band/MultiSelectListPanel.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/JoypadMsgs.h"
#include "ui/UIComponent.h"
#include "ui/UIList.h"
#include "ui/UIListDir.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

MultiSelectListPanel::MultiSelectListPanel()
    : mSelectionMesh(0), mScrollList(0), mStartSection(-1), mSpacing(0),
      mHeightMultiplier(0) {}

void MultiSelectListPanel::FinishLoad() {
    UIPanel::FinishLoad();
    mSelectionMesh = mDir->Find<RndMesh>("full_selection.mesh", true);
    mScrollList = mDir->Find<UIList>("sel_section.lst", true);
    mStartSection = -1;
    mSpacing = mScrollList->GetUIListDir()->ElementSpacing();
    mSelectionMesh->SetShowing(false);
    Transform tf(mSelectionMesh->LocalXfm());
    mHeightMultiplier = 1.0f / tf.m.z.z;
    mSelectionStart = tf.v;
}

void MultiSelectListPanel::Unload() {
    UIPanel::Unload();
    mSelectionMesh = nullptr;
    mScrollList = nullptr;
}

void MultiSelectListPanel::ResetSelectRect(int i1) {
    float fset = mSpacing * (float)i1 * mHeightMultiplier;
    fset = mSelectionMesh->Verts(0).pos.z - fset;
    mSelectionMesh->Verts(1).pos.z = fset;
    mSelectionMesh->Verts(3).pos.z = fset;
    mSelectionMesh->Sync(0x1F);
}

void MultiSelectListPanel::FakeComponentSelect() {
    OnMsg(UIComponentSelectMsg(nullptr, nullptr));
}

void MultiSelectListPanel::FakeComponentScroll() {
    OnMsg(UIComponentScrollMsg(nullptr, nullptr));
}

DataNode MultiSelectListPanel::OnMsg(const UIComponentSelectMsg &) {
    if (mStartSection == -1) {
        mStartSection = mScrollList->Selected();
        if (mStartSection == 0) {
            mSelectionMesh->SetShowing(false);
        } else {
            mSelectionMesh->SetShowing(true);
            Vector3 v(mSelectionStart);
            v.z = -(mSpacing * mScrollList->SelectedDisplay() - v.z);
            mSelectionMesh->SetLocalPos(v);
            ResetSelectRect(1);
        }
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode MultiSelectListPanel::OnMsg(const UIComponentScrollMsg &) {
    if (mScrollList->Selected() < mStartSection) {
        mStartSection = -1;
        mSelectionMesh->SetShowing(false);
        return 1;
    } else if (mStartSection != -1) {
        int i1 = mScrollList->FirstShowing();
        i1 = (mStartSection - i1) + 2;
        if (i1 < 0)
            i1 = 0;
        int i2 = mScrollList->SelectedDisplay();
        Vector3 v(mSelectionStart);
        v.z = -(mSpacing * i1 - v.z);
        mSelectionMesh->SetLocalPos(v);
        ResetSelectRect((i2 - i1) + 1);
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode MultiSelectListPanel::OnMsg(const ButtonDownMsg &) {
    return DataNode(kDataUnhandled, 0);
}

void MultiSelectListPanel::UnChoose() {
    int i1 = Min(mStartSection, mScrollList->GetListState().FirstShowing());
    mScrollList->SetSelected(mStartSection, i1);
    mStartSection = -1;
    mSelectionMesh->SetShowing(false);
}

BEGIN_HANDLERS(MultiSelectListPanel)
    HANDLE_ACTION(un_choose, UnChoose())
    HANDLE_ACTION(fake_component_select, FakeComponentSelect())
    HANDLE_ACTION(fake_component_scroll, FakeComponentScroll())
    HANDLE_MESSAGE(UIComponentSelectMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xAA)
END_HANDLERS