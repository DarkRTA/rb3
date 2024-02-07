/*
    Compile unit: C:\rockband2\band2\src\net_band\EntityUploader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8022CD88 -> 0x80230E98
*/
static class EntityUploader gEntityUploader; // size: 0x48, address: 0x8097CD00
class EntityUploader & TheEntityUploader; // size: 0x4, address: 0x80A4EB28
// Range: 0x8022CD88 -> 0x8022CDEC
void * EntityUploader::EntityUploader(class EntityUploader * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14EntityUploader;
}

// Range: 0x8022CDEC -> 0x8022CE60
void EntityUploader::Init(class EntityUploader * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
}

// Range: 0x8022CE60 -> 0x8022D03C
unsigned char EntityUploader::VerifyCharName(class EntityUploader * const this /* r27 */, const char * charName /* r28 */, class TourSavable * e /* r29 */, class Object * pObjCallback /* r30 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022D03C -> 0x8022D21C
unsigned char EntityUploader::VerifyBandName(class EntityUploader * const this /* r27 */, const char * bandName /* r28 */, class TourSavable * e /* r29 */, class Object * pObjCallback /* r30 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022D21C -> 0x8022D3FC
unsigned char EntityUploader::VerifyBandMotto(class EntityUploader * const this /* r27 */, const char * bandMotto /* r28 */, class TourSavable * e /* r29 */, class Object * pObjCallback /* r30 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022D3FC -> 0x8022D6C4
unsigned char EntityUploader::UpdateChar(class EntityUploader * const this /* r28 */, class TourCharLocal * c /* r29 */, class Object * pObjCallback /* r30 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x30
    int opID; // r0
    class RockCentralOpCompleteMsg msg; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022D6C4 -> 0x8022D988
unsigned char EntityUploader::UpdateBand(class EntityUploader * const this /* r28 */, class TourBandLocal * b /* r29 */, class Object * pObjCallback /* r30 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x30
    int opID; // r0
    class RockCentralOpCompleteMsg msg; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022D988 -> 0x8022DC50
unsigned char EntityUploader::UpdateFromProfile(class EntityUploader * const this /* r28 */, class Profile * pProfile /* r29 */, class Object * pObjCallback /* r30 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x30
    int opCount; // r0
    class RockCentralOpCompleteMsg msg; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022DC50 -> 0x8022DF54
int EntityUploader::BuildStringCheckOp(class DataArray * * uploadOps /* r27 */, const char * checkStr /* r28 */, int opType /* r26 */, class TourSavable * entity /* r29 */) {}

// Range: 0x8022DF54 -> 0x8022E2C0
int EntityUploader::BuildUpdateCharOp(class EntityUploader * const this /* r31 */, class DataArray * * uploadOps /* r28 */, class TourCharLocal * c /* r29 */) {
    // Local variables
    int opID; // r30
}

// Range: 0x8022E2C0 -> 0x8022E608
int EntityUploader::BuildUpdateBandOp(class EntityUploader * const this /* r31 */, class DataArray * * uploadOps /* r28 */, class TourBandLocal * b /* r29 */) {
    // Local variables
    int opID; // r30
}

// Range: 0x8022E608 -> 0x8022ECC0
int EntityUploader::BuildProfileUploadOps(class EntityUploader * const this /* r24 */, class DataArray * * uploadOps /* r25 */, class Profile * pProfile /* r26 */) {
    // Local variables
    class DataArray * newOps; // r29
    int opCount; // r28
    int i; // r27
    int i; // r27
    class TourBandLocal * b; // r31
}

