#include "PseudoGlobalVariable.h"
#include "network/Core/PseudoGlobalVariable.h"

namespace Quazal {
    PseudoGlobalVariableRoot *PseudoGlobalVariableList::s_pVariableListHead;
    unsigned int PseudoGlobalVariableList::m_uiNbOfVariables;

    PseudoGlobalVariableList::PseudoGlobalVariableList() {}
    PseudoGlobalVariableList::~PseudoGlobalVariableList() {}

    void PseudoGlobalVariableList::AddVariable(PseudoGlobalVariableRoot *var) {
        PseudoGlobalVariableRoot *head = s_pVariableListHead;
        if (!s_pVariableListHead) {
            s_pVariableListHead = var;
            m_uiNbOfVariables = 1;
        } else {
            while (head->GetNext()) {
                head = head->GetNext();
            }
            head->SetNext(var);
            m_uiNbOfVariables++;
        }
    }

    void PseudoGlobalVariableList::RemoveVariable(PseudoGlobalVariableRoot *var) {
        if (s_pVariableListHead == var) {
            s_pVariableListHead = s_pVariableListHead->GetNext();
            var->SetNext(0);
            m_uiNbOfVariables--;
        } else {
            for (PseudoGlobalVariableRoot *it = s_pVariableListHead, *root = 0; it != 0;
                 root = it, it = it->GetNext()) {
                if (it == var) {
                    root->SetNext(it->GetNext());
                    var->SetNext(0);
                    m_uiNbOfVariables--;
                    return;
                }
            }
        }
    }
}