/*
    Compile unit: C:\rockband2\band2\src\game\Providers.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8007FBA8 -> 0x80080968
*/
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Friend * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Friend * * _M_start; // offset 0x0, size 0x4
    class Friend * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum FriendEnumState {
    kEnumInactive = 0,
    kEnumFriends = 1,
    kEnumFriendFailure = 2,
    kEnumFriendSuccess = 3,
    kEnumFriendsDone = 4,
    kEnumFriendStats = 5,
    kEnumAllStats = 6,
    kEnumLocalStats = 7,
    kEnumDone = 8,
};
enum ConnectionType {
    kUnconnected = 0,
    kConnectionError = 1,
    kConnected = 2,
};
enum Type {
    kPlayerSong = 0,
    kBandFans = 1,
    kBandSong = 2,
    kTugOfWar = 3,
    kScoreDuel = 4,
    kNumTypes = 5,
};
enum FilterType {
    kByAll = 0,
    kByFriends = 1,
    kByLocal = 2,
};
class PlatformMgrOpCompleteMsg : public Message {
    // total size: 0x8
};
class LeaderboardsMgr : public ListProvider, public Object {
    // total size: 0xB8
    class list mUsers; // offset 0x2C, size 0x8
    class vector mFriendsCollection; // offset 0x34, size 0xC
    class vector mFriendsTemp; // offset 0x40, size 0xC
    enum FriendEnumState mEnumState; // offset 0x4C, size 0x4
    enum ConnectionType mConnectionState; // offset 0x50, size 0x4
    int mPageSize; // offset 0x54, size 0x4
    enum Type mType; // offset 0x58, size 0x4
    enum FilterType mFilter; // offset 0x5C, size 0x4
    int mPlayerNum; // offset 0x60, size 0x4
    class HxGuid mBandID; // offset 0x64, size 0x10
    class Element mHighlight; // offset 0x74, size 0x20
    enum TrackType mTrackType; // offset 0x94, size 0x4
    class LeaderboardLive * mBoardAll; // offset 0x98, size 0x4
    class LeaderboardFriends * mBoardFriends; // offset 0x9C, size 0x4
    class LeaderboardLocal * mBoardLocal; // offset 0xA0, size 0x4
    int mBoardLimits[5]; // offset 0xA4, size 0x14
};
// Range: 0x8007FBA8 -> 0x8007FBF0
void * Providers::Providers(class Providers * const this /* r31 */) {}

// Range: 0x8007FCD4 -> 0x8007FDE4
void * Providers::~Providers(class Providers * const this /* r30 */) {}

