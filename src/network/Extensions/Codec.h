#pragma once
#include "AudioStreamFormat.h"
#include "Platform/RootObject.h"
#include "speex/speex.h"
#include "speex/speex_bits.h"

namespace Quazal {
    class Codec : public RootObject {
    public:
        class EncoderState {
        public:
            void *mState; // 0x0
            SpeexBits mBits; // 0x4

            void Encode(short *s, unsigned char *uc) {
                float input[160];
                for (int i = 0; i < 160; i++) {
                    input[i] = s[i];
                }
                speex_bits_reset(&mBits);
                speex_encode(mState, input, &mBits);
                speex_bits_write(&mBits, (char *)uc, 200);
            }
        };

        class DecoderState {
        public:
            void *mState; // 0x0
            SpeexBits mBits; // 0x4

            void Decode(unsigned char *uc, short *s, int i3) {
                float output[160];
                speex_bits_reset(&mBits);
                speex_bits_read_from(&mBits, (char *)uc, i3);
                speex_decode(mState, &mBits, output);
                for (int i = 0; i < 160; i++) {
                    s[i] = output[i];
                }
            }
        };

        Codec();
        virtual ~Codec();
        virtual const char *GetName() = 0;
        virtual unsigned int GetNbSamplesPerFrame() = 0;
        virtual unsigned int GetNbBytesPerEncodedFrame() = 0;
        virtual float GetCompressionRatio();
        virtual EncoderState *CreateEncoderState() = 0;
        virtual DecoderState *CreateDecoderState() = 0;
        virtual void ReleaseEncoderState(EncoderState *) = 0;
        virtual void ReleaseDecoderState(DecoderState *) = 0;
        virtual void ResetState(EncoderState *) = 0;
        virtual void ResetState(DecoderState *) = 0;
        virtual void Encode(EncoderState *, short *, unsigned char *) = 0;
        virtual void Decode(DecoderState *, unsigned char *, short *) = 0;
        virtual void Trace(unsigned int) {}

        AudioStreamFormat mAudioStreamFormat; // 0x4
    };
}