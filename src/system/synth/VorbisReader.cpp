#include "synth/VorbisReader.h"
#include "obj/DataFile.h"
#include "KeyChain.h"
#include "synth/Synth.h"
#include "utl/BufStream.h"

namespace {
    static unsigned char gKey[256];
    static int gCipher = -1;
    static int gKeySize = 16;
    static unsigned char gRB1Key[16] = { 0x37, 0xB2, 0xE2, 0xB9, 0x1C, 0x74, 0xFA, 0x9E,
                                         0x38, 0x81, 0x08, 0xEA, 0x36, 0x23, 0xDB, 0xE4 };
}

#define VORBIS_FAIL(name, err)                                                           \
    MILO_WARN("Ogg Vorbis failure: %s, error code %i", name, err);

void VorbisReader::setupCypher(int moggVersion) {
    DataArray *arr = DataReadString("{Na 42 'O32'}");
    unsigned int iEval = arr->Evaluate(0).Int();
    arr->Release();

    char i6 = (iEval % 13);
    i6 = i6 + 'A';
    char script[256];
    unsigned char masterKey[256];
    sprintf(script, "{%c %d %c}", i6, (int)masterKey ^ iEval, i6);
    DataArray *buf118Arr = DataReadString(script);
    buf118Arr->Evaluate(0);
    buf118Arr->Release();
    KeyChain::getKey(mKeyIndex, gKey, masterKey);
    TheSynth->mGrinder.GrindArray(mMagicA, mMagicB, gKey, 0x10, moggVersion);
    for (int i = 0; i < 16; i++) {
        gKey[i] ^= mKeyMask[i];
    }
    int ret = ctr_start(gCipher, mNonce, gKey, gKeySize, 0, mCtrState);
    memset(gKey, 0, gKeySize);
    MILO_ASSERT(ret == 0, 0xAA);

    sprintf(script, "{ha %d 1}", mMagicA);
    DataArray *magicGenA = DataReadString(script);
    mMagicHashA = magicGenA->Evaluate(0).Int();
    magicGenA->Release();

    sprintf(script, "{ha %d 2}", mMagicB);
    DataArray *magicGenB = DataReadString(script);
    mMagicHashB = magicGenB->Evaluate(0).Int();
    magicGenB->Release();
}

VorbisReader::VorbisReader(
    File *vorbisFile, bool expectMap, StandardStream *stream, bool b4
)
    : mNumChannels(-1), mSampleRate(-1), mFile(vorbisFile), mHeadersRead(0),
      mReadBuffer(0), mEnableReads(1), unk38(0), unk3c(0), mDone(0), mStream(stream),
      mOggSync(0), mOggStream(0), mVorbisInfo(0), mVorbisComment(0), mVorbisDsp(0),
      mVorbisBlock(0), unk98(0), mSeekTarget(-1), mSamplesToSkip(0), mHdrSize(0),
      mHdrBuf(0), mCtrState(0), unke0(b4), unke1(0), unke2(0), mFail(0),
      mThreadBufferStart(-1), unkf8(0) {
    MILO_ASSERT(mFile, 0xE6);
    if (expectMap) {
        mHdrBuf = new char[60000];
        mFile->ReadAsync(mHdrBuf, 60000);
        mFail = mFile->Fail();
    }
    mOggSync = new ogg_sync_state();
    ogg_sync_init(mOggSync);
}

VorbisReader::~VorbisReader() {
    delete[] mHdrBuf;
    mHdrBuf = 0;
    if (mOggStream)
        ogg_stream_clear(mOggStream);
    if (mVorbisBlock)
        vorbis_block_clear(mVorbisBlock);
    if (mVorbisDsp)
        vorbis_dsp_clear(mVorbisDsp);
    if (mVorbisComment)
        vorbis_comment_clear(mVorbisComment);
    if (mVorbisInfo)
        vorbis_info_clear(mVorbisInfo);
    ogg_sync_clear(mOggSync);
    RELEASE(mVorbisBlock);
    RELEASE(mVorbisDsp);
    RELEASE(mVorbisComment);
    RELEASE(mVorbisInfo);
    RELEASE(mOggStream);
    RELEASE(mOggSync);
    RELEASE(mCtrState);
}

