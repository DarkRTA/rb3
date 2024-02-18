#ifndef QUAZAL_CODEC_HPP
#define QUAZAL_CODEC_HPP
#include "rootobject.hpp"
#include "audiostreamformat.hpp"

namespace Quazal {
    class Codec : RootObject {
    public:
        enum EncoderState {
            enc0,
            enc1,
            enc2
        };
        enum DecoderState {
            dec0,
            dec1,
            dec2
        };

        Codec();
        virtual ~Codec();
        virtual const char *GetName() = 0;
        virtual int GetNbSamplesPerFrame() = 0;
        virtual int GetNbBytesPerEncodedFrame() = 0;
        virtual float GetCompressionRatio();
        virtual void *CreateEncoderState() = 0;
        virtual void *CreateDecoderState() = 0;
        virtual void ReleaseEncoderState(EncoderState *) = 0;
        virtual void ReleaseDecoderState(DecoderState *) = 0;
        virtual void ResetState(EncoderState *) = 0;
        virtual void ResetState(DecoderState *) = 0;
        virtual void Encode(EncoderState *, short *, unsigned char *) = 0;
        virtual void Decode(DecoderState *, unsigned char *, short *) = 0;
        virtual void Trace(unsigned int);

        AudioStreamFormat fmt;
    };
}

#endif
