#include "network/Extensions/SpeexCodec.h"
#include "Codec.h"
#include "speex/speex.h"
#include "speex/speex_bits.h"
#include <stdlib.h>

namespace Quazal {
    SpeexCodec::SpeexCodec(int i1) : unk18(i1 / 20) {
        if (unk18 == 0)
            unk18 = 1;
        unk1c = 160;
        mAudioStreamFormat.mNbSamplesPerPacket = unk18 * 160;
    }

    SpeexCodec::~SpeexCodec() {}
    const char *SpeexCodec::GetName() { return "Speex"; }
    unsigned int SpeexCodec::GetNbBytesPerEncodedFrame() { return unk18 * 20; }
    unsigned int SpeexCodec::GetNbSamplesPerFrame() { return unk18 * 160; }

    Codec::EncoderState *SpeexCodec::CreateEncoderState() {
        EncoderState *state = (EncoderState *)malloc(sizeof(EncoderState));
        ResetState(state);
        speex_bits_init(&state->mBits);
        return state;
    }

    Codec::DecoderState *SpeexCodec::CreateDecoderState() {
        DecoderState *state = (DecoderState *)malloc(sizeof(DecoderState));
        ResetState(state);
        speex_bits_init(&state->mBits);
        return state;
    }

    void SpeexCodec::ReleaseEncoderState(EncoderState *state) {
        speex_encoder_destroy(state->mState);
        speex_bits_destroy(&state->mBits);
        free(state);
    }

    void SpeexCodec::ReleaseDecoderState(DecoderState *state) {
        speex_decoder_destroy(state->mState);
        speex_bits_destroy(&state->mBits);
        free(state);
    }

    void SpeexCodec::ResetState(EncoderState *state) {
        void *speexState = speex_encoder_init(&speex_nb_mode);
        state->mState = speexState;
        int data = 8000;
        speex_encoder_ctl(state->mState, 18, &data);
        data = 8000;
        speex_encoder_ctl(state->mState, 24, &data);
        data = 4;
        speex_encoder_ctl(state->mState, 4, &data);
        speex_encoder_ctl(state->mState, 3, &data);
        unk1c = data;
    }

    void SpeexCodec::ResetState(DecoderState *state) {
        void *speexState = speex_decoder_init(&speex_nb_mode);
        state->mState = speexState;
        int data = 8000;
        speex_decoder_ctl(state->mState, 24, &data);
    }

    void SpeexCodec::Encode(EncoderState *state, short *s, unsigned char *uc) {
        for (int i = 0; i < unk18; i++) {
            state->Encode(&s[i * 160], &uc[i * 20]);
        }
    }

    void SpeexCodec::Decode(DecoderState *state, unsigned char *uc, short *s) {
        for (int i = 0; i < unk18; i++) {
            state->Decode(&uc[i * 20], &s[i * 160], 20);
        }
    }
}