/*
    Compile unit: C:\rockband2\system\src\beatmatch\SongParser.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802FF204 -> 0x803015C0
*/
class Timer gSongLoadTimer; // size: 0x38, address: 0x8097DD78
// Range: 0x802FF204 -> 0x802FF218
char * SongParser::FmtTick(class SongParser * const this /* r5 */) {}

// Range: 0x802FF218 -> 0x802FF954
void * SongParser::SongParser(class SongParser * const this /* r28 */, class InternalSongParserSink & sink /* r30 */, int num_difficulties /* r29 */, unsigned char separate_parts /* r23 */, class Symbol & suffix /* r24 */, class TempoMap * & tempo_map /* r26 */, class MeasureMap * & measure_map /* r25 */) {
    // Local variables
    class DataArray * beatmatcher_cfg; // r26
    class DataArray * watcher_cfg; // r27
    class DataArray * parser_cfg; // r27
    class DataArray * drum_cfg; // r30
    int i; // r25
    class DataArray * vocal_cfg; // r25
    int i; // r27
    int i; // r30

    // References
    // -> struct [anonymous] __RTTI__PQ210SongParser13GemInProgress;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__10SongParser;
}

struct {
    // total size: 0x8
} __RTTI__PQ210SongParser13GemInProgress; // size: 0x8, address: 0x808CDE80
// Range: 0x802FF954 -> 0x802FFA0C
void SongParser::Poll(class SongParser * const this /* r31 */) {
    // Local variables
    unsigned char eof; // r0
}

// Range: 0x802FFA0C -> 0x802FFA14
void SongParser::SetNumPlayers() {}

// Range: 0x802FFA14 -> 0x802FFB20
void SongParser::Reset(class SongParser * const this /* r31 */) {
    // Local variables
    int d; // r7
    int i; // r8
}

// Range: 0x802FFB20 -> 0x802FFB90
void SongParser::AddReceiver(class MidiReceiver * receiver /* r1+0x8 */) {}

// Range: 0x802FFB90 -> 0x802FFB98
void SongParser::OnNewTrack() {}

