#pragma once
#include "Platform/RootObject.h"
#include <cstddef>

namespace Quazal {
    class InstanceControl;

    class InstantiationContext : public RootObject {
    public:
        InstantiationContext();
        ~InstantiationContext();
        bool AddInstance(InstanceControl *, unsigned int);
        bool DelInstance(InstanceControl *, unsigned int);
        unsigned int GetInstance(unsigned int);

        void InitContext() {
            for (int i = 0; i < 11; i++) {
                m_icInstanceContext[i] = nullptr;
            }
        }

        InstanceControl *m_icInstanceContext[11]; // 0x0
        bool m_IsValid; // 0x2c
    };
}