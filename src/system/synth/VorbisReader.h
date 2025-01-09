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
    virtual void EnableReads(bool);
    virtual bool Done();
    virtual bool Fail();
    virtual void Init();
    virtual int ConsumeData(void**, int, int);
    virtual void EndData(){}

    void setupCypher(int);

    int unk20; // 0x20
    int unk24; // 0x24
    File* mFile; // 0x28
    int mHeadersRead; // 0x2c
    int unk30; // 0x30
    bool mEnableReads; // 0x34
    int unk38; // 0x38
    bool unk3c; // 0x3c
    bool unk3d; // 0x3d
    int unk40; // 0x40
    StandardStream* unk44; // 0x44
    ogg_sync_state* unk48; // 0x48
    ogg_stream_state* mOggStream; // 0x4c
    vorbis_info* unk50; // 0x50
    vorbis_comment* unk54; // 0x54
    vorbis_dsp_state* mVorbisDsp; // 0x58
    vorbis_block* mVorbisBlock; // 0x5c
    long unk60; // 0x60 - byte grinder seed A
    long unk64; // 0x64 - byte grinder seed B
    int unk68; // 0x68
    int unk6c; // 0x6c
    int unk70; // 0x60
    int unk74; // 0x64
    int unk78; // 0x68
    int unk7c; // 0x6c
    int unk80; // 0x60
    int unk84; // 0x64
    int unk88; // 0x68
    int unk8c; // 0x6c
    int unk90; // 0x90
    int unk94; // 0x94
    bool unk98; // 0x98
    int mSeekTarget; // 0x9c
    int mSamplesToSkip; // 0xa0
    OggMap unka4; // 0xa4
    int mHdrSize; // 0xb4
    void* unkb8; // 0xb8
    void* unkbc; // 0xbc - actually a symmetric_CTR
    unsigned char unkc0[16]; // 0xc0
    unsigned char unkd0[16]; // 0xd0
    bool unke0; // 0xe0
    bool unke1; // 0xe1
    bool unke2; // 0xe2
    bool unke3; // 0xe3
    std::vector<int> unke4; // 0xe4
    int unkec; // 0xec
    int unkf0; // 0xf0
    int unkf4; // 0xf4
    int unkf8; // 0xf8
};