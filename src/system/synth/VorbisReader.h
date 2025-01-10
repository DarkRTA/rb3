#pragma once
#include "synth/StreamReader.h"
#include "os/CritSec.h"
#include "os/File.h"
#include "synth/StandardStream.h"
#include "synth/OggMap.h"
#include "oggvorbis/ogg.h"
#include "oggvorbis/codec.h"
#include "synth/tomcrypt/mycrypt.h"

class VorbisReader : public StreamReader, public CriticalSection {
public:
    VorbisReader(File*, bool, StandardStream*, bool);
    virtual ~VorbisReader();
    virtual void Poll(float);
    virtual void Seek(int);
    virtual void EnableReads(bool enable){ mEnableReads = enable; }
    virtual bool Done(){ return mDone; }
    virtual bool Fail(){ return mFail; }
    virtual void Init();
    virtual int ConsumeData(void**, int, int);
    virtual void EndData(){}

    void setupCypher(int);
    bool CheckHmxHeader();
    bool DoSeek();
    bool DoFileRead();
    bool TryReadHeader();
    void InitDecoder();
    bool TryConsumeData();
    bool TryDecode();
    int QueuedInputBytes();
    int QueuedOutputSamples();
    void Decrypt(unsigned char*, int);
    bool TryReadPacket(ogg_packet&);
    void DoRawSeek(int);

    int mNumChannels; // 0x20
    int mSampleRate; // 0x24
    File* mFile; // 0x28
    int mHeadersRead; // 0x2c
    char* mReadBuffer; // 0x30
    bool mEnableReads; // 0x34
    int unk38; // 0x38
    bool unk3c; // 0x3c
    bool mDone; // 0x3d
    int unk40; // 0x40
    StandardStream* mStream; // 0x44
    ogg_sync_state* mOggSync; // 0x48
    ogg_stream_state* mOggStream; // 0x4c
    vorbis_info* mVorbisInfo; // 0x50
    vorbis_comment* mVorbisComment; // 0x54
    vorbis_dsp_state* mVorbisDsp; // 0x58
    vorbis_block* mVorbisBlock; // 0x5c
    long mMagicA; // 0x60 - byte grinder seed A
    long mMagicB; // 0x64 - byte grinder seed B
    long mKeyIndex; // 0x68
    long mMagicHashA; // 0x6c
    long mMagicHashB; // 0x70
    int unk74; // 0x74
    ogg_packet mPendingPacket; // 0x78
    bool unk98; // 0x98
    int mSeekTarget; // 0x9c
    int mSamplesToSkip; // 0xa0
    OggMap mMap; // 0xa4
    int mHdrSize; // 0xb4
    char* mHdrBuf; // 0xb8
    symmetric_CTR* mCtrState; // 0xbc
    unsigned char mNonce[16]; // 0xc0
    unsigned char mKeyMask[16]; // 0xd0
    bool unke0; // 0xe0
    bool unke1; // 0xe1
    bool unke2; // 0xe2
    bool mFail; // 0xe3
    std::vector<int> unke4; // 0xe4
    int unkec; // 0xec
    long long mThreadBufferStart; // 0xf0
    int unkf8; // 0xf8
};