void VorbisReader::Poll(float until) {
    if (!mFail && !unk3c && CheckHmxHeader() && !mDone && (mSeekTarget < 0 || DoSeek())) {
        DoFileRead();
        unke2 = mFile->Eof();
        if (mHeadersRead < 3) {
            while (TryReadHeader())
                ;
            if (mHeadersRead >= 3) {
                mNumChannels = mVorbisInfo->channels;
                mSampleRate = mVorbisInfo->rate;
                Init();
                InitDecoder();
            }
        } else {
            Timer timer;
            timer.Start();
            bool b1 = !unke0;
            while (timer.Ms() < until || b1) {
                b1 = false;
                TryConsumeData();
                if (!TryDecode())
                    return;
                DoFileRead();
                timer.Split();
            }
        }
    }
}

void VorbisReader::Seek(int sample) {
    CritSecTracker tracker(this);
    MILO_ASSERT(mHeadersRead == 3, 0x1CC);
    MILO_ASSERT(mEnableReads, 0x1CD);
    MILO_ASSERT(sample >= 0, 0x1CE);
    mSeekTarget = sample;
    mDone = false;
    unke1 = false;
}

bool VorbisReader::DoFileRead() {
    bool ret = false;
    if (mFail)
        return false;
    else {
        if (mEnableReads && !mReadBuffer && !mFile->Eof()
            && QueuedInputBytes() < 0x10000) {
            mReadBuffer = ogg_sync_buffer(mOggSync, 0x4000);
            START_AUTO_TIMER("synth_poll");
            mFile->ReadAsync(mReadBuffer, 0x4000);
            mFail = mFile->Fail();
            ret = true;
        }
        int bytes = 0;
        if (!mFail && mReadBuffer && mFile->ReadDone(bytes) && !unk38) {
            mFail = mFile->Fail();
            if (mFail)
                return false;
            MILO_ASSERT(bytes > 0, 0x1F9);
            Decrypt((unsigned char *)mReadBuffer, bytes);
            ogg_sync_wrote(mOggSync, bytes);
            mReadBuffer = 0;
            ret = true;
        }
        mFail = mFile->Fail();
    }
    return ret;
}

void VorbisReader::Decrypt(unsigned char *data, int bytes) {
    if (!mCtrState)
        return;
    int i = 0;
    int n = 0;
    while (i += n, i < bytes) {
        const int dataLen = 1024;
        unsigned char buf2[dataLen];
        unsigned char buf1[dataLen];

        int n = Min(bytes - i, dataLen);

        memcpy(buf1, data + i, n);
        int ret = ctr_decrypt(buf1, buf2, n, mCtrState);
        unsigned char *after = buf2;
        if ((mMagicHashA != 0 || mMagicHashB != 0)
            && (after[0] == 'H' && after[1] == 'M' && after[2] == 'X' && after[3] == 'A'
            )) {
            after[0] = 'O';
            after[2] = 'g';
            after[1] = 'g';
            after[3] = 'S';
            if (n >= 16) {
                unsigned int *ui = (unsigned int *)&after[12];
                *ui ^= mMagicHashA;
            }
            if (n >= 24) {
                unsigned int *ui = (unsigned int *)&after[20];
                *ui ^= mMagicHashB;
            }
        }
        MILO_ASSERT(ret == 0, 0x234);
        memcpy(data + i, buf2, n);
        i += n;
    }
}

#define kMaxHeader 60000

