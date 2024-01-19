#ifndef QUAZAL_AUDIOSTREAMFORMAT_HPP
#define QUAZAL_AUDIOSTREAMFORMAT_HPP
#include "_ddl_audiostreamformat.hpp"
#include "rootobject.hpp"

namespace Quazal {
    class AudioStreamFormat : _DDL_AudioStreamFormat {
    public:
        AudioStreamFormat();
        virtual ~AudioStreamFormat();

        void Init(int, int, int, int);
        int unk4, unk8, unkc, unk10;
    };
}

#endif
