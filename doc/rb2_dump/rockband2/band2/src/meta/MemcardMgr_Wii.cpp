/*
    Compile unit: C:\rockband2\band2\src\meta\MemcardMgr_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801F48C8 -> 0x801F6D24
*/
class Symbol t; // size: 0x4, address: 0x80A4E3E4
class MemcardMgr TheMemcardMgr; // size: 0x24C0, address: 0x8097A2E0
static const char * kSaveFilename; // size: 0x4, address: 0x80A46940
static const char * kBanFilename; // size: 0x4, address: 0x80A46944
static int kIcons; // size: 0x4, address: 0x80A46948
static int kGameFSBlocks; // size: 0x4, address: 0x80A4694C
static int kBannerFSBlocks; // size: 0x4, address: 0x80A46950
// Range: 0x801F48C8 -> 0x801F49D4
void * MemcardMgr::MemcardMgr(class MemcardMgr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10MemcardMgr;
    // -> struct [anonymous] __vt__14ThreadCallback;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x801F49D4 -> 0x801F4A5C
void * MemcardMgr::~MemcardMgr(class MemcardMgr * const this /* r29 */) {}

// Range: 0x801F4A5C -> 0x801F4BC0
void MemcardMgr::Init(class MemcardMgr * const this /* r30 */) {
    // Local variables
    char homePath[64]; // r1+0x18

    // References
    // -> static const char * kBanFilename;
    // -> static const char * kSaveFilename;
    // -> class MemcardWii TheMC;
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> class ObjectDir * sMainDir;
}

class SaveLoadProfileCompleteMsg : public Message {
    // total size: 0x8
};
static class SaveLoadProfileCompleteMsg msg; // size: 0x8, address: 0x8097C7B0
// Range: 0x801F4BC0 -> 0x801F4E54
void MemcardMgr::SaveLoadProfileComplete(class MemcardMgr * const this /* r29 */, int playerNum /* r30 */) {
    // Local variables
    enum ProfileSaveState saveState; // r31
    class Profile * profile; // r28

    // References
    // -> struct [anonymous] __vt__26SaveLoadProfileCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SaveLoadProfileCompleteMsg msg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
}

static class SaveLoadAllCompleteMsg msg; // size: 0x8, address: 0x8097C7C8
// Range: 0x801F4E54 -> 0x801F4FD4
void MemcardMgr::SaveLoadAllComplete(class MemcardMgr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__22SaveLoadAllCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SaveLoadAllCompleteMsg msg;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x801F4FD4 -> 0x801F501C
void MemcardMgr::SelectDevice() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801F501C -> 0x801F5024
unsigned char MemcardMgr::IsStorageDeviceValid() {}

// Range: 0x801F5024 -> 0x801F502C
int MemcardMgr::ThreadStart() {}

// Range: 0x801F502C -> 0x801F5030
void MemcardMgr::ThreadDone() {}

// Range: 0x801F5030 -> 0x801F5040
class DataNode MemcardMgr::OnMsg() {}

// Range: 0x801F5040 -> 0x801F5050
class DataNode MemcardMgr::OnMsg() {}

// Range: 0x801F5050 -> 0x801F5054
void MemcardMgr::OnCheckForSaveContainer() {}

static int _x; // size: 0x4, address: 0x80A4E3EC
static int _x; // size: 0x4, address: 0x80A4E3F4
struct NANDFileInfo {
    // total size: 0x8C
    long fileDescriptor; // offset 0x0, size 0x4
    long origFd; // offset 0x4, size 0x4
    char origPath[64]; // offset 0x8, size 0x40
    char tmpPath[64]; // offset 0x48, size 0x40
    unsigned char accType; // offset 0x88, size 0x1
    unsigned char stage; // offset 0x89, size 0x1
    unsigned char mark; // offset 0x8A, size 0x1
};
class BufStreamNAND : public BinStream {
    // total size: 0x100
    char * mBuffer; // offset 0xC, size 0x4
    unsigned char mFail; // offset 0x10, size 0x1
    int mTell; // offset 0x14, size 0x4
    int mSize; // offset 0x18, size 0x4
    int mRunningTell; // offset 0x1C, size 0x4
    int mChunkSize; // offset 0x20, size 0x4
    unsigned char mTellReset; // offset 0x24, size 0x1
    unsigned char mFileOpen; // offset 0x25, size 0x1
    char mFilePath[64]; // offset 0x26, size 0x40
    enum MCResult mResult; // offset 0x68, size 0x4
    struct NANDFileInfo mFileInfo; // offset 0x6C, size 0x8C
    class StreamChecksum * mChecksum; // offset 0xF8, size 0x4
    int mBytesChecksummed; // offset 0xFC, size 0x4
};
// Range: 0x801F5054 -> 0x801F52E0
enum MCResult MemcardMgr::StreamSaveGame(class MemcardMgr * const this /* r29 */) {
    // Local variables
    enum MCResult mcResult; // r31
    int num; // r1+0x18
    int bytes; // r1+0x14
    int largestFast; // r1+0x10
    int largestMain; // r1+0xC
    class BufStreamNAND s; // r1+0x20
    class Profile * profile; // r31

    // References
    // -> class ContentMgr & TheContentMgr;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> static int _x;
    // -> static int _x;
}

// Range: 0x801F52E0 -> 0x801F5580
enum MCResult MemcardMgr::SaveGame(class MemcardMgr * const this /* r26 */) {
    // Local variables
    class MCContainerWii * container; // r31
    enum MCResult mcResult; // r0
    unsigned long fsBlocks; // r30
    unsigned long iNodes; // r29
    unsigned char createBanner; // r28
    unsigned char createSave; // r27

    // References
    // -> static int kGameFSBlocks;
    // -> static int kBannerFSBlocks;
    // -> static int kIcons;
    // -> struct [anonymous] __RTTI__11MCContainer;
    // -> struct [anonymous] __RTTI__14MCContainerWii;
}

// Range: 0x801F5580 -> 0x801F5758
void MemcardMgr::OnSaveGame(class MemcardMgr * const this /* r31 */) {
    // Local variables
    enum MCResult result; // r0

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__11MCResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class SynthWii * TheWiiSynth;
}

static int _x; // size: 0x4, address: 0x80A4E3FC
static int _x; // size: 0x4, address: 0x80A4E404
// Range: 0x801F5758 -> 0x801F59F0
enum MCResult MemcardMgr::StreamLoadGame(class MemcardMgr * const this /* r29 */) {
    // Local variables
    enum MCResult mcResult; // r30
    int num; // r1+0x18
    int bytes; // r1+0x14
    int largestFast; // r1+0x10
    int largestMain; // r1+0xC
    class BufStreamNAND s; // r1+0x20
    int version; // r1+0x8
    class Profile * profile; // r0

    // References
    // -> class ContentMgr & TheContentMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> static int _x;
    // -> static int _x;
}

// Range: 0x801F59F0 -> 0x801F5B4C
enum MCResult MemcardMgr::LoadGame(class MemcardMgr * const this /* r28 */) {
    // Local variables
    enum MCResult mcResult; // r31
    class MCContainerWii * container; // r31
    int spaceNeeded; // r30
    int iNodesNeeded; // r29

    // References
    // -> static int kBannerFSBlocks;
    // -> static int kGameFSBlocks;
    // -> struct [anonymous] __RTTI__11MCContainer;
    // -> struct [anonymous] __RTTI__14MCContainerWii;
}

// Range: 0x801F5B4C -> 0x801F5D20
void MemcardMgr::OnLoadGame(class MemcardMgr * const this /* r31 */) {
    // Local variables
    enum MCResult result; // r0

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__11MCResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class SynthWii * TheWiiSynth;
}

// Range: 0x801F5D20 -> 0x801F5D24
void MemcardMgr::OnDeleteSaves() {}

// Range: 0x801F5D24 -> 0x801F5D8C
unsigned char MemcardMgr::DoesSaveFileExist(class MemcardMgr * const this /* r31 */) {
    // Local variables
    class MCContainerWii * pContainer; // r0
    enum MCResult result; // r0

    // References
    // -> struct [anonymous] __RTTI__11MCContainer;
    // -> struct [anonymous] __RTTI__14MCContainerWii;
}

// Range: 0x801F5D8C -> 0x801F5DD8
int MemcardMgr::GetFreeUserBlocks() {
    // Local variables
    class MCContainerWii * pContainer; // r0
    int freeBlocks; // r0

    // References
    // -> struct [anonymous] __RTTI__11MCContainer;
    // -> struct [anonymous] __RTTI__14MCContainerWii;
}

// Range: 0x801F5DD8 -> 0x801F5F50
void * SaveLoadPollThread() {
    // Local variables
    class UIScreen * savescreen; // r28

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x801F5F50 -> 0x801F5FB8
void MemcardMgr::StartPollingThread(class MemcardMgr * const this /* r31 */) {
    // References
    // -> unsigned char gSystemLocked;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x801F5FB8 -> 0x801F5FF0
void MemcardMgr::StopPollingThread() {
    // References
    // -> class WiiRnd TheWiiRnd;
    // -> unsigned char gSystemLocked;
}

static class Symbol _s; // size: 0x4, address: 0x80A4E40C
static class Symbol _s; // size: 0x4, address: 0x80A4E414
static class Symbol _s; // size: 0x4, address: 0x80A4E41C
static class Symbol _s; // size: 0x4, address: 0x80A4E424
static class Symbol _s; // size: 0x4, address: 0x80A4E42C
static class Symbol _s; // size: 0x4, address: 0x80A4E434
static class Symbol _s; // size: 0x4, address: 0x80A4E43C
// Range: 0x801F5FF0 -> 0x801F6C6C
class DataNode MemcardMgr::Handle(class MemcardMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__17StorageChangedMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__12UIChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
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
    // total size: 0x88
} __vt__10MemcardMgr; // size: 0x88, address: 0x808A8538
struct {
    // total size: 0x8
} __RTTI__10MemcardMgr; // size: 0x8, address: 0x808A85F0
struct {
    // total size: 0xC
} __vt__26SaveLoadProfileCompleteMsg; // size: 0xC, address: 0x808A8630
struct {
    // total size: 0x8
} __RTTI__26SaveLoadProfileCompleteMsg; // size: 0x8, address: 0x808A8668
struct {
    // total size: 0x14
} __vt__14ThreadCallback; // size: 0x14, address: 0x808A8670
struct {
    // total size: 0x8
} __RTTI__14ThreadCallback; // size: 0x8, address: 0x808A8698
struct {
    // total size: 0x8
} __RTTI__14MCContainerWii; // size: 0x8, address: 0x808A8750
struct {
    // total size: 0x8
} __RTTI__11MCContainer; // size: 0x8, address: 0x808A8768
// Range: 0x801F6C6C -> 0x801F6CBC
static void __sinit_\MemcardMgr_Wii_cpp() {
    // References
    // -> class MemcardMgr TheMemcardMgr;
}

class Memcard : public Object {
    // total size: 0x28
};
class MemcardWii : public Memcard {
    // total size: 0x2C
    unsigned char mIsMtap0; // offset 0x28, size 0x1
    unsigned char mIsMtap1; // offset 0x29, size 0x1
};

