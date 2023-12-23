#ifndef QUAZAL_SPEEXCODEC_HPP
#define QUAZAL_SPEEXCODEC_HPP
#include "codec.hpp"

namespace Quazal {
    class SpeexCodec : Codec {
    public:
        SpeexCodec(int);
        virtual ~SpeexCodec();
        virtual const char *GetName();
        virtual int GetNbSamplesPerFrame();
        virtual int GetNbBytesPerEncodedFrame();

        virtual void *CreateEncoderState();
        virtual void *CreateDecoderState();
        virtual void ReleaseEncoderState(EncoderState *);
        virtual void ReleaseDecoderState(DecoderState *);
        virtual void ResetState(EncoderState *);
        virtual void ResetState(DecoderState *);
        virtual void Encode(EncoderState *, short *, unsigned char *);
        virtual void Decode(DecoderState *, unsigned char *, short *);

        int unk18;
        int unk1c;
    };
}

#endif