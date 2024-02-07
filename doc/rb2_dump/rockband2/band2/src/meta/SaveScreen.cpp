/*
    Compile unit: C:\rockband2\band2\src\meta\SaveScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80152E04 -> 0x8015D8B4
*/
class Symbol t; // size: 0x4, address: 0x80A4C2B4
class Symbol t; // size: 0x4, address: 0x80A4C2BC
class Symbol t; // size: 0x4, address: 0x80A4C2C4
class Symbol t; // size: 0x4, address: 0x80A4C2CC
class Symbol t; // size: 0x4, address: 0x80A4C2D4
class DataArray * types; // size: 0x4, address: 0x80A4C2D8
static const char * kStrGlobalCacheName; // size: 0x4, address: 0x80A466F8
// Range: 0x80152E04 -> 0x80152F60
void * SaveScreen::SaveScreen(class SaveScreen * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> struct [anonymous] __vt__10SaveScreen;
}

// Range: 0x80152F60 -> 0x80153094
void * SaveScreen::~SaveScreen(class SaveScreen * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> struct [anonymous] __vt__10SaveScreen;
}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4C2E0
// Range: 0x80153094 -> 0x80153118
unsigned char SaveScreen::AutosaveIsEnabled() {
    // Local variables
    unsigned char isSavingEnabled; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_saving_feature;
}

// Range: 0x80153118 -> 0x80153160
unsigned char SaveScreen::IsReasonToAutoload() {}

// Range: 0x80153160 -> 0x801531C4
unsigned char SaveScreen::SongCacheNeedsWrite(class SaveScreen * const this /* r30 */) {
    // References
    // -> class SongMgr & TheSongMgr;
}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4C2E8
// Range: 0x801531C4 -> 0x801532F0
unsigned char SaveScreen::IsReasonToAutosave(class SaveScreen * const this /* r26 */, unsigned char checkUpload /* r27 */) {
    // Local variables
    unsigned char isSavingEnabled; // r0
    unsigned char b2; // r28
    unsigned char b4; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_saving_feature;
}

static class Symbol saveload_skip_upload; // size: 0x4, address: 0x80A4C2F0
static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4C2F8
static class Symbol modifier_online_feature; // size: 0x4, address: 0x80A4C300
// Range: 0x801532F0 -> 0x80153458
unsigned char SaveScreen::IsReasonToUpload() {
    // Local variables
    unsigned char skipUpload; // r0
    unsigned char isConnected; // r0
    unsigned char needsUpload; // r0

    // References
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_online_feature;
    // -> static class Symbol modifier_saving_feature;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Net TheNet;
    // -> static class Symbol saveload_skip_upload;
}

// Range: 0x80153458 -> 0x80153460
void SaveScreen::SetDialogTitle() {}

// Range: 0x80153460 -> 0x80153468
char * SaveScreen::GetDialogTitle() {}

