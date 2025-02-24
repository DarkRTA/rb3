#pragma once
#include "game/PracticeSectionProvider.h"
#include "midi/Midi.h"
#include "utl/FileStream.h"
#include "utl/MeasureMap.h"
#include "utl/MultiTempoTempoMap.h"
#include <cstdio>

class MidiSectionLister : public MidiReceiver {
public:
    MidiSectionLister(std::vector<PracticeSection> *s, FileStream &stream)
        : mSectionList(0), mLastMidiMessageTick(0), mEndMs(0) {
        Init(s, stream);
    }
    virtual ~MidiSectionLister() {}
    virtual void OnNewTrack(int) {}
    virtual void OnEndOfTrack() {}
    virtual void OnAllTracksRead() {}
    virtual void OnMidiMessage(int tick, unsigned char, unsigned char, unsigned char) {
        if (tick > mLastMidiMessageTick)
            mLastMidiMessageTick = tick;
    }
    virtual void OnText(int tick, const char *cc, unsigned char uc) {
        if (uc == 1) {
            char buf[256];
            char otherbuf[256];
            buf[0] = 0;
            if (strncmp(cc, "[section ", 9) == 0) {
                sscanf(cc, "[%s %s]", otherbuf, buf);
                buf[strlen(buf) - 1] = 0;
            } else if (strncmp(cc, "[prc_", 4) == 0) {
                int len = strlen(cc);
                strncpy(buf, cc + 1, len - 2);
                buf[len - 2] = 0;
            }
            if (buf[0] != 0) {
                PracticeSection sect;
                sect.unk0 = buf;
                sect.unk4 = tick;
                sect.unkc = GetMidiReader()->GetTempoMap()->TickToTime(tick);
                sect.unk8 = 0;
                sect.unk14 = true;
                int m, b, t;
                GetMidiReader()->GetMeasureMap()->TickToMeasureBeatTick(tick, m, b, t);
                mSectionList->push_back(sect);
            }
        }
    }

    void Init(std::vector<PracticeSection> *s, FileStream &stream) {
        mSectionList = s;
        mSectionList->clear();
        MidiReader reader(stream, *this, nullptr);
        SetMidiReader(&reader);
        reader.ReadAllTracks();
        mEndMs = reader.GetTempoMap()->TickToTime(mLastMidiMessageTick);
    }

    int GetLastMidiMsgTick() const { return mLastMidiMessageTick; }
    float GetEndMs() const { return mEndMs; }

    std::vector<PracticeSection> *mSectionList; // 0x8
    int mLastMidiMessageTick; // 0xc
    float mEndMs; // 0x10
};