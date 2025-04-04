#pragma once
#include "Core/InstantiationContext.h"
#include "Platform/RootObject.h"
#include "Platform/qStd.h"

namespace Quazal {
    class InstanceControl;

    class InstanceTable : public RootObject {
    public:
        InstanceTable();
        ~InstanceTable();

        unsigned int GetHighestID() const;
        bool AddInstance(InstanceControl *, unsigned int, unsigned int);
        bool DelInstance(InstanceControl *, unsigned int, unsigned int);

        bool ContextIsValid(unsigned int ui) {
            if (ui == 0)
                return true;
            if (ui < m_pvContextVector->size() && (*m_pvContextVector)[ui])
                return true;
            return false;
        }

        static InstanceTable s_oInstanceTable;

        InstantiationContext m_oDefaultContext; // 0x0
        qVector<InstantiationContext *> *m_pvContextVector; // 0x30
    };
}