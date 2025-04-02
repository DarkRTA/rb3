#include "network/Core/PseudoGlobalVariable.h"

namespace Quazal {
    PseudoGlobalVariableList PseudoGlobalVariableRoot::s_oList;
    unsigned int Quazal::PseudoGlobalVariableRoot::s_uiNbOfExtraContexts = 1;

    PseudoGlobalVariableRoot::PseudoGlobalVariableRoot() : mNext(0) {}
    PseudoGlobalVariableRoot::~PseudoGlobalVariableRoot() {}
}