static class Message init; // size: 0x8, address: 0x80979610
static class Symbol saveload_pad_lost; // size: 0x4, address: 0x80A4C308
// Range: 0x80153468 -> 0x801538BC
void SaveScreen::UpdateJoypadConnectionState(class SaveScreen * const this /* r30 */) {
    // Local variables
    unsigned char oldState; // r4
    int padNum; // r29

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Symbol saveload_pad_lost;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801538BC -> 0x80153918
void SaveScreen::LockToCurrentUser(class SaveScreen * const this /* r31 */) {
    // References
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x80153918 -> 0x80153968
void SaveScreen::RestoreUserLock(class SaveScreen * const this /* r31 */) {
    // References
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x80153968 -> 0x80153B08
void SaveScreen::MessageHelperInit(class SaveScreen * const this /* r30 */, class Symbol & symShortMessage /* r31 */) {
    // Local variables
    class Message msg; // r1+0x20

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
}

// Range: 0x80153B08 -> 0x80153BF8
void SaveScreen::MessageHelperPoll(class SaveScreen * const this /* r31 */) {
    // Local variables
    float elapsed; // f0

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x80153BF8 -> 0x80155038
void SaveScreen::Poll(class SaveScreen * const this /* r30 */) {
    // Local variables
    float elapsed; // f0
    enum CacheResult result; // r4
    enum CacheResult result; // r4
    enum CacheResult result; // r4
    enum CacheResult result; // r0
    enum CacheResult result; // r0
    class BufStream stream; // r1+0x40
    enum CacheResult result; // r0
    enum CacheResult result; // r4
    enum CacheResult result; // r4
    enum CacheResult result; // r4
    enum CacheResult result; // r0
    int size; // r0
    class BufStream stream; // r1+0x1C
    enum CacheResult result; // r4
    enum CacheResult result; // r4
    enum CacheResult result; // r0

    // References
    // -> class SynthWii * TheWiiSynth;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> static const char * kStrGlobalCacheName;
    // -> class SongMgr & TheSongMgr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class CacheMgr * TheCacheMgr;
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class NetSession * TheNetSession;
}

static class Symbol mode; // size: 0x4, address: 0x80A4C310
// Range: 0x80155038 -> 0x8015523C
void SaveScreen::Enter(class SaveScreen * const this /* r30 */, class UIScreen * from /* r31 */) {
    // References
    // -> class Symbol t;
    // -> static class Symbol mode;
    // -> class Net TheNet;
    // -> class Symbol t;
    // -> class Symbol t;
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> class Symbol t;
    // -> class Rnd & TheRnd;
}

// Range: 0x8015523C -> 0x8015543C
void SaveScreen::Exit(class SaveScreen * const this /* r30 */, class UIScreen * to /* r31 */) {
    // References
    // -> class BandUI * TheBandUI;
    // -> class Net TheNet;
    // -> class Symbol t;
    // -> class Symbol t;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Symbol t;
    // -> class Symbol t;
    // -> class Rnd & TheRnd;
}

// Range: 0x8015543C -> 0x80155458
unsigned char SaveScreen::Exiting() {}

// Range: 0x80155458 -> 0x8015550C
int SaveScreen::GetNewSigninPlayerNum() {
    // Local variables
    int playerNum; // r31
    class vector profiles; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x8015550C -> 0x801555C0
int SaveScreen::GetAutosavablePlayerNum() {
    // Local variables
    int playerNum; // r31
    class vector profiles; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x801555C0 -> 0x801557E4
void SaveScreen::InitFirstTimeFlags(class SaveScreen * const this /* r28 */) {
    // Local variables
    enum ControllerType ct; // r4

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x801557E4 -> 0x80155948
void SaveScreen::LoadFirstTimeFlags(class SaveScreen * const this /* r29 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4C318
static class Message msgClear; // size: 0x8, address: 0x80979628
static class Message msg; // size: 0x8, address: 0x80979640
static class Message msg; // size: 0x8, address: 0x80979658
static class Message msg; // size: 0x8, address: 0x80979670
static class Message msg; // size: 0x8, address: 0x80979688
static class Message msg; // size: 0x8, address: 0x809796A0
static class Message msg; // size: 0x8, address: 0x809796B8
static class Message msg; // size: 0x8, address: 0x809796D0
static class Message msg; // size: 0x8, address: 0x809796E8
static class Message msg; // size: 0x8, address: 0x80979700
static class Message msg; // size: 0x8, address: 0x80979718
static class Message msg; // size: 0x8, address: 0x80979730
static class Symbol song_info_cache_name; // size: 0x4, address: 0x80A4C32C
static class Message msgUpdateRead; // size: 0x8, address: 0x80979748
static class Symbol update_song_cache_write; // size: 0x4, address: 0x80A4C334
static class Symbol update_song_cache_write_long; // size: 0x4, address: 0x80A4C33C
static class Message msgUpdateCorrupt; // size: 0x8, address: 0x80979760
static class Message msg; // size: 0x8, address: 0x80979778
static class Message msg; // size: 0x8, address: 0x80979790
static class Message msg; // size: 0x8, address: 0x809797A8
static class Symbol global_options_cache_name; // size: 0x4, address: 0x80A4C348
static class Message msgUpdateRead; // size: 0x8, address: 0x809797C0
static class Symbol update_global_options_write; // size: 0x4, address: 0x80A4C350
static class Symbol update_global_options_write_long; // size: 0x4, address: 0x80A4C358
static class Message msgUpdateCorrupt; // size: 0x8, address: 0x809797D8
static class Message msg; // size: 0x8, address: 0x809797F0
static class Message msg; // size: 0x8, address: 0x80979808
static class Message msg; // size: 0x8, address: 0x80979820
static class Message msg; // size: 0x8, address: 0x80979838
static class Message msg; // size: 0x8, address: 0x80979850
static class Message msg; // size: 0x8, address: 0x80979868
static class Message msg; // size: 0x8, address: 0x80979880
static class Message msg; // size: 0x8, address: 0x80979898
static class Message msg; // size: 0x8, address: 0x809798B0
static class Message msg; // size: 0x8, address: 0x809798C8
static class Message msg; // size: 0x8, address: 0x809798E0
static class Message msg; // size: 0x8, address: 0x809798F8
static class Message msg; // size: 0x8, address: 0x80979910
static class Message msg; // size: 0x8, address: 0x80979928
static class Symbol update_song_cache_write; // size: 0x4, address: 0x80A4C36C
static class Symbol update_song_cache_write_long; // size: 0x4, address: 0x80A4C374
static class Message msg; // size: 0x8, address: 0x80979940
static class Message msg; // size: 0x8, address: 0x80979958
static class Message msg; // size: 0x8, address: 0x80979970
static class Message msg; // size: 0x8, address: 0x80979988
static class Message msg; // size: 0x8, address: 0x809799A0
static class Message msg; // size: 0x8, address: 0x809799B8
static class Message msg; // size: 0x8, address: 0x809799D0
static class Message msg; // size: 0x8, address: 0x809799E8
static class Message msg; // size: 0x8, address: 0x80979A00
static class Message msg; // size: 0x8, address: 0x80979A18
static class Message msg; // size: 0x8, address: 0x80979A30
static class Message msg; // size: 0x8, address: 0x80979A48
static class Message msg; // size: 0x8, address: 0x80979A60
static class Message msg; // size: 0x8, address: 0x80979A78
static class Message msg; // size: 0x8, address: 0x80979A90
static class Message msg; // size: 0x8, address: 0x80979AA8
static class Message msg; // size: 0x8, address: 0x80979AC0
static class Message msgClear; // size: 0x8, address: 0x80979AD8
static class Message msg; // size: 0x8, address: 0x80979AF0
static class Message msg; // size: 0x8, address: 0x80979B08
// Range: 0x80155948 -> 0x8015AAB8
void SaveScreen::SetState(class SaveScreen * const this /* r28 */, enum State state /* r31 */) {
    // Local variables
    unsigned char isSavingEnabled; // r0
    int userNum; // r4
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    int size; // r29
    unsigned char ret; // r0
    class BufStream stream; // r1+0x5C8
    unsigned char ret; // r0
    unsigned char ret; // r0
    int optionsSize; // r29
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    unsigned char ret; // r0
    int size; // r29
    unsigned char ret; // r0
    int size; // r31
    class BufStream stream; // r1+0x5A4
    unsigned char ret; // r0
    unsigned char ret; // r0
    int userNum; // r4
    int userNum; // r4
    int userNum; // r4
    enum ProfileSaveState stateComplete; // r0
    int userNum; // r4
    class Profile * pProfile; // r29
    int userNum; // r4
    int padNum; // r4
    int userNum; // r4
    unsigned char wasDisabled; // r0

    // References
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class NetSync * TheNetSync;
    // -> static class Message msgClear;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class InputMgr * TheInputMgr;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class EntityUploader & TheEntityUploader;
    // -> const char * kAssertStr;
    // -> static class Message msg;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol update_song_cache_write_long;
    // -> static class Symbol update_song_cache_write;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class Rnd & TheRnd;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msgUpdateCorrupt;
    // -> static class Symbol update_global_options_write_long;
    // -> static class Symbol update_global_options_write;
    // -> static class Message msgUpdateRead;
    // -> static class Symbol global_options_cache_name;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static const char * kStrGlobalCacheName;
    // -> static class Message msgUpdateCorrupt;
    // -> static class Symbol update_song_cache_write_long;
    // -> static class Symbol update_song_cache_write;
    // -> static class Message msgUpdateRead;
    // -> static class Symbol song_info_cache_name;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class Debug TheDebug;
    // -> static class Message msg;
    // -> class CacheMgr * TheCacheMgr;
    // -> class SongMgr & TheSongMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> class MemcardMgr TheMemcardMgr;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msgClear;
    // -> struct [anonymous] __vt__7Message;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_saving_feature;
}

// Range: 0x8015AAB8 -> 0x8015AB08
void SaveScreen::SaveLoadErrorSetState() {}

// Range: 0x8015AB08 -> 0x8015ABC0
unsigned char SaveScreen::IgnoreInput() {}

// Range: 0x8015ABC0 -> 0x8015AC48
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r30 */, const class ButtonDownMsg & msg /* r31 */) {}

// Range: 0x8015AC48 -> 0x8015AD1C
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r31 */) {
    // Local variables
    class DataNode node; // r1+0x8
}

// Range: 0x8015AD1C -> 0x8015BA64
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r29 */, const class UIComponentSelectDoneMsg & msg /* r30 */) {
    // Local variables
    unsigned char isEventDialogOnTop; // r0
    class DataNode node; // r1+0x8
    enum State prevState; // r25

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class Debug TheDebug;
}

// Range: 0x8015BA64 -> 0x8015BBA4
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8015BBA4 -> 0x8015BD08
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8015BD08 -> 0x8015C060
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r29 */, const class MCResultMsg & msg /* r30 */) {
    // Local variables
    enum MCResult result; // r0

    // References
    // -> class Rnd & TheRnd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol is_meta_loading; // size: 0x4, address: 0x80A4C390
// Range: 0x8015C060 -> 0x8015C440
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r28 */, const class RockCentralOpCompleteMsg & msg /* r29 */) {
    // Local variables
    int sizeArg2; // r30
    class DataArray * srcArray; // r30
    int dstIndex; // r24
    int srcIndex; // r23
    unsigned char isMetaLoading; // r0

    // References
    // -> static class Symbol is_meta_loading;
    // -> class UploadErrorMgr * TheUploadErrorMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8015C440 -> 0x8015C4D0
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x8015C4D0 -> 0x8015C5A8
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r31 */) {}

// Range: 0x8015C5A8 -> 0x8015C654
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r29 */, const class JoypadReassignMsg & msg /* r30 */) {}

// Range: 0x8015C654 -> 0x8015C6DC
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r30 */) {}

// Range: 0x8015C6DC -> 0x8015C724
class DataNode SaveScreen::OnPadLostDismissed() {}

// Range: 0x8015C724 -> 0x8015C844
class DataNode SaveScreen::OnPadLostDisableAutosave(class SaveScreen * const this /* r5 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8015C844 -> 0x8015CAD4
class DataNode SaveScreen::OnMsg(class SaveScreen * const this /* r30 */, const class InviteAcceptedMsg & msg /* r25 */) {
    // References
    // -> struct [anonymous] __vt__17InviteAcceptedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

static class Symbol _s; // size: 0x4, address: 0x80A4C398
static class Symbol _s; // size: 0x4, address: 0x80A4C3A0
static class Symbol _s; // size: 0x4, address: 0x80A4C3A8
static class Symbol _s; // size: 0x4, address: 0x80A4C3B0
static class Symbol _s; // size: 0x4, address: 0x80A4C3B8
static class Symbol _s; // size: 0x4, address: 0x80A4C3C0
static class Symbol _s; // size: 0x4, address: 0x80A4C3C8
static class Symbol _s; // size: 0x4, address: 0x80A4C3D0
static class Symbol _s; // size: 0x4, address: 0x80A4C3D8
static class Symbol _s; // size: 0x4, address: 0x80A4C3E0
static class Symbol _s; // size: 0x4, address: 0x80A4C3E8
static class Symbol _s; // size: 0x4, address: 0x80A4C3F0
static class Symbol _s; // size: 0x4, address: 0x80A4C3F8
static class Symbol _s; // size: 0x4, address: 0x80A4C400
static class Symbol _s; // size: 0x4, address: 0x80A4C408
static class Symbol _s; // size: 0x4, address: 0x80A4C410
// Range: 0x8015CAD4 -> 0x8015D8B4
class DataNode SaveScreen::Handle(class SaveScreen * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x120
    class DataNode r; // r1+0x118
    class DataNode r; // r1+0x110
    class DataNode r; // r1+0x108
    class DataNode r; // r1+0x100
    class DataNode r; // r1+0xF8
    class DataNode r; // r1+0xF0
    class DataNode r; // r1+0xE8
    class DataNode r; // r1+0xE0
    class DataNode r; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode _n; // r1+0xA8

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
}

struct {
    // total size: 0x80
} __vt__10SaveScreen; // size: 0x80, address: 0x80896550
struct {
    // total size: 0x10
} __vt__11MCResultMsg; // size: 0x10, address: 0x80896638
struct {
    // total size: 0x8
} __RTTI__11MCResultMsg; // size: 0x8, address: 0x80896660
struct {
    // total size: 0xC
} __vt__15DeviceChosenMsg; // size: 0xC, address: 0x80896668
struct {
    // total size: 0x8
} __RTTI__15DeviceChosenMsg; // size: 0x8, address: 0x80896698
struct {
    // total size: 0xC
} __vt__17NoDeviceChosenMsg; // size: 0xC, address: 0x808966A0
struct {
    // total size: 0x8
} __RTTI__17NoDeviceChosenMsg; // size: 0x8, address: 0x808966D0
struct {
    // total size: 0xC
} __vt__17StorageChangedMsg; // size: 0xC, address: 0x80896710
struct {
    // total size: 0x8
} __RTTI__17StorageChangedMsg; // size: 0x8, address: 0x80896740
struct {
    // total size: 0xC
} __vt__17JoypadReassignMsg; // size: 0xC, address: 0x808969F8
struct {
    // total size: 0x8
} __RTTI__17JoypadReassignMsg; // size: 0x8, address: 0x80896A28
struct _OKToMemCpy {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class set {
    // total size: 0x18
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class UploadErrorMgr : public Object {
    // total size: 0x40
    class set mDisplayedErrors; // offset 0x28, size 0x18
};
struct CacheIDStoreEntry {
    // total size: 0x8
    class Symbol mName; // offset 0x0, size 0x4
    class CacheID * mCacheID; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct CacheIDStoreEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct CacheIDStoreEntry * _M_start; // offset 0x0, size 0x4
    struct CacheIDStoreEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum OpType {
    kOpNone = 0,
    kOpSearch = 1,
    kOpChoose = 2,
    kOpMount = 3,
    kOpUnmount = 4,
    kOpDelete = 5,
};
class CacheMgr {
    // total size: 0x18
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class vector mCacheIDStore; // offset 0x4, size 0xC
private:
    enum OpType mOpCur; // offset 0x10, size 0x4
    enum CacheResult mLastResult; // offset 0x14, size 0x4
};
enum quitType {
    none = 0,
    shutdown = 1,
    restart = 2,
    menu = 3,
    datamanager = 4,
};

