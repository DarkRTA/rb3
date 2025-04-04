#pragma once
#include "DOHandle.h"
#include "Platform/RootObject.h"
#include "Platform/qStd.h"

namespace Quazal {
    class Selection : public RootObject {
    public:
        Selection(unsigned char);
        virtual ~Selection();

        qMap<DOHandle, class DuplicatedObject *> m_map; // 0x4
        unsigned char m_byFlags; // 0x18;
    };
}