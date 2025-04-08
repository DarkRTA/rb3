#include "midi/MidiParserMgr.h"
#include "midi/MidiConstants.h"
#include "os/Debug.h"
#include "obj/DataFile.h"
#include "obj/Dir.h"
#include "midi/MidiParser.h"
#include "utl/TimeConversion.h"
#include "beatmatch/GemListInterface.h"
#include "utl/Symbols.h"

MidiParserMgr *TheMidiParserMgr;

static inline const char *GetBeatMatcherStr() { return "beatmatcher"; }
static inline const char *GetMidiParsersStr() { return "midi_parsers"; }

inline DataArray *MidiParserArray() {
    return SystemConfig(GetBeatMatcherStr())->FindArray(GetMidiParsersStr(), false);
}

MidiParserMgr::MidiParserMgr(GemListInterface *gListInt, Symbol sym)
    : mGems(gListInt), mLoaded(0), mFilename(0), mTrackName(), mSongName(), mTrackNames(),
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
    MidiParser::ClearManagedParsers();
    TheMidiParserMgr = nullptr;
}

void MidiParserMgr::Reset(int i) {
    if (mLoaded && unk59) {
        float beat = TickToBeat(i);
        FOREACH_CONST (it, MidiParser::sParsers) {
            (*it)->Reset(beat);
        }
    }
}

void MidiParserMgr::Reset() {
    if (mLoaded) {
        FOREACH_CONST (it, MidiParser::sParsers) {
            (*it)->Reset(-2 * kHugeFloat);
        }
    }
}

void MidiParserMgr::Poll() {
    if (unk59) {
        FOREACH_CONST (it, MidiParser::sParsers) {
            (*it)->Poll();
        }
    }
}

void MidiParserMgr::FreeAllData() {
    ClearAndShrink(mText);
    ClearAndShrink(mNoteOns);
}

void MidiParserMgr::OnNewTrack(int) {
    MemDoTempAllocations m(true, false);
    MILO_ASSERT(!mSongName.Null(), 0x7C);
    FreeAllData();
    mNoteOns.resize(128);
    mText.reserve(2000);
    unk58 = true;
}

void MidiParserMgr::OnEndOfTrack() {
    if (!mTrackName.Null()) {
        if (mText.size() > 2000) {
            MILO_WARN(
                "%s track %s has %d text events which is over the limit of %d, if that is correct contact James to increase kMaxTextSize",
                mFilename,
                mTrackName,
                mText.size(),
                2000
            );
        }
        if (mGems)
            mGems->SetTrack(mTrackName);
        FOREACH_CONST (it, MidiParser::sParsers) {
            MidiParser *cur = *it;
            if (cur->TrackName() == mTrackName) {
                int numnotes = cur->ParseAll(mGems, mText);
                if (numnotes > 20000) {
                    MILO_WARN(
                        "%s track %s has %d notes which is over the limit of %d, if that is correct contact James to increase kMaxNoteSize",
                        mFilename,
                        mTrackName,
                        numnotes,
                        20000
                    );
                }
            }
        }
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
    int tick, unsigned char status, unsigned char data1, unsigned char data2
) {
    int i28;
    bool created = CreateNote(tick, status, data1, i28);
    if (created) {
        FOREACH_CONST (it, MidiParser::sParsers) {
            MidiParser *cur = *it;
            if (cur->TrackName() == mTrackName) {
                cur->ParseNote(i28, tick, data1);
            }
        }
    }
}

char *MidiParserMgr::StripEndBracket(char *c1, const char *cc2) {
    char *ret = c1;
    const char *ptr;
    for (ptr = cc2; *ptr != '\0' && *ptr != ']'; ptr++) {
        *ret++ = *ptr;
    }

    if (*ptr == '\0') {
        MILO_WARN(
            "MidiParser: %s, track %s event \"%s\" is missing right bracket",
            mFilename,
            mTrackName,
            cc2
        );
    }

    *ret = '\0';
    return c1;
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
    if (std::find(mTrackNames.begin(), mTrackNames.end(), s) != mTrackNames.end()) {
        FOREACH_CONST (it, MidiParser::sParsers) {
            MidiParser *cur = *it;
            if (cur->TrackName() == s) {
                cur->Clear();
            }
        }
    } else
        mTrackNames.push_back(s);
    mTrackName = s;
}

void MidiParserMgr::OnText(int tick, const char *text, unsigned char type) {
    if (type == kTrackname)
        OnTrackName(text);
    else if (type == kLyricEvent || type == kTextEvent) {
        MemDoTempAllocations m(true, false);
        MidiParser::VocalEvent vocEv;
        vocEv.mTick = tick;
        if (*text == '[') {
            DataArray *parsed = ParseText(text, tick);
            if (!parsed)
                return;
            vocEv.mTextContent = DataNode(parsed, kDataArray);
            parsed->Release();
        } else
            vocEv.mTextContent = text;
        mText.push_back(vocEv);
    }
}

bool MidiParserMgr::CreateNote(
    int tick, unsigned char status, unsigned char data1, int &start_tick
) {
    if (mNoteOns.empty()) {
        if (unk58) {
            MILO_WARN("%s has a track that was not named.", mFilename);
            unk58 = false;
        }
        return true;
    } else {
        switch (MidiGetType(status)) {
        case kNoteOn:
            if (mNoteOns[data1] == -1) {
                mNoteOns[data1] = tick;
            } else
                Error(MakeString("Double note-on (%d)", data1), tick);
            break;
        case kNoteOff:
            int onTick = mNoteOns[data1];
            if (onTick == -1) {
                Error(MakeString("Double note-off (%d)", data1), tick);
            } else {
                mNoteOns[data1] = -1;
                start_tick = onTick;
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
    FOREACH_CONST (it, MidiParser::sParsers) {
        if (s == (*it)->Name())
            return *it;
    }
    return nullptr;
}

BEGIN_PROPSYNCS(MidiParserMgr)
    SYNC_PROP(song_name, mSongName)
END_PROPSYNCS
