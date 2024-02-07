/*
    Compile unit: C:\rockband2\system\src\movie\Movie_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803BEB5C -> 0x803BF4A8
*/
struct BINKRECT {
    // total size: 0x10
    int Left; // offset 0x0, size 0x4
    int Top; // offset 0x4, size 0x4
    int Width; // offset 0x8, size 0x4
    int Height; // offset 0xC, size 0x4
};
struct BINKPLANE {
    // total size: 0xC
    int Allocate; // offset 0x0, size 0x4
    void * Buffer; // offset 0x4, size 0x4
    unsigned int BufferPitch; // offset 0x8, size 0x4
};
struct BINKFRAMEPLANESET {
    // total size: 0x30
    struct BINKPLANE YPlane; // offset 0x0, size 0xC
    struct BINKPLANE cRPlane; // offset 0xC, size 0xC
    struct BINKPLANE cBPlane; // offset 0x18, size 0xC
    struct BINKPLANE APlane; // offset 0x24, size 0xC
};
struct BINKFRAMEBUFFERS {
    // total size: 0x78
    int TotalFrames; // offset 0x0, size 0x4
    unsigned int YABufferWidth; // offset 0x4, size 0x4
    unsigned int YABufferHeight; // offset 0x8, size 0x4
    unsigned int cRcBBufferWidth; // offset 0xC, size 0x4
    unsigned int cRcBBufferHeight; // offset 0x10, size 0x4
    unsigned int FrameNum; // offset 0x14, size 0x4
    struct BINKFRAMEPLANESET Frames[2]; // offset 0x18, size 0x60
};
struct BINKSND {
    // total size: 0x180
    unsigned char * sndwritepos; // offset 0x0, size 0x4
    unsigned int audiodecompsize; // offset 0x4, size 0x4
    unsigned int sndbufsize; // offset 0x8, size 0x4
    unsigned char * sndbuf; // offset 0xC, size 0x4
    unsigned char * sndend; // offset 0x10, size 0x4
    unsigned int sndcomp; // offset 0x14, size 0x4
    unsigned char * sndreadpos; // offset 0x18, size 0x4
    unsigned int orig_freq; // offset 0x1C, size 0x4
    unsigned int freq; // offset 0x20, size 0x4
    int bits; // offset 0x24, size 0x4
    int chans; // offset 0x28, size 0x4
    int BestSizeIn16; // offset 0x2C, size 0x4
    unsigned int BestSizeMask; // offset 0x30, size 0x4
    int OnOff; // offset 0x34, size 0x4
    unsigned int Latency; // offset 0x38, size 0x4
    unsigned int VideoScale; // offset 0x3C, size 0x4
    unsigned int sndendframe; // offset 0x40, size 0x4
    unsigned int sndpad; // offset 0x44, size 0x4
    int sndprime; // offset 0x48, size 0x4
    int NoThreadService; // offset 0x4C, size 0x4
    unsigned int SoundDroppedOut; // offset 0x50, size 0x4
    unsigned int sndconvert8; // offset 0x54, size 0x4
    unsigned char snddata[256]; // offset 0x58, size 0x100
    int (* Ready)(struct BINKSND *); // offset 0x158, size 0x4
    int (* Lock)(struct BINKSND *, unsigned char * *, unsigned int *); // offset 0x15C, size 0x4
    int (* Unlock)(struct BINKSND *, unsigned int); // offset 0x160, size 0x4
    void (* Volume)(struct BINKSND *, int); // offset 0x164, size 0x4
    void (* Pan)(struct BINKSND *, int); // offset 0x168, size 0x4
    int (* Pause)(struct BINKSND *, int); // offset 0x16C, size 0x4
    int (* SetOnOff)(struct BINKSND *, int); // offset 0x170, size 0x4
    void (* Close)(struct BINKSND *); // offset 0x174, size 0x4
    void (* MixBins)(struct BINKSND *, unsigned int *, unsigned int); // offset 0x178, size 0x4
    void (* MixBinVols)(struct BINKSND *, unsigned int *, int *, unsigned int); // offset 0x17C, size 0x4
};
struct BUNDLEPOINTERS {
    // total size: 0x24
    void * typeptr; // offset 0x0, size 0x4
    void * type16ptr; // offset 0x4, size 0x4
    void * colorptr; // offset 0x8, size 0x4
    void * bits2ptr; // offset 0xC, size 0x4
    void * motionXptr; // offset 0x10, size 0x4
    void * motionYptr; // offset 0x14, size 0x4
    void * dctptr; // offset 0x18, size 0x4
    void * mdctptr; // offset 0x1C, size 0x4
    void * patptr; // offset 0x20, size 0x4
};
struct BINKIO {
    // total size: 0x144
    unsigned int (* ReadHeader)(struct BINKIO *, int, void *, unsigned int); // offset 0x0, size 0x4
    unsigned int (* ReadFrame)(struct BINKIO *, unsigned int, int, void *, unsigned int); // offset 0x4, size 0x4
    unsigned int (* GetBufferSize)(struct BINKIO *, unsigned int); // offset 0x8, size 0x4
    void (* SetInfo)(struct BINKIO *, void *, unsigned int, unsigned int, unsigned int); // offset 0xC, size 0x4
    unsigned int (* Idle)(struct BINKIO *); // offset 0x10, size 0x4
    void (* Close)(struct BINKIO *); // offset 0x14, size 0x4
    int (* BGControl)(struct BINKIO *, unsigned int); // offset 0x18, size 0x4
    struct BINK * bink; // offset 0x1C, size 0x4
    unsigned int ReadError; // offset 0x20, size 0x4
    unsigned int DoingARead; // offset 0x24, size 0x4
    unsigned int BytesRead; // offset 0x28, size 0x4
    unsigned int Working; // offset 0x2C, size 0x4
    unsigned int TotalTime; // offset 0x30, size 0x4
    unsigned int ForegroundTime; // offset 0x34, size 0x4
    unsigned int IdleTime; // offset 0x38, size 0x4
    unsigned int ThreadTime; // offset 0x3C, size 0x4
    unsigned int BufSize; // offset 0x40, size 0x4
    unsigned int BufHighUsed; // offset 0x44, size 0x4
    unsigned int CurBufSize; // offset 0x48, size 0x4
    unsigned int CurBufUsed; // offset 0x4C, size 0x4
    unsigned int Suspended; // offset 0x50, size 0x4
    unsigned char iodata[160]; // offset 0x54, size 0xA0
    void (* suspend_callback)(struct BINKIO *); // offset 0xF4, size 0x4
    int (* try_suspend_callback)(struct BINKIO *); // offset 0xF8, size 0x4
    void (* resume_callback)(struct BINKIO *); // offset 0xFC, size 0x4
    void (* idle_on_callback)(struct BINKIO *); // offset 0x100, size 0x4
    unsigned int callback_control[16]; // offset 0x104, size 0x40
};
struct BINK {
    // total size: 0x39C
    unsigned int Width; // offset 0x0, size 0x4
    unsigned int Height; // offset 0x4, size 0x4
    unsigned int Frames; // offset 0x8, size 0x4
    unsigned int FrameNum; // offset 0xC, size 0x4
    unsigned int LastFrameNum; // offset 0x10, size 0x4
    unsigned int FrameRate; // offset 0x14, size 0x4
    unsigned int FrameRateDiv; // offset 0x18, size 0x4
    unsigned int ReadError; // offset 0x1C, size 0x4
    unsigned int OpenFlags; // offset 0x20, size 0x4
    unsigned int BinkType; // offset 0x24, size 0x4
    unsigned int Size; // offset 0x28, size 0x4
    unsigned int FrameSize; // offset 0x2C, size 0x4
    unsigned int SndSize; // offset 0x30, size 0x4
    unsigned int FrameChangePercent; // offset 0x34, size 0x4
    struct BINKRECT FrameRects[8]; // offset 0x38, size 0x80
    int NumRects; // offset 0xB8, size 0x4
    struct BINKFRAMEBUFFERS * FrameBuffers; // offset 0xBC, size 0x4
    void * MaskPlane; // offset 0xC0, size 0x4
    unsigned int MaskPitch; // offset 0xC4, size 0x4
    unsigned int MaskLength; // offset 0xC8, size 0x4
    void * AsyncMaskPlane; // offset 0xCC, size 0x4
    void * InUseMaskPlane; // offset 0xD0, size 0x4
    void * LastMaskPlane; // offset 0xD4, size 0x4
    unsigned int LargestFrameSize; // offset 0xD8, size 0x4
    unsigned int InternalFrames; // offset 0xDC, size 0x4
    int NumTracks; // offset 0xE0, size 0x4
    unsigned int Highest1SecRate; // offset 0xE4, size 0x4
    unsigned int Highest1SecFrame; // offset 0xE8, size 0x4
    int Paused; // offset 0xEC, size 0x4
    int async_in_progress[2]; // offset 0xF0, size 0x8
    unsigned int soundon; // offset 0xF8, size 0x4
    unsigned int videoon; // offset 0xFC, size 0x4
    void * compframe; // offset 0x100, size 0x4
    unsigned int compframesize; // offset 0x104, size 0x4
    unsigned int compframeoffset; // offset 0x108, size 0x4
    unsigned int compframekey; // offset 0x10C, size 0x4
    unsigned int skippedlastblit; // offset 0x110, size 0x4
    unsigned int playingtracks; // offset 0x114, size 0x4
    struct BINKSND * bsnd; // offset 0x118, size 0x4
    int * trackindexes; // offset 0x11C, size 0x4
    struct BUNDLEPOINTERS bunp; // offset 0x120, size 0x24
    unsigned int changepercent; // offset 0x144, size 0x4
    void * preloadptr; // offset 0x148, size 0x4
    unsigned int * frameoffsets; // offset 0x14C, size 0x4
    struct BINKIO bio; // offset 0x150, size 0x144
    unsigned char * ioptr; // offset 0x294, size 0x4
    unsigned int iosize; // offset 0x298, size 0x4
    unsigned int decompwidth; // offset 0x29C, size 0x4
    unsigned int decompheight; // offset 0x2A0, size 0x4
    unsigned int * tracksizes; // offset 0x2A4, size 0x4
    unsigned int * tracktypes; // offset 0x2A8, size 0x4
    int * trackIDs; // offset 0x2AC, size 0x4
    unsigned int numrects; // offset 0x2B0, size 0x4
    unsigned int playedframes; // offset 0x2B4, size 0x4
    unsigned int firstframetime; // offset 0x2B8, size 0x4
    unsigned int startblittime; // offset 0x2BC, size 0x4
    unsigned int startsynctime; // offset 0x2C0, size 0x4
    unsigned int startsyncframe; // offset 0x2C4, size 0x4
    unsigned int twoframestime; // offset 0x2C8, size 0x4
    unsigned int slowestframetime; // offset 0x2CC, size 0x4
    unsigned int slowestframe; // offset 0x2D0, size 0x4
    unsigned int slowest2frametime; // offset 0x2D4, size 0x4
    unsigned int slowest2frame; // offset 0x2D8, size 0x4
    unsigned int totalmem; // offset 0x2DC, size 0x4
    unsigned int timevdecomp; // offset 0x2E0, size 0x4
    unsigned int timeadecomp; // offset 0x2E4, size 0x4
    unsigned int timeblit; // offset 0x2E8, size 0x4
    unsigned int timeopen; // offset 0x2EC, size 0x4
    unsigned int fileframerate; // offset 0x2F0, size 0x4
    unsigned int fileframeratediv; // offset 0x2F4, size 0x4
    unsigned int runtimeframes; // offset 0x2F8, size 0x4
    int rtindex; // offset 0x2FC, size 0x4
    unsigned int * rtframetimes; // offset 0x300, size 0x4
    unsigned int * rtadecomptimes; // offset 0x304, size 0x4
    unsigned int * rtvdecomptimes; // offset 0x308, size 0x4
    unsigned int * rtblittimes; // offset 0x30C, size 0x4
    unsigned int * rtreadtimes; // offset 0x310, size 0x4
    unsigned int * rtidlereadtimes; // offset 0x314, size 0x4
    unsigned int * rtthreadreadtimes; // offset 0x318, size 0x4
    unsigned int lastblitflags; // offset 0x31C, size 0x4
    unsigned int lastdecompframe; // offset 0x320, size 0x4
    unsigned int lastfinisheddoframe; // offset 0x324, size 0x4
    unsigned int lastresynctime; // offset 0x328, size 0x4
    unsigned int doresync; // offset 0x32C, size 0x4
    unsigned int soundskips; // offset 0x330, size 0x4
    unsigned int skipped_status_this_frame; // offset 0x334, size 0x4
    unsigned int very_delayed; // offset 0x338, size 0x4
    unsigned int skippedblits; // offset 0x33C, size 0x4
    unsigned int skipped_in_a_row; // offset 0x340, size 0x4
    unsigned int paused_sync_diff; // offset 0x344, size 0x4
    unsigned int last_time_almost_empty; // offset 0x348, size 0x4
    unsigned int last_read_count; // offset 0x34C, size 0x4
    unsigned int last_sound_count; // offset 0x350, size 0x4
    unsigned int snd_callback_buffer[16]; // offset 0x354, size 0x40
    int allkeys; // offset 0x394, size 0x4
    struct BINKFRAMEBUFFERS * allocatedframebuffers; // offset 0x398, size 0x4
};
struct BINKFRAMETEXTURES {
    // total size: 0x80
    struct _GXTexObj Ytexture; // offset 0x0, size 0x20
    struct _GXTexObj cRtexture; // offset 0x20, size 0x20
    struct _GXTexObj cBtexture; // offset 0x40, size 0x20
    struct _GXTexObj Atexture; // offset 0x60, size 0x20
};
struct BINKTEXTURESET {
    // total size: 0x1D8
    struct BINKFRAMEBUFFERS bink_buffers; // offset 0x0, size 0x78
    struct BINKFRAMETEXTURES textures[2]; // offset 0x78, size 0x100
    void * base_ptr; // offset 0x178, size 0x4
    unsigned int framesize; // offset 0x17C, size 0x4
    unsigned int YAdeswizzle_width; // offset 0x180, size 0x4
    unsigned int YAdeswizzle_height; // offset 0x184, size 0x4
    unsigned int cRcBdeswizzle_width; // offset 0x188, size 0x4
    unsigned int cRcBdeswizzle_height; // offset 0x18C, size 0x4
    struct _GXTexObj YAdeswizzle; // offset 0x190, size 0x20
    struct _GXTexObj cRcBdeswizzle; // offset 0x1B0, size 0x20
    int drawing[2]; // offset 0x1D0, size 0x8
};
struct Impl {
    // total size: 0x208
    class FileLoader * mLoader; // offset 0x0, size 0x4
    class String mPath; // offset 0x4, size 0xC
    struct BINK * mBink; // offset 0x10, size 0x4
    struct BINKTEXTURESET texture_set; // offset 0x14, size 0x1D8
    char * mPreload; // offset 0x1EC, size 0x4
    unsigned char mLoop; // offset 0x1F0, size 0x1
    unsigned char mMute; // offset 0x1F1, size 0x1
    unsigned char mFillWidth; // offset 0x1F2, size 0x1
    unsigned char mAnamorphic; // offset 0x1F3, size 0x1
    class Rect mRect; // offset 0x1F4, size 0x10
    class RndTex * mBufferTex; // offset 0x204, size 0x4
};
// Range: 0x803BEB5C -> 0x803BEBAC
void * Impl::Impl(struct Impl * const this /* r30 */) {}

