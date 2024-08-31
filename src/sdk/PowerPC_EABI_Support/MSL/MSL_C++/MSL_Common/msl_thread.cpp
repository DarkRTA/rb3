#include <MSL_C++/stdexcept>
#include "decomp.h"

void std::tr1::detail::shared_ptr_deleter_common::release()
{
    if (--m_RefCount == 0) {
        dispose();
        if (--m_WeakCount == 0) {
            delete this;
        }
    }
}
