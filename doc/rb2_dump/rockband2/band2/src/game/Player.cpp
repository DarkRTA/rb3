/*
    Compile unit: C:\rockband2\band2\src\game\Player.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800763AC -> 0x8007B6B8
*/
struct PlayerParams {
    // total size: 0x24
    float mCrowdSaveLevel; // offset 0x0, size 0x4
    float mMsToReturnFromBrink; // offset 0x4, size 0x4
    float mCrowdLossPerMs; // offset 0x8, size 0x4
    float mEnergyDrainRate; // offset 0xC, size 0x4
    float mEnergyDeployBonus; // offset 0x10, size 0x4
    float mSpotlightPhraseBonus; // offset 0x14, size 0x4
    float mDeployThreshold; // offset 0x18, size 0x4
    float mSaveEnergy; // offset 0x1C, size 0x4
    float mDisablePauseMs; // offset 0x20, size 0x4
};
// Range: 0x800763AC -> 0x80076530
void * Player::~Player(class Player * const this /* r30 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __vt__6Player;
}

// Range: 0x80076530 -> 0x80076694
void Player::Restart(class Player * const this /* r31 */) {}

// Range: 0x80076694 -> 0x80076728
void Player::Poll(class Player * const this /* r30 */, float ms /* f31 */, const class SongPos & pos /* r31 */) {
    // References
    // -> class SongDB * TheSongDB;
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x80076728 -> 0x800767A0
void Player::PollMultiplier(class Player * const this /* r30 */) {
    // Local variables
    int new_mult; // r31
    class BandTrack * bandTrack; // r0

    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x800767A0 -> 0x800768F0
void Player::PollEnabledState(class Player * const this /* r31 */) {
    // Local variables
    class BandTrack * track; // r0
    float drain_rate; // f31
    class BandTrack * track; // r0

    // References
    // -> class Game * TheGame;
}

// Range: 0x800768F0 -> 0x800769BC
void Player::AddPoints(class Player * const this /* r28 */, float points /* f31 */, unsigned char apply_multiplier /* r29 */, unsigned char apply_streak /* r30 */, unsigned char normalize /* r31 */) {
    // Local variables
    float normalization_factor; // f1
    float add_points; // f1

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

static class Message msg; // size: 0x8, address: 0x80977638
// Range: 0x800769BC -> 0x80076B80
void Player::BroadcastScore(class Player * const this /* r31 */) {
    // Local variables
    float now; // f0
    float ms_since_score_sent; // f1
    int delta_since_score_sent; // r0

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x80076B80 -> 0x80076C0C
void Player::EnterCoda(class Player * const this /* r31 */) {}

// Range: 0x80076C0C -> 0x80076CB8
void Player::AddBonusPoints(class Player * const this /* r30 */, int points /* r31 */) {
    // Local variables
    float normalization_factor; // f1

    // References
    // -> class Game * TheGame;
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80076CB8 -> 0x80076D18
unsigned char Player::CanPause(class Player * const this /* r31 */) {
    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80076D18 -> 0x80076DA0
int Player::GetAccumulatedScore(const class Player * const this /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80076DA0 -> 0x80076E28
float Player::GetTotalStars(const class Player * const this /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80076E28 -> 0x80076E30
int Player::GetLongestStreak() {}

static class Message msg; // size: 0x8, address: 0x80977650
// Range: 0x80076E30 -> 0x800771F0
void Player::SetEnabledState(class Player * const this /* r28 */, enum EnabledState state /* r29 */, int causer /* r30 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800771F0 -> 0x800772B4
enum EnabledState Player::GetEnabledStateAt(const class Player * const this /* r31 */) {
    // Local variables
    int tick; // r0
    int i; // r5
}

// Range: 0x800772B4 -> 0x8007733C
void Player::SendHitMsg(int streak /* r30 */, int score /* r31 */, float crowd /* f31 */) {
    // Local variables
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x8007737C -> 0x80077404
void Player::SendPenalizeMsg(int streak /* r30 */, int score /* r31 */, float crowd /* f31 */) {
    // Local variables
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80077404 -> 0x80077474
void Player::SendUpdateCrowdMsg(float crowd /* f31 */) {
    // Local variables
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80077474 -> 0x800774E4
void Player::SendFillHitMsg(int slot /* r29 */, int numfillswings /* r30 */, int incoda /* r31 */) {
    // Local variables
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x800774E4 -> 0x80077548
void Player::SendHitLastUnisonGemMsg(int phrase /* r30 */, int track /* r31 */) {
    // Local variables
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80077548 -> 0x800775AC
void Player::SendFailUnisonPhraseMsg(int phrase /* r30 */, int track /* r31 */) {
    // Local variables
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

static class Message msg; // size: 0x8, address: 0x80977668
static class Message enable_player; // size: 0x8, address: 0x80977680
static class Message save_player; // size: 0x8, address: 0x80977698
// Range: 0x800775AC -> 0x80077D70
void Player::LocalSetEnabledState(class Player * const this /* r26 */, enum EnabledState state /* r27 */, int tick /* r29 */, int causer /* r28 */) {
    // Local variables
    class vector & players; // r0
    class Player * * it; // r25
    struct Extent e; // r1+0x78
    int phraseId; // r29
    const class GameGemList & gemList; // r27
    int gemId; // r25
    struct Extent ext; // r1+0x70

    // References
    // -> static class Message save_player;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
    // -> class GamePanel * TheGamePanel;
    // -> static class Message enable_player;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Game * TheGame;
}

// Range: 0x80077D70 -> 0x80077DE0
unsigned char Player::Saveable() {}

// Range: 0x80077DE0 -> 0x80077DF8
void Player::Save() {}

// Range: 0x80077DF8 -> 0x80077E1C
float GetPlayerPan() {}

static class Message player_failed; // size: 0x8, address: 0x809776B0
static class Message disable_player; // size: 0x8, address: 0x809776C8
// Range: 0x80077E1C -> 0x800782D0
void Player::DisablePlayer(class Player * const this /* r29 */, int strikes /* r26 */) {
    // Local variables
    const char * sfxName; // r27
    float pan; // f2
    class BandTrack * track; // r0

    // References
    // -> static class Message disable_player;
    // -> class WorldDir * TheWorld;
    // -> static class Message player_failed;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Synth * TheSynth;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800782D0 -> 0x80078338
int Player::UserNum(const class Player * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80078338 -> 0x800783A0
int Player::GetSlot(const class Player * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800783A0 -> 0x800783A8
unsigned char Player::IsNet() {}

// Range: 0x800783A8 -> 0x80078408
int Player::GetMultiplier(const class Player * const this /* r30 */) {}

// Range: 0x80078408 -> 0x8007845C
unsigned char Player::CanDeployStarPower() {
    // References
    // -> class GameMode * TheGameMode;
}

static class Message hit; // size: 0x8, address: 0x809776E0
// Range: 0x8007845C -> 0x8007865C
void Player::Hit(class Player * const this /* r31 */) {
    // Local variables
    char buffer[7]; // r1+0x30

    // References
    // -> class GamePanel * TheGamePanel;
    // -> static class Message hit;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8007865C -> 0x80078664
unsigned char Player::IsDeployingBandEnergy() {}

// Range: 0x80078664 -> 0x80078754
void Player::StopDeployingBandEnergy(class Player * const this /* r30 */, unsigned char playerFailed /* r31 */) {
    // Local variables
    const char * sfxName; // r0
    class BandTrack * track; // r0

    // References
    // -> class Synth * TheSynth;
}

// Range: 0x80078754 -> 0x80078760
void Player::DisablePhraseBonus() {}

// Range: 0x80078760 -> 0x8007876C
void Player::EnablePhraseBonus() {}

// Range: 0x8007876C -> 0x8007878C
float Player::SpotlightPhraseBonus() {}

// Range: 0x8007878C -> 0x800787C0
void Player::CompleteCommonPhrase(class Player * const this /* r31 */) {}

// Range: 0x800787C0 -> 0x8007882C
int Player::GetIndividualMultiplier(const class Player * const this /* r31 */) {
    // Local variables
    int mult; // r1+0x14

    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x8007882C -> 0x80078838
int Player::GetMaxIndividualMultipler() {}

// Range: 0x80078838 -> 0x800788C8
int Player::GetNumStars(const class Player * const this /* r29 */) {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x800788C8 -> 0x80078968
float Player::GetNumStarsFloat(const class Player * const this /* r28 */, unsigned char enforce_diff_restrictions /* r29 */) {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x80078968 -> 0x800789F8
int Player::GetScoreForStars(const class Player * const this /* r28 */, int numStars /* r29 */) {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x800789F8 -> 0x80078A68
void Player::SavePersistentData(const class Player * const this /* r30 */, class PersistentPlayerData & data /* r31 */) {}

// Range: 0x80078A68 -> 0x80078AF4
void Player::LoadPersistentData(class Player * const this /* r30 */, const class PersistentPlayerData & data /* r31 */) {}

static class Message msg; // size: 0x8, address: 0x809776F8
// Range: 0x80078AF4 -> 0x80078E44
unsigned char Player::DeployBandEnergyIfPossible(class Player * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
}

// Range: 0x80078E44 -> 0x80078EB4
int Player::LocalDeployBandEnergy(class Player * const this /* r30 */) {
    // Local variables
    int num_saved; // r31
}

// Range: 0x80078EB4 -> 0x80078F48
void Player::PerformDeployBandEnergy(class Player * const this /* r30 */, int num_saved /* r31 */) {}

static class Symbol deploy; // size: 0x4, address: 0x80A49C54
static class Message deployMsg; // size: 0x8, address: 0x80977710
// Range: 0x80078F48 -> 0x8007916C
void Player::Deploy(class Player * const this /* r31 */) {
    // Local variables
    class BandTrack * track; // r0

    // References
    // -> static class Message deployMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol deploy;
    // -> class Synth * TheSynth;
}

// Range: 0x8007916C -> 0x8007918C
void Player::RemoteAlreadySaved() {}

// Range: 0x8007918C -> 0x800791E0
void Player::PopupHelp(class Symbol & help /* r30 */, unsigned char state /* r31 */) {
    // Local variables
    class BandTrack * track; // r0
}

// Range: 0x800791E0 -> 0x8007922C
void Player::AddEnergy() {}

// Range: 0x8007922C -> 0x80079238
class Symbol Player::GetStreakType() {}

// Range: 0x80079238 -> 0x80079368
void Player::UpdateEnergy(class Player * const this /* r30 */, const class SongPos & pos /* r31 */) {
    // Local variables
    float cur_beat; // f0
    float last_beat; // f0
    float beat_diff; // f1

    // References
    // -> class GameMode * TheGameMode;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80079368 -> 0x800793B4
void Player::SubtractEnergy() {}

static class Message msg; // size: 0x8, address: 0x80977728
// Range: 0x800793B4 -> 0x80079758
void Player::SetEnergy(class Player * const this /* r31 */, float val /* f30 */) {
    // Local variables
    float old_energy; // f31
    unsigned char energy_increasing; // r30
    float now; // f0
    float ms_since_energy_sent; // f1
    class Message setEnergyMsg; // r1+0x40

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
}

static class Symbol ready; // size: 0x4, address: 0x80A49C5C
static class Symbol none; // size: 0x4, address: 0x80A49C64
// Range: 0x80079758 -> 0x80079900
void Player::SetEnergyAutomatically(class Player * const this /* r29 */, float val /* f31 */) {
    // Local variables
    unsigned char oldCanDeploy; // r0
    class BandTrack * track; // r0
    float threshold; // f0

    // References
    // -> static class Symbol none;
    // -> static class Symbol ready;
}

// Range: 0x80079900 -> 0x80079904
void Player::SetEnergyFromNet() {}

// Range: 0x80079904 -> 0x8007997C
unsigned char Player::ShouldDrainEnergy(const class Player * const this /* r30 */) {
    // Local variables
    int slot; // r31

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8007997C -> 0x80079B3C
void Player::CheckCrowdFailure(class Player * const this /* r30 */) {
    // Local variables
    int DisabledCount; // r31
    class vector & players; // r0
    int i; // r5

    // References
    // -> class Game * TheGame;
    // -> class ModifierMgr * TheModifierMgr;
    // -> class GameMode * TheGameMode;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80079B3C -> 0x80079BCC
class DataNode Player::OnMsg(class Player * const this /* r30 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x80079BCC -> 0x80079C90
void Player::EnterDisconnectedState(class Player * const this /* r30 */) {
    // Local variables
    int leaderNum; // r31

    // References
    // -> class Game * TheGame;
    // -> class NetSession * TheNetSession;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x80079C90 -> 0x80079CB8
class BandTrack * Player::GetBandTrack() {}

// Range: 0x80079CB8 -> 0x80079CDC
void Player::UnisonMiss() {}

static class Message msg; // size: 0x8, address: 0x80977740
static class Message unisonHitMsg; // size: 0x8, address: 0x80977758
// Range: 0x80079CDC -> 0x8007A02C
void Player::UnisonHit(class Player * const this /* r29 */) {
    // Local variables
    class BandTrack * trackDir; // r0

    // References
    // -> static class Message unisonHitMsg;
    // -> class GameMode * TheGameMode;
    // -> class TaskMgr TheTaskMgr;
    // -> class Synth * TheSynth;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8007A02C -> 0x8007A158
class DataNode Player::OnSendNetGameplayMsg(class Player * const this /* r25 */, class DataArray * msg /* r26 */) {
    // Local variables
    enum PacketType type; // r30
    int arg1; // r29
    int arg2; // r28
    int arg3; // r27
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x8007A158 -> 0x8007A2A0
class DataNode Player::OnSendNetGameplayMsgToPlayer(class Player * const this /* r24 */, class DataArray * msg /* r25 */) {
    // Local variables
    enum PacketType type; // r29
    int arg1; // r28
    int arg2; // r27
    int arg3; // r26
    class PlayerGameplayMsg gameplayMsg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x8007A2A0 -> 0x8007A2FC
class DataNode Player::OnGetOverdriveMeter() {
    // Local variables
    class BandTrack * track; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A49C6C
static class Symbol _s; // size: 0x4, address: 0x80A49C74
static class Symbol _s; // size: 0x4, address: 0x80A49C7C
static class Symbol _s; // size: 0x4, address: 0x80A49C84
static class Symbol _s; // size: 0x4, address: 0x80A49C8C
static class Symbol _s; // size: 0x4, address: 0x80A49C94
static class Symbol _s; // size: 0x4, address: 0x80A49C9C
static class Symbol _s; // size: 0x4, address: 0x80A49CA4
static class Symbol _s; // size: 0x4, address: 0x80A49CAC
static class Symbol _s; // size: 0x4, address: 0x80A49CB4
static class Symbol _s; // size: 0x4, address: 0x80A49CBC
static class Symbol _s; // size: 0x4, address: 0x80A49CC4
static class Symbol _s; // size: 0x4, address: 0x80A49CCC
static class Symbol _s; // size: 0x4, address: 0x80A49CD4
static class Symbol _s; // size: 0x4, address: 0x80A49CDC
static class Symbol _s; // size: 0x4, address: 0x80A49CE4
static class Symbol _s; // size: 0x4, address: 0x80A49CEC
static class Symbol _s; // size: 0x4, address: 0x80A49CF4
static class Symbol _s; // size: 0x4, address: 0x80A49CFC
static class Symbol _s; // size: 0x4, address: 0x80A49D04
static class Symbol _s; // size: 0x4, address: 0x80A49D0C
static class Symbol _s; // size: 0x4, address: 0x80A49D14
static class Symbol _s; // size: 0x4, address: 0x80A49D1C
static class Symbol _s; // size: 0x4, address: 0x80A49D24
static class Symbol _s; // size: 0x4, address: 0x80A49D2C
static class Symbol _s; // size: 0x4, address: 0x80A49D34
static class Symbol _s; // size: 0x4, address: 0x80A49D3C
static class Symbol _s; // size: 0x4, address: 0x80A49D44
static class Symbol _s; // size: 0x4, address: 0x80A49D4C
static class Symbol _s; // size: 0x4, address: 0x80A49D54
static class Symbol _s; // size: 0x4, address: 0x80A49D5C
static class Symbol _s; // size: 0x4, address: 0x80A49D64
static class Symbol _s; // size: 0x4, address: 0x80A49D6C
static class Symbol _s; // size: 0x4, address: 0x80A49D74
static class Symbol _s; // size: 0x4, address: 0x80A49D7C
static class Symbol _s; // size: 0x4, address: 0x80A49D84
static class Symbol _s; // size: 0x4, address: 0x80A49D8C
static class Symbol _s; // size: 0x4, address: 0x80A49D94
static class Symbol _s; // size: 0x4, address: 0x80A49D9C
static class Symbol _s; // size: 0x4, address: 0x80A49DA4
static class Symbol _s; // size: 0x4, address: 0x80A49DAC
static class Symbol _s; // size: 0x4, address: 0x80A49DB4
// Range: 0x8007A2FC -> 0x8007B6B8
class DataNode Player::Handle(class Player * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

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
    // -> class Game * TheGame;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x1E4
} __vt__6Player; // size: 0x1E4, address: 0x80878130
class TimeSigChange {
    // total size: 0x10
public:
    int mMeasure; // offset 0x0, size 0x4
    int mNum; // offset 0x4, size 0x4
    int mDenom; // offset 0x8, size 0x4
    int mTick; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TimeSigChange * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TimeSigChange * _M_start; // offset 0x0, size 0x4
    class TimeSigChange * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class MeasureMap {
    // total size: 0xC
    class vector mTimeSigChanges; // offset 0x0, size 0xC
};

