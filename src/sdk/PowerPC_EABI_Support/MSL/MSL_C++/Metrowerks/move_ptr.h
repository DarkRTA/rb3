#ifndef _METROWERKS_MOVE_PTR
#define _METROWERKS_MOVE_PTR

#include "MSL_C++/MSL_Common/detail/default_delete.h"

namespace Metrowerks {

    template <typename T, typename Deleter = std::detail::default_delete<T> >
    class move_ptr {
    public:
        ~move_ptr() {
            if (m_Ptr.first()) {
                m_Ptr.second()(m_Ptr.first());
            }
        }

    private:
        Metrowerks::compressed_pair<T *, Deleter> m_Ptr;
    };

}

#endif
