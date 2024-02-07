/*
    Compile unit: C:\rockband2\band2\src\meta\ProfileMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80146694 -> 0x8014C9BC
*/
class Symbol t; // size: 0x4, address: 0x80A4C044
// Range: 0x80146694 -> 0x801466C8
static void SetVolume() {
    // References
    // -> class Game * TheGame;
}

// Range: 0x801466C8 -> 0x80146784
class vector ProfileMgr::GetAll(class vector * profiles /* r30 */, class ProfileMgr * const this /* r31 */) {
    // Local variables
    class Profile * it; // r1+0xC
}

// Range: 0x80146784 -> 0x8014685C
class vector ProfileMgr::GetSignedIn(class vector * profiles /* r30 */, class ProfileMgr * const this /* r31 */) {
    // Local variables
    class Profile * it; // r1+0xC
    int pad; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x8014685C -> 0x801468C4
class Profile * ProfileMgr::GetProfile(class ProfileMgr * const this /* r30 */, const class User * pUser /* r31 */) {}

// Range: 0x801468C4 -> 0x801469CC
class DataNode ProfileMgr::OnGetProfile(class ProfileMgr * const this /* r31 */) {
    // Local variables
    class User * pUser; // r4
    class DataNode node; // r1+0x8

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
    // -> class UserMgr * TheUserMgr;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4C04C
static class Symbol is_practice; // size: 0x4, address: 0x80A4C054
static class Symbol is_drum_trainer; // size: 0x4, address: 0x80A4C05C
static class Symbol is_tutorial; // size: 0x4, address: 0x80A4C064
// Range: 0x801469CC -> 0x80146D00
class GameplayOptions * ProfileMgr::GetGameplayOptionsFromUser(class ProfileMgr * const this /* r28 */, class BandUser * user /* r26 */) {
    // Local variables
    enum ControllerType type; // r0
    int slot; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tutorial;
    // -> static class Symbol is_drum_trainer;
    // -> static class Symbol is_practice;
    // -> static class Symbol is_h2h_arrangement;
}

// Range: 0x80146D00 -> 0x80146DA8
class Profile * ProfileMgr::GetSaveData(class ProfileMgr * const this /* r29 */, class BandUser * pUser /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80146DA8 -> 0x80146E1C
unsigned char ProfileMgr::CanSave(class ProfileMgr * const this /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80146E1C -> 0x80146F30
class vector ProfileMgr::GetNewlySignedIn(class vector * profiles /* r27 */, class ProfileMgr * const this /* r28 */) {
    // Local variables
    class Profile * it; // r1+0xC
    int pad; // r29

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80146F30 -> 0x80147044
class vector ProfileMgr::GetShouldAutosave(class vector * profiles /* r27 */, class ProfileMgr * const this /* r28 */) {
    // Local variables
    class Profile * it; // r30
    class Profile & profile; // r1+0xC
    int pad; // r0
    unsigned char b1; // r0
    unsigned char b2; // r29
    unsigned char b3; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80147044 -> 0x801470C0
unsigned char ProfileMgr::HasUnsavedData(class ProfileMgr * const this /* r30 */) {
    // Local variables
    int padNum; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801470C0 -> 0x80147194
unsigned char ProfileMgr::HasUnsavedDataForPad(class ProfileMgr * const this /* r30 */, int padNum /* r29 */) {
    // Local variables
    class Profile * pData; // r30

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class ProfileChangedMsg msg; // size: 0x8, address: 0x80979358
// Range: 0x80147194 -> 0x80147428
void ProfileMgr::PurgeOldData(class ProfileMgr * const this /* r29 */) {
    // Local variables
    class Profile * it; // r30

    // References
    // -> struct [anonymous] __vt__17ProfileChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ProfileChangedMsg msg;
}

// Range: 0x80147428 -> 0x80147488
void ProfileMgr::MarkAllSaveDataAsCheated(class ProfileMgr * const this /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80147488 -> 0x801474EC
void ProfileMgr::MarkCheatersForPurge(class ProfileMgr * const this /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x801474EC -> 0x801475E4
void ProfileMgr::GetUsersWhoCanOwnCharacters(const class ProfileMgr * const this /* r27 */, class vector & users /* r28 */, unsigned char includeFull /* r29 */) {
    // Local variables
    const class Profile * it; // r30

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x801475E4 -> 0x80147678
unsigned char ProfileMgr::CanAnyProfileOwnANewChar() {
    // Local variables
    class vector users; // r1+0xC
}

// Range: 0x80147678 -> 0x80147770
void ProfileMgr::GetUsersWhoCanOwnBands(const class ProfileMgr * const this /* r27 */, class vector & users /* r28 */, unsigned char includeFull /* r29 */) {
    // Local variables
    const class Profile * it; // r30

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80147770 -> 0x80147804
unsigned char ProfileMgr::CanAnyProfileOwnANewBand() {
    // Local variables
    class vector users; // r1+0xC
}

// Range: 0x80147804 -> 0x8014787C
unsigned char ProfileMgr::IsCharNameUnique(const char * charName /* r30 */) {
    // Local variables
    class Profile * pProfile; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8014787C -> 0x80147944
class DataNode ProfileMgr::OnIsCharNameUnique(class ProfileMgr * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    class String strCharName; // r1+0x8

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
}

// Range: 0x80147944 -> 0x801479BC
unsigned char ProfileMgr::IsBandNameUnique(const char * bandName /* r30 */) {
    // Local variables
    class Profile * pProfile; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801479BC -> 0x80147A84
class DataNode ProfileMgr::OnIsBandNameUnique(class ProfileMgr * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    class String strBandName; // r1+0x8

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
}

// Range: 0x80147A84 -> 0x80147B34
unsigned char ProfileMgr::IsCharAvailable(const class CharData * c /* r28 */, class vector & users /* r29 */) {
    // Local variables
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80147B34 -> 0x80147BC8
class Profile * ProfileMgr::FindCharOwnerFromGuid(class ProfileMgr * const this /* r29 */, const class HxGuid & guidChar /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80147BC8 -> 0x80147C64
class TourCharLocal * ProfileMgr::FindCharFromGuid(class ProfileMgr * const this /* r29 */, const class HxGuid & guidChar /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80147C64 -> 0x80147CF8
class Profile * ProfileMgr::FindBandOwner(class ProfileMgr * const this /* r29 */, const class TourBandLocal * band /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80147CF8 -> 0x80147DEC
void ProfileMgr::FindBandMembers(class ProfileMgr * const this /* r27 */, const class TourBand * band /* r28 */, class vector & members /* r29 */) {
    // Local variables
    class Profile * it; // [invalid]
    class Profile & profile; // r31
    int n; // r30
    class TourCharLocal * c; // r1+0xC
}

// Range: 0x80147DEC -> 0x80147E80
class Profile * ProfileMgr::FindRemoteBandOwner(class ProfileMgr * const this /* r29 */, const class HxGuid & guidBand /* r30 */) {
    // Local variables
    class Profile * it; // r31
    class RemoteBandData * pBand; // r0
}

// Range: 0x80147E80 -> 0x80147F04
void ProfileMgr::DeleteCharFromAllProfiles(class ProfileMgr * const this /* r30 */) {
    // Local variables
    class HxGuid charGuidCopy; // r1+0x8
    class Profile * it; // r31
}

// Range: 0x80147F04 -> 0x80147F88
void ProfileMgr::DeleteBandFromAllProfiles(class ProfileMgr * const this /* r30 */) {
    // Local variables
    class HxGuid bandGuidCopy; // r1+0x8
    class Profile * it; // r31
}

// Range: 0x80147F88 -> 0x80148000
int ProfileMgr::FindPlayerNumFromTourchar(class ProfileMgr * const this /* r29 */, class TourCharLocal * pChar /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80148000 -> 0x801480B0
class BandUser * ProfileMgr::GetUserFromCharData(class ProfileMgr * const this /* r29 */) {
    // Local variables
    class TourCharLocal * pCharLocal; // r31
    class Profile * it; // r30

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x801480B0 -> 0x80148128
int ProfileMgr::FindPlayerNumFromTourBand(class ProfileMgr * const this /* r29 */, class TourBand * pBand /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80148128 -> 0x80148198
void ProfileMgr::ResyncBandName(class ProfileMgr * const this /* r29 */, class TourBandLocal * pBand /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80148198 -> 0x8014824C
void ProfileMgr::ResyncCharName(class ProfileMgr * const this /* r28 */, class CharData * pChar /* r29 */, unsigned char charNameUnchecked /* r30 */) {
    // Local variables
    class Profile * it; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8014824C -> 0x80148320
void ProfileMgr::ResyncAllBandsAndChars(class ProfileMgr * const this /* r27 */) {
    // Local variables
    class Profile * it; // [invalid]
    class Profile & profile; // r29
    int bandCount; // r0
    int iBand; // r30
    class TourBandLocal * pBand; // r0
    int charCount; // r0
    int iChar; // r28
}

// Range: 0x80148320 -> 0x8014857C
void ProfileMgr::CacheBandData(class ProfileMgr * const this /* r28 */, class TourBand * band /* r29 */) {
    // Local variables
    class Profile * it; // r30
    unsigned char shouldCache; // r27
    class vector members; // r1+0x1C
    int n; // r26
    class RemoteBandData * bandCache; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8014857C -> 0x8014861C
class DataNode ProfileMgr::OnMsg() {
    // Local variables
    class vector profiles; // r1+0xC
    class Profile * * it; // r31
}

// Range: 0x8014861C -> 0x80148694
unsigned char ProfileMgr::NeedsUpload(class ProfileMgr * const this /* r30 */) {
    // Local variables
    class Profile * it; // r31
}

// Range: 0x80148694 -> 0x801486FC
unsigned char ProfileMgr::IsPadActive() {
    // Local variables
    class Profile * pProfile; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801486FC -> 0x80148704
int ProfileMgr::GetMaxChars() {}

// Range: 0x80148704 -> 0x8014870C
int ProfileMgr::GetMaxBands() {}

// Range: 0x8014870C -> 0x80148714
int ProfileMgr::GetMaxRemoteBands() {}

// Range: 0x80148714 -> 0x801487A8
unsigned char ProfileMgr::CanCreateChar(class ProfileMgr * const this /* r31 */) {
    // Local variables
    class Profile * pProfile; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801487A8 -> 0x801487C0
unsigned char ProfileMgr::UnlockAllSongs() {
    // Local variables
    unsigned char t; // r4
}

// Range: 0x801487C0 -> 0x801487CC
void ProfileMgr::RelockSongs() {}

// Range: 0x801487CC -> 0x80148858
unsigned char ProfileMgr::IsSongUnlocked(class ProfileMgr * const this /* r29 */, class Symbol & song /* r30 */) {
    // Local variables
    class Profile * p; // r31
}

// Range: 0x80148858 -> 0x801488FC
void ProfileMgr::UnlockSong(class Symbol & song /* r30 */) {
    // Local variables
    class vector profiles; // r1+0x10
    class Profile * * p; // r31
}

// Range: 0x801488FC -> 0x80148990
void ProfileMgr::RemoveCharFromBand(class ProfileMgr * const this /* r29 */, const class HxGuid & charGuid /* r30 */) {
    // Local variables
    class HxGuid bandGuidCopy; // r1+0x8
    class Profile * iter; // r31
}

// Range: 0x80148990 -> 0x80148B58
void ProfileMgr::GetUniqueProfiles(class vector & profiles /* r28 */, unsigned char only_particpating /* r29 */) {
    // Local variables
    class vector bul; // r1+0x20
    class BandUser * * u; // r30
    class Profile * p; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80148B58 -> 0x80148B60
enum ProfileSaveState ProfileMgr::GetGlobalOptionsSaveState() {}

// Range: 0x80148B60 -> 0x80148BD8
void ProfileMgr::SetGlobalOptionsSaveState(class ProfileMgr * const this /* r30 */, enum ProfileSaveState state /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80148BD8 -> 0x80148CA8
unsigned char ProfileMgr::GlobalOptionsNeedsSave(class ProfileMgr * const this /* r31 */) {
    // Local variables
    int i; // r4
    int i; // r4
    int i; // r4
}

// Range: 0x80148CA8 -> 0x80148CFC
int ProfileMgr::GetGlobalOptionsSize(class ProfileMgr * const this /* r30 */) {
    // Local variables
    int size; // r31
}

// Range: 0x80148CFC -> 0x80148F68
void ProfileMgr::SaveGlobalOptions(class ProfileMgr * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int i; // r29
    int i; // r29
    int i; // r29
}

// Range: 0x80148F68 -> 0x80149268
void ProfileMgr::LoadGlobalOptions(class ProfileMgr * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int version; // r1+0x10
    int i; // r29
    int i; // r29
    int i; // r29

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
}

// Range: 0x80149268 -> 0x80149310
void ProfileMgr::InitSliders(class ProfileMgr * const this /* r29 */) {}

// Range: 0x80149310 -> 0x801493EC
float ProfileMgr::SliderIxToDb(const class ProfileMgr * const this /* r29 */, int ixVol /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801493EC -> 0x801494C8
float ProfileMgr::SliderIxToRatio(const class ProfileMgr * const this /* r29 */, int ixVol /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801494C8 -> 0x80149534
int ProfileMgr::GetSliderStepCount(const class ProfileMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80149534 -> 0x80149BF4
void ProfileMgr::PushAllOptions(class ProfileMgr * const this /* r29 */) {
    // Local variables
    class vector & players; // r0
    class Player * * it; // r28

    // References
    // -> class Rnd & TheRnd;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6FxSend;
    // -> class Game * TheGame;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Synth * TheSynth;
}

// Range: 0x80149BF4 -> 0x80149C04
void ProfileMgr::SetBackgroundVolume() {}

// Range: 0x80149C04 -> 0x80149C14
void ProfileMgr::SetForegroundVolume() {}

// Range: 0x80149C14 -> 0x80149C24
void ProfileMgr::SetFxVolume() {}

// Range: 0x80149C24 -> 0x80149C40
int ProfileMgr::GetFxVolume() {}

// Range: 0x80149C40 -> 0x80149C50
void ProfileMgr::SetCrowdVolume() {}

// Range: 0x80149C50 -> 0x80149CB0
void ProfileMgr::SetVocalCueVolume(class ProfileMgr * const this /* r30 */, int ixVol /* r31 */) {}

// Range: 0x80149CB0 -> 0x80149CC0
void ProfileMgr::SetBassBoost() {}

// Range: 0x80149CC0 -> 0x80149CD0
void ProfileMgr::SetDolby() {}

// Range: 0x80149CD0 -> 0x80149D30
void ProfileMgr::SetOverscan(class ProfileMgr * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80149D30 -> 0x80149D40
void ProfileMgr::SetMono() {}

// Range: 0x80149D40 -> 0x80149D50
void ProfileMgr::SetSyncPresetIx() {}

// Range: 0x80149D50 -> 0x80149D60
float ProfileMgr::GetSongToTaskMgrMs() {}

// Range: 0x80149D60 -> 0x80149D68
float ProfileMgr::GetSongToTaskMgrMsRaw() {}

// Range: 0x80149D68 -> 0x80149D84
void ProfileMgr::SetSongToTaskMgrMsRaw() {}

static class Symbol wii_guitar; // size: 0x4, address: 0x80A4C06C
static class Symbol wii_roguitar; // size: 0x4, address: 0x80A4C074
static class Symbol wii_drums; // size: 0x4, address: 0x80A4C07C
static class Symbol wii_rodrums; // size: 0x4, address: 0x80A4C084
static class Symbol wii_remote; // size: 0x4, address: 0x80A4C08C
static class Symbol wii_classic; // size: 0x4, address: 0x80A4C094
// Range: 0x80149D84 -> 0x80149F14
float ProfileMgr::GetPadExtraLag(int padNum /* r30 */) {
    // Local variables
    float controllerExtraLag; // f31

    // References
    // -> static class Symbol wii_classic;
    // -> static class Symbol wii_remote;
    // -> static class Symbol wii_rodrums;
    // -> static class Symbol wii_drums;
    // -> static class Symbol wii_roguitar;
    // -> static class Symbol wii_guitar;
}

// Range: 0x80149F14 -> 0x80149F74
float ProfileMgr::GetSyncOffset(const class ProfileMgr * const this /* r31 */) {
    // Local variables
    float controllerExtraLag; // f31
}

// Range: 0x80149F74 -> 0x80149F7C
float ProfileMgr::GetSyncOffsetRaw() {}

// Range: 0x80149F7C -> 0x80149F9C
void ProfileMgr::SetSyncOffsetRaw() {}

// Range: 0x80149F9C -> 0x80149FD4
float ProfileMgr::GetExcessVideoLag(const class ProfileMgr * const this /* r31 */) {}

// Range: 0x80149FD4 -> 0x8014A048
void ProfileMgr::SetExcessVideoLag(class ProfileMgr * const this /* r31 */, float ms /* f30 */) {
    // Local variables
    float fOldAudioLag; // f31
}

// Range: 0x8014A048 -> 0x8014A07C
float ProfileMgr::GetExcessAudioLagNeutral(const class ProfileMgr * const this /* r31 */) {}

// Range: 0x8014A07C -> 0x8014A0B0
float ProfileMgr::GetExcessVideoLagNeutral(const class ProfileMgr * const this /* r31 */) {}

// Range: 0x8014A0B0 -> 0x8014A108
float ProfileMgr::GetExcessAudioLag(const class ProfileMgr * const this /* r31 */) {}

// Range: 0x8014A108 -> 0x8014A160
void ProfileMgr::SetExcessAudioLag(class ProfileMgr * const this /* r31 */, float ms /* f31 */) {}

// Range: 0x8014A160 -> 0x8014A21C
void ProfileMgr::SetPlayedBefore() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8014A21C -> 0x8014A29C
unsigned char ProfileMgr::GetPlayedBefore() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8014A29C -> 0x8014A2A4
float ProfileMgr::GetBackgroundVolumeDb() {}

// Range: 0x8014A2A4 -> 0x8014A2AC
float ProfileMgr::GetForegroundVolumeDb() {}

// Range: 0x8014A2AC -> 0x8014A2E4
float ProfileMgr::GetFxVolumeDb(const class ProfileMgr * const this /* r31 */) {}

// Range: 0x8014A2E4 -> 0x8014A2EC
float ProfileMgr::GetVocalCueVolumeDb() {}

// Range: 0x8014A2EC -> 0x8014A2F4
float ProfileMgr::GetCrowdVolumeDb() {}

// Range: 0x8014A2F4 -> 0x8014A3A0
void ProfileMgr::UpdateVocalVolue(class ProfileMgr * const this /* r29 */) {
    // Local variables
    class BandUser * user; // r31
    int padNum; // r4
    class Mic * mic; // r30
    int ixVol; // r0

    // References
    // -> class Synth * TheSynth;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8014A3A0 -> 0x8014A44C
void ProfileMgr::UpdateMicGain(class ProfileMgr * const this /* r29 */) {
    // Local variables
    class BandUser * user; // r31
    int padNum; // r4
    class Mic * mic; // r30
    int ixVol; // r0

    // References
    // -> class Synth * TheSynth;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8014A44C -> 0x8014A4B4
void ProfileMgr::SetUsername(class ProfileMgr * const this /* r31 */) {
    // References
    // -> class Net TheNet;
}

// Range: 0x8014A4B4 -> 0x8014A4C0
void ProfileMgr::OnEnableSigninActivation() {}

static class Symbol is_tour; // size: 0x4, address: 0x80A4C09C
static class Symbol sign_out; // size: 0x4, address: 0x80A4C0A4
static class Message init; // size: 0x8, address: 0x80979370
enum SignoutError {
    kLocalUserSignedOut = 0,
    kBandOwnerSignedOut = 1,
    kProfileOwnerSignedOut = 2,
};
// Range: 0x8014A4C0 -> 0x8014AAA0
class DataNode ProfileMgr::OnMsg(class ProfileMgr * const this /* r24 */) {
    // Local variables
    unsigned char isSignout; // r30
    unsigned char isBadState; // r29
    enum SignoutError errorReason; // r28
    unsigned long signinChangeMask; // r27
    int padCur; // r26
    unsigned char isMatchmaking; // r25
    enum TransitionState ts; // r0
    class Profile * pProfile; // r21
    int playerNum; // r20
    class TourBandLocal * band; // r0
    class BandUser * pSignedOutUser; // r0
    class vector users; // r1+0x38
    class BandUser * * it; // r20
    class BandUser * pOtherUser; // r19
    const char * tour_band_sel_screen; // r19
    class UIScreen * screen; // r0

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol sign_out;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Tour * TheTour;
    // -> class NetSession * TheNetSession;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> struct [anonymous] __RTTI__17MatchmakingScreen;
    // -> class UIManager TheUI;
}

// Range: 0x8014AAA0 -> 0x8014ABA8
class DataNode ProfileMgr::OnMsg(class ProfileMgr * const this /* r27 */, const class ButtonDownMsg & msg /* r28 */) {
    // Local variables
    unsigned char isButtonHandled; // r30
    class Profile * it; // r29
    class DataNode ret; // r1+0x8
}

static class Symbol _s; // size: 0x4, address: 0x80A4C0AC
static class Symbol _s; // size: 0x4, address: 0x80A4C0B4
static class Symbol _s; // size: 0x4, address: 0x80A4C0BC
static class Symbol _s; // size: 0x4, address: 0x80A4C0C4
static class Symbol _s; // size: 0x4, address: 0x80A4C0CC
static class Symbol _s; // size: 0x4, address: 0x80A4C0D4
static class Symbol _s; // size: 0x4, address: 0x80A4C0DC
static class Symbol _s; // size: 0x4, address: 0x80A4C0E4
static class Symbol _s; // size: 0x4, address: 0x80A4C0EC
static class Symbol _s; // size: 0x4, address: 0x80A4C0F4
static class Symbol _s; // size: 0x4, address: 0x80A4C0FC
static class Symbol _s; // size: 0x4, address: 0x80A4C104
static class Symbol _s; // size: 0x4, address: 0x80A4C10C
static class Symbol _s; // size: 0x4, address: 0x80A4C114
static class Symbol _s; // size: 0x4, address: 0x80A4C11C
static class Symbol _s; // size: 0x4, address: 0x80A4C124
static class Symbol _s; // size: 0x4, address: 0x80A4C12C
static class Symbol _s; // size: 0x4, address: 0x80A4C134
static class Symbol _s; // size: 0x4, address: 0x80A4C13C
static class Symbol _s; // size: 0x4, address: 0x80A4C144
static class Symbol _s; // size: 0x4, address: 0x80A4C14C
static class Symbol _s; // size: 0x4, address: 0x80A4C154
static class Symbol _s; // size: 0x4, address: 0x80A4C15C
static class Symbol _s; // size: 0x4, address: 0x80A4C164
static class Symbol _s; // size: 0x4, address: 0x80A4C16C
static class Symbol _s; // size: 0x4, address: 0x80A4C174
static class Symbol _s; // size: 0x4, address: 0x80A4C17C
static class Symbol _s; // size: 0x4, address: 0x80A4C184
static class Symbol _s; // size: 0x4, address: 0x80A4C18C
static class Symbol _s; // size: 0x4, address: 0x80A4C194
static class Symbol _s; // size: 0x4, address: 0x80A4C19C
static class Symbol _s; // size: 0x4, address: 0x80A4C1A4
static class Symbol _s; // size: 0x4, address: 0x80A4C1AC
static class Symbol _s; // size: 0x4, address: 0x80A4C1B4
static class Symbol _s; // size: 0x4, address: 0x80A4C1BC
static class Symbol _s; // size: 0x4, address: 0x80A4C1C4
static class Symbol _s; // size: 0x4, address: 0x80A4C1CC
static class Symbol _s; // size: 0x4, address: 0x80A4C1D4
static class Symbol _s; // size: 0x4, address: 0x80A4C1DC
static class Symbol _s; // size: 0x4, address: 0x80A4C1E4
static class Symbol _s; // size: 0x4, address: 0x80A4C1EC
static class Symbol _s; // size: 0x4, address: 0x80A4C1F4
static class Symbol _s; // size: 0x4, address: 0x80A4C1FC
static class Symbol _s; // size: 0x4, address: 0x80A4C204
static class Symbol _s; // size: 0x4, address: 0x80A4C20C
static class Symbol _s; // size: 0x4, address: 0x80A4C214
static class Symbol _s; // size: 0x4, address: 0x80A4C21C
static class Symbol _s; // size: 0x4, address: 0x80A4C224
static class Symbol _s; // size: 0x4, address: 0x80A4C22C
static class Symbol _s; // size: 0x4, address: 0x80A4C234
static class Symbol _s; // size: 0x4, address: 0x80A4C23C
static class Symbol _s; // size: 0x4, address: 0x80A4C244
static class Symbol _s; // size: 0x4, address: 0x80A4C24C
static class Symbol _s; // size: 0x4, address: 0x80A4C254
static class Symbol _s; // size: 0x4, address: 0x80A4C25C
static class Symbol _s; // size: 0x4, address: 0x80A4C264
static class Symbol _s; // size: 0x4, address: 0x80A4C26C
static class Symbol _s; // size: 0x4, address: 0x80A4C274
static class Symbol _s; // size: 0x4, address: 0x80A4C27C
static class Symbol _s; // size: 0x4, address: 0x80A4C284
static class Symbol _s; // size: 0x4, address: 0x80A4C28C
static class Symbol _s; // size: 0x4, address: 0x80A4C294
static class Symbol _s; // size: 0x4, address: 0x80A4C29C
static class Symbol _s; // size: 0x4, address: 0x80A4C2A4
static class Symbol _s; // size: 0x4, address: 0x80A4C2AC
// Range: 0x8014ABA8 -> 0x8014C91C
class DataNode ProfileMgr::Handle(class ProfileMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0xA8
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

class ProfileMgr TheProfileMgr; // size: 0x278, address: 0x80979388
struct {
    // total size: 0x6C
} __vt__10ProfileMgr; // size: 0x6C, address: 0x80894848
struct {
    // total size: 0x8
} __RTTI__10ProfileMgr; // size: 0x8, address: 0x808948E0
struct {
    // total size: 0xC
} __vt__22ServerStatusChangedMsg; // size: 0xC, address: 0x80894AD0
struct {
    // total size: 0x8
} __RTTI__22ServerStatusChangedMsg; // size: 0x8, address: 0x80894B00
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_List_node<Q29MsgSource4Sink>; // size: 0x8, address: 0x80894CA0
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std39_List_node<Q29MsgSource13EventSinkElem>; // size: 0x8, address: 0x80894CE0
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std34_List_node<Q29MsgSource9EventSink>; // size: 0x8, address: 0x80894D18
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__P7Profile; // size: 0x8, address: 0x80894DA0
// Range: 0x8014C91C -> 0x8014C96C
static void __sinit_\ProfileMgr_cpp() {
    // References
    // -> class ProfileMgr TheProfileMgr;
}


