#pragma once
#include "InstanceTable.h"
#include "Platform/RootObject.h"

namespace Quazal {

    class InstanceControl : public RootObject {
    public:
        InstanceControl(unsigned int, unsigned int);
        virtual ~InstanceControl();

        void SetDelegatorInstance(void *);
        unsigned int GetHighestID();

        static bool ContextIsValid(unsigned int);
        static InstanceTable s_oInstanceTable;

        unsigned int m_icInstanceContext; // 0x4
        unsigned int m_icInstanceType; // 0x8
        void *m_pDelegatorInstance; // 0xc
        bool m_bIsValid; // 0x10
    };

};