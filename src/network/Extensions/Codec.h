#pragma once
#include "AudioStreamFormat.h"
#include "Platform/RootObject.h"

namespace Quazal {
    class Codec : public RootObject {
    public:
        class EncoderState {
        public:
        };

        class DecoderState {
        public:
        };

        Codec();
        virtual ~Codec();
        virtual const char *GetName() = 0;
        virtual unsigned int GetNbSamplesPerFrame() = 0;
        virtual unsigned int GetNbBytesPerEncodedFrame() = 0;
        virtual float GetCompressionRatio();
        virtual void *CreateEncoderState() = 0;
        virtual void *CreateDecoderState() = 0;
        virtual void ReleaseEncoderState(EncoderState *) = 0;
        virtual void ReleaseDecoderState(DecoderState *) = 0;
        virtual void ResetState(EncoderState *) = 0;
        virtual void ResetState(DecoderState *) = 0;
        virtual void Encode(EncoderState *, short *, unsigned char *) = 0;
        virtual void Decode(DecoderState *, unsigned char *, short *) = 0;
        virtual void Trace(unsigned int) {}

        AudioStreamFormat mAudioStreamFormat;
    };
}