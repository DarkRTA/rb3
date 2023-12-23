#ifndef QUAZAL_STREAM_HPP
#define QUAZAL_STREAM_HPP
#include "rootobject.hpp"

namespace Quazal {
    class Stream : RootObject {
    public:
        enum Type {
            StreamType0,
            StreamType1,
            StreamType2
        };

        Stream(Type);
        virtual ~Stream();
        // 3 pure virtuals
        virtual void StreamUnk1() = 0;
        virtual void StreamUnk2() = 0;
        virtual void StreamUnk3() = 0;

        Type sType;
    };
}

#endif