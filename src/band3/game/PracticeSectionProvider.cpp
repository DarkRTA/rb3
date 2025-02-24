#include "game/PracticeSectionProvider.h"
#include "game/GameConfig.h"
#include "meta_band/AppLabel.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "midi/MidiSectionLister.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/FileStream.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

PracticeSectionProvider::PracticeSectionProvider() {
    SetName("practice_section_provider", ObjectDir::sMainDir);
    mSections.reserve(100);
}

void PracticeSectionProvider::InitData(RndDir *) {
    mSections.clear();
    unk4c = 0;
    FileStream stream(
        TheSongMgr->MidiFile(MetaPerformer::Current()->Song()), FileStream::kRead, false
    );
    MidiSectionLister lister(&mSections, stream);
    unk28.unk0 = "full_song";
    unk28.unk4 = 0;
    unk28.unkc = 0;
    unk28.unk8 = lister.GetLastMidiMsgTick();
    unk28.unk10 = lister.GetEndMs();
    unk28.unk14 = false;
    unk28.unk18 = 0;
    unk28.unk1c = 0;
    unk28.unk20 = 0;
    if (mSections.empty())
        return;
    else {
        for (int i = 0; i < mSections.size(); i++) {
            if (i != mSections.size() - 1U) {
                mSections[i].unk8 = mSections[i + 1].unk4;
                mSections[i].unk10 = mSections[i + 1].unkc;
            } else {
                mSections[i].unk8 = unk28.unk8;
                mSections[i].unk10 = unk28.unk10;
            }
            mSections[i].unk14 = 0;
        }
    }
}

void PracticeSectionProvider::Text(int, int idx, UIListLabel *, UILabel *label) const {
    AppLabel *app_label = dynamic_cast<AppLabel *>(label);
    MILO_ASSERT(app_label, 0xD0);
    app_label->SetSectionName(GetSection(idx - 1));
}

Symbol PracticeSectionProvider::DataSymbol(int idx) const {
    return GetSection(idx - 1).unk0;
}

int PracticeSectionProvider::DataIndex(Symbol s) const {
    for (int i = 0; i < NumData(); i++) {
        if (DataSymbol(i) == s)
            return i;
    }
    return -1;
}

const PracticeSection &PracticeSectionProvider::GetSection(int idx) const {
    if (idx >= (int)mSections.size()) {
        idx = mSections.size() - 1;
    }
    if (idx >= 0) {
        return mSections[idx];
    } else
        return unk28;
}

Symbol PracticeSectionProvider::SectionAfterLast() {
    int sects = TheGameConfig->Property("practice_sections", true)->Array()->Int(1);
    if (sects == -1 || sects == mSections.size() - 1)
        return Symbol();
    else
        return mSections[sects + 1].unk0;
}

bool PracticeSectionProvider::IsActive(int idx) const {
    if (idx < unk4c)
        return false;
    else if (idx > 0 && mSections[idx - 1].unk14)
        return false;
    else
        return true;
}

UIColor *
PracticeSectionProvider::SlotColorOverride(int, int, UIListWidget *, UIColor *c) const {
    return c;
}

float PracticeSectionProvider::GetSectionStartMs(int idx) const {
    if (idx >= (int)mSections.size()) {
        idx = mSections.size() - 1;
    }
    if (idx == -1)
        return unk28.unkc;
    else
        return mSections[idx].unkc;
}

float PracticeSectionProvider::GetSectionEndMs(int idx) const {
    if (idx >= (int)mSections.size()) {
        idx = mSections.size() - 1;
    }
    if (idx == -1)
        return unk28.unk10;
    else
        return mSections[idx].unk10;
}

BEGIN_HANDLERS(PracticeSectionProvider)
    HANDLE_EXPR(section_after_last, SectionAfterLast())
    HANDLE_ACTION(set_start_section, unk4c = _msg->Int(2) + 1)
    HANDLE_ACTION(init_sections, InitData(nullptr))
    HANDLE_EXPR(get_section_start_ms, GetSectionStartMs(_msg->Int(2)))
    HANDLE_EXPR(get_section_end_ms, GetSectionEndMs(_msg->Int(2)))
    HANDLE_EXPR(num_data, NumData())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x155)
END_HANDLERS