#include "midi/MidiParserMgr.h"
#include "midi/MidiConstants.h"
#include "os/Debug.h"
#include "obj/DataFile.h"
#include "obj/Dir.h"
#include "midi/MidiParser.h"
#include "utl/TimeConversion.h"
#include "beatmatch/GemListInterface.h"
#include "utl/Symbols.h"

#define FOREACH_MIDIPARSER(code)                                                         \
    const std::list<MidiParser *> &parsers = MidiParser::sParsers;                       \
    for (std::list<MidiParser *>::const_iterator it = parsers.begin();                   \
         it != parsers.end();                                                            \
         ++it) {                                                                         \
        code;                                                                            \
    }

MidiParserMgr *TheMidiParserMgr;

static inline const char *GetBeatMatcherStr() { return "beatmatcher"; }
static inline const char *GetMidiParsersStr() { return "midi_parsers"; }

inline DataArray *MidiParserArray() {
    return SystemConfig(GetBeatMatcherStr())->FindArray(GetMidiParsersStr(), false);
}

MidiParserMgr::MidiParserMgr(GemListInterface *gListInt, Symbol sym)
    : mGems(gListInt), mLoaded(0), mFilename(0), mTrackName(), mSongName(), unk50(),
      unk58(true), unk59(true) {
    MILO_ASSERT(!TheMidiParserMgr, 0x27);
    TheMidiParserMgr = this;
    SetName("midiparsermgr", ObjectDir::sMainDir);
    mSongName = sym;
    MidiParser::Init();
    DataArray *arr = MidiParserArray();
    if (arr) {
        DataArray *initArr = arr->FindArray("init", false);
        if (initArr)
            initArr->ExecuteScript(1, this, 0, 1);
        else
            MILO_WARN(
                "Could not find init block in midi parser array, no parsers will be constructed"
            );
    }
}

MidiParserMgr::~MidiParserMgr() {
    ClearManagedParsers();
    TheMidiParserMgr = nullptr;
}

void MidiParserMgr::Reset(int i) {
    if (mLoaded && unk59) {
        float beat = TickToBeat(i);
        FOREACH_MIDIPARSER((*it)->Reset(beat);)
    }
}

void MidiParserMgr::Reset() {
    if (mLoaded) {
        FOREACH_MIDIPARSER((*it)->Reset(-2 * kHugeFloat);)
    }
}

void MidiParserMgr::Poll() {
    if (unk59) {
        FOREACH_MIDIPARSER((*it)->Poll();)
    }
}

void MidiParserMgr::FreeAllData() {
    ClearAndShrink(unk30);
    ClearAndShrink(unk24);
}

void MidiParserMgr::OnNewTrack(int i) {
    MemDoTempAllocations m(true, false);
    MILO_ASSERT(!mSongName.Null(), 0x7C);
    FreeAllData();
    unk24.resize(128);
    unk30.reserve(2000);
    unk58 = true;
}

void MidiParserMgr::OnEndOfTrack() {
    if (!mTrackName.Null()) {
        if (unk30.size() > 2000) {
            MILO_WARN(
                "%s track %s has %d text events which is over the limit of %d, if that is correct contact James to increase kMaxTextSize",
                mFilename,
                mTrackName,
                unk30.size(),
                2000
            );
        }
        if (mGems)
            mGems->SetTrack(mTrackName);
        FOREACH_MIDIPARSER(MidiParser *cur = *it; if (cur->TrackName() == mTrackName) {
            int numnotes = cur->ParseAll(mGems, unk30);
            if (numnotes > 20000) {
                MILO_WARN(
                    "%s track %s has %d notes which is over the limit of %d, if that is correct contact James to increase kMaxNoteSize",
                    mFilename,
                    mTrackName,
                    numnotes,
                    20000
                );
            }
        })
        FreeAllData();
        mTrackName = Symbol("");
    }
}

void MidiParserMgr::OnAllTracksRead() {}

void MidiParserMgr::FinishLoad() {
    DataArray *arr = MidiParserArray();
    if (arr) {
        DataArray *finishArr = arr->FindArray("finish_loading", false);
        if (finishArr) {
            finishArr->ExecuteScript(1, this, 0, 1);
        }
    }
    mLoaded = true;
}

