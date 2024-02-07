/*
    Compile unit: C:\rockband2\band2\src\game\Game.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800501B0 -> 0x80054E50
*/
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>; // size: 0x8, address: 0x80873990
class Symbol name; // size: 0x4, address: 0x80A4945C
class PlayerGameplayMsg : public NetMessage {
    // total size: 0x18
    int mPlayerNum; // offset 0x4, size 0x4
    int mOpCode; // offset 0x8, size 0x4
    int mArg1; // offset 0xC, size 0x4
    int mArg2; // offset 0x10, size 0x4
    int mArg3; // offset 0x14, size 0x4
};
class NetMessage {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RestartGameMsg : public NetMessage {
    // total size: 0x4
};
class LoadAllCharsMsg : public NetMessage {
    // total size: 0x4
};
class PlayerStatsMsg : public NetMessage {
    // total size: 0x30
    int mPlayerNum; // offset 0x4, size 0x4
    int mNotesHit; // offset 0x8, size 0x4
    int mLongestStreak; // offset 0xC, size 0x4
    float mNotesHitFraction; // offset 0x10, size 0x4
    unsigned char mFailedDeploy; // offset 0x14, size 0x1
    int mSavedCount; // offset 0x18, size 0x4
    int mFillHitCount; // offset 0x1C, size 0x4
    unsigned char mStrummedDown; // offset 0x20, size 0x1
    unsigned char mStrummedUp; // offset 0x21, size 0x1
    int mDeployCount; // offset 0x24, size 0x4
    int mScore; // offset 0x28, size 0x4
    int mSoloPercentage; // offset 0x2C, size 0x4
};
class SetPlayerTrackTypeMsg : public NetMessage {
    // total size: 0x14
    int mPlayerNum; // offset 0x4, size 0x4
    class String mTrackType; // offset 0x8, size 0xC
};
class SetPlayerDifficultyMsg : public NetMessage {
    // total size: 0x14
    int mPlayerNum; // offset 0x4, size 0x4
    class String mDifficulty; // offset 0x8, size 0xC
};
class ReassignPlayerTrackTypeMsg : public NetMessage {
    // total size: 0xC
    int mPlayerNum; // offset 0x4, size 0x4
    int mTrackType; // offset 0x8, size 0x4
};
class H2HSetTrackTypesMsg : public NetMessage {
    // total size: 0x4
};
class ReadyForSongsMsg : public NetMessage {
    // total size: 0x4
};
class LocalSongsMsg : public NetMessage {
    // total size: 0x1C
    class vector mLocalPlayers; // offset 0x4, size 0xC
    class vector mSongNames; // offset 0x10, size 0xC
};
class SharedSongsMsg : public NetMessage {
    // total size: 0x10
    class vector mSongNames; // offset 0x4, size 0xC
};
class LocalBattlesMsg : public NetMessage {
    // total size: 0x20
    class vector mLocalPlayers; // offset 0x4, size 0xC
    class list mChallengeBattles; // offset 0x10, size 0x8
    class list mWorldBattles; // offset 0x18, size 0x8
};
class SharedBattlesMsg : public NetMessage {
    // total size: 0x14
    class list mChallengeBattles; // offset 0x4, size 0x8
    class list mWorldBattles; // offset 0xC, size 0x8
};
class Game * TheGame; // size: 0x4, address: 0x80A49460
// Range: 0x800501B0 -> 0x8005057C
void GameInit() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> class SongMgr & TheSongMgr;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
}

// Range: 0x8005057C -> 0x800505B0
void GameTerminate() {
    // References
    // -> class SongMgr & TheSongMgr;
}

