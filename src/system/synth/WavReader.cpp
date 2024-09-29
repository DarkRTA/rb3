#include "WavReader.h"

WavReader::WavReader(File *file, bool enableReads, StandardStream *stream) {
    mInFile = file;
    mOutStream = stream;
    MILO_ASSERT(mInFile, 0x1a);

    // TODO: figure out how to properly construct these, can't quite get it right
    //FileStream fileStream = FileStream(mInFile, true);
    //mInFileStream = &fileStream;

    //WaveFile waveFile(*mInFileStream);
    //mInWaveFile = &waveFile;

    // this only likes 44100khz, 16-bit, stereo files
    MILO_ASSERT(mInWaveFile->SamplesPerSec() == 44100, 0x21);
    MILO_ASSERT(mInWaveFile->BitsPerSample() == 16, 0x21);
    MILO_ASSERT(mInWaveFile->NumChannels() <= 2, 0x21);

    mNumChannels = mInWaveFile->mNumChannels;
    mSampleRate = mInWaveFile->mSamplesPerSec;
    mSamplesLeft = mInWaveFile->mNumSamples;

    //WaveFileData waveFileData(*mInWaveFile);
    //mInWaveFileData = &waveFileData;

    mInputBuffers[0] = new unsigned short[0x2000];
    mInputBuffers[1] = new unsigned short[0x2000];

    mRawInputBuffer = new unsigned short[0x4000];

    mTotalSamplesConsumed = 0;
    mBufNumSamples = 0;
    mBufOffset = 0;
    mEnableReads = true;
    mInitted = false;
}

WavReader::~WavReader() {
    if (this != nullptr) {
        if (mInWaveFileData != nullptr) {
            mInWaveFileData->~WaveFileData();
        }
        mInWaveFile->~WaveFile();
        if (mInFileStream != nullptr) {
            mInFileStream->~FileStream();
        }
        delete (mInputBuffers[0]);
        delete (mInputBuffers[1]);
        delete (mRawInputBuffer);
    }
    return;
}

void WavReader::Init() {
    MILO_ASSERT(mOutStream, 0x9c);

    mOutStream->InitInfo(mNumChannels, mSampleRate, false, mInWaveFile->mNumSamples);
}

void WavReader::ConsumeData(void **pcm, int samples, int startSamp) {
    MILO_ASSERT(mOutStream, 0xa3);

    mOutStream->ConsumeData(pcm, samples, startSamp);
}

bool WavReader::Done() {
    return mSamplesLeft == 0;
}

void WavReader::EnableReads(bool enabled) {
    mEnableReads = enabled;
}

void WavReader::EndData() {
    return;
}

bool WavReader::Fail() {
    return false;
}

void WavReader::Seek(int pos) {
    mInWaveFileData->Seek(pos * mNumChannels * 2, BinStream::kSeekBegin);
}