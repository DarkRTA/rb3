/*
    Compile unit: C:\rockband2\system\src\beatmatch\SongData.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802FB13C -> 0x802FC7D8
*/
// Range: 0x802FB13C -> 0x802FB1B8
void * TrackInfo::TrackInfo(struct TrackInfo * const this /* r29 */, class Symbol & instrument /* r30 */, unsigned char independent_slots /* r31 */) {}

// Range: 0x802FB1B8 -> 0x802FB2C0
void * TrackInfo::~TrackInfo(struct TrackInfo * const this /* r30 */) {}

// Range: 0x802FB2C0 -> 0x802FB318
struct TrackInfo * TrackInfo::Duplicate(const struct TrackInfo * const this /* r31 */) {}

// Range: 0x802FB318 -> 0x802FB428
void * SongData::SongData(class SongData * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8SongData;
}

// Range: 0x802FB428 -> 0x802FBAAC
void * SongData::~SongData(class SongData * const this /* r29 */) {
    // Local variables
    int i; // r31

    // References
    // -> struct [anonymous] __vt__8SongData;
}

union SHA1_WORKSPACE_BLOCK {
    unsigned char c[64]; // offset 0x0, size 0x40
    unsigned long l[16]; // offset 0x0, size 0x40
};
class CSHA1 {
    // total size: 0xC4
public:
    unsigned long m_state[5]; // offset 0x0, size 0x14
    unsigned long m_count[2]; // offset 0x14, size 0x8
    unsigned long m_reserved1[1]; // offset 0x1C, size 0x4
    unsigned char m_buffer[64]; // offset 0x20, size 0x40
    unsigned char m_digest[20]; // offset 0x60, size 0x14
    unsigned long m_reserved2[3]; // offset 0x74, size 0xC
private:
    unsigned char m_workspace[64]; // offset 0x80, size 0x40
    union SHA1_WORKSPACE_BLOCK * m_block; // offset 0xC0, size 0x4
};
class StreamChecksum {
    // total size: 0xCC
    const unsigned char * mSignature; // offset 0x0, size 0x4
    const char * mFile; // offset 0x4, size 0x4
    class CSHA1 mSHA1; // offset 0x8, size 0xC4
};
// Range: 0x802FBAAC -> 0x802FBB68
static void Validate(class MemStream * stream /* r29 */, const char * file /* r30 */, unsigned char nameOnly /* r31 */) {
    // Local variables
    class StreamChecksum chk; // r1+0x8
}

// Range: 0x802FBB68 -> 0x802FBC44
unsigned char SongData::Poll(class SongData * const this /* r30 */) {
    // Local variables
    class Timer t; // r1+0x8
}

// Range: 0x802FBC44 -> 0x802FBCB4
void SongData::AddSink(class SongParserSink * sink /* r1+0x8 */) {}

// Range: 0x802FBCB4 -> 0x802FBFE8
void SongData::DuplicateTrack(class SongData * const this /* r27 */, int old_track /* r28 */) {
    // Local variables
    int i; // r29

    // References
    // -> struct [anonymous] __vt__12DrumFillInfo;
    // -> struct [anonymous] __RTTI__P10FillExtent;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P13TickedInfo<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__8FillInfo;
}

// Range: 0x802FBFE8 -> 0x802FC164
void SongData::FixUpTrackConfig(class SongData * const this /* r30 */, class PlayerTrackConfigList * player_track_config_list /* r31 */) {
    // Local variables
    class vector instruments; // r1+0x24
    int t; // r29
    int t; // r29
}

// Range: 0x802FC164 -> 0x802FC1D4
void SongData::SetBeatMatcher(class BeatMatcher * beat_matcher /* r1+0x8 */) {}

// Range: 0x802FC1D4 -> 0x802FC1DC
void SongData::SetSeparateParts() {}

// Range: 0x802FC1DC -> 0x802FC1F8
class PhraseList & SongData::GetPhraseList() {}

// Range: 0x802FC1F8 -> 0x802FC40C
void SongData::AddTrack(class SongData * const this /* r30 */, int track /* r31 */, class Symbol & name /* r27 */, class Symbol & instrument /* r29 */, unsigned char independent_slots /* r28 */) {
    // Local variables
    int i; // r28

    // References
    // -> struct [anonymous] __vt__12DrumFillInfo;
}

