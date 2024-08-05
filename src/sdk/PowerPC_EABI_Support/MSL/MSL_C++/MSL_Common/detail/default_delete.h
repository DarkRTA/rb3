#ifndef _MSL_DETAILS_DEFAULT_DELETE
#define _MSL_DETAILS_DEFAULT_DELETE

namespace std {

    namespace detail {

        template <typename T>
        struct default_delete {
            void operator()(T *ptr) { delete ptr; }
        };

        template <typename T>
        struct default_delete<T[]> {
            void operator()(T ptr[]) { delete[] ptr; }
        };

    }

}

#endif