bool VorbisReader::CheckHmxHeader() {
    if (!mHdrBuf)
        return true;
    else {
        int bytes;
        if (mFile->ReadDone(bytes)) {
            BufStream bs(mHdrBuf, 60000, true);
            int version;
            bs >> version;
            bs >> mHdrSize;
            MILO_ASSERT(version >= 10, 0x24A);
            MILO_ASSERT(version <= 16, 0x24B);
            MILO_ASSERT(mHdrSize <= kMaxHeader, 0x24C);
            MILO_ASSERT(mHdrSize >= 0, 0x24D);
            mMap.Read(bs);
            mKeyIndex = 0;
            memset(mKeyMask, 0, sizeof(mKeyMask));
            mMagicA = mMagicB = 0;
            mMagicHashA = mMagicHashB = 0;
            if (version - 0xCU <= 4) {
                bs.Read(mNonce, sizeof(mNonce));
                bs >> mMagicA;
                bs >> mMagicB;
                unsigned char stuff[16];
                bs.Read(stuff, sizeof(stuff));
                bs.Read(stuff, sizeof(stuff));
                bs >> mKeyIndex;
                mKeyIndex = mKeyIndex % 6 + 6;
                TheSynth->mGrinder.HvDecrypt(stuff, mKeyMask, version);
                gCipher = register_cipher(&rijndael_desc);
                MILO_ASSERT(gCipher >= 0, 0x279);
                mCtrState = new symmetric_CTR();
                int keyIndex = mKeyIndex;
                MILO_ASSERT_RANGE( keyIndex, 0, KeyChain::getNumKeys(), 0x27E);
                setupCypher(version);
            } else if (version == 0xB) {
                bs.Read(mNonce, sizeof(mNonce));
                gCipher = register_cipher(&rijndael_desc);
                MILO_ASSERT(gCipher >= 0, 0x287);
                mCtrState = new symmetric_CTR();
                int ret = ctr_start(gCipher, mNonce, gRB1Key, gKeySize, 0, mCtrState);
                MILO_ASSERT(ret == 0, 0x28F);
            } else
                MILO_NOTIFY_ONCE("old mogg version!");
            delete[] mHdrBuf;
            mHdrBuf = 0;
            mFile->Seek(mHdrSize, BinStream::kSeekBegin);
        }
        mFail = mFile->Fail();
        return !mHdrBuf;
    }
}

bool VorbisReader::TryReadHeader() {
    if (!mOggStream) {
        ogg_page page;
        int pageOut = ogg_sync_pageout(mOggSync, &page);
        if (pageOut < 0)
            VORBIS_FAIL("StreamInit", pageOut);
        if (pageOut > 0) {
            mOggStream = new ogg_stream_state();
            ogg_stream_init(mOggStream, ogg_page_serialno(&page));
            ogg_stream_pagein(mOggStream, &page);
            mVorbisInfo = new vorbis_info();
            vorbis_info_init(mVorbisInfo);
            mVorbisComment = new vorbis_comment();
            vorbis_comment_init(mVorbisComment);
        } else
            return false;
    }
    if (mHeadersRead == 3)
        return false;
    else {
        ogg_packet packet;
        if (TryReadPacket(packet)) {
            int vorbisErr =
                vorbis_synthesis_headerin(mVorbisInfo, mVorbisComment, &packet);
            if (vorbisErr < 0)
                VORBIS_FAIL("HeaderIn", vorbisErr);
            mHeadersRead++;
            return true;
        } else
            return false;
    }
}

void VorbisReader::InitDecoder() {
    MILO_ASSERT(!mVorbisDsp && !mVorbisBlock, 0x2D1);
    MILO_ASSERT(mHeadersRead == 3, 0x2D2);
    mVorbisDsp = new vorbis_dsp_state();
    vorbis_synthesis_init(mVorbisDsp, mVorbisInfo);
    mVorbisBlock = new vorbis_block();
    vorbis_block_init(mVorbisDsp, mVorbisBlock);
}

bool VorbisReader::TryConsumeData() {
    int ret = 0;
    float **pcm;
    int pcmErr = vorbis_synthesis_pcmout(mVorbisDsp, &pcm);
    if (pcmErr < 0) {
        VORBIS_FAIL("PCMOut", pcmErr);
    }
    if (pcmErr > 0) {
        ret = ConsumeData((void **)pcm, pcmErr, mVorbisDsp->granulepos - pcmErr);
        vorbis_synthesis_read(mVorbisDsp, ret);
    }
    return ret;
}

