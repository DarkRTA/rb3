#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"
#include "Platform/qChain.h"

namespace Quazal {
    class ThreadVariableRoot : public RootObject {
    public:
        ThreadVariableRoot();
        virtual ~ThreadVariableRoot();
        virtual void ResetValues();
        virtual void ClearValue();

        int unk4;
        int unk8;
    };

    class ThreadVariableList : public RootObject {
    public:
        ThreadVariableList() : m_csList(0) { s_isValid = true; }
        ~ThreadVariableList();

        static ThreadVariableList &GetInstanceRef();
        static bool s_isValid;

        qChain<int> m_tvList;
        CriticalSection m_csList;
    };

    template <class T>
    class ThreadVariable : public ThreadVariableRoot {
    public:
        ThreadVariable();
        virtual ~ThreadVariable();
        virtual void ResetValues();
        virtual void ClearValue();
    };
}