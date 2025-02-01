#include "meta/CreditsPanel.h"
#include "ui/UIList.h"
#include "synth/Faders.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "ui/UIListLabel.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

CreditsPanel::CreditsPanel()
    : mLoader(0), mNames(0), mStream(0), mAutoScroll(1), mSavedSpeed(-1.0f), mPaused(0) {}

CreditsPanel::~CreditsPanel() {}

void CreditsPanel::Load() {
    UIPanel::Load();
    mLoader =
        new DataLoader(FilePath(SystemConfig("credits_file")->Str(1)), kLoadFront, true);
}

bool CreditsPanel::IsLoaded() const { return UIPanel::IsLoaded() && mLoader->IsLoaded(); }

void CreditsPanel::FinishLoad() {
    UIPanel::FinishLoad();
    mNames = mLoader->Data();
    MILO_ASSERT(mNames, 0x35);
    mNames->AddRef();
    mList = mDir->Find<UIList>("credits.lst", true);
    mList->SetProvider(this);
    delete mLoader;
    mLoader = 0;
}

void CreditsPanel::Exit() {
    if (mStream && !mPaused) {
        mStream->Faders()->FindLocal("fade", true)->DoFade(-96.0f, 2000.0f);
    }
    UIPanel::Exit();
}

// fn_8050C398
bool CreditsPanel::Exiting() const {
    return mStream && mStream->Faders()->FindLocal("fade", true)->IsFading()
        || UIPanel::Exiting();
}

void CreditsPanel::Unload() {
    UIPanel::Unload();
    if (mNames) {
        mNames->Release();
        mNames = 0;
    }
    RELEASE(mStream);
}

void CreditsPanel::Enter() {
    UIPanel::Enter();
#ifdef MILO_DEBUG
    mCheatOn = false;
#endif
    mPaused = false;
    mList->SetSelected(0, -1);
    mAutoScroll = true;
    mList->AutoScroll();
}

void CreditsPanel::Poll() {
    UIPanel::Poll();
    if (!mStream) {
        mStream = TheSynth->NewStream("sfx/streams/credits", 0, 0, 0);
        MILO_ASSERT_FMT(mStream, "sfx/streams/credits.foo missing");
        mStream->SetJump(Stream::kStreamEndMs, 0, 0);
        mStream->SetPan(0, -1.0f);
        mStream->SetPan(1, 1.0f);
        mStream->SetVolume(-4.0f);
        mStream->Faders()->AddLocal("fade");
    } else {
        if (!mStream->IsPlaying() && mStream->IsReady() && !mPaused) {
            mStream->Play();
        }
    }
    if (mAutoScroll && !TheUI->InTransition()) {
        if (!mList->IsScrolling()) {
            HandleType(credits_done_msg);
            SetAutoScroll(false);
        }
    }
}

void CreditsPanel::SetAutoScroll(bool b) {
    if (b == mAutoScroll)
        return;
    mAutoScroll = b;
    if (mAutoScroll)
        mList->AutoScroll();
    else
        mList->StopAutoScroll();
}

void CreditsPanel::PausePanel(bool b) {
    if (mPaused != b) {
        mPaused = b;
        if (mPaused) {
            SetAutoScroll(false);
            if (mStream && !mStream->IsPaused()) {
                mStream->Stop();
            }
        } else {
            SetAutoScroll(true);
            if (mStream && mStream->IsPaused()) {
                mStream->Play();
            }
        }
    }
}

#ifdef MILO_DEBUG
void CreditsPanel::DebugToggleAutoScroll() {
    if (!mAutoScroll) {
        mList->SetSpeed(mSavedSpeed);
        SetAutoScroll(true);
        mCheatOn = false;
    } else {
        mSavedSpeed = mList->Speed();
        mList->SetSpeed(0.0f);
        SetAutoScroll(false);
        mCheatOn = true;
    }
}
#endif

BEGIN_HANDLERS(CreditsPanel)
    HANDLE_ACTION(pause_panel, PausePanel(_msg->Int(2)))
#ifdef MILO_DEBUG
    HANDLE_EXPR(is_cheat_on, mCheatOn)
#else
    HANDLE_EXPR(is_cheat_on, false)
#endif
#ifdef MILO_DEBUG
    HANDLE_ACTION(debug_toggle_autoscroll, DebugToggleAutoScroll())
#endif
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xD5)
END_HANDLERS

DataNode CreditsPanel::OnMsg(const ButtonDownMsg &msg) {
    if (!mAutoScroll)
        return DataNode(kDataUnhandled, 0);
    else
        return 1;
}

void CreditsPanel::Text(int i, int j, UIListLabel *listlabel, UILabel *label) const {
    DataArray *arr = mNames->Array(j);
    MILO_ASSERT(label, 0xE9);
    label->SetCreditsText(arr, listlabel);
}

RndMat *CreditsPanel::Mat(int i, int j, UIListMesh *mesh) const {
    DataArray *arr = mNames->Array(j);
    Symbol s = blank;
    if (arr->Size() != 0)
        s = arr->Sym(0);
    if (s == image) {
        return mDir->Find<RndMat>(arr->Str(1), true);
    } else
        return nullptr;
}

int CreditsPanel::NumData() const { return mNames->Size(); }