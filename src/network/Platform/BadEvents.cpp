#include "BadEvents.h"

namespace Quazal {
    int* BadEvents::s_pInstance;
    void BadEvents::Signal(BadEvents::_ID id) {
        if (s_pInstance) {
            s_pInstance[id]++;
        }
    }
}