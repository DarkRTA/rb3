#include "network/Platform/ThreadVariable.h"

namespace Quazal {

    ThreadVariableList::~ThreadVariableList() {}

    ThreadVariableList &ThreadVariableList::GetInstanceRef() {
        static ThreadVariableList sInstance;
        return sInstance;
    }

    void ThreadVariableRoot::ResetValues() {}
}