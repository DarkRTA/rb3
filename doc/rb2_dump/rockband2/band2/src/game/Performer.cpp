/*
    Compile unit: C:\rockband2\band2\src\game\Performer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800741C4 -> 0x80076284
*/
// Range: 0x800741C4 -> 0x80074360
void * Performer::Performer(class Performer * const this /* r28 */, class BandUser * config /* r29 */, class Band * group /* r30 */, int player_num /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameConfig * TheGameConfig;
    // -> struct [anonymous] __vt__9Performer;
}

// Range: 0x80074360 -> 0x80074418
void * Performer::~Performer(class Performer * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9Performer;
}

// Range: 0x80074418 -> 0x80074434
int Performer::GetScore() {}

// Range: 0x80074434 -> 0x8007443C
int Performer::GetMultiplier() {}

// Range: 0x8007443C -> 0x80074444
int Performer::GetCurrentStreak() {}

// Range: 0x80074444 -> 0x80074450
float Performer::GetCrowdRating() {}

// Range: 0x80074450 -> 0x8007445C
float Performer::GetCrowdWarningLevel() {}

// Range: 0x8007445C -> 0x80074468
float Performer::GetRawCrowdRating() {}

// Range: 0x80074468 -> 0x800744B8
unsigned char Performer::IsInCrowdWarning() {
    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x800744B8 -> 0x800744C0
int Performer::GetTotalHits() {}

// Range: 0x800744C0 -> 0x800744C8
float Performer::PollMs() {}

// Range: 0x800744C8 -> 0x8007450C
float Performer::GetCrowdBoost() {}

// Range: 0x8007450C -> 0x80074514
unsigned char Performer::CanStreak() {}

// Range: 0x80074514 -> 0x80074570
float Performer::GetFractionComplete(const class Performer * const this /* r31 */) {
    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80074570 -> 0x800745E0
int Performer::GetPercentComplete() {}

// Range: 0x800745E0 -> 0x80074618
class Symbol Performer::GetStarRating() {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x80074618 -> 0x800746E4
void Performer::Restart(class Performer * const this /* r30 */) {}

// Range: 0x800746E4 -> 0x80074884
void Performer::Poll(class Performer * const this /* r29 */, float ms /* f30 */, const class SongPos & pos /* r30 */) {
    // Local variables
    float song_duration_ms; // f0
    unsigned char canWin; // r31

    // References
    // -> class Game * TheGame;
    // -> class TaskMgr TheTaskMgr;
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80074884 -> 0x8007488C
void Performer::SetCrowdMeterActive() {}

// Range: 0x8007488C -> 0x800748FC
void Performer::UpdateScore(class Performer * const this /* r30 */, int score /* r31 */) {}

// Range: 0x800748FC -> 0x8007492C
void Performer::ForceScore() {}

// Range: 0x8007492C -> 0x80074970
void Performer::FinalizeStats(class Performer * const this /* r31 */) {}

// Range: 0x80074970 -> 0x80074A3C
void Performer::SendRemoteStats(class Performer * const this /* r22 */, int playerNum /* r23 */) {
    // Local variables
    class PlayerStatsMsg msg; // r1+0x18

    // References
    // -> class Net TheNet;
}

// Range: 0x80074A3C -> 0x80074B30
void Performer::SetStats(class Performer * const this /* r30 */, int deployCount /* r12 */, int score /* r11 */, int soloPercentage /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80074B30 -> 0x80074BD8
void Performer::AddPoints(class Performer * const this /* r31 */, float points /* r1+0x8 */) {
    // Local variables
    int multiplier; // r3
    float add_points; // f1
}

// Range: 0x80074BD8 -> 0x80074BE0
void Performer::Hit() {}

// Range: 0x80074BE0 -> 0x80074C34
void Performer::BuildStreak(class Performer * const this /* r31 */) {}

// Range: 0x80074C34 -> 0x80074C88
void Performer::EndStreak(class Performer * const this /* r31 */) {}

static class Message msg; // size: 0x8, address: 0x80977608
// Range: 0x80074C88 -> 0x80074E34
void Performer::SendStreak(class Performer * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80074E34 -> 0x80074E3C
void Performer::SetStreak() {}

// Range: 0x80074E3C -> 0x80074E94
void Performer::SetRemoteStreak(class Performer * const this /* r30 */, int streak /* r31 */) {}

// Range: 0x80074E94 -> 0x80074F48
void Performer::CheckGameWon(class Performer * const this /* r31 */) {
    // Local variables
    class vector & players; // r0
    int i; // r5

    // References
    // -> class Game * TheGame;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80074F48 -> 0x80074FA4
void Performer::TrulyWinGame(class Performer * const this /* r31 */) {
    // References
    // -> class GamePanel * TheGamePanel;
    // -> class GameConfig * TheGameConfig;
}

static class Message msg; // size: 0x8, address: 0x80977620
// Range: 0x80074FA4 -> 0x80075138
void Performer::WinGame(class Performer * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x80075138 -> 0x80075194
void Performer::ForceStars(class Performer * const this /* r31 */) {}

// Range: 0x80075194 -> 0x800752BC
unsigned char Performer::LoseGame(class Performer * const this /* r31 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class GamePanel * TheGamePanel;
    // -> class GameMode * TheGameMode;
    // -> class Game * TheGame;
}

// Range: 0x800752BC -> 0x800752CC
void Performer::SetLost() {}

// Range: 0x800752CC -> 0x800752D4
void Performer::RemoteUpdateCrowd() {}

// Range: 0x800752D4 -> 0x80075334
float Performer::GetPartialStreakFraction(const class Performer * const this /* r31 */) {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x80075334 -> 0x80075370
int Performer::GetNotesPerStreak() {
    // References
    // -> class Scoring * TheScoring;
}

static class Symbol _s; // size: 0x4, address: 0x80A49B2C
static class Symbol _s; // size: 0x4, address: 0x80A49B34
static class Symbol _s; // size: 0x4, address: 0x80A49B3C
static class Symbol _s; // size: 0x4, address: 0x80A49B44
static class Symbol _s; // size: 0x4, address: 0x80A49B4C
static class Symbol _s; // size: 0x4, address: 0x80A49B54
static class Symbol _s; // size: 0x4, address: 0x80A49B5C
static class Symbol _s; // size: 0x4, address: 0x80A49B64
static class Symbol _s; // size: 0x4, address: 0x80A49B6C
static class Symbol _s; // size: 0x4, address: 0x80A49B74
static class Symbol _s; // size: 0x4, address: 0x80A49B7C
static class Symbol _s; // size: 0x4, address: 0x80A49B84
static class Symbol _s; // size: 0x4, address: 0x80A49B8C
static class Symbol _s; // size: 0x4, address: 0x80A49B94
static class Symbol _s; // size: 0x4, address: 0x80A49B9C
static class Symbol _s; // size: 0x4, address: 0x80A49BA4
static class Symbol _s; // size: 0x4, address: 0x80A49BAC
static class Symbol _s; // size: 0x4, address: 0x80A49BB4
static class Symbol _s; // size: 0x4, address: 0x80A49BBC
static class Symbol _s; // size: 0x4, address: 0x80A49BC4
static class Symbol _s; // size: 0x4, address: 0x80A49BCC
static class Symbol _s; // size: 0x4, address: 0x80A49BD4
static class Symbol _s; // size: 0x4, address: 0x80A49BDC
static class Symbol _s; // size: 0x4, address: 0x80A49BE4
static class Symbol _s; // size: 0x4, address: 0x80A49BEC
static class Symbol _s; // size: 0x4, address: 0x80A49BF4
static class Symbol _s; // size: 0x4, address: 0x80A49BFC
static class Symbol _s; // size: 0x4, address: 0x80A49C04
static class Symbol _s; // size: 0x4, address: 0x80A49C0C
static class Symbol _s; // size: 0x4, address: 0x80A49C14
static class Symbol _s; // size: 0x4, address: 0x80A49C1C
static class Symbol _s; // size: 0x4, address: 0x80A49C24
static class Symbol _s; // size: 0x4, address: 0x80A49C2C
static class Symbol _s; // size: 0x4, address: 0x80A49C34
static class Symbol _s; // size: 0x4, address: 0x80A49C3C
static class Symbol _s; // size: 0x4, address: 0x80A49C44
// Range: 0x80075370 -> 0x80076284
class DataNode Performer::Handle(class Performer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x14
    class MessageTimer _mt; // r1+0x20
    class DataNode _n; // r1+0x18

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
}

struct {
    // total size: 0xE0
} __vt__9Performer; // size: 0xE0, address: 0x80877AF0