// Range: 0x802FFB98 -> 0x802FFC08
void SongParser::OnEndOfTrack(class SongParser * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802FFC08 -> 0x802FFC78
void SongParser::OnAllTracksRead(class SongParser * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802FFC78 -> 0x802FFD6C
void SongParser::OnMidiMessage(class SongParser * const this /* r26 */, int tick /* r27 */, unsigned char status /* r28 */, unsigned char data1 /* r29 */, unsigned char data2 /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802FFD6C -> 0x802FFE2C
void SongParser::OnMidiMessageGem(class SongParser * const this /* r28 */, int tick /* r29 */, unsigned char status /* r30 */, unsigned char data1 /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802FFE2C -> 0x802FFEF4
void SongParser::OnMidiMessageGemOff(class SongParser * const this /* r29 */, int tick /* r30 */, unsigned char pitch /* r31 */) {}

// Range: 0x802FFEF4 -> 0x802FFF84
unsigned char SongParser::HandlePhraseEnd(class SongParser * const this /* r29 */, int tick /* r30 */, unsigned char pitch /* r31 */) {}

// Range: 0x802FFF84 -> 0x802FFF98
void SongParser::OnCommonPhraseEnd() {}

// Range: 0x802FFF98 -> 0x802FFFAC
void SongParser::OnSoloPhraseEnd() {}

// Range: 0x802FFFAC -> 0x803000D0
void SongParser::AddPhrase(class SongParser * const this /* r25 */, enum BeatmatchPhraseType type /* r26 */, int diff /* r27 */, int & on_tick /* r28 */, int off_tick /* r29 */) {
    // Local variables
    float on_time; // f30
    float off_time; // f0
}

// Range: 0x803000D0 -> 0x80300144
unsigned char SongParser::HandleFillEnd(class SongParser * const this /* r28 */, int tick /* r29 */, unsigned char pitch /* r30 */) {
    // Local variables
    unsigned char ok; // r31
}

// Range: 0x80300144 -> 0x803001D0
void SongParser::OnFillEnd(class SongParser * const this /* r29 */, int tick /* r30 */) {}

// Range: 0x803001D0 -> 0x803003B0
void SongParser::OnGemEnd(class SongParser * const this /* r28 */, int tick /* r24 */) {
    // Local variables
    int diff; // r1+0x8
    int slot; // r30
    int on_tick; // r29
    float off_time; // f0
    class MultiGemInfo info; // r1+0xC
}

// Range: 0x803003B0 -> 0x80300488
int SongParser::ComputeSlots(class SongParser * const this /* r26 */, int on_tick /* r27 */, class vector & gems /* r31 */) {
    // Local variables
    int slots; // r29
    int s; // r28
}

// Range: 0x80300488 -> 0x80300690
void SongParser::OnMidiMessageVocals(class SongParser * const this /* r29 */, int tick /* r30 */, unsigned char status /* r28 */, unsigned char data1 /* r31 */) {
    // Local variables
    int pitch; // [invalid]
    int player; // r5
    int player; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80300690 -> 0x80300904
void SongParser::EndVocalNote(class SongParser * const this /* r31 */, int tick /* r29 */) {
    // Local variables
    float time; // f0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80300904 -> 0x80300A38
unsigned char SongParser::ParseAndStripLyricText(const char * text /* r28 */, class VocalNote & note /* r29 */) {
    // Local variables
    unsigned char bends; // r30
    int len; // r0
    const char * endChar; // r31
    class String stripped; // r1+0x8
}

// Range: 0x80300A38 -> 0x80300B00
void SongParser::OnMidiMessageBeat(class SongParser * const this /* r28 */, int tick /* r29 */, unsigned char status /* r30 */, unsigned char data1 /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80300B00 -> 0x80300C94
void SongParser::OnText(class SongParser * const this /* r28 */, int tick /* r29 */, const char * str /* r30 */, unsigned char type /* r31 */) {
    // Local variables
    int i; // r27

    // References
    // -> struct __locale _current_locale;
}

// Range: 0x80300C94 -> 0x80300DC0
unsigned char SongParser::OnAcceptMaps(class SongParser * const this /* r29 */, class TempoMap * tempo /* r30 */, class MeasureMap * measure /* r31 */) {}

// Range: 0x80300DC0 -> 0x80300E44
void SongParser::SetMidiReader(class SongParser * const this /* r29 */, class MidiReader * r /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x80300E44 -> 0x80300E98
int SongParser::PitchToSlot() {
    // Local variables
    int slot; // r6
}

// Range: 0x80300E98 -> 0x80300EAC
unsigned char SongParser::IsCommonPhraseMarker() {}

// Range: 0x80300EAC -> 0x80300EC0
unsigned char SongParser::IsSoloPhraseMarker() {}

// Range: 0x80300EC0 -> 0x80300F08
unsigned char SongParser::CheckDrumFillMarker() {}

// Range: 0x80300F08 -> 0x80300F0C
unsigned char SongParser::CheckFillMarker() {}

// Range: 0x80300F0C -> 0x80300FC4
unsigned char SongParser::CheckForceHopoMarker() {
    // Local variables
    int slot; // r7
    int diff; // r5
}

// Range: 0x80300FC4 -> 0x80301040
unsigned char SongParser::CheckDrumMapMarker(class SongParser * const this /* r10 */, int tick /* r9 */, int pitch /* r8 */) {}

// Range: 0x80301040 -> 0x803010B8
unsigned char SongParser::SuffixMatches(const char * suffix /* r29 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x803010B8 -> 0x80301188
unsigned char SongParser::UseNullSuffix(class SongParser * const this /* r29 */, const class vector & parts /* r30 */, class Symbol & instrument /* r31 */) {
    // Local variables
    int t; // r28

    // References
    // -> const char * gNullStr;
}

// Range: 0x80301188 -> 0x803011D4
unsigned char SongParser::UsePart() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x803011D4 -> 0x80301280
void SplitTrackName(const char * track_name /* r0 */, class Symbol & oInstrument /* r30 */, class Symbol & oMode /* r31 */) {
    // Local variables
    char instrument[64]; // r1+0x10
    char * c; // r4

    // References
    // -> const char * gNullStr;
}

// Range: 0x80301280 -> 0x80301328
unsigned char SongParser::InstrumentUsed(class SongParser * const this /* r28 */, class Symbol & instrument /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80301328 -> 0x80301338
void SongParser::InitReadingState() {}

// Range: 0x80301338 -> 0x80301344
void SongParser::SetSectionBounds() {}

// Range: 0x80301344 -> 0x80301384
unsigned char SongParser::FilterTick() {}

class MidiTrackLister : public MidiReceiver {
    // total size: 0xC
    class vector * mTrackList; // offset 0x8, size 0x4
};
// Range: 0x80301384 -> 0x803013F0
void * MidiTrackLister::MidiTrackLister(class MidiTrackLister * const this /* r29 */, class vector & tracks /* r30 */, class BinStream & file /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15MidiTrackLister;
}

// Range: 0x803013F0 -> 0x80301430
void * MidiTrackLister::~MidiTrackLister(class MidiTrackLister * const this /* r31 */) {}

// Range: 0x80301430 -> 0x80301484
void MidiTrackLister::FillTrackList(class MidiTrackLister * const this /* r6 */, class vector & tracks /* r0 */) {
    // Local variables
    class MidiReader reader; // r1+0x8
}

// Range: 0x80301484 -> 0x8030151C
void MidiTrackLister::OnText(class MidiTrackLister * const this /* r31 */) {}

// Range: 0x8030151C -> 0x80301578
void FillTrackList(class vector & tracks /* r0 */, class BinStream & file /* r31 */) {
    // Local variables
    class MidiTrackLister lister; // r1+0x8
}

// Range: 0x80301578 -> 0x8030157C
void MidiTrackLister::OnMidiMessage() {}

// Range: 0x8030157C -> 0x80301580
void MidiTrackLister::OnAllTracksRead() {}

// Range: 0x80301580 -> 0x80301584
void MidiTrackLister::OnEndOfTrack() {}

// Range: 0x80301584 -> 0x80301588
void MidiTrackLister::OnNewTrack() {}

struct {
    // total size: 0x30
} __vt__15MidiTrackLister; // size: 0x30, address: 0x808CE0A0
struct {
    // total size: 0x8
} __RTTI__15MidiTrackLister; // size: 0x8, address: 0x808CE0F0
struct {
    // total size: 0x30
} __vt__10SongParser; // size: 0x30, address: 0x808CE0F8
struct {
    // total size: 0x8
} __RTTI__10SongParser; // size: 0x8, address: 0x808CE140
// Range: 0x80301588 -> 0x803015B4
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PQ210SongParser14DifficultyInfo; // size: 0x8, address: 0x808CE1A0
struct {
    // total size: 0x8
} __RTTI__P8PartInfo; // size: 0x8, address: 0x808CE1B8
// Range: 0x803015B4 -> 0x803015C0
static void __sinit_\SongParser_cpp() {
    // References
    // -> class Timer gSongLoadTimer;
}


