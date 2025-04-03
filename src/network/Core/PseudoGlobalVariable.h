#pragma once
#include "Platform/MemoryManager.h"
#include "Platform/RootObject.h"
#include "Plugins/StreamSettings.h"

namespace Quazal {
    class PseudoGlobalVariableRoot;

    class PseudoGlobalVariableList : public RootObject {
    public:
        PseudoGlobalVariableList();
        virtual ~PseudoGlobalVariableList();

        void AddVariable(PseudoGlobalVariableRoot *);
        void RemoveVariable(PseudoGlobalVariableRoot *);

        static unsigned int m_uiNbOfVariables;
        static PseudoGlobalVariableRoot *s_pVariableListHead;
    };

    class PseudoGlobalVariableRoot : public RootObject {
    public:
        PseudoGlobalVariableRoot();
        virtual ~PseudoGlobalVariableRoot();
        virtual void AllocateExtraContexts() = 0;
        virtual void FreeExtraContexts() = 0;
        virtual void ResetContext(unsigned int) = 0;
        virtual PseudoGlobalVariableRoot *GetNext() = 0;
        virtual void SetNext(PseudoGlobalVariableRoot *) = 0;

        static PseudoGlobalVariableList s_oList;
        static unsigned int s_uiNbOfExtraContexts;

        PseudoGlobalVariableRoot *mNext; // 0x4
    };

    template <class T>
    class PseudoGlobalVariable : public PseudoGlobalVariableRoot {
    public:
        PseudoGlobalVariable(const T &item = T()) {
            mDefaultValue = item;
            mValueInDefaultContext = mDefaultValue;
            mValueInContextList = 0;
            s_oList.AddVariable(this);
            if (s_uiNbOfExtraContexts > 1) {
                AllocateExtraContexts();
            }
        }
        virtual ~PseudoGlobalVariable() {
            s_oList.RemoveVariable(this);
            FreeExtraContexts();
        }
        virtual void AllocateExtraContexts() {
            if (s_uiNbOfExtraContexts == -1) {
                mValueInContextList = new T[0xffffffc0];
            } else {
                mValueInContextList = (StreamSettings *)QUAZAL_DEFAULT_ALLOC(
                    s_uiNbOfExtraContexts * 0x50, 0x77, _InstType10
                );
            }
            for (int i = 0; i < s_uiNbOfExtraContexts; i++) {
                mValueInContextList[i] = T();
            }
        }
        virtual void FreeExtraContexts() {
            if (mValueInContextList) {
                for (int i = 0; i < s_uiNbOfExtraContexts; i++) {
                    mValueInContextList[i].~T();
                }
                QUAZAL_DEFAULT_FREE(mValueInContextList, _InstType10);
                mValueInContextList = 0;
            }
        }
        virtual void ResetContext(unsigned int idx) {
            mValueInContextList[idx] = mDefaultValue;
        }
        virtual PseudoGlobalVariableRoot *GetNext() { return mNext; }
        virtual void SetNext(PseudoGlobalVariableRoot *root) { mNext = root; }

        T *mValueInContextList;
        T mValueInDefaultContext;
        T mDefaultValue;
    };
}