/*
    Compile unit: C:\rockband2\system\src\bandobj\Scoreboard.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802CA270 -> 0x802CD064
*/
class DataArray * types; // size: 0x4, address: 0x80A50468
static class Symbol normal; // size: 0x4, address: 0x80A50470
static class Symbol botb; // size: 0x4, address: 0x80A50478
static class Symbol botb_star; // size: 0x4, address: 0x80A50480
// Range: 0x802CA270 -> 0x802CA664
void * Scoreboard::Scoreboard(class Scoreboard * const this /* r30 */) {
    // References
    // -> static class Symbol botb_star;
    // -> static class Symbol botb;
    // -> static class Symbol normal;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__10Scoreboard;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802CA664 -> 0x802CAC34
void * Scoreboard::~Scoreboard(class Scoreboard * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
}

// Range: 0x802CAC34 -> 0x802CB184
void Scoreboard::SyncObjects(class Scoreboard * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> struct [anonymous] __RTTI__3Sfx;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> struct [anonymous] __RTTI__7RndText;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x802CB184 -> 0x802CB354
void Scoreboard::Reset(class Scoreboard * const this /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802CB354 -> 0x802CB434
void Scoreboard::SetScore(class Scoreboard * const this /* r30 */, float score /* f31 */) {}

// Range: 0x802CB434 -> 0x802CB534
void Scoreboard::SetOpponentScore(class Scoreboard * const this /* r30 */, float score /* f31 */) {}

// Range: 0x802CB534 -> 0x802CB57C
void Scoreboard::SetStarBattle() {}

// Range: 0x802CB57C -> 0x802CBA68
void Scoreboard::SetNumStars(class Scoreboard * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndMatAnim;
}

// Range: 0x802CBA68 -> 0x802CBAA0
void Scoreboard::PlayStarSound() {}

static class Symbol normal; // size: 0x4, address: 0x80A50488
static class Symbol botb; // size: 0x4, address: 0x80A50490
static class Symbol botb_star; // size: 0x4, address: 0x80A50498
// Range: 0x802CBAA0 -> 0x802CBC10
void Scoreboard::SetConfig(class Scoreboard * const this /* r29 */, class Symbol & config /* r30 */) {
    // References
    // -> static class Symbol botb_star;
    // -> static class Symbol botb;
    // -> static class Symbol normal;
}

// Range: 0x802CBC10 -> 0x802CBC28
void Scoreboard::ShowStars() {}

static class Symbol _s; // size: 0x4, address: 0x80A504A0
static class Symbol _s; // size: 0x4, address: 0x80A504A8
static class Symbol _s; // size: 0x4, address: 0x80A504B0
static class Symbol _s; // size: 0x4, address: 0x80A504B8
static class Symbol _s; // size: 0x4, address: 0x80A504C0
// Range: 0x802CBC28 -> 0x802CC3A4
class DataNode Scoreboard::Handle(class Scoreboard * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
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

static class Symbol _s; // size: 0x4, address: 0x80A504C8
static class Symbol _s; // size: 0x4, address: 0x80A504D0
static class Symbol _s; // size: 0x4, address: 0x80A504D8
static class Symbol _s; // size: 0x4, address: 0x80A504E0
static class Symbol _s; // size: 0x4, address: 0x80A504E8
static class Symbol _s; // size: 0x4, address: 0x80A504F0
// Range: 0x802CC3A4 -> 0x802CC958
unsigned char Scoreboard::SyncProperty(class Scoreboard * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x802CC958 -> 0x802CCC18
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class ObjPtr * it; // r31
    class ObjPtr tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802CCC18 -> 0x802CCC5C
void Scoreboard::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802CCC5C -> 0x802CCDFC
void Scoreboard::PreLoad(class Scoreboard * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
}

// Range: 0x802CCDFC -> 0x802CCE00
void Scoreboard::PostLoad() {}

// Range: 0x802CCE00 -> 0x802CD064
void Scoreboard::Copy(class Scoreboard * const this /* r29 */, const class Object * o /* r26 */, enum CopyType ct /* r25 */) {
    // Local variables
    const class Scoreboard * sb; // r0

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10Scoreboard;
}

struct {
    // total size: 0x21C
} __vt__10Scoreboard; // size: 0x21C, address: 0x808C8AF0

