#pragma once
#include "Core/InstantiationContext.h"
#include "Platform/RootObject.h"
#include "Platform/SystemError.h"
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

        bool
        AddInstanceToVector(InstanceControl *ic, unsigned int ui1, unsigned int ui2) {
            if (ui2 < m_pvContextVector->size()) {
                InstantiationContext *ctx = (*m_pvContextVector)[ui2];
                if (ctx) {
                    if (ctx->AddInstance(ic, ui1) == true) {
                        return true;
                    }
                } else {
                    SystemError::SignalError(0, 0, 0xe0000008, 0);
                    return false;
                }
            }
            SystemError::SignalError(0, 0, 0xe0000003, 0);
            return false;
        }

        bool
        DelInstanceFromVector(InstanceControl *ic, unsigned int ui, unsigned int idx) {
            return (*m_pvContextVector)[idx]->DelInstance(ic, ui);
        }

        unsigned int GetInstanceFromVector(unsigned int ui, unsigned int idx) {
            if (idx == 0) {
                return m_oDefaultContext.GetInstance(ui);
            } else if (idx >= m_pvContextVector->size()) {
                SystemError::SignalError(0, 0, 0xe0000003, 0);
                return -1;
            } else {
                return (*m_pvContextVector)[idx]->GetInstance(ui);
            }
        }

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