#pragma once
#include "Platform/RootObject.h"

namespace Quazal {

    class InstanceControl : public RootObject {
    public:
        InstanceControl(unsigned int, unsigned int);
        virtual ~InstanceControl();

        unsigned int unk4;
        unsigned int unk8;
        int unkc;
        bool unk10;
    };

};