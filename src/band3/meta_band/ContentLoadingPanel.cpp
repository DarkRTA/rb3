#include "meta_band/ContentLoadingPanel.h"
#include "bandobj/MeterDisplay.h"
#include "obj/ObjMacros.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UITrigger.h"
#include "utl/Locale.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

ContentLoadingPanel::ContentLoadingPanel()
    : unk3c(0), unk40(0), unk44(0), mProgressLabel(0), mMessageLabel(0), mFindingTrig(0),
      mLoadingTrig(0) {
    TheContentMgr->RegisterCallback(this, false);
    SetShowing(false);
}

ContentLoadingPanel::~ContentLoadingPanel() {
    TheContentMgr->UnregisterCallback(this, false);
}

void ContentLoadingPanel::ContentStarted() {
    unk3c = 0;
    mMessageLabel->SetTextToken(finding_additional_content);
    mProgressLabel->SetTokenFmt(finding_additional_progress, LocalizeSeparatedInt(unk3c));
    mFindingTrig->Trigger();
    SetBlocking(false);
    ShowIfPossible();
}

bool ContentLoadingPanel::ContentDiscovered(Symbol) {
    unk3c++;
    mProgressLabel->SetTokenFmt(finding_additional_progress, LocalizeSeparatedInt(unk3c));
    return true;
}

void ContentLoadingPanel::ContentMountBegun(int n) {
    unk40 = n;
    unk44 = 0;
    if (n > 0) {
        mLoadingTrig->Trigger();
        UpdateMeterValues();
        mMessageLabel->SetTextToken(loading_additional_content);
        mProgressLabel->SetTokenFmt(
            loading_additional_progress,
            LocalizeSeparatedInt(unk44),
            LocalizeSeparatedInt(unk40)
        );
        ShowIfPossible();
    }
}

void ContentLoadingPanel::ContentMounted(const char *, const char *) {
    unk44++;
    mProgressLabel->SetTokenFmt(
        loading_additional_progress,
        LocalizeSeparatedInt(unk44),
        LocalizeSeparatedInt(unk40)
    );
    ShowIfPossible();
}

void ContentLoadingPanel::ContentFailed(const char *) {
    unk44++;
    mProgressLabel->SetTokenFmt(
        loading_additional_progress,
        LocalizeSeparatedInt(unk44),
        LocalizeSeparatedInt(unk40)
    );
    ShowIfPossible();
}

void ContentLoadingPanel::ContentDone() {
    unk44 = 0;
    unk40 = 0;
    if (Showing())
        Exit();
}

void ContentLoadingPanel::Poll() {
    MILO_ASSERT(Showing(), 0x81);
    UIPanel::Poll();
    UpdateMeterValues();
    if (Showing() && TheUI.InTransition()) {
        SetBlocking(true);
    }
    if (GetState() != kUp && !Exiting()) {
        SetShowing(false);
    }
}

void ContentLoadingPanel::FinishLoad() {
    UIPanel::FinishLoad();
    mProgressLabel = mDir->Find<UILabel>("progress.lbl", true);
    mMessageLabel = mDir->Find<UILabel>("message.lbl", true);
    mFindingTrig = mDir->Find<UITrigger>("finding.trg", true);
    mLoadingTrig = mDir->Find<UITrigger>("loading.trg", true);
}

void ContentLoadingPanel::ShowIfPossible() {
    if (!mShowing && TheContentMgr->ShowCurRefreshProgress()) {
        MILO_ASSERT(IsLoaded(), 0xA0);
        mShowing = true;
        Enter();
    }
}

void ContentLoadingPanel::SetBlocking(bool b) {
    const char *matname = b ? "redmask.mat" : "blackmask.mat";
    RndMat *mat = mDir->Find<RndMat>(matname, true);
    RndMesh *mesh = mDir->Find<RndMesh>("mask.mesh", true);
    mesh->SetMat(mat);
}

void ContentLoadingPanel::UpdateMeterValues() {
    MeterDisplay *disp = mDir->Find<MeterDisplay>("progress.md", true);
    if (unk40 == 0) {
        disp->SetValues(1, 1);
    } else
        disp->SetValues(unk44, unk40);
}

BEGIN_HANDLERS(ContentLoadingPanel)
    HANDLE_ACTION(set_blocking, SetBlocking(_msg->Int(2)))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xBF)
END_HANDLERS