class MidiSectionLister : public MidiReceiver {
    // total size: 0x14
    class vector * mSectionList; // offset 0x8, size 0x4
    int m_LastMidiMessageTick; // offset 0xC, size 0x4
    float mEndMs; // offset 0x10, size 0x4
};
enum State {
    kStart = 0,
    kNewTrack = 1,
    kInTrack = 2,
    kEnd = 3,
};
struct Midi {
    // total size: 0x3
    unsigned char mStat; // offset 0x0, size 0x1
    unsigned char mD1; // offset 0x1, size 0x1
    unsigned char mD2; // offset 0x2, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Midi * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Midi * _M_start; // offset 0x0, size 0x4
    struct Midi * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct TempoInfoPoint {
    // total size: 0xC
    float mMs; // offset 0x0, size 0x4
    int mTick; // offset 0x4, size 0x4
    int mTempo; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TempoInfoPoint * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TempoInfoPoint * _M_start; // offset 0x0, size 0x4
    struct TempoInfoPoint * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class MultiTempoTempoMap : public TempoMap {
    // total size: 0x10
    class vector mTempoPoints; // offset 0x4, size 0xC
};
class MidiReader {
    // total size: 0x60
    class BinStream * mStream; // offset 0x0, size 0x4
    unsigned char mStreamCreatedHere; // offset 0x4, size 0x1
    class String mStreamName; // offset 0x8, size 0xC
    class MidiReceiver & mRcvr; // offset 0x14, size 0x4
    enum State mState; // offset 0x18, size 0x4
    signed short mNumTracks; // offset 0x1C, size 0x2
    signed short mTicksPerQuarter; // offset 0x1E, size 0x2
    signed short mDesiredTPQ; // offset 0x20, size 0x2
    int mTrackEndPos; // offset 0x24, size 0x4
    int mCurTrackIndex; // offset 0x28, size 0x4
    int mCurTick; // offset 0x2C, size 0x4
    unsigned char mPrevStatus; // offset 0x30, size 0x1
    class String mCurTrackName; // offset 0x34, size 0xC
    class vector mMidiList; // offset 0x40, size 0xC
    int mMidiListTick; // offset 0x4C, size 0x4
    unsigned char (* mLessFunc)(struct Midi &, struct Midi &); // offset 0x50, size 0x4
    unsigned char mOwnMaps; // offset 0x54, size 0x1
    class MultiTempoTempoMap * mTempoMap; // offset 0x58, size 0x4
    class MeasureMap * mMeasureMap; // offset 0x5C, size 0x4
};
// Range: 0x8007FDE4 -> 0x8007FE24
void * MidiSectionLister::~MidiSectionLister(class MidiSectionLister * const this /* r31 */) {}

// Range: 0x8007FE24 -> 0x8007FE5C
char * PracticeSectionProvider::Text() {}

// Range: 0x8007FE5C -> 0x8007FE84
class Symbol PracticeSectionProvider::DataSymbol() {}

// Range: 0x8007FE84 -> 0x8007FF1C
int PracticeSectionProvider::DataIndex(const class PracticeSectionProvider * const this /* r29 */, class Symbol & sym /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x8007FF1C -> 0x8007FF48
int PracticeSectionProvider::NumData() {}

// Range: 0x8007FF48 -> 0x8007FF68
struct PracticeSection & PracticeSectionProvider::GetSection() {}

// Range: 0x8007FF68 -> 0x8007FFB0
unsigned char PracticeSectionProvider::IsActive() {}

// Range: 0x8007FFB0 -> 0x8007FFF4
void PracticeSectionProvider::GetColor() {}

// Range: 0x8007FFF4 -> 0x80080018
float PracticeSectionProvider::GetSectionStartMs() {}

// Range: 0x80080018 -> 0x8008003C
float PracticeSectionProvider::GetSectionEndMs() {}

static class Symbol _s; // size: 0x4, address: 0x80A49DD4
static class Symbol _s; // size: 0x4, address: 0x80A49DDC
static class Symbol _s; // size: 0x4, address: 0x80A49DE4
static class Symbol _s; // size: 0x4, address: 0x80A49DEC
static class Symbol _s; // size: 0x4, address: 0x80A49DF4
// Range: 0x8008003C -> 0x800807B4
class DataNode PracticeSectionProvider::Handle(class PracticeSectionProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x800807B4 -> 0x800807C8
void MidiSectionLister::OnMidiMessage() {}

// Range: 0x800807C8 -> 0x800807CC
void MidiSectionLister::OnAllTracksRead() {}

// Range: 0x800807CC -> 0x800807D0
void MidiSectionLister::OnEndOfTrack() {}

// Range: 0x800807D0 -> 0x800807D4
void MidiSectionLister::OnNewTrack() {}

// Range: 0x800807D4 -> 0x80080968
void MidiSectionLister::OnText(class MidiSectionLister * const this /* r28 */, int tick /* r29 */, const char * str /* r30 */) {
    // Local variables
    char temp[256]; // r1+0x130
    char section[256]; // r1+0x30
    struct PracticeSection p; // r1+0x18

    // References
    // -> const char * gNullStr;
}

struct {
    // total size: 0x30
} __vt__17MidiSectionLister; // size: 0x30, address: 0x80879110
struct {
    // total size: 0x8
} __RTTI__17MidiSectionLister; // size: 0x8, address: 0x80879160
struct {
    // total size: 0x8
} __RTTI__12MidiReceiver; // size: 0x8, address: 0x80879178
struct {
    // total size: 0x9C
} __vt__23PracticeSectionProvider; // size: 0x9C, address: 0x80879180
struct {
    // total size: 0x8
} __RTTI__23PracticeSectionProvider; // size: 0x8, address: 0x80879258
struct {
    // total size: 0x8
} __RTTI__P15PracticeSection; // size: 0x8, address: 0x808792C8

