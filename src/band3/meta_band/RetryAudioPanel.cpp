#include "meta_band/RetryAudioPanel.h"
#include "ContextChecker.h"
#include "meta_band/VoiceoverPanel.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/Messages2.h"

RetryAudioPanel::RetryAudioPanel() : mFinished(0) {}

RetryAudioPanel::~RetryAudioPanel() {}

void RetryAudioPanel::PollForLoading() {
    UpdateVoiceoverState();
    bool done = !DoneLoading();
    if (!mFinished && done) {
        mFinished = true;
        Handle(handle_audio_finished_msg, true);
    }
}

bool RetryAudioPanel::IsLoaded() const {
    if (UIPanel::IsLoaded()) {
        return mFinished;
    } else
        return false;
}

inline static const char *VOContextStr() { return "vo_retry_context"; }

inline Symbol RetryAudioPanel::RandomVOContextItem() {
    DataArray *cfg = SystemConfig(VOContextStr());
    return RandomContextSensitiveItem(cfg, false);
}

void RetryAudioPanel::Load() {
    UIPanel::Load();
    mFinished = false;
    Symbol item = RandomVOContextItem();
    if (item != "") {
        SetVoiceoverSymbol(item);
        GetVoiceover()->SetPreLoad(false);
        PlayVoiceover();
    }
}

void RetryAudioPanel::Enter() { UIPanel::Enter(); }

BEGIN_HANDLERS(RetryAudioPanel)
    HANDLE_SUPERCLASS(VoiceoverPanel)
    HANDLE_CHECK(0x6B)
END_HANDLERS