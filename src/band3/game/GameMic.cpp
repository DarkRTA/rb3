#include "game/GameMic.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "synth/MicNull.h"
#include "utl/MemStream.h"
#include "utl/Wav.h"

bool gIdxTaken[6];

GameMic::GameMic(int id)
    : mMicID(id), unk8(1), unk9(1), mWriteWav(0), unkc(0), mStoredAudio(0), mDetector(0),
      mNullMic(0), unk24(1), unk8030(0), unk8034(0), unk8038(0) {
    if (id == -1) {
        mNullMic = new MicNull();
    }
    mFonixIdx = -1;
    for (int i = 0; i < 6; i++) {
        if (!gIdxTaken[i]) {
            mFonixIdx = i;
            gIdxTaken[i] = true;
            break;
        }
    }
    MILO_ASSERT(mFonixIdx != -1, 0x5D);
    mWriteWav = DataVariable("do_record").Int();
    SetInputFile(nullptr);
    unk28 = 0;
    unk1c = 0;
    unk2c = -1;
    unk20 = -1;
    if (mWriteWav) {
        mStoredAudio = new MemStream();
        mStoredAudio->Reserve(0x1c00000);
    }
    memset(mSamplesRecent, 0, sizeof(mSamplesRecent));
    memset(mSamplesContinuous, 0, sizeof(mSamplesContinuous));
}

GameMic::~GameMic() {
    if (mWriteWav) {
        WriteWav(
            "mic_output_fonix.wav",
            16000,
            mStoredAudio->Buffer(),
            mStoredAudio->BufferSize()
        );
    }
    RELEASE(mStoredAudio);
    unkc = 0;
    gIdxTaken[mFonixIdx] = false;
    delete mDetector;
}

void GameMic::SetInputFile(const char *) {}

void GameMic::AccessContinuousSamples(const short *&s, int &i) const {
    s = mSamplesContinuous;
    i = unk8034;
}