// Range: 0x803BEBAC -> 0x803BEC00
unsigned char Impl::Ready() {}

struct BINKSUMMARY {
    // total size: 0x7C
    unsigned int Width; // offset 0x0, size 0x4
    unsigned int Height; // offset 0x4, size 0x4
    unsigned int TotalTime; // offset 0x8, size 0x4
    unsigned int FileFrameRate; // offset 0xC, size 0x4
    unsigned int FileFrameRateDiv; // offset 0x10, size 0x4
    unsigned int FrameRate; // offset 0x14, size 0x4
    unsigned int FrameRateDiv; // offset 0x18, size 0x4
    unsigned int TotalOpenTime; // offset 0x1C, size 0x4
    unsigned int TotalFrames; // offset 0x20, size 0x4
    unsigned int TotalPlayedFrames; // offset 0x24, size 0x4
    unsigned int SkippedFrames; // offset 0x28, size 0x4
    unsigned int SkippedBlits; // offset 0x2C, size 0x4
    unsigned int SoundSkips; // offset 0x30, size 0x4
    unsigned int TotalBlitTime; // offset 0x34, size 0x4
    unsigned int TotalReadTime; // offset 0x38, size 0x4
    unsigned int TotalVideoDecompTime; // offset 0x3C, size 0x4
    unsigned int TotalAudioDecompTime; // offset 0x40, size 0x4
    unsigned int TotalIdleReadTime; // offset 0x44, size 0x4
    unsigned int TotalBackReadTime; // offset 0x48, size 0x4
    unsigned int TotalReadSpeed; // offset 0x4C, size 0x4
    unsigned int SlowestFrameTime; // offset 0x50, size 0x4
    unsigned int Slowest2FrameTime; // offset 0x54, size 0x4
    unsigned int SlowestFrameNum; // offset 0x58, size 0x4
    unsigned int Slowest2FrameNum; // offset 0x5C, size 0x4
    unsigned int AverageDataRate; // offset 0x60, size 0x4
    unsigned int AverageFrameSize; // offset 0x64, size 0x4
    unsigned int HighestMemAmount; // offset 0x68, size 0x4
    unsigned int TotalIOMemory; // offset 0x6C, size 0x4
    unsigned int HighestIOUsed; // offset 0x70, size 0x4
    unsigned int Highest1SecRate; // offset 0x74, size 0x4
    unsigned int Highest1SecFrame; // offset 0x78, size 0x4
};
// Range: 0x803BEC00 -> 0x803BED94
unsigned char Impl::Poll(struct Impl * const this /* r30 */) {
    // Local variables
    unsigned char decode; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BED94 -> 0x803BEDD8
void Impl::Draw(struct Impl * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x803BEDD8 -> 0x803BEE50
void Impl::CheckReadError() {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x803BEE50 -> 0x803BEEA0
void Impl::AllocFrames(struct Impl * const this /* r31 */) {}

// Range: 0x803BEEA0 -> 0x803BEEE0
void Impl::FreeFrames(struct Impl * const this /* r31 */) {}

class WiiOrthoProj {
    // total size: 0x1C
    float mSavedProjection[7]; // offset 0x0, size 0x1C
};
// Range: 0x803BEEE0 -> 0x803BF014
void Impl::DrawBinkTexture(struct Impl * const this /* r30 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x8

    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x803BF014 -> 0x803BF090
void Impl::DrawNativeRes(struct Impl * const this /* r31 */) {
    // Local variables
    class WiiOrthoProj _ortho; // r1+0x8
}

// Range: 0x803BF090 -> 0x803BF110
void Movie::Init() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
}

// Range: 0x803BF110 -> 0x803BF114
void Movie::Terminate() {}

static unsigned char initialized; // size: 0x1, address: 0x80A51768
// Range: 0x803BF114 -> 0x803BF1A4
void * Movie::Movie(class Movie * const this /* r31 */) {
    // References
    // -> static unsigned char initialized;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BF1A4 -> 0x803BF220
void * Movie::~Movie(class Movie * const this /* r29 */) {}

// Range: 0x803BF220 -> 0x803BF228
unsigned char Movie::Ready() {}

// Range: 0x803BF228 -> 0x803BF230
unsigned char Movie::Begin() {}

static class Timer * _t; // size: 0x4, address: 0x80A5176C
// Range: 0x803BF230 -> 0x803BF2FC
unsigned char Movie::Poll(class Movie * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

static class Timer * _t; // size: 0x4, address: 0x80A51774
// Range: 0x803BF2FC -> 0x803BF3C8
void Movie::Draw(class Movie * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

// Range: 0x803BF3C8 -> 0x803BF3D0
void Movie::End() {}

static class Timer * _t; // size: 0x4, address: 0x80A5177C
// Range: 0x803BF3D0 -> 0x803BF49C
void Movie::DrawNativeRes(class Movie * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

// Range: 0x803BF49C -> 0x803BF4A8
void Movie::SetAnamorphic() {}


