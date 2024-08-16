#ifndef _METROWERKS_PAIR
#define _METROWERKS_PAIR

#include "MSL_C++/MSL_Common/type_traits.h"
#include "MSL_C++/Metrowerks/type_traits.h"

namespace Metrowerks {

    namespace details {

        template <
            typename T1,
            typename T2,
            bool T1Empty = std::is_empty<T1>::value,
            bool T2Empty = std::is_empty<T2>::value>
        struct compressed_pair_selector {
            static const int value = 0;
        };

        template <typename T1, typename T2>
        struct compressed_pair_selector<T1, T2, true, false> {
            static const int value = 1;
        };

        template <typename T1, typename T2>
        struct compressed_pair_selector<T1, T2, false, true> {
            static const int value = 2;
        };

        template <typename T1, typename T2>
        struct compressed_pair_selector<T1, T2, true, true> {
            static const int value = 3;
        };

        template <typename T>
        struct compressed_pair_selector<T, T, false, false> {
            static const int value = 0;
        };

        template <typename T>
        struct compressed_pair_selector<T, T, true, true> {
            static const int value = 1;
        };

        // Note to future self: template signature must stay as-is for symbols
        template <
            typename T1,
            typename T2,
            int Selector = compressed_pair_selector<T1, T2>::value>
        class compressed_pair_imp {
        public:
            typedef typename Metrowerks::call_traits<T1>::param_type first_param;
            typedef typename Metrowerks::call_traits<T2>::param_type second_param;

            compressed_pair_imp() {}
            compressed_pair_imp(first_param first, second_param second)
                : m_First(first), m_Second(second) {}
            compressed_pair_imp(first_param first) : m_First(first) {}
            compressed_pair_imp(second_param second) : m_Second(second) {}

            T1 &first() { return m_First; }
            const T1 &first() const { return m_First; }

            T2 &second() { return m_Second; }
            const T2 &second() const { return m_Second; }

        private:
            T1 m_First;
            T2 m_Second;
        };

        template <typename T1, typename T2>
        class compressed_pair_imp<T1, T2, 1> : private T1 {
        public:
            typedef typename Metrowerks::call_traits<T1>::param_type first_param;
            typedef typename Metrowerks::call_traits<T2>::param_type second_param;

            compressed_pair_imp() {}
            compressed_pair_imp(first_param first, second_param second)
                : T1(first), m_Second(second) {}
            compressed_pair_imp(first_param first) : T1(first) {}
            compressed_pair_imp(second_param second) : m_Second(second) {}

            T1 &first() { return *this; }
            const T1 &first() const { return *this; }

            T2 &second() { return m_Second; }
            const T2 &second() const { return m_Second; }

        private:
            T2 m_Second;
        };

        template <typename T1, typename T2>
        class compressed_pair_imp<T1, T2, 2> : private T2 {
        public:
            typedef typename Metrowerks::call_traits<T1>::param_type first_param;
            typedef typename Metrowerks::call_traits<T2>::param_type second_param;

            compressed_pair_imp() {}
            compressed_pair_imp(first_param first, second_param second)
                : m_First(first), T2(second) {}
            compressed_pair_imp(first_param first) : m_First(first) {}
            compressed_pair_imp(second_param second) : T2(second) {}

            T1 &first() { return m_First; }
            const T1 &first() const { return m_First; }

            T2 &second() { return *this; }
            const T2 &second() const { return *this; }

        private:
            T1 m_First;
        };

    }

    template <typename T1, typename T2>
    struct compressed_pair : public details::compressed_pair_imp<T1, T2> {
        typedef typename details::compressed_pair_imp<T1, T2>::first_param first_param;
        typedef typename details::compressed_pair_imp<T1, T2>::second_param second_param;

        compressed_pair() {}
        compressed_pair(first_param first) : compressed_pair_imp(first) {}
        compressed_pair(second_param second) : compressed_pair_imp(second) {}
        compressed_pair(first_param first, second_param second)
            : compressed_pair_imp(first, second) {}
    };

}

#endif
