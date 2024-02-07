/*
    Compile unit: C:\rockband2\band2\src\game\GameConfig.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80055D00 -> 0x8005DACC
*/
class Symbol t; // size: 0x4, address: 0x80A4959C
class Symbol t; // size: 0x4, address: 0x80A495A4
class Symbol t; // size: 0x4, address: 0x80A495AC
class GameConfig * TheGameConfig; // size: 0x4, address: 0x80A495B0
static class Symbol venues; // size: 0x4, address: 0x80A495B8
static class Symbol INTRO; // size: 0x4, address: 0x80A495C0
// Range: 0x80055D00 -> 0x80055F00
void * GameConfig::GameConfig(class GameConfig * const this /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Symbol INTRO;
    // -> static class Symbol venues;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameConfig * TheGameConfig;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__10GameConfig;
}

// Range: 0x80055F00 -> 0x800560C0
void * GameConfig::~GameConfig(class GameConfig * const this /* r29 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Net TheNet;
    // -> struct [anonymous] __vt__10GameConfig;
}

static class Symbol venues; // size: 0x4, address: 0x80A495C8
static class Symbol INTRO; // size: 0x4, address: 0x80A495D0
// Range: 0x800560C0 -> 0x80056214
void GameConfig::Reset(class GameConfig * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongOfferProvider * TheSongOfferProvider;
    // -> class InputMgr * TheInputMgr;
    // -> class NetSync * TheNetSync;
    // -> static class Symbol INTRO;
    // -> static class Symbol venues;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * gNullStr;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x80056214 -> 0x80056264
unsigned char GameConfig::IsMultiplayerVs() {
    // References
    // -> class GameMode * TheGameMode;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80056264 -> 0x8005633C
int GameConfig::GetTrackNum(const class GameConfig * const this /* r30 */, int player /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8005633C -> 0x8005642C
enum Difficulty GameConfig::GetAverageDifficulty() {
    // Local variables
    int num_players; // r31
    int total_diff; // r30
    class vector users; // r1+0xC
    class BandUser * * it; // r29
    class BandUser * pUser; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8005642C -> 0x80056524
enum Difficulty GameConfig::GetMaxDifficulty() {
    // Local variables
    int max_diff; // r1+0x10
    class vector users; // r1+0x14
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol joypad; // size: 0x4, address: 0x80A495D8
static class Symbol controller_mapping; // size: 0x4, address: 0x80A495E0
// Range: 0x80056524 -> 0x8005674C
class Symbol GameConfig::GetController(class BandUser * user /* r28 */) {
    // Local variables
    unsigned char lefty; // r29
    class GameplayOptions * options; // r30
    class Symbol type; // r1+0x20
    class DataArray * mapping; // r0
    class DataArray * assoc; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol controller_mapping;
    // -> static class Symbol joypad;
}

// Range: 0x8005674C -> 0x80056754
class Symbol GameConfig::GetVenue() {}

// Range: 0x80056754 -> 0x80056788
unsigned char GameConfig::IsPlayerLocal() {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol vocals; // size: 0x4, address: 0x80A495E8
// Range: 0x80056788 -> 0x80056A38
unsigned char GameConfig::IsMissingMic(int player /* r27 */, unsigned char needTwo /* r28 */) {
    // Local variables
    class BandUser * pUser; // r29
    enum ControllerType ctOverride; // r0
    class vector users; // r1+0x10
    class BandUser * * it; // r29
    class BandUser * pUserCur; // r31

    // References
    // -> class Synth * TheSynth;
    // -> static class Symbol vocals;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80056A38 -> 0x80056B58
unsigned char GameConfig::IsInstrumentUsed(class Symbol & inst /* r29 */) {
    // Local variables
    class vector users; // r1+0x14
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80056B58 -> 0x80056C78
unsigned char GameConfig::IsOnlyInstrumentUsed(class Symbol & inst /* r29 */) {
    // Local variables
    class vector users; // r1+0x14
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80056C78 -> 0x80056DB4
unsigned char GameConfig::IsControllerConnected(enum ControllerType controllerType /* r28 */, enum GameControllerState state /* r29 */) {
    // Local variables
    class vector users; // r1+0x10
    class BandUser * * it; // r31
    class BandUser * pUser; // r30
    unsigned char participating; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80056DB4 -> 0x80056F14
class DataNode GameConfig::OnIsControllerConnected(const class GameConfig * const this /* r28 */, class DataArray * a /* r29 */) {
    // Local variables
    const class DataNode & arg; // r3
    enum ControllerType ct; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80056F14 -> 0x80056FA4
unsigned char GameConfig::CanEndGame() {
    // Local variables
    int leaderNum; // r30

    // References
    // -> class Net TheNet;
    // -> class SessionMgr * TheSessionMgr;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80056FA4 -> 0x80056FF8
void GameConfig::SetVenue(class GameConfig * const this /* r31 */) {}

static class Symbol none; // size: 0x4, address: 0x80A495F0
// Range: 0x80056FF8 -> 0x80057168
void GameConfig::AssignTracks(class GameConfig * const this /* r26 */) {
    // Local variables
    int p; // r27
    class BandUser * cfg; // r31
    unsigned char isRemote; // r0

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol none;
}

static class Symbol variant; // size: 0x4, address: 0x80A495F8
static class Symbol objects; // size: 0x4, address: 0x80A49600
static class Symbol symWorldDir; // size: 0x4, address: 0x80A49608
static class Symbol types; // size: 0x4, address: 0x80A49610
// Range: 0x80057168 -> 0x800572B4
class DataArray * GameConfig::VenueData(class Symbol & venue /* r30 */) {
    // Local variables
    char buffer[256]; // r1+0x20
    class DataArray * dataTypes; // r31
    class DataArray * arr; // r0

    // References
    // -> static class Symbol types;
    // -> static class Symbol symWorldDir;
    // -> static class Symbol objects;
    // -> static class Symbol variant;
}

// Range: 0x800572B4 -> 0x800572DC
class Player * GameConfig::GetPlayer() {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800572DC -> 0x80057304
class Track * GameConfig::GetTrack() {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol vocals; // size: 0x4, address: 0x80A49618
static class Symbol drum; // size: 0x4, address: 0x80A49620
// Range: 0x80057304 -> 0x80057498
class DataNode GameConfig::OnMsg(class GameConfig * const this /* r27 */, const class NewRemotePlayerMsg & msg /* r28 */) {
    // Local variables
    int leaderNum; // r29
    int newSlot; // r29
    enum ControllerType controllerType; // r0
    class BandUser * pUser; // r0
    class BandUser * pUser; // r0

    // References
    // -> class PassiveMessenger * ThePassiveMessenger;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol drum;
    // -> static class Symbol vocals;
    // -> class GameMode * TheGameMode;
    // -> class NetSession * TheNetSession;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x80057498 -> 0x8005759C
class DataNode GameConfig::OnMsg(class GameConfig * const this /* r29 */, const class RemotePlayerLeftMsg & msg /* r30 */) {
    // Local variables
    class BandUser * pUser; // r31

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class PassiveMessenger * ThePassiveMessenger;
}

// Range: 0x8005759C -> 0x800576C4
class DataNode GameConfig::OnMsg(const class XMPStateChangedMsg & msg /* r28 */) {
    // Local variables
    class MetaMusic * pmm; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9MetaPanel;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x800576C4 -> 0x800576CC
void GameConfig::DisableAvailablePlayer() {}

// Range: 0x800576CC -> 0x80057774
unsigned char GameConfig::IsControllerAvailable(const class GameConfig * const this /* r29 */, enum ControllerType controllerType /* r30 */) {
    // Local variables
    int flags; // r0
    int num; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80057774 -> 0x8005778C
int GameConfig::MaxNumControllers() {}

static class Symbol guitar; // size: 0x4, address: 0x80A49628
// Range: 0x8005778C -> 0x800578C0
unsigned char GameConfig::HasParticipatingGuitarController() {
    // Local variables
    class vector users; // r1+0x10
    class BandUser * * it; // r30
    class BandUser * pUser; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol guitar;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A49630
// Range: 0x800578C0 -> 0x80057B10
void GameConfig::AutoAssignMissingSlots() {
    // Local variables
    enum ControllerType controllerType; // r28
    class vector & users; // r0
    class BandUser * * it; // r27
    class BandUser * pUser; // r26

    // References
    // -> class GameMode * TheGameMode;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol is_h2h_arrangement;
}

static class Symbol bass; // size: 0x4, address: 0x80A49638
// Range: 0x80057B10 -> 0x800580F8
void GameConfig::GetInstrumentTrackOrder(class GameConfig * const this /* r26 */, class vector * out /* r27 */, unsigned char gemTracksOnly /* r28 */) {
    // Local variables
    int guitar0_player; // r24
    int guitar1_player; // r30
    int drum_player; // r29
    int vocal_player; // r0
    enum TrackInstrument guitar0_instrument; // r1+0x74
    enum TrackInstrument guitar1_instrument; // r1+0x70
    enum TrackInstrument localGuitarInstrument; // r1+0x6C
    enum TrackInstrument netGuitarInstrument; // r1+0x68

    // References
    // -> static class Symbol bass;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800580F8 -> 0x80058188
unsigned char GameConfig::IsControllerTypeWithLowestPadNum(enum ControllerType ct /* r29 */) {
    // Local variables
    int padNum; // r31
    int i; // r30
    int userNum; // r0
    class BandUser * pUser; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80058188 -> 0x800581EC
void GameConfig::SetPlayerSlotNum(class GameConfig * const this /* r31 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800581EC -> 0x80058300
void GameConfig::SetActiveRoster(class GameConfig * const this /* r26 */, unsigned char set /* r27 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r29
    class BandUser * pUser; // r28

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol world; // size: 0x4, address: 0x80A49640
static class Symbol net; // size: 0x4, address: 0x80A49648
// Range: 0x80058300 -> 0x800583E8
class DataNode GameConfig::OnLoadAllChars(class GameConfig * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    unsigned char configure_for_world; // r1+0x9
    unsigned char net_sync; // r1+0x8

    // References
    // -> static class Symbol net;
    // -> static class Symbol world;
}

// Range: 0x800583E8 -> 0x80058474
void GameConfig::OnSetRemotePlayerTrackType(int playerNum /* r30 */) {
    // Local variables
    class SetPlayerTrackTypeMsg msg; // r1+0x18

    // References
    // -> class Net TheNet;
}

// Range: 0x800584D4 -> 0x80058560
void GameConfig::OnSetRemotePlayerDifficulty(int playerNum /* r30 */) {
    // Local variables
    class SetPlayerDifficultyMsg msg; // r1+0x18

    // References
    // -> class Net TheNet;
}

// Range: 0x800585C0 -> 0x8005860C
void GameConfig::OnReassignPlayerTrackType(int playerNum /* r31 */) {
    // Local variables
    class ReassignPlayerTrackTypeMsg msg; // r1+0x8

    // References
    // -> class Net TheNet;
}

// Range: 0x8005864C -> 0x8005868C
void GameConfig::OnSendH2HSetTracksMsg() {
    // Local variables
    class H2HSetTrackTypesMsg msg; // r1+0x8

    // References
    // -> class Net TheNet;
    // -> struct [anonymous] __vt__19H2HSetTrackTypesMsg;
}

// Range: 0x800586CC -> 0x800587F0
class DataNode GameConfig::OnGetSectionBounds(class GameConfig * const this /* r31 */, class DataArray * a /* r30 */) {
    // Local variables
    float start; // r1+0xC
    float end; // r1+0x8
}

// Range: 0x800587F0 -> 0x80058A24
class DataNode GameConfig::OnGetSectionBoundsTick(class GameConfig * const this /* r28 */, class DataArray * a /* r31 */) {
    // Local variables
    const struct PracticeSection & sec; // r0

    // References
    // -> class Game * TheGame;
}

// Range: 0x80058A24 -> 0x80058A70
void GameConfig::GetSectionBoundsTick(int & start /* r30 */, int & end /* r31 */) {
    // Local variables
    const struct PracticeSection & sec; // r0
}

// Range: 0x80058A70 -> 0x80058B14
class DataNode GameConfig::OnGetSection(class GameConfig * const this /* r30 */, class DataArray * a /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80058B14 -> 0x80058BD4
class DataNode GameConfig::OnSetSection(class GameConfig * const this /* r29 */, class DataArray * a /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class Rand {
    // total size: 0x410
    unsigned int mRandIndex1; // offset 0x0, size 0x4
    unsigned int mRandIndex2; // offset 0x4, size 0x4
    unsigned int mRandTable[256]; // offset 0x8, size 0x400
    float mSpareGaussianValue; // offset 0x408, size 0x4
    unsigned char mSpareGaussianAvailable; // offset 0x40C, size 0x1
};
static class Rand gPrefabGroupRand; // size: 0x410, address: 0x80976E48
static class DataArray * groups; // size: 0x4, address: 0x80A4964C
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80058BD4 -> 0x80059218
class DataArray * GetAppropriatePrefabGroup(class Symbol & genre /* r26 */, class Symbol & decade /* r27 */) {
    // Local variables
    class vector possibleGroups; // r1+0x88
    class vector possibleGenreGroups; // r1+0x7C
    class vector possibleDecadeGroups; // r1+0x70
    int i; // r28
    class DataArray * keys; // r31
    class DataArray * chars; // r1+0x5C
    unsigned char hasGenre; // r0
    unsigned char hasDecade; // r0

    // References
    // -> class Debug TheDebug;
    // -> static class Rand gPrefabGroupRand;
    // -> const char * gNullStr;
    // -> static class DataArray * groups;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class DataArray * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DataArray * * _M_start; // offset 0x0, size 0x4
    class DataArray * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
static class LoadAllCharsMsg msg; // size: 0x4, address: 0x80A49654
static class Symbol bass; // size: 0x4, address: 0x80A4965C
static class Symbol guitar; // size: 0x4, address: 0x80A49664
static class Symbol is_band_arrangement; // size: 0x4, address: 0x80A4966C
static class Symbol BAND_COOP_CHARS; // size: 0x4, address: 0x80A49674
class list : public _List_base {
    // total size: 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x80059218 -> 0x8005A22C
void GameConfig::LoadAllChars(class GameConfig * const this /* r30 */, unsigned char configure_for_world /* r31 */) {
    // Local variables
    class Symbol song; // r1+0x13C
    class Symbol vocal_gender; // r1+0x138
    class Symbol genre; // r1+0x134
    class Symbol decade; // r1+0x130
    class DataArray * group; // r27
    unsigned char coop; // r26
    int maxSlot; // r0
    class list active_insts; // r1+0x1B0
    class list active_tracks; // r1+0x1A8
    class list jukebox_members; // r1+0x1A0
    class list choosen_guids; // r1+0x198
    class vector users; // r1+0x20C
    class BandUser * * it; // r25
    class BandUser * pUser; // r24
    enum ControllerType controllerType; // r23
    class CharData * cd; // r22
    enum TrackType trackType; // r19
    int index; // r18
    enum TrackType replaceTrackType; // r20
    class BandUser * user; // r0
    class Profile * leaderProfile; // r18
    class TourBandLocal * band; // r0
    class vector roster; // r1+0x200
    enum TrackType trackTypes[4]; // r1+0x1F0
    enum ControllerType controllerTypes[4]; // r1+0x1E0
    int i; // r22
    class Profile * profile; // r0
    class TourCharLocal * charLocal; // r0
    enum TrackType trackType; // r23
    enum ControllerType controllerType; // r18
    class list prefabs; // r1+0x190
    class DataArray * npc_names; // r22
    class String macro; // r1+0x1D0
    int npc; // r1+0x12C
    int i; // r23
    class String name; // r1+0x1C4
    int pos; // r0
    class Symbol symTrack; // r1+0x128
    enum TrackType track; // r1+0x124
    enum ControllerType playerControllerType; // r24
    const class CharData * npc_char; // r25
    class TourBand * tb; // r0
    class CharData * stand_in; // r18
    const class HxGuid & guid; // r26
    class Symbol gender; // r1+0x120
    const class CharData * p; // r18
    const class PrefabChar * prefab; // r0

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std23_List_node<PC8CharData>;
    // -> struct [anonymous] __RTTI__10PrefabChar;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__14TourCharRemote;
    // -> class Tour * TheTour;
    // -> static class Symbol BAND_COOP_CHARS;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> class ProfileMgr TheProfileMgr;
    // -> class SessionMgr * TheSessionMgr;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9TrackType>;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<14ControllerType>;
    // -> class CharCache * TheCharCache;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6HxGuid>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class JukeboxPanel * TheJukeboxPanel;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> class SongMgr & TheSongMgr;
    // -> const char * gNullStr;
    // -> static class Symbol is_band_arrangement;
    // -> static class Symbol guitar;
    // -> static class Symbol bass;
    // -> static class Rand gPrefabGroupRand;
    // -> class Net TheNet;
    // -> static class LoadAllCharsMsg msg;
    // -> struct [anonymous] __vt__15LoadAllCharsMsg;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    enum ControllerType _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    enum TrackType _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    class HxGuid _M_data; // offset 0x8, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std19_List_node<6HxGuid>; // size: 0x8, address: 0x80874580
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<14ControllerType>; // size: 0x8, address: 0x808745B8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<9TrackType>; // size: 0x8, address: 0x808745E8
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    const class CharData * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std23_List_node<PC8CharData>; // size: 0x8, address: 0x80874620
// Range: 0x8005A22C -> 0x8005A458
void GameConfig::GetRandomTrackAndControllerTypes(enum TrackType * t /* r29 */, enum ControllerType * c /* r30 */) {
    // Local variables
    enum TrackType trackTypes[4]; // r1+0x40
    enum ControllerType controllerTypes[4]; // r1+0x30
    class vector indices; // r1+0x24
    int i; // r1+0x20
    int i; // r31
    int j; // r0
    int index; // r1+0x1C
}

// Range: 0x8005A458 -> 0x8005A6CC
class DataNode GameConfig::ForEach(const class DataArray * a /* r27 */, unsigned char user /* r28 */, unsigned char local_only /* r29 */) {
    // Local variables
    class DataNode tmp; // r1+0x28
    class vector users; // r1+0x30
    class BandUser * * it; // r30
    class BandUser * pUser; // r25
    int j; // r25

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8005A6CC -> 0x8005A748
unsigned char GameConfig::IsVenueAvailable(class GameConfig * const this /* r30 */) {
    // Local variables
    unsigned char multi_only; // r1+0x8
}

// Range: 0x8005A748 -> 0x8005A810
int GameConfig::GetOriginalTrackNum(int player /* r30 */) {
    // References
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8005A810 -> 0x8005A8A8
char * GameConfig::GetVenueDir(class Symbol & venue /* r30 */) {
    // Local variables
    char base[256]; // r1+0x10

    // References
    // -> class Debug TheDebug;
}

static class Symbol max_players; // size: 0x4, address: 0x80A4967C
// Range: 0x8005A8A8 -> 0x8005A90C
int GameConfig::GetNumPlayersAllowed() {
    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol max_players;
}

static class Symbol ranked; // size: 0x4, address: 0x80A49684
// Range: 0x8005A90C -> 0x8005A97C
unsigned char GameConfig::IsRanked() {
    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol ranked;
}

static class Symbol local_network; // size: 0x4, address: 0x80A4968C
// Range: 0x8005A97C -> 0x8005A9EC
unsigned char GameConfig::IsLocalNetwork() {
    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol local_network;
}

static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A49694
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x8005A9EC -> 0x8005AC28
int GameConfig::WinningPlayer() {
    // Local variables
    class list players; // r1+0x38
    int player0; // r31
    int player1; // r29
    enum EndGameResult result; // r0

    // References
    // -> class Game * TheGame;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class User * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4969C
static class Symbol separate_parts; // size: 0x4, address: 0x80A496A4
// Range: 0x8005AC28 -> 0x8005AE3C
unsigned int GameConfig::LeaderboardID(const class GameConfig * const this /* r29 */) {
    // Local variables
    unsigned char pro; // r0
    enum TrackType trackType; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol separate_parts;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
}

// Range: 0x8005AE3C -> 0x8005AE48
unsigned int GameConfig::PublicID() {}

// Range: 0x8005AE48 -> 0x8005AF10
void GameConfig::SyncSave(const class GameConfig * const this /* r29 */, class BinStream & dest /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x8005AF10 -> 0x8005AFE4
void GameConfig::SyncLoad(class GameConfig * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    char leader; // r1+0xA
    int i; // r31
    char slot; // r1+0x9

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x8005AFE4 -> 0x8005AFE8
unsigned char GameConfig::HasSyncPermission() {}

static class Message game_changed; // size: 0x8, address: 0x80977270
// Range: 0x8005AFE8 -> 0x8005B128
void GameConfig::OnSynchronized() {
    // References
    // -> class UIManager TheUI;
    // -> static class Message game_changed;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8005B128 -> 0x8005B454
void GameConfig::AuthenticationData(class BinStream & dest /* r29 */, const class User * user /* r30 */) {
    // Local variables
    enum TourMode tMode; // r0
    class TourBand * band; // r27
    class vector members; // r1+0x2C
    int n; // r27
    class vector users; // r1+0x20
    const class BandUser * pBandUser; // r27
    class BandUser * const * it; // r27

    // References
    // -> struct [anonymous] __RTTI__4User;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
    // -> class BandUI * TheBandUI;
}

// Range: 0x8005B454 -> 0x8005B468
static void AlertIfMemberRejected() {
    // References
    // -> class PassiveMessenger * ThePassiveMessenger;
}

// Range: 0x8005B468 -> 0x8005B828
unsigned char GameConfig::AuthenticateJoin(const class GameConfig * const this /* r27 */, class BinStream & authData /* r28 */, int & customError /* r29 */) {
    // Local variables
    unsigned char invited; // r0
    unsigned char isBandMember; // r30
    class TourBand * band; // r26
    unsigned char numGuids; // r1+0xF
    unsigned char valid; // r24
    int n; // r23
    class HxGuid guid; // r1+0x20
    int needGuitar; // r23
    int needDrummer; // r24
    int needVocalist; // r25
    class vector users; // r1+0x14
    enum ControllerType controller; // r0
    int numPlayers; // r1+0x10
    unsigned char failed; // r26
    int n; // r27
    unsigned char type; // r1+0xE
    enum ControllerType controller; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
    // -> class NetSession * TheNetSession;
}

// Range: 0x8005B828 -> 0x8005B8B8
void GameConfig::SetJoiningAllowed(unsigned char joiningAllowed /* r30 */) {
    // Local variables
    int leaderNum; // r31

    // References
    // -> class Tour * TheTour;
    // -> class NetSession * TheNetSession;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x8005B8B8 -> 0x8005B90C
void GameConfig::ChangeRandomSeed(class GameConfig * const this /* r31 */) {}

static class Symbol vocals; // size: 0x4, address: 0x80A496AC
// Range: 0x8005B90C -> 0x8005BC68
void GameConfig::AssignUSBMics() {
    // Local variables
    int voc0; // r30
    int voc1; // r29
    class vector users; // r1+0xC
    class BandUser * * it; // r28
    class BandUser * pUser; // r26
    unsigned char vox; // r0
    int tmp; // r0
    int pad; // r4
    int tmp; // r0
    int i; // r26
    class BandUser * * it; // r26
    class BandUser * pUser; // r27
    int pad; // r4

    // References
    // -> class Synth * TheSynth;
    // -> class Game * TheGame;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol vocals;
}

// Range: 0x8005BC68 -> 0x8005BD14
void GameConfig::GetSectionBounds(float & start /* r27 */, float & end /* r28 */) {
    // Local variables
    const struct PracticeSection & sec; // r0

    // References
    // -> class Game * TheGame;
}

// Range: 0x8005BD14 -> 0x8005BD28
void GameConfig::GetPracticeSections() {}

static class Symbol joypad; // size: 0x4, address: 0x80A496B4
static class Symbol five_way_controllers; // size: 0x4, address: 0x80A496BC
// Range: 0x8005BD28 -> 0x8005BEDC
int GameConfig::GetFxSwitchPosition(int player /* r30 */) {
    // Local variables
    class DataArray * supported; // r28
    int i; // r27
    int lookup[30]; // r1+0x20
    float val; // f0

    // References
    // -> static class Symbol five_way_controllers;
    // -> static class Symbol joypad;
}

// Range: 0x8005BEDC -> 0x8005C090
unsigned char GameConfig::WantCoda(class GameConfig * const this /* r29 */) {
    // Local variables
    int startSection; // r1+0x20
    int endSection; // r1+0x1C
    float startMs; // r1+0x18
    float endMs; // r1+0x14
    class vector users; // r1+0x24
    class BandUser * * it; // r30
    class BandUser * pUser; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class TaskMgr TheTaskMgr;
    // -> class GameMode * TheGameMode;
}

static class Symbol _s; // size: 0x4, address: 0x80A496C4
static class Symbol _s; // size: 0x4, address: 0x80A496CC
static class Symbol _s; // size: 0x4, address: 0x80A496D4
static class Symbol _s; // size: 0x4, address: 0x80A496DC
static class Symbol _s; // size: 0x4, address: 0x80A496E4
static class Symbol _s; // size: 0x4, address: 0x80A496EC
static class Symbol _s; // size: 0x4, address: 0x80A496F4
static class Symbol _s; // size: 0x4, address: 0x80A496FC
static class Symbol _s; // size: 0x4, address: 0x80A49704
static class Symbol _s; // size: 0x4, address: 0x80A4970C
static class Symbol _s; // size: 0x4, address: 0x80A49714
static class Symbol _s; // size: 0x4, address: 0x80A4971C
static class Symbol _s; // size: 0x4, address: 0x80A49724
static class Symbol _s; // size: 0x4, address: 0x80A4972C
static class Symbol _s; // size: 0x4, address: 0x80A49734
static class Symbol _s; // size: 0x4, address: 0x80A4973C
static class Symbol _s; // size: 0x4, address: 0x80A49744
static class Symbol _s; // size: 0x4, address: 0x80A4974C
static class Symbol _s; // size: 0x4, address: 0x80A49754
static class Symbol _s; // size: 0x4, address: 0x80A4975C
static class Symbol _s; // size: 0x4, address: 0x80A49764
static class Symbol _s; // size: 0x4, address: 0x80A4976C
static class Symbol _s; // size: 0x4, address: 0x80A49774
static class Symbol _s; // size: 0x4, address: 0x80A4977C
static class Symbol _s; // size: 0x4, address: 0x80A49784
static class Symbol _s; // size: 0x4, address: 0x80A4978C
static class Symbol _s; // size: 0x4, address: 0x80A49794
static class Symbol _s; // size: 0x4, address: 0x80A4979C
static class Symbol _s; // size: 0x4, address: 0x80A497A4
static class Symbol _s; // size: 0x4, address: 0x80A497AC
static class Symbol _s; // size: 0x4, address: 0x80A497B4
static class Symbol _s; // size: 0x4, address: 0x80A497BC
static class Symbol _s; // size: 0x4, address: 0x80A497C4
static class Symbol _s; // size: 0x4, address: 0x80A497CC
static class Symbol _s; // size: 0x4, address: 0x80A497D4
static class Symbol _s; // size: 0x4, address: 0x80A497DC
static class Symbol _s; // size: 0x4, address: 0x80A497E4
static class Symbol _s; // size: 0x4, address: 0x80A497EC
static class Symbol _s; // size: 0x4, address: 0x80A497F4
static class Symbol _s; // size: 0x4, address: 0x80A497FC
static class Symbol _s; // size: 0x4, address: 0x80A49804
// Range: 0x8005C090 -> 0x8005D5E0
class DataNode GameConfig::Handle(class GameConfig * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode _n; // r1+0x78

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
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

class NewRemotePlayerMsg : public Message {
    // total size: 0x8
};
class RemotePlayerLeftMsg : public Message {
    // total size: 0x8
};
static class Symbol _s; // size: 0x4, address: 0x80A4980C
static class Symbol _s; // size: 0x4, address: 0x80A49814
static class Symbol _s; // size: 0x4, address: 0x80A4981C
static class Symbol _s; // size: 0x4, address: 0x80A49824
// Range: 0x8005D5E0 -> 0x8005DA4C
unsigned char GameConfig::SyncProperty(class GameConfig * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC
} __vt__19RemotePlayerLeftMsg; // size: 0xC, address: 0x80874C50
struct {
    // total size: 0x8
} __RTTI__19RemotePlayerLeftMsg; // size: 0x8, address: 0x80874C80
struct {
    // total size: 0xC
} __vt__18NewRemotePlayerMsg; // size: 0xC, address: 0x80874C88
struct {
    // total size: 0x8
} __RTTI__18NewRemotePlayerMsg; // size: 0x8, address: 0x80874CB8
class MomentJukebox {
    // total size: 0x2C
    class Jukebox mJuke; // offset 0x0, size 0x10
    const class TourWorld & mWorld; // offset 0x10, size 0x4
    class list mSeen; // offset 0x14, size 0x8
    int mEventsLeft; // offset 0x1C, size 0x4
    int mMinEvents; // offset 0x20, size 0x4
    int mMaxEvents; // offset 0x24, size 0x4
    class TourMoment * mNextMoment; // offset 0x28, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    const class TourStaff * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    const class TourStaff * * _M_start; // offset 0x0, size 0x4
    const class TourStaff * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class HxGuid * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class HxGuid * _M_start; // offset 0x0, size 0x4
    class HxGuid * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourBandLocal : public TourBand, public TourSavable {
    // total size: 0x2A8
protected:
    class MomentJukebox mMomentJuke; // offset 0x1F0, size 0x2C
private:
    class vector mStarRating; // offset 0x21C, size 0xC
    class vector mDiffRating; // offset 0x228, size 0xC
    class vector mWorldHintsSeen; // offset 0x234, size 0xC
    unsigned char mUnlockedStaff; // offset 0x240, size 0x1
    class vector mChallengeHintsSeen; // offset 0x244, size 0xC
    int mPrevNumTowns; // offset 0x250, size 0x4
    class list mPrevWorldEvents; // offset 0x254, size 0x8
    class vector mPrevStaff; // offset 0x25C, size 0xC
    class Profile * mOwner; // offset 0x268, size 0x4
    class OnlineID * mOwnerID; // offset 0x26C, size 0x4
    class vector mStandInGuids; // offset 0x270, size 0xC
};
class MemHandle {
    // total size: 0x4
public:
    class HandleInfo * mMem; // offset 0x0, size 0x4
};
class MetaMusic : public Object {
    // total size: 0x80
    class Stream * mStream; // offset 0x28, size 0x4
    unsigned char mLoop; // offset 0x2C, size 0x1
    float mFadeTime; // offset 0x30, size 0x4
    float mVolume; // offset 0x34, size 0x4
    unsigned char mPlayFromBuffer; // offset 0x38, size 0x1
    unsigned char mRndHeap; // offset 0x39, size 0x1
    class String mFilename; // offset 0x3C, size 0xC
    class MemHandle * mBufferH; // offset 0x48, size 0x4
    unsigned char * mBuf; // offset 0x4C, size 0x4
    class File * mFile; // offset 0x50, size 0x4
    class Symbol mExt; // offset 0x54, size 0x4
    int mBufSize; // offset 0x58, size 0x4
    int mBytesRead; // offset 0x5C, size 0x4
    class Fader * mFader; // offset 0x60, size 0x4
    class Fader * mFaderMute; // offset 0x64, size 0x4
    class ObjPtrList mExtraFaders; // offset 0x68, size 0x14
    class MetaMusicLoader * mLoader; // offset 0x7C, size 0x4
};
class MetaPanel : public UIPanel {
    // total size: 0x98
protected:
    class ModifierMgr * mModifierMgr; // offset 0x30, size 0x4
    class Shop * mShop; // offset 0x34, size 0x4
    class Tour * mTour; // offset 0x38, size 0x4
    const char * mBackgroundSfx; // offset 0x3C, size 0x4
    float mMinSfxDelaySec; // offset 0x40, size 0x4
    float mMaxSfxDelaySec; // offset 0x44, size 0x4
    float mPlaySfxTime; // offset 0x48, size 0x4
    class vector mRecentIndices; // offset 0x4C, size 0xC
    int mCurrentSlot; // offset 0x58, size 0x4
    class MetaMusic * mMusic; // offset 0x5C, size 0x4
    class ObjDirPtr mBank; // offset 0x60, size 0xC
};
struct {
    // total size: 0x8
} __RTTI__9MetaPanel; // size: 0x8, address: 0x80874D88
struct {
    // total size: 0xD4
} __vt__10GameConfig; // size: 0xD4, address: 0x80874E20
struct {
    // total size: 0x8
} __RTTI__10GameConfig; // size: 0x8, address: 0x80874F28
struct {
    // total size: 0xC
} __vt__18XMPStateChangedMsg; // size: 0xC, address: 0x80874F30
struct {
    // total size: 0x8
} __RTTI__18XMPStateChangedMsg; // size: 0x8, address: 0x80874F60
struct {
    // total size: 0x2C
} __vt__11NetGameData; // size: 0x2C, address: 0x80874FA8
struct {
    // total size: 0x8
} __RTTI__11NetGameData; // size: 0x8, address: 0x80874FE0
struct {
    // total size: 0x8
} __RTTI__PP9DataArray; // size: 0x8, address: 0x80875048
struct {
    // total size: 0x8
} __RTTI__P15TrackInstrument; // size: 0x8, address: 0x80875068
// Range: 0x8005DA4C -> 0x8005DA5C
static void __sinit_\GameConfig_cpp() {
    // References
    // -> static class Rand gPrefabGroupRand;
}

class ProcessedJoinRequestMsg : public Message {
    // total size: 0x8
};
class JukeboxBandProvider : public ListProvider, public Object {
    // total size: 0x2C
};
class JukeboxPanel : public UIPanel {
    // total size: 0x64
    int mBand; // offset 0x30, size 0x4
    class JukeboxBandProvider * mProvider; // offset 0x34, size 0x4
};
class PassiveMessenger : public Object {
    // total size: 0x60
    class Timer mTourReadyTimer; // offset 0x28, size 0x38
};
class MatchmakingSettings {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class Symbol mModeName; // offset 0x4, size 0x4
    int mModeFilter; // offset 0x8, size 0x4
    unsigned char mRanked; // offset 0xC, size 0x1
    class vector mCustomIDs; // offset 0x10, size 0xC
    class vector mCustomValues; // offset 0x1C, size 0xC
};
class SessionSettings : public MatchmakingSettings, public Synchronizable {
    // total size: 0x4C
    unsigned char mPublic; // offset 0x48, size 0x1
};
class SessionReadyMsg : public Message {
    // total size: 0x8
};
class Offer : public Object {
    // total size: 0x2C
protected:
    const class DataArray * mData; // offset 0x28, size 0x4
};
class StoreSort : public Object {
    // total size: 0x28
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class StoreSort * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class StoreSort * * _M_start; // offset 0x0, size 0x4
    class StoreSort * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class OfferProvider : public Object, public ListProvider {
    // total size: 0x48
protected:
    class vector mAvailableSorts; // offset 0x2C, size 0xC
    int mSortIndex; // offset 0x38, size 0x4
    class vector mAllSorts; // offset 0x3C, size 0xC
};
class SongOffer : public Offer {
    // total size: 0x38
    class Symbol mShortName; // offset 0x2C, size 0x4
    unsigned char mIsDownload; // offset 0x30, size 0x1
    unsigned char mIsExported; // offset 0x31, size 0x1
    unsigned char mIsShared; // offset 0x32, size 0x1
    unsigned char mHasMissingParts; // offset 0x33, size 0x1
    unsigned char mVersionOK; // offset 0x34, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SongOffer * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SongOffer * _M_start; // offset 0x0, size 0x4
    class SongOffer * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum ElementType {
    ElementNone = 0,
    ElementSong = 1,
    ElementHeader = 2,
    ElementSubheader = 3,
    ElementFunction = 4,
};
class Element {
    // total size: 0x20
public:
    enum ElementType mType; // offset 0x0, size 0x4
    class Symbol mSymbol; // offset 0x4, size 0x4
    class Symbol mArtist; // offset 0x8, size 0x4
    class SongOffer * mOffer; // offset 0xC, size 0x4
    int mHdrSongCount; // offset 0x10, size 0x4
    int mHdrDiscSongCount; // offset 0x14, size 0x4
    int mHdrDownloadSongCount; // offset 0x18, size 0x4
    unsigned char mCover; // offset 0x1C, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Element * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Element * * _M_start; // offset 0x0, size 0x4
    class Element * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SetlistProvider : public ListProvider, public Object {
    // total size: 0x30
    class RndMat * mBgMat; // offset 0x2C, size 0x4
};
class GroupProvider : public ListProvider, public Object {
    // total size: 0x48
    const class OfferProvider * mOfferProvider; // offset 0x2C, size 0x4
    class vector mActiveGroups; // offset 0x30, size 0xC
    class vector mGroups; // offset 0x3C, size 0xC
};
class SortProvider : public ListProvider, public Object {
    // total size: 0x3C
    const class OfferProvider * mOfferProvider; // offset 0x2C, size 0x4
    class vector mSorts; // offset 0x30, size 0xC
};
class SongOfferProvider : public OfferProvider, public Callback {
    // total size: 0xC0
    class vector mAllOffers; // offset 0x4C, size 0xC
    class vector mFilteredOffers; // offset 0x58, size 0xC
    class RndMat * mGroupBgMat; // offset 0x64, size 0x4
    class RndMat * mAlbumMat; // offset 0x68, size 0x4
    class RndMat * mSongBgMat; // offset 0x6C, size 0x4
    class RndMat * mDownloadMat; // offset 0x70, size 0x4
    class RndMat * mRockBand2Mat; // offset 0x74, size 0x4
    class RndMat * mRockBand1Mat; // offset 0x78, size 0x4
    float mSelectGap; // offset 0x7C, size 0x4
    unsigned char mIsLeaderboards; // offset 0x80, size 0x1
    unsigned char mSetListMode; // offset 0x81, size 0x1
    class Element mHighlight; // offset 0x84, size 0x20
    class vector mElements; // offset 0xA4, size 0xC
    class SetlistProvider * mSetlistProvider; // offset 0xB0, size 0x4
    class GroupProvider * mGroupProvider; // offset 0xB4, size 0x4
    class SortProvider * mSortProvider; // offset 0xB8, size 0x4
    unsigned char mRegisteredWithCM; // offset 0xBC, size 0x1
};
enum InputLimitType {
    kLimitNone = 0,
    kLimitSession = 1,
    kLimitSessionLeader = 2,
    kLimitMax = 3,
};
class SessionBusyMsg : public Message {
    // total size: 0x8
};
class InputMgr : public MsgSource {
    // total size: 0xB0
    class BandUserMgr & mBandUserMgr; // offset 0x1C, size 0x4
    class BandUI * mBandUI; // offset 0x20, size 0x4
    unsigned char mButtonDownSwitch; // offset 0x24, size 0x1
    unsigned char mButtonUpSwitch; // offset 0x25, size 0x1
    enum InputLimitType mLimit; // offset 0x28, size 0x4
    class BandUser * mUser; // offset 0x2C, size 0x4
    unsigned char mNetworkBusy; // offset 0x30, size 0x1
    class Timer mTime; // offset 0x38, size 0x38
    float mLastUpDown[4]; // offset 0x70, size 0x10
    class Object * mObjInvalidUserSink; // offset 0x80, size 0x4
};
enum ReadyType {
    kReadyAddLocal = 0,
    kReadySavePlayers = 1,
};
struct SavePlayer {
    // total size: 0x10
    class BandUser * mUser; // offset 0x0, size 0x4
    enum ControllerType mCt; // offset 0x4, size 0x4
    class CharData * mChar; // offset 0x8, size 0x4
    int mSlot; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SavePlayer * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SavePlayer * _M_start; // offset 0x0, size 0x4
    struct SavePlayer * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class JoinResultMsg : public Message {
    // total size: 0x8
};
class ModeChangedMsg : public Message {
    // total size: 0x8
};
class Matchmaker : public Object {
    // total size: 0x78
    unsigned char mSearching; // offset 0x28, size 0x1
    unsigned char mPublicizeAfterSearch; // offset 0x29, size 0x1
    class Timer mTime; // offset 0x30, size 0x38
    float mSearchingInterval; // offset 0x68, size 0x4
    float mNextSearch; // offset 0x6C, size 0x4
    int mDevChannel; // offset 0x70, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class User * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class User * * _M_start; // offset 0x0, size 0x4
    class User * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class RemotePlayersProvider : public ListProvider, public Object {
    // total size: 0x44
    class vector mRemotePlayers; // offset 0x2C, size 0xC
    unsigned char mShowMuteStatus; // offset 0x38, size 0x1
    class RndMat * mCheckedMat; // offset 0x3C, size 0x4
    class RndMat * mUncheckedMat; // offset 0x40, size 0x4
};
enum ShowGamercardResult {
    kGamercardPadError = -3,
    kGamercardPrivilegeError = -2,
    kGamercardShowError = -1,
    kGamercardSuccessful = 0,
};
class SessionPlayersProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mPlayers; // offset 0x2C, size 0xC
};
class AddPlayerResultMsg : public Message {
    // total size: 0x8
};
class SessionMgr : public MsgSource {
    // total size: 0x88
    class NetSession * mSession; // offset 0x1C, size 0x4
    enum ReadyType mReadyType; // offset 0x20, size 0x4
    struct SavePlayer mNewPlayer; // offset 0x24, size 0x10
    class vector mSavedPlayers; // offset 0x34, size 0xC
    class Matchmaker * mMatchmaker; // offset 0x40, size 0x4
    class RemotePlayersProvider * mRemotePlayersProvider; // offset 0x44, size 0x4
    class SessionPlayersProvider * mSessionPlayersProvider; // offset 0x48, size 0x4
    class vector mPossibleAutoJoinPads; // offset 0x4C, size 0xC
    int mLeaderNum; // offset 0x58, size 0x4
};

