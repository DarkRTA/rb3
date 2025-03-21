#include "meta_band/PatchSelectPanel.h"
#include "bandobj/PatchDir.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/EditSetlistPanel.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Mat.h"
#include "tour/TourBand.h"
#include "ui/UIGridProvider.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

PatchSelectPanel::PatchSelectPanel()
    : mPatchProvider(0), mGridProvider(0), mPatchList(0), mDescriptor(0),
      mSourceProfile(0), mStartingPatchIx(-1), mStartWithMenu(0) {}

void PatchSelectPanel::Enter() { UIPanel::Enter(); }
void PatchSelectPanel::Draw() { UIPanel::Draw(); }

void PatchSelectPanel::Load() {
    UIPanel::Load();
    if (!mDescriptor) {
        MILO_FAIL("PatchSelectPanel must have a patch to edit!");
    }
    if (!mSourceProfile) {
        MILO_FAIL("PatchSelectPanel must have a profile to pull from!");
    }
    mPatchProvider = new PatchProvider(mSourceProfile->mPatches);
    mGridProvider = new UIGridProvider(mPatchProvider, 3);
}

void PatchSelectPanel::FinishLoad() {
    mPatchList = mDir->Find<UIList>("patch.lst", true);
    mPatchList->SetProvider(mGridProvider);
    UIPanel::FinishLoad();
}

void PatchSelectPanel::Unload() {
    RELEASE(mGridProvider);
    RELEASE(mPatchProvider);
    mPatchList = nullptr;
    UIPanel::Unload();
}

int PatchSelectPanel::DuplicatePatch(PatchDir *dir) {
    MILO_ASSERT(mSourceProfile, 0xC9);
    PatchDir *emptyDir = mSourceProfile->GetFirstEmptyPatch();
    if (emptyDir) {
        emptyDir->Copy(dir, kCopyDeep);
        int ix = mSourceProfile->GetPatchIndex(emptyDir);
        MILO_ASSERT(ix >= 0, 0xD0);
        return ix;
    } else
        return -1;
}

void PatchSelectPanel::SetupForBandLogo(BandProfile *p) {
    SetDescriptor(p->GetTourBand()->GetLogo());
    mSourceProfile = p;
}

void PatchSelectPanel::SetupForSetlistArt(EditSetlistPanel *e, BandProfile *p) {
    SetDescriptor(&e->mSetlistArt);
    mSourceProfile = p;
}

void PatchSelectPanel::SetupForCharacterPatch() {
    ClosetMgr *pClosetMgr = ClosetMgr::GetClosetMgr();
    MILO_ASSERT(pClosetMgr, 0xE8);
    SetDescriptor(&pClosetMgr->unk50);
    MILO_ASSERT(mDescriptor, 0xEB);
    mSourceProfile = pClosetMgr->GetProfile();
    MILO_ASSERT(mSourceProfile, 0xEE);
}

void PatchSelectPanel::SetDescriptor(PatchDescriptor *d) {
    mDescriptor = d;
    mStartWithMenu = false;
    if (d->patchType == 0) {
        mStartingPatchIx = -1;
    } else
        mStartingPatchIx = d->patchIndex;
}

void PatchSelectPanel::Confirm(int i1) {
    MILO_ASSERT(mDescriptor, 0xFD);
    int i3 = i1 >= 0;
    if (mSourceProfile && mSourceProfile->GetTourBand()->GetLogo() == mDescriptor) {
        mSourceProfile->GetTourBand()->ChooseBandLogo(i3, i1);
    } else {
        mDescriptor->patchType = i3;
        mDescriptor->patchIndex = i1;
    }
}

BEGIN_HANDLERS(PatchSelectPanel)
    HANDLE_EXPR(patch_dir, mPatchProvider->GetPatchDir(_msg->Int(2)))
    HANDLE_EXPR(has_any_patches, mPatchProvider->HasAnyPatches())
    HANDLE_EXPR(duplicate_patch, DuplicatePatch(_msg->Obj<PatchDir>(2)))
    HANDLE_ACTION(select_patch, mGridProvider->SetListToData(mPatchList, _msg->Int(2) + 1))
    HANDLE_EXPR(
        selected_patch,
        mPatchProvider->GetPatchDir(mGridProvider->GetDataFromList(mPatchList))
    )
    HANDLE_EXPR(selected_patch_ix, mGridProvider->GetDataFromList(mPatchList) - 1)
    HANDLE_ACTION(setup_for_band_logo, SetupForBandLogo(_msg->Obj<BandProfile>(2)))
    HANDLE_ACTION(
        setup_for_setlist_art,
        SetupForSetlistArt(_msg->Obj<EditSetlistPanel>(2), _msg->Obj<BandProfile>(3))
    )
    HANDLE_ACTION(setup_for_character_patch, SetupForCharacterPatch())
    HANDLE_ACTION(confirm, Confirm(_msg->Int(2)))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x129)
END_HANDLERS

BEGIN_PROPSYNCS(PatchSelectPanel)
    SYNC_PROP_SET(starting_patch_ix, mStartingPatchIx, mStartingPatchIx = _val.Int())
    SYNC_PROP_SET(start_with_menu, mStartWithMenu, mStartWithMenu = _val.Int())
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS

inline bool PatchProvider::HasAnyPatches() const {
    for (int i = 0; i < mPatches.size(); i++) {
        PatchDir *patch = mPatches[i];
        MILO_ASSERT(patch, 0x82);
        if (patch->HasLayers())
            return true;
    }
    return false;
}

inline PatchDir *PatchProvider::GetPatchDir(int idx) const {
    if (idx == 0)
        return nullptr;
    else {
        PatchDir *patch = mPatches[idx - 1];
        MILO_ASSERT(patch, 0x78);
        return patch;
    }
}

inline int PatchProvider::NumData() const { return mPatches.size() + 1; }

inline RndMat *PatchProvider::Mat(int, int idx, UIListMesh *slot) const {
    if (slot->Matches("patch")) {
        if (idx == 0)
            return mEmptyMat;
        else {
            PatchDir *patch = GetPatchDir(idx);
            if (patch->HasLayers()) {
                return unk24[idx - 1];
            } else
                return nullptr;
        }
    } else
        return slot->DefaultMat();
}

inline void PatchProvider::Text(int, int idx, UIListLabel *slot, UILabel *label) const {
    if (idx == 0)
        label->SetTextToken(shell_no_patch);
    else if (slot->Matches("patch_name") && !GetPatchDir(idx)->HasLayers()) {
        label->SetTextToken(shell_new_patch);
    } else
        label->SetTextToken(gNullStr);
}

inline void PatchProvider::InitData(RndDir *dir) {
    DeleteAll(unk24);
    mEmptyMat = dir->Find<RndMat>("patch.mat", true);
    for (int i = 0; i < mPatches.size(); i++) {
        RndMat *newMat = Hmx::Object::New<RndMat>();
        newMat->Copy(mEmptyMat, kCopyShallow);
        newMat->SetDiffuseTex(mPatches[i]->GetTex());
        newMat->SetAlphaCut(true);
        newMat->SetAlphaThreshold(false);
        unk24.push_back(newMat);
    }
}