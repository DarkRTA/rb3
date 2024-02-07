/*
    Compile unit: C:\rockband2\system\src\synth\VorbisReader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805983D0 -> 0x8059A290
*/
static int gCipher; // size: 0x4, address: 0x80A47778
static int gKeySize; // size: 0x4, address: 0x80A4777C
static unsigned char gRB1Key[16]; // size: 0x10, address: 0x80920DF8
static unsigned char gKey[256]; // size: 0x100, address: 0x80983530
struct ogg_sync_state {
    // total size: 0x1C
    unsigned char * data; // offset 0x0, size 0x4
    int storage; // offset 0x4, size 0x4
    int fill; // offset 0x8, size 0x4
    int returned; // offset 0xC, size 0x4
    int unsynced; // offset 0x10, size 0x4
    int headerbytes; // offset 0x14, size 0x4
    int bodybytes; // offset 0x18, size 0x4
};
struct ogg_stream_state {
    // total size: 0x168
    unsigned char * body_data; // offset 0x0, size 0x4
    long body_storage; // offset 0x4, size 0x4
    long body_fill; // offset 0x8, size 0x4
    long body_returned; // offset 0xC, size 0x4
    int * lacing_vals; // offset 0x10, size 0x4
    long long * granule_vals; // offset 0x14, size 0x4
    long lacing_storage; // offset 0x18, size 0x4
    long lacing_fill; // offset 0x1C, size 0x4
    long lacing_packet; // offset 0x20, size 0x4
    long lacing_returned; // offset 0x24, size 0x4
    unsigned char header[282]; // offset 0x28, size 0x11A
    int header_fill; // offset 0x144, size 0x4
    int e_o_s; // offset 0x148, size 0x4
    int b_o_s; // offset 0x14C, size 0x4
    long serialno; // offset 0x150, size 0x4
    long pageno; // offset 0x154, size 0x4
    long long packetno; // offset 0x158, size 0x8
    long long granulepos; // offset 0x160, size 0x8
};
struct vorbis_info {
    // total size: 0x20
    int version; // offset 0x0, size 0x4
    int channels; // offset 0x4, size 0x4
    long rate; // offset 0x8, size 0x4
    long bitrate_upper; // offset 0xC, size 0x4
    long bitrate_nominal; // offset 0x10, size 0x4
    long bitrate_lower; // offset 0x14, size 0x4
    long bitrate_window; // offset 0x18, size 0x4
    void * codec_setup; // offset 0x1C, size 0x4
};
struct vorbis_comment {
    // total size: 0x10
    char * * user_comments; // offset 0x0, size 0x4
    int * comment_lengths; // offset 0x4, size 0x4
    int comments; // offset 0x8, size 0x4
    char * vendor; // offset 0xC, size 0x4
};
struct vorbis_dsp_state {
    // total size: 0x70
    int analysisp; // offset 0x0, size 0x4
    struct vorbis_info * vi; // offset 0x4, size 0x4
    float * * pcm; // offset 0x8, size 0x4
    float * * pcmret; // offset 0xC, size 0x4
    int pcm_storage; // offset 0x10, size 0x4
    int pcm_current; // offset 0x14, size 0x4
    int pcm_returned; // offset 0x18, size 0x4
    int preextrapolate; // offset 0x1C, size 0x4
    int eofflag; // offset 0x20, size 0x4
    long lW; // offset 0x24, size 0x4
    long W; // offset 0x28, size 0x4
    long nW; // offset 0x2C, size 0x4
    long centerW; // offset 0x30, size 0x4
    long long granulepos; // offset 0x38, size 0x8
    long long sequence; // offset 0x40, size 0x8
    long long glue_bits; // offset 0x48, size 0x8
    long long time_bits; // offset 0x50, size 0x8
    long long floor_bits; // offset 0x58, size 0x8
    long long res_bits; // offset 0x60, size 0x8
    void * backend_state; // offset 0x68, size 0x4
};
struct oggpack_buffer {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
};
struct alloc_chain {
    // total size: 0x8
    void * ptr; // offset 0x0, size 0x4
    struct alloc_chain * next; // offset 0x4, size 0x4
};
enum /* @enum$6162VorbisReader_cpp */ {
    vss_init = 0,
    vss_decode = 1,
    vss_mdct = 2,
};
struct vorbis_block {
    // total size: 0x70
    float * * pcm; // offset 0x0, size 0x4
    struct oggpack_buffer opb; // offset 0x4, size 0x14
    long lW; // offset 0x18, size 0x4
    long W; // offset 0x1C, size 0x4
    long nW; // offset 0x20, size 0x4
    int pcmend; // offset 0x24, size 0x4
    int mode; // offset 0x28, size 0x4
    int eofflag; // offset 0x2C, size 0x4
    long long granulepos; // offset 0x30, size 0x8
    long long sequence; // offset 0x38, size 0x8
    struct vorbis_dsp_state * vd; // offset 0x40, size 0x4
    void * localstore; // offset 0x44, size 0x4
    long localtop; // offset 0x48, size 0x4
    long localalloc; // offset 0x4C, size 0x4
    long totaluse; // offset 0x50, size 0x4
    struct alloc_chain * reap; // offset 0x54, size 0x4
    long glue_bits; // offset 0x58, size 0x4
    long time_bits; // offset 0x5C, size 0x4
    long floor_bits; // offset 0x60, size 0x4
    long res_bits; // offset 0x64, size 0x4
    void * internal; // offset 0x68, size 0x4
    enum /* @enum$6162VorbisReader_cpp */ {
        vss_init = 0,
        vss_decode = 1,
        vss_mdct = 2,
    } synthesis_state; // offset 0x6C, size 0x4
};
enum DecodeStatus {
    kDone = 0,
    kPacketReady = 1,
    kPacketDecoded = 2,
};
class VorbisReader : public StreamReader, public CriticalSection {
    // total size: 0x110
protected:
    int mNumChannels; // offset 0x20, size 0x4
    int mSampleRate; // offset 0x24, size 0x4
private:
    class File * mFile; // offset 0x28, size 0x4
    int mHeadersRead; // offset 0x2C, size 0x4
    unsigned char * mReadBuffer; // offset 0x30, size 0x4
    unsigned char mEnableReads; // offset 0x34, size 0x1
    int mDecryptBytes; // offset 0x38, size 0x4
    unsigned char mNeedInitDecoder; // offset 0x3C, size 0x1
    unsigned char mDone; // offset 0x3D, size 0x1
    float mStartMs; // offset 0x40, size 0x4
    class StandardStream * mStream; // offset 0x44, size 0x4
    struct ogg_sync_state * mOggSync; // offset 0x48, size 0x4
    struct ogg_stream_state * mOggStream; // offset 0x4C, size 0x4
    struct vorbis_info * mVorbisInfo; // offset 0x50, size 0x4
    struct vorbis_comment * mVorbisComment; // offset 0x54, size 0x4
    struct vorbis_dsp_state * mVorbisDsp; // offset 0x58, size 0x4
    struct vorbis_block * mVorbisBlock; // offset 0x5C, size 0x4
    long mMagicA; // offset 0x60, size 0x4
    long mMagicB; // offset 0x64, size 0x4
    long mKeyIndex; // offset 0x68, size 0x4
    long mMagicHashA; // offset 0x6C, size 0x4
    long mMagicHashB; // offset 0x70, size 0x4
    struct ogg_packet mPendingPacket; // offset 0x78, size 0x20
    unsigned char mDecodePending; // offset 0x98, size 0x1
    int mSeekTarget; // offset 0x9C, size 0x4
    int mSamplesToSkip; // offset 0xA0, size 0x4
    class OggMap mMap; // offset 0xA4, size 0x14
    int mHdrSize; // offset 0xB8, size 0x4
    char * mHdrBuf; // offset 0xBC, size 0x4
    struct Symmetric_CTR * mCtrState; // offset 0xC0, size 0x4
    unsigned char mNonce[16]; // offset 0xC4, size 0x10
    unsigned char mKeyMask[16]; // offset 0xD4, size 0x10
    unsigned char mAllowDecode; // offset 0xE4, size 0x1
    unsigned char mEof; // offset 0xE5, size 0x1
    unsigned char mFail; // offset 0xE6, size 0x1
    class vector mThreadBuffers; // offset 0xE8, size 0xC
    long long mThreadBufferStart; // offset 0xF8, size 0x8
    int mThreadBufferConsumed; // offset 0x100, size 0x4
    enum DecodeStatus mDecodeStatus; // offset 0x104, size 0x4
    unsigned char mDecodeDone; // offset 0x108, size 0x1
};
// Range: 0x805983D0 -> 0x80598658
void VorbisReader::setupCypher(class VorbisReader * const this /* r30 */) {
    // Local variables
    char script[256]; // r1+0x108
    unsigned char masterKey[256]; // r1+0x8
    class DataArray * randomGen; // r29
    unsigned long masher; // r0
    char functionName; // r5
    class DataArray * masterKeyGen; // r28
    int ix; // r6
    int ret; // r0
    class DataArray * magicGenA; // r28
    class DataArray * magicGenB; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gKeySize;
    // -> static int gCipher;
    // -> class Synth * TheSynth;
    // -> static unsigned char gKey[256];
}

