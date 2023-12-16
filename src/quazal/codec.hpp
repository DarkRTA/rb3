#ifndef QUAZAL_CODEC_HPP
#define QUAZAL_CODEC_HPP
#include "rootobject.hpp"
#include "audiostreamformat.hpp"

namespace Quazal {
    class Codec : RootObject {
    public:
        Codec();
        virtual ~Codec();

        AudioStreamFormat fmt;
    };
}

#endif