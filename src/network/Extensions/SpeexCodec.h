#pragma once
#include "Codec.h"

namespace Quazal {
    class SpeexCodec : public Codec {
    public:
        SpeexCodec(int);
        virtual ~SpeexCodec();
        virtual const char *GetName();
        virtual unsigned int GetNbSamplesPerFrame();
        virtual unsigned int GetNbBytesPerEncodedFrame();
        virtual EncoderState *CreateEncoderState();
        virtual DecoderState *CreateDecoderState();
        virtual void ReleaseEncoderState(EncoderState *);
        virtual void ReleaseDecoderState(DecoderState *);
        virtual void ResetState(EncoderState *);
        virtual void ResetState(DecoderState *);
        virtual void Encode(EncoderState *, short *, unsigned char *);
        virtual void Decode(DecoderState *, unsigned char *, short *);

        unsigned int unk18;
        int unk1c;
    };
}