#ifndef MIDI_MIDIPARSERMGR_H
#define MIDI_MIDIPARSERMGR_H
#include "midi/Midi.h"
#include "midi/MidiParser.h"
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
    void FinishLoad();
    void Poll();
    void ClearManagedParsers();
    void FreeAllData();
    DataEventList* GetEventsList();
    MidiParser* GetParser(Symbol);
    const char* GetSongName() const { return mSongName.Str(); }

    // static DataArray* MidiParserArray(){
    //     return SystemConfig("beatmatcher")->FindArray("midi_parsers", false);
    // }

    std::vector<int, unsigned int> unk24; // 0x24
    std::vector<MidiParser::VocalEvent, unsigned int> unk30; // 0x30
    GemListInterface* mGems; // 0x3c
    bool mLoaded; // 0x40
    const char* mFilename; // 0x44
    Symbol mTrackName; // 0x48
    Symbol mSongName; // 0x4c
    std::vector<int> unk50; // 0x50
    bool unk58, unk59;
};

extern MidiParserMgr* TheMidiParserMgr;

#endif
