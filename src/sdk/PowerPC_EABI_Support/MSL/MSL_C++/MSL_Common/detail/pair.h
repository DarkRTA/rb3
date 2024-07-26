#ifndef _MSL_DETAILS_PAIR
#define _MSL_DETAILS_PAIR

#include "MSL_C++/MSL_Common/detail/type_traits.h"
#include "MSL_C++/MSL_Common/detail/type_manips.h"

namespace Metrowerks {

    namespace details {

        template <bool T1Empty, bool T2Empty, bool BothAreValue>
        struct compressed_pair_switch {
            static const int value = 0;
        };

        template <>
        struct compressed_pair_switch<true, false, true> {
            static const int value = 1;
        };

        template <>
        struct compressed_pair_switch<false, true, true> {
            static const int value = 2;
        };

        template <typename T1, typename T2>
        struct compressed_pair_selector {
            static const int value = compressed_pair_switch<
                is_empty<T1>::result,
                is_empty<T2>::result,
                is_value_type<T1>::result | is_value_type<T2>::result>::value;
        };

        template <bool T1Empty, bool T2Empty, bool BothAreValue>
        struct compressed_pair_ctor_args {
            static const int value = 0;
        };

        template <typename T1, typename T2, int C>
        class compressed_pair_imp {
        public:
            compressed_pair_imp(const T1 &first, const T2 &second)
                : m_First(first), m_Second(second) {}
            compressed_pair_imp(const T1 &first) : m_First(first) {}
            compressed_pair_imp(const T2 &second) : m_Second(second) {}

            T1 &first() { return m_First; }
            T2 &second() { return m_Second; }

        private:
            T1 m_First;
            T2 m_Second;
        };

        template <typename T1, typename T2, int C>
        class compressed_pair_imp<T1, T2, 1> : public T1 {
        public:
            compressed_pair_imp(const T1 &first, const T2 &second)
                : T1(first), m_Second(second) {}
            compressed_pair_imp(const T1 &first) : T1(first) {}
            compressed_pair_imp(const T2 &second) : m_Second(second) {}

            T1 &first() { return *this; }
            T2 &second() { return m_Second; }

        private:
            T2 m_Second;
        };

        template <typename T1, typename T2, int C>
        class compressed_pair_imp<T1, T2, 2> : public T2 {
        public:
            compressed_pair_imp(const T1 &first, const T2 &second)
                : m_First(first), T2(second) {}
            compressed_pair_imp(const T1 &first) : m_First(first) {}
            compressed_pair_imp(const T2 &second) : T2(second) {}

            T1 &first() { return m_First; }
            T2 &second() { return *this; }

        private:
            T1 m_First;
        };

    }

    // clang-format off: wastes space here
    template <typename T1, typename T2>
    struct compressed_pair
        : public details::compressed_pair_imp<T1, T2, details::compressed_pair_selector<T1, T2>::value>
    {
        // clang-format on
        compressed_pair(const T1 &first, const T2 &second)
            : compressed_pair_imp(first, second) {}
        compressed_pair(const T1 &first) : compressed_pair_imp(first) {}
        compressed_pair(const T2 &second) : compressed_pair_imp(second) {}
    };
}

#endif