// Range: 0x80598658 -> 0x805987E0
void * VorbisReader::VorbisReader(class VorbisReader * const this /* r27 */, class File * vorbisFile /* r31 */, unsigned char expectMap /* r28 */, class StandardStream * s /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12VorbisReader;
    // -> struct [anonymous] __vt__12StreamReader;
}

class StlNodeAlloc {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    signed short * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    signed short * _M_start; // offset 0x0, size 0x4
    signed short * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class vector * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class vector * _M_start; // offset 0x0, size 0x4
    class vector * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x805987E0 -> 0x805989E4
void * VorbisReader::~VorbisReader(class VorbisReader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12VorbisReader;
}

static class Timer * _t; // size: 0x4, address: 0x80A54848
// Range: 0x805989E4 -> 0x80598EE0
void VorbisReader::Poll(class VorbisReader * const this /* r31 */, float until /* f31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    class Timer t; // r1+0x10

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Timer * _t;
}

class CritSecTracker {
    // total size: 0x4
    class CriticalSection * mCritSec; // offset 0x0, size 0x4
};
// Range: 0x80598EE0 -> 0x80598FF4
void VorbisReader::Seek(class VorbisReader * const this /* r29 */, int sample /* r30 */) {
    // Local variables
    class CritSecTracker __cst; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Timer * _t; // size: 0x4, address: 0x80A54850
static class Timer * _t; // size: 0x4, address: 0x80A54858
// Range: 0x80598FF4 -> 0x80599280
unsigned char VorbisReader::DoFileRead(class VorbisReader * const this /* r30 */) {
    // Local variables
    unsigned char ret; // r29
    int bytes; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

// Range: 0x80599280 -> 0x805993F8
void VorbisReader::Decrypt(class VorbisReader * const this /* r26 */, unsigned char * data /* r27 */, int bytes /* r28 */) {
    // Local variables
    unsigned char tmp[1024]; // r1+0x410
    int pos; // r30
    int act; // r29
    unsigned char align[1024]; // r1+0x10
    int ret; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class DebugWarner _dw; // size: 0x100, address: 0x80983630
// Range: 0x805993F8 -> 0x80599864
unsigned char VorbisReader::CheckHmxHeader(class VorbisReader * const this /* r30 */) {
    // Local variables
    int bytes; // r1+0xC
    class BufStream bs; // r1+0x38
    int version; // r1+0x8
    unsigned char rawKeymask[16]; // r1+0x28
    int keyIndex; // r28
    int ret; // r0

    // References
    // -> static class DebugWarner _dw;
    // -> static int gKeySize;
    // -> static unsigned char gRB1Key[16];
    // -> static int gCipher;
    // -> struct _cipher_descriptor rijndael_desc;
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct ogg_page {
    // total size: 0x10
    unsigned char * header; // offset 0x0, size 0x4
    long header_len; // offset 0x4, size 0x4
    unsigned char * body; // offset 0x8, size 0x4
    long body_len; // offset 0xC, size 0x4
};
struct ogg_packet {
    // total size: 0x20
    unsigned char * packet; // offset 0x0, size 0x4
    long bytes; // offset 0x4, size 0x4
    long b_o_s; // offset 0x8, size 0x4
    long e_o_s; // offset 0xC, size 0x4
    long long granulepos; // offset 0x10, size 0x8
    long long packetno; // offset 0x18, size 0x8
};
// Range: 0x80599864 -> 0x805999C0
unsigned char VorbisReader::TryReadHeader(class VorbisReader * const this /* r29 */) {
    // Local variables
    struct ogg_page pg; // r1+0x8
    int result; // r30
    struct ogg_packet pk; // r1+0x18
    int result; // r5

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805999C0 -> 0x80599AA0
void VorbisReader::InitDecoder(class VorbisReader * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80599AA0 -> 0x80599B6C
unsigned char VorbisReader::TryConsumeData(class VorbisReader * const this /* r29 */) {
    // Local variables
    float * * pcm; // r1+0x8
    int consumed; // r31
    int samples; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80599B6C -> 0x80599D20
unsigned char VorbisReader::TryDecode(class VorbisReader * const this /* r30 */) {
    // Local variables
    int result; // r5

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80599D20 -> 0x80599E2C
unsigned char VorbisReader::TryReadPacket(class VorbisReader * const this /* r28 */, struct ogg_packet & pk /* r29 */) {
    // Local variables
    int res; // r30
    struct ogg_page pg; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80599E2C -> 0x80599EF4
unsigned char VorbisReader::DoSeek(class VorbisReader * const this /* r31 */) {
    // Local variables
    int byteOffset; // r1+0xC
    int actSamp; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80599EF4 -> 0x8059A0E4
void VorbisReader::DoRawSeek(class VorbisReader * const this /* r31 */, int byte /* r29 */) {
    // Local variables
    int res; // r5
    int ret; // r0

    // References
    // -> static int gCipher;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x8059A0E4 -> 0x8059A0F8
int VorbisReader::QueuedInputBytes() {}

// Range: 0x8059A0F8 -> 0x8059A114
int VorbisReader::QueuedOutputSamples() {}

// Range: 0x8059A114 -> 0x8059A188
void VorbisReader::Init(class VorbisReader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059A188 -> 0x8059A28C
int VorbisReader::ConsumeData(class VorbisReader * const this /* r28 */, void * pcm /* r29 */, int samples /* r1+0x8 */, int startSamp /* r30 */) {
    // Local variables
    int consumed; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059A28C -> 0x8059A290
void VorbisReader::EndData() {}

struct {
    // total size: 0x2C
} __vt__12VorbisReader; // size: 0x2C, address: 0x8092105C
struct {
    // total size: 0x8
} __RTTI__12VorbisReader; // size: 0x8, address: 0x809210B0
struct {
    // total size: 0x8
} __RTTI__15CriticalSection; // size: 0x8, address: 0x809210C8

