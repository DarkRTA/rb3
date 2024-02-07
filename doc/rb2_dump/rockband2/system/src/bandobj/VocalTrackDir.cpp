/*
    Compile unit: C:\rockband2\system\src\bandobj\VocalTrackDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802AAC00 -> 0x802B33A4
*/
class DataArray * types; // size: 0x4, address: 0x80A4FDD0
// Range: 0x802AAC00 -> 0x802AB3C4
void * VocalTrackDir::VocalTrackDir(class VocalTrackDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndLine,9ObjectDir>;
    // -> struct [anonymous] __vt__13VocalTrackDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802AB3C4 -> 0x802ABFC4
void VocalTrackDir::Copy(class VocalTrackDir * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class VocalTrackDir * d; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13VocalTrackDir;
}

// Range: 0x802ABFC4 -> 0x802AC020
void VocalTrackDir::Load(class VocalTrackDir * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x802AC020 -> 0x802AC6E0
void VocalTrackDir::PostLoad(class VocalTrackDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class list sRevs;
}

static class Message apply; // size: 0x8, address: 0x8097D3D8
// Range: 0x802AC6E0 -> 0x802ACA40
void VocalTrackDir::SetConfiguration(class VocalTrackDir * const this /* r30 */, class Object * config /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11StreakMeter;
    // -> static class Message apply;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802ACA40 -> 0x802ACE24
void VocalTrackDir::UpdateConfiguration(class VocalTrackDir * const this /* r31 */) {
    // Local variables
    unsigned char wide; // r25
    unsigned char scrolling; // r0
    const char * configName; // r25
    class Object * gameMode; // r24

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Rnd & TheRnd;
}

// Range: 0x802ACE24 -> 0x802ACE54
unsigned char VocalTrackDir::IsScrolling() {}

static class Message kResetMsg; // size: 0x8, address: 0x8097D3F0
static class Symbol loop; // size: 0x4, address: 0x80A4FDD8
// Range: 0x802ACE54 -> 0x802AD2E8
void VocalTrackDir::TrackReset(class VocalTrackDir * const this /* r30 */) {
    // Local variables
    float timeTillNext; // f31

    // References
    // -> static class Symbol loop;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message kResetMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x802AD2E8 -> 0x802AD350
void VocalTrackDir::PlayIntro(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802AD350 -> 0x802AD358
void VocalTrackDir::SetStreak() {}

// Range: 0x802AD358 -> 0x802AD3A8
void VocalTrackDir::Deploy(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802AD3A8 -> 0x802AD3B0
void VocalTrackDir::SetStaticVocals() {}

// Range: 0x802AD3B0 -> 0x802AD658
void VocalTrackDir::UpdateFade(class VocalTrackDir * const this /* r28 */) {
    // Local variables
    float leftOut; // f31
    float rightOut; // f30

    // References
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Message kResetMsg; // size: 0x8, address: 0x8097D408
// Range: 0x802AD658 -> 0x802AD7EC
void VocalTrackDir::SetTambourine(class VocalTrackDir * const this /* r30 */, unsigned char state /* r31 */) {
    // References
    // -> static class Message kResetMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802AD7EC -> 0x802AD928
void VocalTrackDir::Tambourine(class VocalTrackDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7Message;
}

static class Message tambNote; // size: 0x8, address: 0x8097D420
// Range: 0x802AD928 -> 0x802ADA84
void VocalTrackDir::TambourineNote(class VocalTrackDir * const this /* r31 */) {
    // References
    // -> static class Message tambNote;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802ADA84 -> 0x802ADB58
void VocalTrackDir::SetFeedbackState(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802ADB58 -> 0x802ADC08
void VocalTrackDir::SetArrowVisible(class VocalTrackDir * const this /* r29 */, unsigned char visible /* r30 */) {}

// Range: 0x802ADC08 -> 0x802ADC90
void VocalTrackDir::SetFrameScore(class VocalTrackDir * const this /* r30 */) {
    // Local variables
    unsigned char scoring; // r31
}

// Range: 0x802ADC90 -> 0x802ADD24
void VocalTrackDir::SetPitched(class VocalTrackDir * const this /* r30 */, unsigned char pitched /* r31 */) {}

// Range: 0x802ADD24 -> 0x802ADD78
void VocalTrackDir::SetPhraseMeter(class VocalTrackDir * const this /* r31 */, float pct /* f31 */) {}

// Range: 0x802ADD78 -> 0x802ADD90
void VocalTrackDir::SetEnableVocalsOptions() {}

// Range: 0x802ADD90 -> 0x802ADE40
void VocalTrackDir::ShowPhraseFeedback(class VocalTrackDir * const this /* r29 */, class Color & color /* r30 */) {
    // Local variables
    unsigned char updateText; // r1+0x8
}

// Range: 0x802ADE40 -> 0x802ADECC
void VocalTrackDir::SpotlightPhraseSuccess(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802ADECC -> 0x802ADF30
void VocalTrackDir::NewPhrase(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802ADF30 -> 0x802AE028
void VocalTrackDir::UpdateVolumeDisplay(int val /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UISlider;
}

static class Symbol pause_screen; // size: 0x4, address: 0x80A4FDE0
static class Symbol confirm_quit_screen; // size: 0x4, address: 0x80A4FDE8
// Range: 0x802AE028 -> 0x802AE34C
void VocalTrackDir::ActivateVolume(class VocalTrackDir * const this /* r29 */, enum VocalParam param /* r30 */) {
    // Local variables
    class Object * gameMode; // r25

    // References
    // -> struct [anonymous] __RTTI__8UISlider;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> static class Symbol confirm_quit_screen;
    // -> static class Symbol pause_screen;
    // -> class UIManager TheUI;
}

// Range: 0x802AE34C -> 0x802AE3A4
void VocalTrackDir::DeactivateVolume(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802AE3A4 -> 0x802AE408
void VocalTrackDir::IncrementVolume(class VocalTrackDir * const this /* r31 */) {}

// Range: 0x802AE408 -> 0x802AE598
void VocalTrackDir::CanChat(class VocalTrackDir * const this /* r27 */, unsigned char allow /* r28 */) {
    // References
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x802AE598 -> 0x802AE5FC
void VocalTrackDir::SetupNetVocals(class VocalTrackDir * const this /* r31 */) {}

static class Symbol fade_max; // size: 0x4, address: 0x80A4FDF0
// Range: 0x802AE5FC -> 0x802AE888
void VocalTrackDir::SetPlayerLocal(class VocalTrackDir * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> static class Symbol fade_max;
}

static class Message display_mode; // size: 0x8, address: 0x8097D438
// Range: 0x802AE888 -> 0x802AE9E0
class DataNode VocalTrackDir::OnGetDisplayMode(class VocalTrackDir * const this /* r31 */) {
    // References
    // -> static class Message display_mode;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802AE9E0 -> 0x802AEAEC
class DataNode VocalTrackDir::OnMsg(class VocalTrackDir * const this /* r30 */) {
    // Local variables
    enum JoypadButton rawButton; // r0
}

// Range: 0x802AEAEC -> 0x802AEBF4
class DataNode VocalTrackDir::OnMsg(class VocalTrackDir * const this /* r28 */, const class ButtonUpMsg & msg /* r29 */) {
    // Local variables
    enum JoypadButton rawButton; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A4FDF8
static class Symbol _s; // size: 0x4, address: 0x80A4FE00
static class Symbol _s; // size: 0x4, address: 0x80A4FE08
static class Symbol _s; // size: 0x4, address: 0x80A4FE10
static class Symbol _s; // size: 0x4, address: 0x80A4FE18
static class Symbol _s; // size: 0x4, address: 0x80A4FE20
static class Symbol _s; // size: 0x4, address: 0x80A4FE28
static class Symbol _s; // size: 0x4, address: 0x80A4FE30
static class Symbol _s; // size: 0x4, address: 0x80A4FE38
static class Symbol _s; // size: 0x4, address: 0x80A4FE40
static class Symbol _s; // size: 0x4, address: 0x80A4FE48
static class Symbol _s; // size: 0x4, address: 0x80A4FE50
static class Symbol _s; // size: 0x4, address: 0x80A4FE58
static class Symbol _s; // size: 0x4, address: 0x80A4FE60
static class Symbol _s; // size: 0x4, address: 0x80A4FE68
static class Symbol _s; // size: 0x4, address: 0x80A4FE70
static class Symbol _s; // size: 0x4, address: 0x80A4FE78
static class Symbol _s; // size: 0x4, address: 0x80A4FE80
static class Symbol _s; // size: 0x4, address: 0x80A4FE88
static class Symbol _s; // size: 0x4, address: 0x80A4FE90
static class Symbol _s; // size: 0x4, address: 0x80A4FE98
static class Symbol _s; // size: 0x4, address: 0x80A4FEA0
static class Symbol _s; // size: 0x4, address: 0x80A4FEA8
static class Symbol _s; // size: 0x4, address: 0x80A4FEB0
static class Symbol _s; // size: 0x4, address: 0x80A4FEB8
static class Symbol _s; // size: 0x4, address: 0x80A4FEC0
static class Symbol _s; // size: 0x4, address: 0x80A4FEC8
static class Symbol _s; // size: 0x4, address: 0x80A4FED0
static class Symbol _s; // size: 0x4, address: 0x80A4FED8
static class Symbol _s; // size: 0x4, address: 0x80A4FEE0
static class Symbol _s; // size: 0x4, address: 0x80A4FEE8
static class Symbol _s; // size: 0x4, address: 0x80A4FEF0
static class Symbol _s; // size: 0x4, address: 0x80A4FEF8
static class Symbol _s; // size: 0x4, address: 0x80A4FF00
static class Symbol _s; // size: 0x4, address: 0x80A4FF08
static class Symbol _s; // size: 0x4, address: 0x80A4FF10
static class Symbol _s; // size: 0x4, address: 0x80A4FF18
static class Symbol _s; // size: 0x4, address: 0x80A4FF20
static class Symbol _s; // size: 0x4, address: 0x80A4FF28
static class Symbol _s; // size: 0x4, address: 0x80A4FF30
static class Symbol _s; // size: 0x4, address: 0x80A4FF38
static class Symbol _s; // size: 0x4, address: 0x80A4FF40
static class Symbol _s; // size: 0x4, address: 0x80A4FF48
static class Symbol _s; // size: 0x4, address: 0x80A4FF50
static class Symbol _s; // size: 0x4, address: 0x80A4FF58
static class Symbol _s; // size: 0x4, address: 0x80A4FF60
static class Symbol _s; // size: 0x4, address: 0x80A4FF68
static class Symbol _s; // size: 0x4, address: 0x80A4FF70
static class Symbol _s; // size: 0x4, address: 0x80A4FF78
static class Symbol _s; // size: 0x4, address: 0x80A4FF80
static class Symbol _s; // size: 0x4, address: 0x80A4FF88
static class Symbol _s; // size: 0x4, address: 0x80A4FF90
static class Symbol _s; // size: 0x4, address: 0x80A4FF98
static class Symbol _s; // size: 0x4, address: 0x80A4FFA0
static class Symbol _s; // size: 0x4, address: 0x80A4FFA8
static class Symbol _s; // size: 0x4, address: 0x80A4FFB0
static class Symbol _s; // size: 0x4, address: 0x80A4FFB8
static class Symbol _s; // size: 0x4, address: 0x80A4FFC0
static class Symbol _s; // size: 0x4, address: 0x80A4FFC8
static class Symbol _s; // size: 0x4, address: 0x80A4FFD0
static class Symbol _s; // size: 0x4, address: 0x80A4FFD8
static class Symbol _s; // size: 0x4, address: 0x80A4FFE0
static class Symbol _s; // size: 0x4, address: 0x80A4FFE8
static class Symbol _s; // size: 0x4, address: 0x80A4FFF0
static class Symbol _s; // size: 0x4, address: 0x80A4FFF8
static class Symbol _s; // size: 0x4, address: 0x80A50000
static class Symbol _s; // size: 0x4, address: 0x80A50008
static class Symbol _s; // size: 0x4, address: 0x80A50010
static class Symbol _s; // size: 0x4, address: 0x80A50018
static class Symbol _s; // size: 0x4, address: 0x80A50020
static class Symbol _s; // size: 0x4, address: 0x80A50028
static class Symbol _s; // size: 0x4, address: 0x80A50030
static class Symbol _s; // size: 0x4, address: 0x80A50038
static class Symbol _s; // size: 0x4, address: 0x80A50040
static class Symbol _s; // size: 0x4, address: 0x80A50048
static class Symbol _s; // size: 0x4, address: 0x80A50050
static class Symbol _s; // size: 0x4, address: 0x80A50058
static class Symbol _s; // size: 0x4, address: 0x80A50060
static class Symbol _s; // size: 0x4, address: 0x80A50068
static class Symbol _s; // size: 0x4, address: 0x80A50070
static class Symbol _s; // size: 0x4, address: 0x80A50078
// Range: 0x802AEBF4 -> 0x802B155C
unsigned char VocalTrackDir::SyncProperty(class VocalTrackDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x802B155C -> 0x802B1C14
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class RndTransformable * obj; // r31
    class RndTransformable * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A50080
static class Symbol _s; // size: 0x4, address: 0x80A50088
static class Symbol _s; // size: 0x4, address: 0x80A50090
static class Symbol _s; // size: 0x4, address: 0x80A50098
static class Symbol _s; // size: 0x4, address: 0x80A500A0
static class Symbol _s; // size: 0x4, address: 0x80A500A8
static class Symbol _s; // size: 0x4, address: 0x80A500B0
static class Symbol _s; // size: 0x4, address: 0x80A500B8
static class Symbol _s; // size: 0x4, address: 0x80A500C0
static class Symbol _s; // size: 0x4, address: 0x80A500C8
static class Symbol _s; // size: 0x4, address: 0x80A500D0
static class Symbol _s; // size: 0x4, address: 0x80A500D8
static class Symbol _s; // size: 0x4, address: 0x80A500E0
static class Symbol _s; // size: 0x4, address: 0x80A500E8
static class Symbol _s; // size: 0x4, address: 0x80A500F0
static class Symbol _s; // size: 0x4, address: 0x80A500F8
static class Symbol _s; // size: 0x4, address: 0x80A50100
static class Symbol _s; // size: 0x4, address: 0x80A50108
static class Symbol _s; // size: 0x4, address: 0x80A50110
static class Symbol _s; // size: 0x4, address: 0x80A50118
static class Symbol _s; // size: 0x4, address: 0x80A50120
static class Symbol _s; // size: 0x4, address: 0x80A50128
static class Symbol _s; // size: 0x4, address: 0x80A50130
static class Symbol _s; // size: 0x4, address: 0x80A50138
static class Symbol _s; // size: 0x4, address: 0x80A50140
static class Symbol _s; // size: 0x4, address: 0x80A50148
static class Symbol _s; // size: 0x4, address: 0x80A50150
static class Symbol _s; // size: 0x4, address: 0x80A50158
static class Symbol _s; // size: 0x4, address: 0x80A50160
static class Symbol _s; // size: 0x4, address: 0x80A50168
static class Symbol _s; // size: 0x4, address: 0x80A50170
static class Symbol _s; // size: 0x4, address: 0x80A50178
static class Symbol _s; // size: 0x4, address: 0x80A50180
static class Symbol _s; // size: 0x4, address: 0x80A50188
static class Symbol _s; // size: 0x4, address: 0x80A50190
static class Symbol _s; // size: 0x4, address: 0x80A50198
static class Symbol _s; // size: 0x4, address: 0x80A501A0
static class Symbol _s; // size: 0x4, address: 0x80A501A8
static class Symbol _s; // size: 0x4, address: 0x80A501B0
static class Symbol _s; // size: 0x4, address: 0x80A501B8
static class Symbol _s; // size: 0x4, address: 0x80A501C0
static class Symbol _s; // size: 0x4, address: 0x80A501C8
static class Symbol _s; // size: 0x4, address: 0x80A501D0
static class Symbol _s; // size: 0x4, address: 0x80A501D8
static class Symbol _s; // size: 0x4, address: 0x80A501E0
static class Symbol _s; // size: 0x4, address: 0x80A501E8
static class Symbol _s; // size: 0x4, address: 0x80A501F0
static class Symbol _s; // size: 0x4, address: 0x80A501F8
static class Symbol _s; // size: 0x4, address: 0x80A50200
// Range: 0x802B1C14 -> 0x802B31F4
class DataNode VocalTrackDir::Handle(class VocalTrackDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x1C
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

// Range: 0x802B31F4 -> 0x802B33A4
class DataNode VocalTrackDir::DataForEachConfigObj(class VocalTrackDir * const this /* r28 */, class DataArray * array /* r30 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode val; // r1+0x30
    class iterator it; // r1+0x18
    int j; // r28
}

struct {
    // total size: 0x2A4
} __vt__13VocalTrackDir; // size: 0x2A4, address: 0x808C2D10
struct {
    // total size: 0x18
} __vt__41ObjPtrList<16RndTransformable,9ObjectDir>; // size: 0x18, address: 0x808C3028
struct {
    // total size: 0x8
} __RTTI__41ObjPtrList<16RndTransformable,9ObjectDir>; // size: 0x8, address: 0x808C3078

