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
    unsigned int iEval = arr->Evaluate(0).Int();
    arr->Release();
    
    char i6 = (iEval % 13);
    i6 = i6 + 'A';
    char script[256];
    unsigned char masterKey[256];
    sprintf(script, "{%c %d %c}", i6, (int)masterKey ^ iEval, i6);
    DataArray* buf118Arr = DataReadString(script);
    buf118Arr->Evaluate(0);
    buf118Arr->Release();
    KeyChain::getKey(mKeyIndex, gKey, masterKey);
    TheSynth->mGrinder.GrindArray(mMagicA, mMagicB, gKey, 0x10, moggVersion);
    for(int i = 0; i < 16; i++){
        gKey[i] ^= mKeyMask[i];
    }
    int ret = ctr_start(gCipher, mNonce, gKey, gKeySize, 0, mCtrState);
    memset(gKey, 0, gKeySize);
    MILO_ASSERT(ret == 0, 0xAA);

    sprintf(script, "{ha %d 1}", mMagicA);
    DataArray* magicGenA = DataReadString(script);
    mMagicHashA = magicGenA->Evaluate(0).Int();
    magicGenA->Release();

    sprintf(script, "{ha %d 2}", mMagicB);
    DataArray* magicGenB = DataReadString(script);
    mMagicHashB = magicGenB->Evaluate(0).Int();
    magicGenB->Release();
}

VorbisReader::VorbisReader(File* vorbisFile, bool expectMap, StandardStream* stream, bool b4) : 
    unk20(-1), unk24(-1), mFile(vorbisFile), mHeadersRead(0), unk30(0), mEnableReads(1), unk38(0), unk3c(0),
    mDone(0), unk44(stream), mOggSync(0), mOggStream(0), unk50(0), unk54(0), mVorbisDsp(0), mVorbisBlock(0),
    unk98(0), mSeekTarget(-1), mSamplesToSkip(0), mHdrSize(0), mHdrBuf(0), mCtrState(0), unke0(b4), unke1(0),
    unke2(0), mFail(0), mThreadBufferStart(-1), unkf8(0) {
    MILO_ASSERT(mFile, 0xE6);
    if(expectMap){
        mHdrBuf = new char[60000];
        mFile->ReadAsync(mHdrBuf,60000);
        mFail = mFile->Fail();
    }
    mOggSync = new ogg_sync_state();
    ogg_sync_init(mOggSync);
}

VorbisReader::~VorbisReader(){
    delete [] mHdrBuf;
    mHdrBuf = 0;
    if(mOggStream) ogg_stream_clear(mOggStream);
    if(mVorbisBlock) vorbis_block_clear(mVorbisBlock);
    if(mVorbisDsp) vorbis_dsp_clear(mVorbisDsp);
    if(unk54) vorbis_comment_clear(unk54);
    if(unk50) vorbis_info_clear(unk50);
    ogg_sync_clear(mOggSync);
    RELEASE(mVorbisBlock);
    RELEASE(mVorbisDsp);
    RELEASE(unk54);
    RELEASE(unk50);
    RELEASE(mOggStream);
    RELEASE(mOggSync);
    RELEASE(mCtrState);
}

void VorbisReader::Poll(float until){

}