bool VorbisReader::TryDecode() {
    if (mFail)
        return false;
    if (QueuedOutputSamples() > 0)
        return false;
    if (!unk98 && TryReadPacket(mPendingPacket)) {
        unk98 = true;
    }
    if (unk98) {
        START_AUTO_TIMER("vorbis_synthesis_poll_cpu");
        if (mVorbisBlock->synthesis_state == vorbis_block::vss_init) {
            START_AUTO_TIMER("vorbis_synthesis_vssinit_cpu");
        } else if (mVorbisBlock->synthesis_state == vorbis_block::vss_decode) {
            START_AUTO_TIMER("vorbis_synthesis_vssdecode_cpu");
        } else {
            START_AUTO_TIMER("vorbis_synthesis_vssmdct_cpu");
        }
        int pollErr = vorbis_synthesis_poll(mVorbisBlock, &mPendingPacket);
        if (pollErr == OV_ENOTAUDIO) {
            unk98 = false;
        } else {
            if (pollErr == -0x32)
                return true;
            if (pollErr < 0) {
                VORBIS_FAIL("Synthesis", pollErr);
            }
            unk98 = false;
            if (pollErr == 0) {
                START_AUTO_TIMER("vorbis_synthesis_blockin_cpu");
                int blockErr = vorbis_synthesis_blockin(mVorbisDsp, mVorbisBlock);
                if (blockErr < 0) {
                    VORBIS_FAIL("BlockIn", blockErr);
                }
                return true;
            }
        }
    } else if (unke2 && !mReadBuffer && QueuedOutputSamples() == 0 && !mDone) {
        EndData();
        mDone = true;
    }
    return false;
}

bool VorbisReader::TryReadPacket(ogg_packet &pk) {
    MILO_ASSERT(mOggStream, 0x3AA);
    while (true) {
        int streamErr = ogg_stream_packetout(mOggStream, &pk);
        if (streamErr < 0) {
            VORBIS_FAIL("PacketOut", streamErr);
        }
        if (streamErr > 0)
            return true;
        ogg_page page;
        int syncErr = ogg_sync_pageout(mOggSync, &page);
        if (syncErr > 0)
            ogg_stream_pagein(mOggStream, &page);
        else
            return false;
    }
}

bool VorbisReader::DoSeek() {
    mEnableReads = false;
    DoFileRead();
    if (!mFail && !mReadBuffer) {
        int i1, i2;
        mMap.GetSeekPos(mSeekTarget, i1, i2);
        DoRawSeek(i1);
        mSamplesToSkip = mSeekTarget - i2;
        MILO_ASSERT(mSamplesToSkip >= 0, 0x3D0);
        mSeekTarget = -1;
        mEnableReads = true;
        return true;
    }
    return false;
}

void VorbisReader::DoRawSeek(int byte) {
    if (mReadBuffer) {
        mEnableReads = false;
        while (!mFail && mReadBuffer)
            DoFileRead();
        mEnableReads = true;
    }
    int streamErr = ogg_stream_reset(mOggStream);
    if (streamErr < 0)
        VORBIS_FAIL("StreamReset", streamErr);
    int syncErr = ogg_sync_reset(mOggSync);
    if (syncErr < 0)
        VORBIS_FAIL("SyncReset", syncErr);
    vorbis_block_clear(mVorbisBlock);
    int restartErr = vorbis_synthesis_restart(mVorbisDsp);
    if (restartErr < 0)
        VORBIS_FAIL("DspReset", restartErr);
    vorbis_block_init(mVorbisDsp, mVorbisBlock);
    unk98 = false;
    mFile->Seek(byte + mHdrSize, 0);
    if (mCtrState) {
        MILO_ASSERT(byte%16 == 0, 0x402);
        // this is the part where the word that makes up byte gets assigned to the word
        // that makes up mNonce
        // unsigned char mNonce[16]; // 0xc0
        int ret = ctr_reinit(gCipher, mNonce, mCtrState);
        MILO_ASSERT(ret == 0, 0x405);
    }
    mDone = false;
    unke2 = false;
}

inline int VorbisReader::QueuedInputBytes() {
    return mOggSync->fill - mOggSync->returned;
}

int VorbisReader::QueuedOutputSamples() {
    if (mVorbisDsp) {
        START_AUTO_TIMER("vorbis_synthesis_pcmout_cpu");
        return vorbis_synthesis_pcmout(mVorbisDsp, nullptr);
    } else
        return 0;
}

void VorbisReader::Init() {
    MILO_ASSERT(mStream, 0x42D);
    mStream->InitInfo(mNumChannels, mSampleRate, true, -1);
}

int VorbisReader::ConsumeData(void **v, int i1, int i2) {
    MILO_ASSERT(mSeekTarget == -1, 0x444);
    if (mSamplesToSkip > 0) {
        int ret = Min(i1, mSamplesToSkip);
        mSamplesToSkip -= ret;
        return ret;
    } else {
        MILO_ASSERT(mStream, 0x44D);
        return mStream->ConsumeData(v, i1, i2);
    }
}