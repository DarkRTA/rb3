/*
    Compile unit: C:\rockband2\band2\src\game\GamePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8005F898 -> 0x800646C4
*/
class DataArray * types; // size: 0x4, address: 0x80A49850
class Symbol t; // size: 0x4, address: 0x80A49858
class GamePanel * TheGamePanel; // size: 0x4, address: 0x80A4985C
// Range: 0x8005F898 -> 0x8005FB70
void * GamePanel::GamePanel(class GamePanel * const this /* r30 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GamePanel * TheGamePanel;
    // -> struct [anonymous] __vt__32ObjPtr<11BandCamShot,9ObjectDir>;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__9GamePanel;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x8005FB70 -> 0x8005FFD0
void * GamePanel::~GamePanel(class GamePanel * const this /* r29 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11BandCamShot,9ObjectDir>;
    // -> class NetSession * TheNetSession;
    // -> class GamePanel * TheGamePanel;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9GamePanel;
}

// Range: 0x8005FFD0 -> 0x8005FFEC
void GamePanel::ResetJitter() {}

static class DataNode & no_jitter; // size: 0x4, address: 0x80A49864
// Range: 0x8005FFEC -> 0x8006018C
float GamePanel::DeJitter(class GamePanel * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    float newMs; // f30
    int index; // r6
    float lastAv; // f3

    // References
    // -> static class DataNode & no_jitter;
}

static class Message resetMsg; // size: 0x8, address: 0x809772A0
// Range: 0x8006018C -> 0x80060320
void GamePanel::Reset(class GamePanel * const this /* r31 */) {
    // References
    // -> static class Message resetMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x80060320 -> 0x80060398
void GamePanel::LoadCrowdAudio(class GamePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol coop; // size: 0x4, address: 0x80A4986C
static class Symbol h2h_bass; // size: 0x4, address: 0x80A49874
static class Symbol h2h_drum; // size: 0x4, address: 0x80A4987C
static class Symbol h2h_guitar; // size: 0x4, address: 0x80A49884
static class Symbol h2h_vocals; // size: 0x4, address: 0x80A4988C
static class DataNode & playMode; // size: 0x4, address: 0x80A49894
// Range: 0x80060398 -> 0x80060B6C
void GamePanel::Load(class GamePanel * const this /* r30 */) {
    // Local variables
    const char * bank; // r29
    int arrangement; // r0
    class list configs; // r1+0x68

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class DataNode & playMode;
    // -> static class Symbol h2h_vocals;
    // -> static class Symbol h2h_guitar;
    // -> static class Symbol h2h_drum;
    // -> static class Symbol h2h_bass;
    // -> static class Symbol coop;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x80060B6C -> 0x80060BD8
void GamePanel::CreateGame(class GamePanel * const this /* r31 */) {}

static class Symbol variant; // size: 0x4, address: 0x80A4989C
static class Symbol blank_variant; // size: 0x4, address: 0x80A498A4
// Range: 0x80060BD8 -> 0x80060EC4
unsigned char GamePanel::IsLoaded(class GamePanel * const this /* r29 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class GameMode * TheGameMode;
    // -> const char * gNullStr;
    // -> class WorldDir * TheWorld;
    // -> static class Symbol blank_variant;
    // -> static class Symbol variant;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> class UIManager TheUI;
}

// Range: 0x80060EC4 -> 0x80061004
void GamePanel::FinishLoad(class GamePanel * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80061004 -> 0x80061244
void GamePanel::Unload(class GamePanel * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80061244 -> 0x80061298
void GamePanel::UnloadCrowdAudio(class GamePanel * const this /* r31 */) {}

// Range: 0x80061298 -> 0x800613F0
void GamePanel::Enter(class GamePanel * const this /* r27 */) {
    // Local variables
    int gem_track_count; // r31
    class PlayerTrackConfigList * player_configs; // r28
    int i; // r27

    // References
    // -> unsigned char mShotLOD;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameConfig * TheGameConfig;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x800613F0 -> 0x80061450
void GamePanel::Exit(class GamePanel * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80061450 -> 0x800614E8
void GamePanel::StartGame(class GamePanel * const this /* r31 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x800614E8 -> 0x80061590
void GamePanel::RunVocalTest(class GamePanel * const this /* r31 */) {
    // Local variables
    float time; // f30
    float end; // f0

    // References
    // -> class Debug TheDebug;
    // -> class TaskMgr TheTaskMgr;
    // -> class SongDB * TheSongDB;
}

static class Timer * _t; // size: 0x4, address: 0x80A498A8
// Range: 0x80061590 -> 0x8006176C
void GamePanel::Poll(class GamePanel * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Timer * _t;
}

static class Message pick_intro; // size: 0x8, address: 0x809772B8
// Range: 0x8006176C -> 0x800618EC
void GamePanel::StartIntro(class GamePanel * const this /* r31 */) {
    // References
    // -> static class Message pick_intro;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800618EC -> 0x80061A20
void GamePanel::UpdateNowBar(class GamePanel * const this /* r25 */) {
    // Local variables
    const class SongPos & pos; // r0
    float sec; // f30
    float sec_left; // f1
    char sec_left_prefix; // r26

    // References
    // -> class SongDB * TheSongDB;
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class LatencyCallback : public Callback {
    // total size: 0x8
public:
    unsigned char mWhite; // offset 0x4, size 0x1
};
static class LatencyCallback gGamePanelCallback; // size: 0x8, address: 0x809772D0
static class DataNode & latency_test; // size: 0x4, address: 0x80A498B0
static class DataNode & pad_button; // size: 0x4, address: 0x80A498B8
static int count; // size: 0x4, address: 0x80A498BC
static unsigned char wasPressed; // size: 0x1, address: 0x80A498C0
static class Object * beep; // size: 0x4, address: 0x80A498C4
static class Message playMsg; // size: 0x8, address: 0x809772E8
static int frame; // size: 0x4, address: 0x80A498CC
static float frames[2]; // size: 0x8, address: 0x809772F0
// Range: 0x80061A20 -> 0x80061E4C
void GamePanel::UpdateLatency(class GamePanel * const this /* r28 */) {
    // Local variables
    unsigned char white; // r26
    unsigned char beep; // r25
    int player; // r29
    class JoypadData * joy; // r0
    class ObjectDir * d; // r25

    // References
    // -> static float frames[2];
    // -> static int frame;
    // -> class Rnd & TheRnd;
    // -> static class Message playMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Object * beep;
    // -> static class LatencyCallback gGamePanelCallback;
    // -> static unsigned char wasPressed;
    // -> static int count;
    // -> class TaskMgr TheTaskMgr;
    // -> static class DataNode & pad_button;
    // -> static class DataNode & latency_test;
}

// Range: 0x80061E4C -> 0x80061E98
void GamePanel::SetPaused(class GamePanel * const this /* r30 */, unsigned char paused /* r31 */) {}

// Range: 0x80061E98 -> 0x80061F24
void GamePanel::SetPausedExceptCrowdAudio(class GamePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80061F24 -> 0x80061FEC
void GamePanel::SetGameOver() {
    // Local variables
    enum EndGameResult result; // r31
    unsigned char report; // r30

    // References
    // -> class NetSession * TheNetSession;
    // -> class GameMode * TheGameMode;
    // -> class Game * TheGame;
}

static class DataArrayPtr restart; // size: 0x8, address: 0x80977308
class GameEndedMsg : public Message {
    // total size: 0x8
};
// Range: 0x80061FEC -> 0x80062814
class DataNode GamePanel::OnMsg(class GamePanel * const this /* r30 */, const class GameEndedMsg & msg /* r27 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__7Message;
    // -> static class DataArrayPtr restart;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class Game * TheGame;
}

// Range: 0x80062814 -> 0x8006284C
void GamePanel::SendRestartGameNetMsg() {
    // Local variables
    class RestartGameMsg msg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __vt__14RestartGameMsg;
}

static class Message msg; // size: 0x8, address: 0x80977320
// Range: 0x8006288C -> 0x80062A7C
void GamePanel::SetExcitementLevel(class GamePanel * const this /* r30 */, enum ExcitementLevel level /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol _s; // size: 0x4, address: 0x80A498D4
static class Symbol _s; // size: 0x4, address: 0x80A498DC
static class Symbol _s; // size: 0x4, address: 0x80A498E4
static class Symbol _s; // size: 0x4, address: 0x80A498EC
static class Symbol _s; // size: 0x4, address: 0x80A498F4
static class Symbol _s; // size: 0x4, address: 0x80A498FC
static class Symbol _s; // size: 0x4, address: 0x80A49904
static class Symbol _s; // size: 0x4, address: 0x80A4990C
static class Symbol _s; // size: 0x4, address: 0x80A49914
static class Symbol _s; // size: 0x4, address: 0x80A4991C
static class Symbol _s; // size: 0x4, address: 0x80A49924
static class Symbol _s; // size: 0x4, address: 0x80A4992C
// Range: 0x80062A7C -> 0x80063D0C
class DataNode GamePanel::Handle(class GamePanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x60
    class MessageTimer _mt; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode _n; // r1+0x80
    class DataNode _n; // r1+0x78
    class DataNode _n; // r1+0x70

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__12GameEndedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80063D0C -> 0x80063E00
class DataNode GamePanel::OnStartLoadSong(class GamePanel * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    class Symbol song; // r1+0x14
    class QuickplayPerformer * qp; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__13MetaPerformer;
    // -> struct [anonymous] __RTTI__18QuickplayPerformer;
}

// Range: 0x80063E00 -> 0x80063E50
class DataNode GamePanel::OnStartSongNow(class GamePanel * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A49934
static class Symbol _s; // size: 0x4, address: 0x80A4993C
static class Symbol _s; // size: 0x4, address: 0x80A49944
static class Symbol _s; // size: 0x4, address: 0x80A4994C
static class Symbol _s; // size: 0x4, address: 0x80A49954
// Range: 0x80063E50 -> 0x80064350
unsigned char GamePanel::SyncProperty(class GamePanel * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80064350 -> 0x800644AC
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11BandCamShot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xC
} __vt__12GameEndedMsg; // size: 0xC, address: 0x80875AE8
struct {
    // total size: 0x8
} __RTTI__12GameEndedMsg; // size: 0x8, address: 0x80875B10
struct {
    // total size: 0xC8
} __vt__9GamePanel; // size: 0xC8, address: 0x80875B18
struct {
    // total size: 0x8
} __RTTI__9GamePanel; // size: 0x8, address: 0x80875C18
struct {
    // total size: 0x8
} __RTTI__15HeldButtonPanel; // size: 0x8, address: 0x80875C98
struct {
    // total size: 0x8
} __RTTI__11BandCamShot; // size: 0x8, address: 0x80875CD0
struct {
    // total size: 0x18
} __vt__32ObjPtr<11BandCamShot,9ObjectDir>; // size: 0x18, address: 0x80875CD8
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11BandCamShot,9ObjectDir>; // size: 0x8, address: 0x80875D20
struct {
    // total size: 0x8
} __RTTI__7CamShot; // size: 0x8, address: 0x80875D50
struct {
    // total size: 0xC
} __vt__12DataArrayPtr; // size: 0xC, address: 0x80875EA8
struct {
    // total size: 0x8
} __RTTI__12DataArrayPtr; // size: 0x8, address: 0x80875EC8
// Range: 0x800644AC -> 0x800644D4
static void __sinit_\GamePanel_cpp() {
    // References
    // -> struct [anonymous] __vt__15LatencyCallback;
    // -> static class LatencyCallback gGamePanelCallback;
}

// Range: 0x800644D4 -> 0x800645EC
float LatencyCallback::UpdateOverlay(float topY /* f31 */) {
    // Local variables
    class Color col; // r1+0x50

    // References
    // -> class Rnd & TheRnd;
}

struct {
    // total size: 0x10
} __vt__15LatencyCallback; // size: 0x10, address: 0x80875F60
struct {
    // total size: 0x8
} __RTTI__15LatencyCallback; // size: 0x8, address: 0x80875F90
struct {
    // total size: 0x10
} __vt__Q210RndOverlay8Callback; // size: 0x10, address: 0x80875F98
struct {
    // total size: 0x8
} __RTTI__Q210RndOverlay8Callback; // size: 0x8, address: 0x80875FC0
class JoypadConnectionMsg : public Message {
    // total size: 0x8
};

