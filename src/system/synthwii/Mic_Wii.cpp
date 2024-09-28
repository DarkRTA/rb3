#include "Mic_Wii.h"
#include <os/Debug.h>

float MicWii::GetEarpieceVolume() const {
    return 0.0f;
}

void MicWii::SetEarpieceVolume(float) {
    return;
}

int MicWii::GetClipping() const {
    return 0;
}

float MicWii::GetGain() const {
    return mGain;
}

int MicWii::GetSampleRate() const {
    return 1;
}

float MicWii::GetVolume() const {
    return mVolume;
}

short *MicWii::GetBuf() {
    return mOutBuf;
}

int MicWii::GetBufSamples() const {
    return mOutBufSamples;
}

void MicWii::SetMicIndex(int micIndex) {
    MILO_ASSERT(micIndex >= -1 && micIndex < 4, 0x288);
    mMicIndex = micIndex;
}