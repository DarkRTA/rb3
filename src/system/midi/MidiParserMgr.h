#pragma once
#include "midi/Midi.h"
#include "midi/MidiParser.h"
#include "obj/Object.h"
#include "utl/VectorSizeDefs.h"
#include <vector>

class GemListInterface; // forward dec

class MidiParserMgr : public MidiReceiver, public Hmx::Object {
public:
    MidiParserMgr(GemListInterface *, Symbol);
    virtual ~MidiParserMgr();
    virtual void OnNewTrack(int);
    virtual void OnEndOfTrack();
    virtual void OnAllTracksRead();
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char);
    virtual void OnText(int, const char *, unsigned char);
    virtual void SetMidiReader(MidiReader *mr);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    void Reset();
    void Reset(int);
    void FinishLoad();
    void Poll();
    void ClearManagedParsers();
    void FreeAllData();
    DataEventList *GetEventsList();
    MidiParser *GetParser(Symbol);
    bool CreateNote(int, unsigned char, unsigned char, int &);
    char *StripEndBracket(char *, const char *);
    DataArray *ParseText(const char *, int);
    void OnTrackName(Symbol);
    const char *GetSongName() const { return mSongName.Str(); }

    std::vector<int VECTOR_SIZE_LARGE> unk24; // 0x24
    std::vector<MidiParser::VocalEvent VECTOR_SIZE_LARGE> unk30; // 0x30
    GemListInterface *mGems; // 0x3c
    bool mLoaded; // 0x40
    const char *mFilename; // 0x44
    Symbol mTrackName; // 0x48
    Symbol mSongName; // 0x4c
    std::vector<Symbol> unk50; // 0x50
    bool unk58, unk59;
};

extern MidiParserMgr *TheMidiParserMgr;
