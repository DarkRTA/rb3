/*
    Compile unit: C:\rockband2\band2\src\meta\StorePreviewMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80190FAC -> 0x80190FAC
*/
class Symbol t; // size: 0x4, address: 0x80A4CF5C
class StreamPlayer : public Object {
    // total size: 0x38
    float mMasterVol; // offset 0x28, size 0x4
    float mStreamVol; // offset 0x2C, size 0x4
    unsigned char mLoop; // offset 0x30, size 0x1
    unsigned char mStarted; // offset 0x31, size 0x1
    unsigned char mPaused; // offset 0x32, size 0x1
    class Stream * mStream; // offset 0x34, size 0x4
};
class PreviewDownloadCompleteMsg : public Message {
    // total size: 0x8
};
struct {
    // total size: 0xC
} __vt__26PreviewDownloadCompleteMsg; // size: 0xC, address: 0x8089C5E0
struct {
    // total size: 0x8
} __RTTI__26PreviewDownloadCompleteMsg; // size: 0x8, address: 0x8089C618

