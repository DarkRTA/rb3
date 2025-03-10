#include "WavReader.h"
#include "os/Debug.h"
#include "utl/FileStream.h"

WavReader::WavReader(File *file, bool enableReads, StandardStream *stream) {
    mInFile = file;
    mOutStream = stream;
    MILO_ASSERT(mInFile, 0x1a);

    mInFileStream = new FileStream(file, true);

    mInWaveFile = new WaveFile(*mInFileStream);

    // this only likes 44100khz, 16-bit, stereo files
    MILO_ASSERT(mInWaveFile->SamplesPerSec() == 44100, 33);
    MILO_ASSERT(mInWaveFile->BitsPerSample() == 16, 34);
    MILO_ASSERT(mInWaveFile->NumChannels() <= 2, 35);

    mNumChannels = mInWaveFile->mNumChannels;
    mSampleRate = mInWaveFile->mSamplesPerSec;
    mSamplesLeft = mInWaveFile->mNumSamples;

    mInWaveFileData = new WaveFileData(*mInWaveFile);

    mInputBuffers[0] = new unsigned short[0x1000];
    mInputBuffers[1] = new unsigned short[0x1000];

    mRawInputBuffer = new unsigned short[0x2000];

    mTotalSamplesConsumed = 0;
    mBufNumSamples = 0;
    mBufOffset = 0;
    mEnableReads = true;
    mInitted = false;
}

WavReader::~WavReader() {
    delete mInWaveFileData;
    delete mInWaveFile;
    delete mInFileStream;
    delete[] (mInputBuffers[0]);
    delete[] (mInputBuffers[1]);
    delete[] (mRawInputBuffer);
}

void WavReader::Poll(float) {
    if (!mInitted) {
        mInitted = true;
        Init();
    }
    if (mBufNumSamples != 0) {
        ConsumeData(
            (void **)(mInputBuffers + (mBufOffset * 2)),
            mBufNumSamples,
            mTotalSamplesConsumed
        );

        while (mSamplesLeft != 0) {
        }
    }
}

void WavReader::Seek(int pos) {
    mInWaveFileData->Seek(pos * mNumChannels * 2, BinStream::kSeekBegin);
}

void WavReader::Init() {
    MILO_ASSERT(mOutStream, 0x9c);

    mOutStream->InitInfo(mNumChannels, mSampleRate, false, mInWaveFile->mNumSamples);
}

void WavReader::ConsumeData(void **pcm, int samples, int startSamp) {
    MILO_ASSERT(mOutStream, 0xa3);

    mOutStream->ConsumeData(pcm, samples, startSamp);
}