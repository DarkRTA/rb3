#include "speexcodec.hpp"

Quazal::SpeexCodec::SpeexCodec(int i) {
    int val = i / 20;
    unk18 = val;
    if (val == 0)
        unk18 = 1;
    unk1c = 0xA0;
    fmt.unk4 = unk18 * 0xA0;
}

Quazal::SpeexCodec::~SpeexCodec() {
}

const char *Quazal::SpeexCodec::GetName() {
    return "Speex";
}

int Quazal::SpeexCodec::GetNbBytesPerEncodedFrame() {
    return unk18 * 20;
}

int Quazal::SpeexCodec::GetNbSamplesPerFrame() {
    return unk18 * 0xA0;
}