class BonusAwards {
    // total size: 0xC
    class vector mRows; // offset 0x0, size 0xC
};
// Range: 0x800505B0 -> 0x80050D60
void * Game::Game(class Game * const this /* r29 */) {
    // Local variables
    unsigned int i; // r27
    unsigned char isBandArrangement; // r0
    class vector users; // r1+0x64
    class BandUser * * it; // r27
    class BandUser * pUser; // r28
    class DataArray * meter_cfg; // r31
    int i; // r31
    class vector users; // r1+0x58
    class Player * pPlayer; // r0

    // References
    // -> class Net TheNet;
    // -> class GameMode * TheGameMode;
    // -> class Synth * TheSynth;
    // -> class GameConfig * TheGameConfig;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class ObjectDir * sMainDir;
    // -> class Game * TheGame;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
    // -> struct [anonymous] __vt__4Game;
    // -> struct [anonymous] __vt__14BeatMasterSink;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BonusRow * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BonusRow * _M_start; // offset 0x0, size 0x4
    struct BonusRow * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80050D60 -> 0x80051070
void * Game::~Game(class Game * const this /* r30 */) {
    // Local variables
    class PersistentGameData * game_data; // r4
    int i; // r28

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class SongDB * TheSongDB;
    // -> class Game * TheGame;
    // -> class GameConfig * TheGameConfig;
    // -> struct [anonymous] __vt__4Game;
}

// Range: 0x80051070 -> 0x800511A8
void Game::LoadSong(class Game * const this /* r27 */) {
    // Local variables
    class Symbol song; // r1+0x1C
    class DataArray * data; // r29
    unsigned char onDisc; // r0
    unsigned char exported; // r0
    enum SongDataValidate validateMode; // r28

    // References
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
    // -> class SongMgr & TheSongMgr;
    // -> class Timer gSongLoadTimer;
}

// Range: 0x800511A8 -> 0x800512D8
unsigned char Game::IsLoaded(class Game * const this /* r31 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Synth * TheSynth;
    // -> class GameConfig * TheGameConfig;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800512D8 -> 0x800515EC
void Game::PostLoad(class Game * const this /* r31 */) {
    // Local variables
    int codaEndTick; // r26
    const class vector & players; // r0
    class Player * const * it; // r25
    struct Extent e; // r1+0x10
    float codaEndMs; // f31
    class Player * const * it; // r25
    class MetaPerformer * mp; // r25
    int total_target_score; // r25
    int total_base_score; // r26
    class Player * const * it; // r28
    class Player * const * it; // r28
    float score_frac; // f1

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x800515EC -> 0x8005167C
unsigned char Game::IsReady(class Game * const this /* r30 */) {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30
}

// Range: 0x8005167C -> 0x800516CC
void Game::Start(class Game * const this /* r31 */) {}

// Range: 0x800516CC -> 0x8005177C
void Game::PostWaitStart(class Game * const this /* r29 */) {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30

    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8005177C -> 0x800517DC
void Game::StartIntro() {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30
}

// Range: 0x800517DC -> 0x800518E0
void Game::Reset(class Game * const this /* r30 */) {
    // References
    // -> class GamePanel * TheGamePanel;
    // -> class TaskMgr TheTaskMgr;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800518E0 -> 0x80051D10
void Game::Poll(class Game * const this /* r23 */) {
    // Local variables
    float ms; // f31
    float tick; // f0
    int b; // r22

    // References
    // -> class GameMode * TheGameMode;
    // -> class TaskMgr TheTaskMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class GamePanel * TheGamePanel;
}

class Shuttle {
    // total size: 0x10
    float mMs; // offset 0x0, size 0x4
    float mEndMs; // offset 0x4, size 0x4
    unsigned char mActive; // offset 0x8, size 0x1
    int mController; // offset 0xC, size 0x4
};
class MidiReceiver {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class MidiReader * mReader; // offset 0x4, size 0x4
};
struct TextEvent {
    // total size: 0x8
    class DataArray * text; // offset 0x0, size 0x4
    int startTick; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TextEvent * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TextEvent * _M_start; // offset 0x0, size 0x4
    struct TextEvent * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class DataEvent {
    // total size: 0xC
public:
    float start; // offset 0x0, size 0x4
    float end; // offset 0x4, size 0x4
protected:
    class DataArray * mMsg; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class DataEvent * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DataEvent * _M_start; // offset 0x0, size 0x4
    class DataEvent * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct CompEv {
    // total size: 0xC
    float start; // offset 0x0, size 0x4
    float end; // offset 0x4, size 0x4
    int value; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct CompEv * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct CompEv * _M_start; // offset 0x0, size 0x4
    struct CompEv * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class DataEventList {
    // total size: 0x38
    int mCurIndex; // offset 0x0, size 0x4
    int mSize; // offset 0x4, size 0x4
    class vector mEvents; // offset 0x8, size 0xC
    class vector mComps; // offset 0x14, size 0xC
    int mElement; // offset 0x20, size 0x4
    class DataEvent mTemplate; // offset 0x24, size 0xC
    enum DataType mCompType; // offset 0x30, size 0x4
    int * mValue; // offset 0x34, size 0x4
};
struct Note {
    // total size: 0xC
    int note; // offset 0x0, size 0x4
    int startTick; // offset 0x4, size 0x4
    int endTick; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Note * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Note * _M_start; // offset 0x0, size 0x4
    struct Note * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct PostProcess {
    // total size: 0x1C
    unsigned char zeroLength; // offset 0x0, size 0x1
    float startOffset; // offset 0x4, size 0x4
    float endOffset; // offset 0x8, size 0x4
    float minLength; // offset 0xC, size 0x4
    float maxLength; // offset 0x10, size 0x4
    float minGap; // offset 0x14, size 0x4
    float maxGap; // offset 0x18, size 0x4
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
class list : public _List_base {
    // total size: 0x8
};
class MidiParser : public MsgSource {
    // total size: 0xC8
    class DataEventList * mEvents; // offset 0x1C, size 0x4
    class Symbol mTrackName; // offset 0x20, size 0x4
    class DataArray * mGemParser; // offset 0x24, size 0x4
    class DataArray * mNoteParser; // offset 0x28, size 0x4
    class DataArray * mTextParser; // offset 0x2C, size 0x4
    class DataArray * mIdleParser; // offset 0x30, size 0x4
    class DataArray * mCurParser; // offset 0x34, size 0x4
    class DataArray * mAllowedNotes; // offset 0x38, size 0x4
    class vector * mText; // offset 0x3C, size 0x4
    class vector mNotes; // offset 0x40, size 0xC
    const class GameGemList * mGems; // offset 0x4C, size 0x4
    unsigned char mInverted; // offset 0x50, size 0x1
    struct PostProcess mProcess; // offset 0x54, size 0x1C
    float mLastStart; // offset 0x70, size 0x4
    float mLastEnd; // offset 0x74, size 0x4
    float mFirstEnd; // offset 0x78, size 0x4
    const class DataEvent * mEvent; // offset 0x7C, size 0x4
    class Symbol mMessageType; // offset 0x80, size 0x4
    unsigned char mAppendLength; // offset 0x84, size 0x1
    unsigned char mMessageSelf; // offset 0x85, size 0x1
    unsigned char mCompressed; // offset 0x86, size 0x1
    int mGemIndex; // offset 0x88, size 0x4
    int mNoteIndex; // offset 0x8C, size 0x4
    int mTextIndex; // offset 0x90, size 0x4
    float mStart; // offset 0x94, size 0x4
    int mBefore; // offset 0x98, size 0x4
};
class MidiParserMgr : public MidiReceiver {
    // total size: 0x38
    class vector mNoteOns; // offset 0x8, size 0xC
    class vector mText; // offset 0x14, size 0xC
    class SongData * mSongData; // offset 0x20, size 0x4
    unsigned char mLoaded; // offset 0x24, size 0x1
    const char * mFileName; // offset 0x28, size 0x4
    class Symbol mTrackName; // offset 0x2C, size 0x4
    int mMaxNoteSize; // offset 0x30, size 0x4
    int mMaxTextSize; // offset 0x34, size 0x4
};
// Range: 0x80051D10 -> 0x80051DD8
float Game::PollShuttle(class Game * const this /* r31 */) {
    // Local variables
    float ms; // f31

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80051DD8 -> 0x80051E10
float Game::GetSongMs() {}

// Range: 0x80051E10 -> 0x80051E70
class Symbol Game::GetSectionAtMs() {
    // Local variables
    int tick; // r0
    class vector & sections; // r0
    struct PracticeSection * s; // r6

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80051E70 -> 0x80051F14
void Game::WaitUntilReady() {
    // Local variables
    class MasterAudio * audio; // r31
    unsigned char printed; // r30

    // References
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
}

// Range: 0x80051F14 -> 0x80051F1C
void Game::SetStartTime() {}

// Range: 0x80051F1C -> 0x80051F78
void Game::SetTimePaused(class Game * const this /* r30 */, unsigned char paused /* r31 */) {}

// Range: 0x80051F78 -> 0x800520A0
void Game::SetPaused(class Game * const this /* r27 */, unsigned char paused /* r28 */, unsigned char playing /* r29 */) {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30

    // References
    // -> class GamePanel * TheGamePanel;
    // -> class WiiRnd TheWiiRnd;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x800520A0 -> 0x800521B0
void Game::SetTimeOffset(class Game * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x800521B0 -> 0x800522C8
void Game::SetRealtime(class Game * const this /* r28 */, unsigned char realtime /* r29 */) {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class GameMode * TheGameMode;
}

// Range: 0x800522C8 -> 0x8005233C
void Game::SetMusicSpeed(float speed /* f31 */) {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30
}

// Range: 0x8005233C -> 0x800523BC
void Game::SetMusicVolume(class Game * const this /* r31 */, float volume /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800523BC -> 0x80052400
void Game::SetIntroRealTime(class Game * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80052400 -> 0x800524A0
class Band * Game::GetBand(class Game * const this /* r30 */, int band /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800524A0 -> 0x80052540
class Player * Game::GetPlayer(const class Game * const this /* r30 */, int player_num /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80052540 -> 0x800525E0
class Player * Game::GetLocalPlayer(const class Game * const this /* r30 */, int player_num /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800525E0 -> 0x80052664
unsigned char Game::IsActivePlayer(const class Game * const this /* r29 */, int playerNum /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x80052664 -> 0x80052708
int Game::GetActivePlayerID(const class Game * const this /* r29 */, int playerNum /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80052708 -> 0x80052788
class Player * Game::GetPlayerFromTrack() {
    // Local variables
    int n; // r6

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80052788 -> 0x800527A0
int Game::NumActivePlayers() {}

// Range: 0x800527A0 -> 0x800527B8
int Game::NumLocalPlayers() {}

// Range: 0x800527B8 -> 0x800527D0
int Game::NumBands() {}

// Range: 0x800527D0 -> 0x800528C0
enum EndGameResult Game::GetResult(class Game * const this /* r29 */) {
    // Local variables
    enum EndGameResult result; // r3
    int s0; // r0
    int s1; // r0
}

// Range: 0x800528C0 -> 0x80052A5C
enum EndGameResult Game::GetResultForPlayer(class Game * const this /* r24 */, int player_num /* r25 */) {
    // Local variables
    enum EndGameResult result; // r29
    unsigned char in_band0; // r28
    class vector & users; // r0
    class BandUser * * it; // r27
    class BandUser * pUser; // r26
    class Player * player; // r26

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80052A5C -> 0x80052A6C
class Player * Game::GetActivePlayer() {}

// Range: 0x80052A6C -> 0x80052B70
void Game::Jump(class Game * const this /* r28 */, float ms /* f31 */, unsigned char syncAudio /* r29 */) {
    // Local variables
    int b; // r31
    const class vector & players; // r0
    class Player * const * it; // r30
}

// Range: 0x80052B70 -> 0x80052C5C
void Game::PostWaitJump(class Game * const this /* r30 */) {
    // References
    // -> class GameMode * TheGameMode;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x80052C5C -> 0x80052C6C
void Game::ResetAudio() {}

// Range: 0x80052C6C -> 0x80052CB0
void Game::ClearState() {
    // Local variables
    int p; // r5
    class Player * player; // r4
}

// Range: 0x80052CB0 -> 0x80052D38
void Game::Restart(class Game * const this /* r30 */, unsigned char reset /* r31 */) {
    // References
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x80052D38 -> 0x80052F70
void Game::PostWaitRestart(class Game * const this /* r31 */) {
    // Local variables
    const char * str; // r0
    class vector & users; // r0
    class BandUser * * it; // r27
    class BandUser * pUser; // r28
    int b; // r27
    class MetaPerformer * mp; // r27
    class PersistentGameData * game_data; // r28
    int b; // r27

    // References
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x80052F70 -> 0x80052F78
class vector & Game::GetActivePlayers() {}

// Range: 0x80052F78 -> 0x80052F84
void Game::SetBackgroundVolume() {}

// Range: 0x80052F84 -> 0x80052F90
void Game::SetForegroundVolume() {}

// Range: 0x80052F90 -> 0x80052F9C
void Game::SetVocalCueVolume() {}

// Range: 0x80052F9C -> 0x80052FA8
void Game::SetStereo() {}

// Range: 0x80052FA8 -> 0x8005304C
void Game::AddMusicFader(class Game * const this /* r30 */, class Fader * f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8005304C -> 0x80053294
void Game::PopulatePlayerLists(class Game * const this /* r29 */) {
    // Local variables
    class vector & users; // r0
    class BandUser * * it; // r30
    class BandUser * pUser; // r28
    int p; // r28
    int b; // r27
    class Player * player; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80053294 -> 0x8005334C
int Game::BandOfPlayer(class Game * const this /* r29 */, int player /* r30 */) {
    // Local variables
    int b; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8005334C -> 0x80053460
void Game::AddBonusPoints(class Game * const this /* r30 */, int points /* r28 */, int bonus_id /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80053460 -> 0x8005353C
void Game::SavePersistentGameData(const class Game * const this /* r29 */, class PersistentGameData & data /* r30 */) {
    // Local variables
    class Performer * perf; // r31
    int p; // r31
    class Player * player; // r3
}

// Range: 0x8005353C -> 0x8005361C
void Game::LoadPersistentGameData(class Game * const this /* r28 */, const class PersistentGameData & data /* r29 */, unsigned char restart /* r30 */) {
    // Local variables
    int p; // r31
    class Player * player; // r3
}

// Range: 0x8005361C -> 0x80053758
void Game::EnforceMaxDelta(class Game * const this /* r31 */) {
    // Local variables
    int min_score; // r1+0xC
    int b; // r30
    int score; // r1+0x8
    int max_score; // r29
    int b; // r28
    class Performer * performer; // r27
    int score; // r0
}

// Range: 0x80053758 -> 0x800537D8
void Game::SetGamePaused(class Game * const this /* r30 */, unsigned char paused /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Synth * TheSynth;
}

// Range: 0x800537D8 -> 0x800537E4
class Performer * Game::GetMainPerformer() {}

// Range: 0x800537E4 -> 0x80053818
enum ExcitementLevel Game::GetCrowdExcitement() {}

// Range: 0x80053818 -> 0x8005384C
unsigned char Game::AllowInput() {}

// Range: 0x8005384C -> 0x80053854
void Game::SetKickAutoplay() {
    // References
    // -> unsigned char gKickAutoplay;
}

// Range: 0x80053854 -> 0x80053980
unsigned char Game::HandleWait(class Game * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Synth * TheSynth;
}

// Range: 0x80053980 -> 0x80053998
unsigned char Game::UseSyncedWait() {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x80053998 -> 0x80053A38
unsigned char Game::IsWaiting(class Game * const this /* r30 */) {}

// Range: 0x80053A38 -> 0x80053AA4
void Game::PrintBasePoints() {
    // Local variables
    int base_points; // r31

    // References
    // -> class Debug TheDebug;
    // -> class SongDB * TheSongDB;
}

// Range: 0x80053AA4 -> 0x80053AAC
void Game::SetBotbReset() {}

// Range: 0x80053AAC -> 0x80053AB4
unsigned char Game::GetBotbReset() {}

static class Symbol _s; // size: 0x4, address: 0x80A49468
static class Symbol _s; // size: 0x4, address: 0x80A49470
static class Symbol _s; // size: 0x4, address: 0x80A49478
static class Symbol _s; // size: 0x4, address: 0x80A49480
static class Symbol _s; // size: 0x4, address: 0x80A49488
static class Symbol _s; // size: 0x4, address: 0x80A49490
static class Symbol _s; // size: 0x4, address: 0x80A49498
static class Symbol _s; // size: 0x4, address: 0x80A494A0
static class Symbol _s; // size: 0x4, address: 0x80A494A8
static class Symbol _s; // size: 0x4, address: 0x80A494B0
static class Symbol _s; // size: 0x4, address: 0x80A494B8
static class Symbol _s; // size: 0x4, address: 0x80A494C0
static class Symbol _s; // size: 0x4, address: 0x80A494C8
static class Symbol _s; // size: 0x4, address: 0x80A494D0
static class Symbol _s; // size: 0x4, address: 0x80A494D8
static class Symbol _s; // size: 0x4, address: 0x80A494E0
static class Symbol _s; // size: 0x4, address: 0x80A494E8
static class Symbol _s; // size: 0x4, address: 0x80A494F0
static class Symbol _s; // size: 0x4, address: 0x80A494F8
static class Symbol _s; // size: 0x4, address: 0x80A49500
static class Symbol _s; // size: 0x4, address: 0x80A49508
static class Symbol _s; // size: 0x4, address: 0x80A49510
static class Symbol _s; // size: 0x4, address: 0x80A49518
static class Symbol _s; // size: 0x4, address: 0x80A49520
static class Symbol _s; // size: 0x4, address: 0x80A49528
static class Symbol _s; // size: 0x4, address: 0x80A49530
static class Symbol _s; // size: 0x4, address: 0x80A49538
static class Symbol _s; // size: 0x4, address: 0x80A49540
static class Symbol _s; // size: 0x4, address: 0x80A49548
static class Symbol _s; // size: 0x4, address: 0x80A49550
static class Symbol _s; // size: 0x4, address: 0x80A49558
static class Symbol _s; // size: 0x4, address: 0x80A49560
static class Symbol _s; // size: 0x4, address: 0x80A49568
static class Symbol _s; // size: 0x4, address: 0x80A49570
static class Symbol _s; // size: 0x4, address: 0x80A49578
static class Symbol _s; // size: 0x4, address: 0x80A49580
static class Symbol _s; // size: 0x4, address: 0x80A49588
static class Symbol _s; // size: 0x4, address: 0x80A49590
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct SoloSongStatus {
    // total size: 0x28
    class Symbol mSongName; // offset 0x0, size 0x4
    int mScore[4]; // offset 0x4, size 0x10
    unsigned char mDirty[4]; // offset 0x14, size 0x4
    enum Difficulty mDiff[4]; // offset 0x18, size 0x10
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class SoloSongStatusMgr : public Object {
    // total size: 0x40
    int mPadNum; // offset 0x28, size 0x4
    const class SongMgr * mSongMgr; // offset 0x2C, size 0x4
    class list mSongList; // offset 0x30, size 0x8
    struct SoloSongStatus * mUpdatingScore; // offset 0x38, size 0x4
    int mUpdatingTrackType; // offset 0x3C, size 0x4
};
class HighScoreSongStatusMgr {
    // total size: 0x10
    class vector mSongs; // offset 0x0, size 0xC
    const class SongMgr * mSongMgr; // offset 0xC, size 0x4
};
// Range: 0x80053AB4 -> 0x80054BBC
class DataNode Game::Handle(class Game * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28
    class DataNode _n; // r1+0x20

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
    // -> class TempoMap * TheTempoMap;
    // -> class TaskMgr TheTaskMgr;
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

// Range: 0x80054BBC -> 0x80054CC0
class DataNode Game::OnSetShuttle(class Game * const this /* r30 */, class DataArray * a /* r31 */) {
    // Local variables
    unsigned char active; // r31

    // References
    // -> class Synth * TheSynth;
}

// Range: 0x80054CC0 -> 0x80054E50
class DataNode Game::ForEachActivePlayer(class Game * const this /* r28 */, const class DataArray * a /* r29 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode tmp; // r1+0x18
    int i; // r30
    int j; // r26
}

struct {
    // total size: 0x28
} __vt__10NetMessage; // size: 0x28, address: 0x80873F00
struct {
    // total size: 0x8
} __RTTI__10NetMessage; // size: 0x8, address: 0x80873F38
struct {
    // total size: 0x74
} __vt__4Game; // size: 0x74, address: 0x80873F40
struct {
    // total size: 0x8
} __RTTI__4Game; // size: 0x8, address: 0x80873FD8
struct {
    // total size: 0x1C
} __vt__14BeatMasterSink; // size: 0x1C, address: 0x80873FE0
struct {
    // total size: 0x8
} __RTTI__14BeatMasterSink; // size: 0x8, address: 0x80874010
struct {
    // total size: 0x8
} __RTTI__PP4Band; // size: 0x8, address: 0x80874050
struct BonusRow {
    // total size: 0x10
    int mBandScores[2]; // offset 0x0, size 0x8
    int mPointsAwarded; // offset 0x8, size 0x4
    unsigned char mDirty; // offset 0xC, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__P8BonusRow; // size: 0x8, address: 0x80874080
class LogFile : public TextStream {
    // total size: 0x20
    class String mFilePattern; // offset 0x4, size 0xC
    int mSerialNumber; // offset 0x10, size 0x4
    unsigned char mDirty; // offset 0x14, size 0x1
    class TextFileStream * mFile; // offset 0x18, size 0x4
    unsigned char mActive; // offset 0x1C, size 0x1
};
enum Type {
    kDisconnected = 0,
    kHeadset = 1,
    kUSBMic = 2,
};
class Mic {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
struct TypeCreatorPair {
    // total size: 0x10
    class String mType; // offset 0x0, size 0xC
    class NetMessage * (* mCreator)(); // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TypeCreatorPair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TypeCreatorPair * _M_start; // offset 0x0, size 0x4
    struct TypeCreatorPair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class NetMessageFactory {
    // total size: 0xC
    class vector mFactoryList; // offset 0x0, size 0xC
};

