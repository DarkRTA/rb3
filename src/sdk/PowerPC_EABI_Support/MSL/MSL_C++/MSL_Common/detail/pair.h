#ifndef _MSL_DETAILS_PAIR
#define _MSL_DETAILS_PAIR

#include "MSL_C++/MSL_Common/type_traits.h"

namespace Metrowerks {

    namespace details {

        template <typename T1, typename T2, bool T1Empty, bool T2Empty>
        class compressed_pair_imp {
        public:
            compressed_pair_imp(const T1 &first, const T2 &second)
                : m_First(first), m_Second(second) {}
            compressed_pair_imp(const T1 &first) : m_First(first) {}
            compressed_pair_imp(const T2 &second) : m_Second(second) {}

            T1 &first() { return m_First; }
            const T1 &first() const { return m_First; }

            T2 &second() { return m_Second; }
            const T2 &second() const { return m_Second; }

        private:
            T1 m_First;
            T2 m_Second;
        };

        template <typename T1, typename T2, bool T2Empty>
        class compressed_pair_imp<T1, T2, true, T2Empty> : public T1 {
        public:
            compressed_pair_imp(const T1 &first, const T2 &second)
                : T1(first), m_Second(second) {}
            compressed_pair_imp(const T1 &first) : T1(first) {}
            compressed_pair_imp(const T2 &second) : m_Second(second) {}

            T1 &first() { return *this; }
            const T1 &first() const { return *this; }

            T2 &second() { return m_Second; }
            const T2 &second() const { return m_Second; }

        private:
            T2 m_Second;
        };

        template <typename T1, typename T2, bool T1Empty>
        class compressed_pair_imp<T1, T2, T1Empty, true> : public T2 {
        public:
            compressed_pair_imp(const T1 &first, const T2 &second)
                : m_First(first), T2(second) {}
            compressed_pair_imp(const T1 &first) : m_First(first) {}
            compressed_pair_imp(const T2 &second) : T2(second) {}

            T1 &first() { return m_First; }
            const T1 &first() const { return m_First; }

            T2 &second() { return *this; }
            const T2 &second() const { return *this; }

        private:
            T1 m_First;
        };

    }

    // clang-format off: wastes space here
    template <typename T1, typename T2>
    struct compressed_pair
        : public details::compressed_pair_imp<T1, T2, std::is_empty<T1>::value, std::is_empty<T2>::value>
    {
        // clang-format on
        compressed_pair(const T1 &first, const T2 &second)
            : compressed_pair_imp(first, second) {}
        compressed_pair(const T1 &first) : compressed_pair_imp(first) {}
        compressed_pair(const T2 &second) : compressed_pair_imp(second) {}
    };
}

#endif
