#include "meta_band/VoiceoverPanel.h"
#include "meta_band/BandSongMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/ContentMgr.h"
#include "os/ContentMgr_Wii.h"
#include "os/Debug.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

VoiceoverPanel::VoiceoverPanel()
    : mVoiceOver(Hmx::Object::New<BinkClip>()), mFader(Hmx::Object::New<Fader>()),
      mVolumeOffsetSymbol(0), mWaitingForLoad(0), mWaitingForMount(0), mLoadingFailed(0),
      mDLCName(0), mDLCVoiceoverPath(0) {
    mVoiceOver->AddFader(mFader);
    mVoiceOver->UnloadWhenFinishedPlaying(true);
    TheContentMgr->RegisterCallback(this, false);
}

VoiceoverPanel::~VoiceoverPanel() {
    RELEASE(mVoiceOver);
    RELEASE(mFader);
    TheContentMgr->UnregisterCallback(this, false);
}

void VoiceoverPanel::Unload() {
    UIPanel::Unload();
    if (mVoiceOver && ShouldFade() && !ShouldHandleFadeOutOnExit()) {
        FadeOutVoiceover();
    }
}

void VoiceoverPanel::Exit() {
    UIPanel::Exit();
    if (mVoiceOver && ShouldFade() && ShouldHandleFadeOutOnExit()) {
        FadeOutVoiceover();
    }
}

void VoiceoverPanel::PollForLoading() {
    UpdateVoiceoverState();
    UIPanel::PollForLoading();
}

void VoiceoverPanel::Poll() {
    UIPanel::Poll();
    UpdateVoiceoverState();
}

void VoiceoverPanel::UpdateVoiceoverState() {
    if (mWaitingForLoad && !mWaitingForMount) {
        MILO_ASSERT(mVoiceOver, 0x5C);
        if (mVoiceOver->IsReadyToPlay()) {
            mVoiceOver->Play();
            mWaitingForLoad = false;
        }
    }
}

void VoiceoverPanel::ContentMounted(const char *contentName, const char *) {
    MILO_ASSERT(contentName, 0x68);
    Symbol s1 = contentName;
    if (s1 == mDLCName) {
        mDLCName = 0;
        SetVoiceoverFile(mDLCVoiceoverPath.c_str(), s1);
    }
}

void VoiceoverPanel::ContentFailed(const char *contentName) {
    MILO_ASSERT(contentName, 0x76);
    Symbol s1 = contentName;
    if (s1 == mDLCName) {
        mLoadingFailed = true;
        mDLCName = 0;
    }
}

void VoiceoverPanel::SetVoiceoverFile(const char *cc, Symbol s) {
    mWaitingForLoad = true;
    mLoadingFailed = false;
    char buf[128];
    strcpy(buf, cc);
    char *str = strstr(buf, "mogg");
    if (str) {
        str[0] = 'b';
        str[1] = 'i';
        str[2] = 'k';
        str[3] = '\0';
    }

    if (!s.Null()) {
        const char *name = TheSongMgr.ContentName(s, true);
        if (name) {
            TheWiiContentMgr.UnmountContents(name);
            if (!TheContentMgr->MountContent(name)) {
                mDLCName = name;
                mDLCVoiceoverPath = buf;
                mWaitingForMount = true;
                return;
            }
        }
    }
    mWaitingForMount = false;
    mVoiceOver->SetFile(buf);
}

void VoiceoverPanel::SetVoiceoverSymbol(Symbol s) {
    DataArray *cfg = SystemConfig("voiceovers");
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *cur = cfg->Array(i);
        if (cur->Sym(0) == s) {
            SetVoiceoverFile(cur->Str(1), 0);
            return;
        }
    }
    String str(s);
    std::vector<String> substrings;
    if (str.split("|", substrings) > 0) {
        if (substrings.size() != 4) {
            MILO_FAIL("Voiceover Symbol unrecognized: %s", s.Str());
        }
        Symbol s40(substrings[1].c_str());
        Symbol s44(substrings[2].c_str());
        strtol(substrings[3].c_str(), nullptr, 10);
        SetVoiceoverFile("", s40);
    } else {
        MILO_FAIL("Voiceover Symbol not found: %s", s.Str());
    }
}

void VoiceoverPanel::PlayVoiceover() {
    MILO_ASSERT(mVoiceOver, 0xE3);
    if (mVoiceOver->IsReadyToPlay()) {
        mVoiceOver->Play();
        mWaitingForLoad = false;
    } else {
        mWaitingForLoad = true;
    }
}

void VoiceoverPanel::FadeOutVoiceover() {
    if (mWaitingForLoad) {
        mVoiceOver->SetFile("");
        mWaitingForLoad = false;
    } else {
        DataArray *cfg = SystemConfig("voiceover_fade_duration");
        mVoiceOver->FadeOut(cfg->Float(1));
    }
}

void VoiceoverPanel::SetVolumeOffsetSymbol(Symbol s) {
    mVolumeOffsetSymbol = s;
    UpdateVolumeOffset();
}

void VoiceoverPanel::UpdateVolumeOffset() {
    if (!mVolumeOffsetSymbol.Null()) {
        DataArray *cfg = SystemConfig(mVolumeOffsetSymbol.Str());
        mFader->SetVal(cfg->Float(1));
    }
}

BEGIN_HANDLERS(VoiceoverPanel)
    HANDLE_ACTION(set_voiceover_symbol, SetVoiceoverSymbol(_msg->Sym(2)))
    HANDLE_ACTION(play_voiceover, PlayVoiceover())
    HANDLE_ACTION(set_volume_offset_symbol, SetVolumeOffsetSymbol(_msg->Sym(2)))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x125)
END_HANDLERS