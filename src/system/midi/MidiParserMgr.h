#ifndef MIDI_MIDIPARSERMGR_H
#define MIDI_MIDIPARSERMGR_H
#include "midi/Midi.h"
#include "obj/Object.h"
#include <vector>

class GemListInterface; // forward dec

class MidiParserMgr : public MidiReceiver, public Hmx::Object {
public:
    MidiParserMgr(GemListInterface*, Symbol);
    virtual ~MidiParserMgr();
    virtual void OnNewTrack(int);
    virtual void OnEndOfTrack();
    virtual void OnAllTracksRead();
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char);
    virtual void OnText(int, const char*, unsigned char);
    virtual void SetMidiReader(MidiReader* mr);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    void Reset();
    void Reset(int);

    int unk24, unk28, unk2c;
    int unk30, unk34, unk38;
    GemListInterface* mGems;
    bool mLoaded;
    const char* mFilename;
    Symbol unk48;
    Symbol mSongName;
    std::vector<int> unk50;
    bool unk58, unk59;
};

extern MidiParserMgr* TheMidiParserMgr;

#endif
