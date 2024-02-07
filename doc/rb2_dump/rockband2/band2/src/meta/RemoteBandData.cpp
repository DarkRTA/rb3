/*
    Compile unit: C:\rockband2\band2\src\meta\RemoteBandData.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80150BEC -> 0x801519E8
*/
// Range: 0x80150BEC -> 0x80150D04
void * RemoteBandData::RemoteBandData(class RemoteBandData * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__14RemoteBandData;
    // -> struct [anonymous] __vt__8BandData;
}

// Range: 0x80150D04 -> 0x80150F18
void * RemoteBandData::~RemoteBandData(class RemoteBandData * const this /* r30 */) {}

// Range: 0x80150F18 -> 0x80151084
void RemoteBandData::Save(const class RemoteBandData * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x80151084 -> 0x80151320
void RemoteBandData::Load(class RemoteBandData * const this /* r29 */, class BandData * src /* r30 */) {}

// Range: 0x80151320 -> 0x80151328
unsigned char RemoteBandData::IsDirty() {}

// Range: 0x80151328 -> 0x8015133C
void RemoteBandData::SaveLoadComplete() {}

// Range: 0x8015133C -> 0x80151344
unsigned char RemoteBandData::HasWritePermission() {}

// Range: 0x80151344 -> 0x8015134C
char * RemoteBandData::BandName() {}

// Range: 0x8015134C -> 0x80151354
class HxGuid & RemoteBandData::Guid() {}

// Range: 0x80151354 -> 0x80151548
void RemoteBandData::GetRoster(const class RemoteBandData * const this /* r29 */, class vector & members /* r30 */) {
    // Local variables
    int n; // r31
    struct BandMember rosterMember; // r1+0x20
}

// Range: 0x80151548 -> 0x80151550
int RemoteBandData::Fans() {}

// Range: 0x80151550 -> 0x80151568
int RemoteBandData::TourScore() {}

// Range: 0x80151568 -> 0x80151570
int RemoteBandData::WorldFame() {}

// Range: 0x80151570 -> 0x80151580
int RemoteBandData::GetBandLogoPos() {}

// Range: 0x80151580 -> 0x80151588
char * RemoteBandData::GetMotto() {}

// Range: 0x80151588 -> 0x80151590
int RemoteBandData::StarRating() {}

// Range: 0x80151590 -> 0x80151598
enum Difficulty RemoteBandData::DifficultyRating() {}

// Range: 0x80151598 -> 0x801515A0
class OnlineID * RemoteBandData::OwnerID() {}

// Range: 0x801515A0 -> 0x801515A8
char * RemoteBandData::OwnerName() {}

// Range: 0x801515A8 -> 0x80151628
class String RemoteBandData::GetLogoPatchDir(const class RemoteBandData * const this /* r31 */) {
    // References
    // -> class String sDefaultLogo;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80151628 -> 0x8015163C
struct DateTime RemoteBandData::GetCreationDate(const class RemoteBandData * const this /* r4 */) {}

// Range: 0x8015163C -> 0x80151644
class Symbol RemoteBandData::Hometown() {}

// Range: 0x80151644 -> 0x801517F0
void RemoteBandData::GetTopSongs(const class RemoteBandData * const this /* r28 */, class vector & songs /* r29 */, int numSongs /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x801517F0 -> 0x801518B0
void RemoteBandData::UpdateCharName(class RemoteBandData * const this /* r27 */, const class HxGuid & charGuid /* r28 */, const char * charName /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x801518B0 -> 0x80151938
unsigned char RemoteBandData::IsMember(class RemoteBandData * const this /* r29 */, const class HxGuid & charGuid /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x80151938 -> 0x80151990
void RemoteBandData::SetBandName(class RemoteBandData * const this /* r30 */, const char * name /* r31 */) {}

// Range: 0x80151990 -> 0x801519E8
void RemoteBandData::UpdateOwnerName(class RemoteBandData * const this /* r30 */, const char * name /* r31 */) {}

struct {
    // total size: 0xBC
} __vt__14RemoteBandData; // size: 0xBC, address: 0x80894EEC
struct {
    // total size: 0x8
} __RTTI__P10BandMember; // size: 0x8, address: 0x80894FB8
struct {
    // total size: 0x8
} __RTTI__P10SongStatus; // size: 0x8, address: 0x80894FD0