// Range: 0x802FC40C -> 0x802FC414
void SongData::AddVocalNote() {}

// Range: 0x802FC414 -> 0x802FC41C
void SongData::OnTambourineGem() {}

// Range: 0x802FC41C -> 0x802FC424
void SongData::StartVocalPlayerPhrase() {}

// Range: 0x802FC424 -> 0x802FC42C
void SongData::EndVocalPlayerPhrase() {}

// Range: 0x802FC42C -> 0x802FC4D4
void SongData::AddPhrase(class SongData * const this /* r25 */, enum BeatmatchPhraseType type /* r26 */, int track /* r27 */, float ms /* f30 */, int tick /* r28 */, float duration /* f31 */, int duration_ticks /* r29 */) {
    // Local variables
    int min_diff; // [invalid]
    int max_diff; // r31
    int i; // r30
}

// Range: 0x802FC4D4 -> 0x802FC4DC
void SongData::SetFakeHitGemsInFill() {}

// Range: 0x802FC4DC -> 0x802FC4E4
unsigned char SongData::GetFakeHitGemsInFill() {}

// Range: 0x802FC4E4 -> 0x802FC534
void SongData::RecalculateGemTimes(class SongData * const this /* r30 */) {
    // Local variables
    class GameGemDB * const * it; // r31
}

// Range: 0x802FC534 -> 0x802FC630
void SongData::EnableGems(float startMs /* f30 */, float endMs /* f31 */) {
    // Local variables
    class vector & v; // r0
    unsigned int i; // r7
    float gemEnd; // f0
}

// Range: 0x802FC630 -> 0x802FC640
class GameGemList & SongData::GetGemListByDiff() {}

// Range: 0x802FC640 -> 0x802FC650
class GameGemList & SongData::GetGemList() {}

// Range: 0x802FC650 -> 0x802FC69C
class GameGemInfoList & SongData::GetGemInfoList(int track /* r31 */) {}

// Range: 0x802FC69C -> 0x802FC6B8
class TickedInfoCollection * SongData::GetSubmixes() {}

// Range: 0x802FC6B8 -> 0x802FC708
int SongData::TrackNamed() {
    // Local variables
    int i; // r6
}

// Range: 0x802FC708 -> 0x802FC718
class DrumFillInfo * SongData::GetDrumFillInfo() {}

// Range: 0x802FC718 -> 0x802FC71C
class FillInfo * SongData::GetFillInfo() {}

// Range: 0x802FC71C -> 0x802FC72C
class DrumMap * SongData::GetDrumMap() {}

// Range: 0x802FC72C -> 0x802FC7D8
char * SongData::SongName(const class SongData * const this /* r31 */) {
    // Local variables
    const char * extended_name; // r0
    const char * c; // r4
}

struct {
    // total size: 0x3C
} __vt__8SongData; // size: 0x3C, address: 0x808CDB28
struct {
    // total size: 0x8
} __RTTI__8SongData; // size: 0x8, address: 0x808CDB80
struct {
    // total size: 0x3C
} __vt__22InternalSongParserSink; // size: 0x3C, address: 0x808CDB88
struct {
    // total size: 0x8
} __RTTI__22InternalSongParserSink; // size: 0x8, address: 0x808CDBE0
struct {
    // total size: 0x8
} __RTTI__PP9DrumMixDB; // size: 0x8, address: 0x808CDC70
struct {
    // total size: 0x8
} __RTTI__PP13GameGemInfoDB; // size: 0x8, address: 0x808CDC90
struct {
    // total size: 0x8
} __RTTI__PP8PhraseDB; // size: 0x8, address: 0x808CDCA8
struct {
    // total size: 0x8
} __RTTI__PP9GameGemDB; // size: 0x8, address: 0x808CDCC0
struct {
    // total size: 0x8
} __RTTI__PP7DrumMap; // size: 0x8, address: 0x808CDCD8
struct {
    // total size: 0x8
} __RTTI__PP12DrumFillInfo; // size: 0x8, address: 0x808CDCF0
struct {
    // total size: 0x8
} __RTTI__PPQ28SongData9TrackInfo; // size: 0x8, address: 0x808CDD10
struct {
    // total size: 0x8
} __RTTI__PP11BeatMatcher; // size: 0x8, address: 0x808CDD28
struct {
    // total size: 0x8
} __RTTI__PP14SongParserSink; // size: 0x8, address: 0x808CDD48
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};

