#include "synth/VorbisReader.h"
#include "obj/DataFile.h"
#include "KeyChain.h"
#include "synth/Synth.h"

namespace {
    static unsigned char gKey[256];
    static int gCipher = -1;
    static int gKeySize = 16;
    static unsigned char gRB1Key[16] = {
        0x37, 0xB2, 0xE2, 0xB9, 0x1C, 0x74, 0xFA, 0x9E,
        0x38, 0x81, 0x08, 0xEA, 0x36, 0x23, 0xDB, 0xE4
    };
}

void VorbisReader::setupCypher(int moggVersion){
    DataArray* arr = DataReadString("{Na 42 'O32'}");
    char iEval = arr->Evaluate(0).Int();
    arr->Release();
    
    int i6 = (iEval + (iEval / 0xD) * -0xD + 'A');
    char buf118[256];
    unsigned char buf218[256];
    sprintf(buf118, "{%c %d %c}", i6, buf218[0] ^ iEval, i6);
    DataArray* buf118Arr = DataReadString(buf118);
    buf118Arr->Evaluate(0);
    buf118Arr->Release();
    KeyChain::getKey(unk68, gKey, buf218);
    TheSynth->mGrinder.GrindArray(unk60, unk64, gKey, 0x10, moggVersion);
    for(int i = 0; i < 16; i++){
        gKey[i] ^= unkd0[i];
    }
    int ret = ctr_start(gCipher, unkc0, gKey, gKeySize, 0, (symmetric_CTR*)unkbc);
    memset(gKey, 0, gKeySize);
    MILO_ASSERT(ret == 0, 0xAA);

    sprintf(buf118, "{ha %d 1}", unk60);
    DataArray* unk6cArr = DataReadString(buf118);
    unk6c = unk6cArr->Evaluate(0).Int();
    unk6cArr->Release();

    sprintf(buf118, "{ha %d 2}", unk64);
    DataArray* unk70Arr = DataReadString(buf118);
    unk70 = unk70Arr->Evaluate(0).Int();
    unk70Arr->Release();
}

VorbisReader::VorbisReader(File* file, bool b2, StandardStream* stream, bool b4) : 
    unk20(-1), unk24(-1), mFile(file), mHeadersRead(0), unk30(0), mEnableReads(1), unk38(0), unk3c(0),
    unk3d(0), unk44(stream), unk48(0), mOggStream(0), unk50(0), unk54(0), mVorbisDsp(0), mVorbisBlock(0),
    unk98(0), mSeekTarget(-1), mSamplesToSkip(0), mHdrSize(0), unkb8(0), unkbc(0), unke0(b4), unke1(0),
    unke2(0), unke3(0), unkf4(-1), unkf0(-1), unkf8(0) {
    MILO_ASSERT(mFile, 0xE6);
    if(b2){
        unkb8 = new unsigned char[60000];
        mFile->ReadAsync(unkb8,60000);
        unke3 = mFile->Fail();
    }
    unk48 = new ogg_sync_state();
    ogg_sync_init(unk48);
}

VorbisReader::~VorbisReader(){
    delete [] unkb8;
    unkb8 = 0;
    if(mOggStream) ogg_stream_clear(mOggStream);
    if(mVorbisBlock) vorbis_block_clear(mVorbisBlock);
    if(mVorbisDsp) vorbis_dsp_clear(mVorbisDsp);
    if(unk54) vorbis_comment_clear(unk54);
    if(unk50) vorbis_info_clear(unk50);
    ogg_sync_clear(unk48);
    RELEASE(mVorbisBlock);
    RELEASE(mVorbisDsp);
    RELEASE(unk54);
    RELEASE(unk50);
    RELEASE(mOggStream);
    RELEASE(unk48);
    RELEASE(unkbc);
}