// Range: 0x8022ECC0 -> 0x8022F108
void EntityUploader::RockCentralOpComplete(class EntityUploader * const this /* r26 */, int retCode /* r27 */, int id /* r28 */) {
    // Local variables
    unsigned char allOpsComplete; // r31
    int i; // r30
    unsigned char stringWasAcceptable; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__11TourSavable;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x8022F108 -> 0x8022F43C
void EntityUploader::Poll(class EntityUploader * const this /* r28 */) {
    // Local variables
    class Object * pObjCallback; // r29
    int callType; // r4
    class RockCentralOpCompleteMsg msg; // r1+0x30
    class Object * pObjCallback; // r29
    class RockCentralOpCompleteMsg msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8022F43C -> 0x8022F490
void EntityUploader::MarkUncheckedFlag() {}

// Range: 0x8022F490 -> 0x8022F924
void EntityUploader::ReturnProfileResults(class EntityUploader * const this /* r26 */, class Object * pObjCallback /* r27 */) {
    // Local variables
    unsigned char allSvrDown; // r28
    int i; // r29
    class RockCentralOpCompleteMsg msg; // r1+0x48
    class DataArray * results; // r30
    int retCount; // r29
    int i; // r28
    class RockCentralOpCompleteMsg msg; // r1+0x40

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8022F924 -> 0x8022F9E8
class DataNode EntityUploader::OnVerifyCharName(class EntityUploader * const this /* r28 */, class DataArray * data /* r29 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TourSavable;
}

// Range: 0x8022F9E8 -> 0x8022FAAC
class DataNode EntityUploader::OnVerifyBandName(class EntityUploader * const this /* r28 */, class DataArray * data /* r29 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TourSavable;
}

// Range: 0x8022FAAC -> 0x8022FB70
class DataNode EntityUploader::OnVerifyBandMotto(class EntityUploader * const this /* r28 */, class DataArray * data /* r29 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TourSavable;
}

// Range: 0x8022FB70 -> 0x8022FC28
class DataNode EntityUploader::OnUpdateChar(class EntityUploader * const this /* r29 */, class DataArray * data /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x8022FC28 -> 0x8022FCE0
class DataNode EntityUploader::OnUpdateBand(class EntityUploader * const this /* r29 */, class DataArray * data /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
}

// Range: 0x8022FCE0 -> 0x8022FD98
class DataNode EntityUploader::OnUpdateFromProfile(class EntityUploader * const this /* r29 */, class DataArray * data /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7Profile;
}

// Range: 0x8022FD98 -> 0x8022FE3C
class DataNode EntityUploader::OnRockCentralOpComplete(class EntityUploader * const this /* r28 */, class DataArray * data /* r29 */) {}

// Range: 0x8022FE3C -> 0x802301D0
int EntityUploader::BeginQuazalOps(class EntityUploader * const this /* r28 */, int flags /* r29 */) {
    // Local variables
    int opsStarted; // r31
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x802301D0 -> 0x802301D8
void EntityUploader::RecordSubmissionTime() {}

// Range: 0x802301D8 -> 0x80230250
unsigned char EntityUploader::HasServerTimedOut(class EntityUploader * const this /* r30 */) {
    // Local variables
    struct DateTime now; // r1+0x8
    unsigned int timeDiff; // r4
}

static class Symbol _s; // size: 0x4, address: 0x80A4EB30
static class Symbol _s; // size: 0x4, address: 0x80A4EB38
static class Symbol _s; // size: 0x4, address: 0x80A4EB40
static class Symbol _s; // size: 0x4, address: 0x80A4EB48
static class Symbol _s; // size: 0x4, address: 0x80A4EB50
static class Symbol _s; // size: 0x4, address: 0x80A4EB58
static class Symbol _s; // size: 0x4, address: 0x80A4EB60
// Range: 0x80230250 -> 0x80230E48
class DataNode EntityUploader::Handle(class EntityUploader * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
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

struct {
    // total size: 0x78
} __vt__14EntityUploader; // size: 0x78, address: 0x808B0078
struct {
    // total size: 0x8
} __RTTI__14EntityUploader; // size: 0x8, address: 0x808B0118
// Range: 0x80230E48 -> 0x80230E98
static void __sinit_\EntityUploader_cpp() {
    // References
    // -> class EntityUploader & TheEntityUploader;
    // -> static class EntityUploader gEntityUploader;
}


