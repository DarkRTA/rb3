#pragma once
#include "midi/Midi.h"
#include "midi/MidiParser.h"
#include "obj/Object.h"
#include "utl/VectorSizeDefs.h"
#include <vector>

class GemListInterface; // forward dec

/** Manager for all midi parsers. */
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
    void Reset(int tick);
    /** Routine to run when parsing is complete. */
    void FinishLoad();
    void Poll();
    /** Get the DataEventList from the events_parser. */
    DataEventList *GetEventsList();
    /** Get the parser with the supplied name. */
    MidiParser *GetParser(Symbol name);
    const char *GetSongName() const { return mSongName.Str(); }

private:
    /** Strip the end bracket from the input string. (i.e. remove the ']')
     * @param [in] new_str The buffer where the output string will go.
     * @param [in] old_str The input string we want to strip ']' from.
     * returns The buffer with the removed ']'.
     */
    char *StripEndBracket(char *new_str, const char *old_str);
    /** Parse the text at the supplied tick.
     * @param [in] str The text.
     * @param [in] tick The tick at which this occurs.
     * @returns The DataArray corresponding to the text.
     */
    DataArray *ParseText(const char *str, int tick);
    bool CreateNote(int tick, unsigned char status, unsigned char data1, int &start_tick);
    /** Routine to run when parsing a track name event.
     * @param [in] trackname The track name.
     */
    void OnTrackName(Symbol trackname);
    /** Clear the lists of parsed note-ons and text events. */
    void FreeAllData();

    std::vector<int VECTOR_SIZE_LARGE> mNoteOns; // 0x24
    std::vector<MidiParser::VocalEvent VECTOR_SIZE_LARGE> mText; // 0x30
    GemListInterface *mGems; // 0x3c
    bool mLoaded; // 0x40
    const char *mFilename; // 0x44
    Symbol mTrackName; // 0x48
    Symbol mSongName; // 0x4c
    std::vector<Symbol> mTrackNames; // 0x50
    bool unk58; // 0x58
    bool unk59; // 0x59
};

extern MidiParserMgr *TheMidiParserMgr;