void MidiParserMgr::OnMidiMessage(
    int tick, unsigned char c1, unsigned char c2, unsigned char c3
) {
    int i28;
    bool created = CreateNote(tick, c1, c2, i28);
    if (created) {
        FOREACH_MIDIPARSER(MidiParser *cur = *it; if (cur->TrackName() == mTrackName) {
            cur->ParseNote(i28, tick, c2);
        })
    }
}

char *MidiParserMgr::StripEndBracket(char *c1, const char *cc2) {
    char *ret = c1;
    for (const char *ptr = cc2; *ptr != '\0'; ptr++) {
        char ptrChar = *ptr;
        if (ptrChar == ']')
            goto finalize;
        else
            *ret++ = ptrChar;
    }
    MILO_WARN(
        "MidiParser: %s, track %s event \"%s\" is missing right bracket",
        mFilename,
        mTrackName,
        cc2
    );
finalize:
    *ret = '\0';
    return ret;
}

DataArray *MidiParserMgr::ParseText(const char *str, int tick) {
    MILO_ASSERT(strlen(str) < 256, 0xF3);
    char buf[256];
    StripEndBracket(buf, str + 1);
    DataArray *parsed = nullptr;
    MILO_TRY { parsed = DataReadString(buf); }
    MILO_CATCH(errMsg) {
        parsed = nullptr;
        MILO_WARN(MakeString(
            "MidiParser: %s, track %s, tick %d, event \"%s\" has bad format: %s",
            TheMidiParserMgr->mFilename,
            mTrackName,
            tick,
            buf,
            errMsg
        ));
    }
    return parsed;
}

void MidiParserMgr::OnTrackName(Symbol s) {
    if (std::find(unk50.begin(), unk50.end(), s) != unk50.end()) {
        FOREACH_MIDIPARSER(MidiParser *cur = *it;
                           if (cur->TrackName() == s) { cur->Clear(); })
    } else
        unk50.push_back(s);
    mTrackName = s;
}

void MidiParserMgr::OnText(int i1, const char *cc, unsigned char uc) {
    if (uc == 3)
        OnTrackName(cc);
    else if (uc == 5 || uc == 1) {
        MemDoTempAllocations m(true, false);
        MidiParser::VocalEvent vocEv;
        vocEv.unk8 = i1;
        if (*cc == '[') {
            DataArray *parsed = ParseText(cc, i1);
            if (!parsed)
                return;
            vocEv.unk0 = DataNode(parsed, kDataArray);
            parsed->Release();
        } else
            vocEv.unk0 = cc;
        unk30.push_back(vocEv);
    }
}

bool MidiParserMgr::CreateNote(int i1, unsigned char uc1, unsigned char uc2, int &iref) {
    if (unk24.empty()) {
        if (unk58) {
            MILO_WARN("%s has a track that was not named.", mFilename);
            unk58 = false;
        }
        return true;
    } else {
        switch (MidiGetType(uc1)) {
        case 0x90:
            if (unk24[uc2] == -1) {
                unk24[uc2] = i1;
            } else
                Error(MakeString("Double note-on (%d)", uc2), i1);
            break;
        case 0x80:
            int ref = unk24[uc2];
            if (ref == -1) {
                Error(MakeString("Double note-off (%d)", uc2), i1);
            } else {
                unk24[uc2] = -1;
                iref = ref;
                return true;
            }
            break;
        default:
            break;
        }
        return false;
    }
}

void MidiParserMgr::SetMidiReader(MidiReader *mr) {
    MidiReceiver::SetMidiReader(mr);
    mFilename = mr->GetFilename();
}

DataEventList *MidiParserMgr::GetEventsList() {
    MidiParser *evParser = GetParser("events_parser");
    MILO_ASSERT(evParser, 0x17E);
    return evParser->Events();
}

MidiParser *MidiParserMgr::GetParser(Symbol s) {
    FOREACH_MIDIPARSER(if (s == (*it)->Name()) return *it;)
    return nullptr;
}

BEGIN_PROPSYNCS(MidiParserMgr)
    SYNC_PROP(song_name, mSongName)
END_PROPSYNCS