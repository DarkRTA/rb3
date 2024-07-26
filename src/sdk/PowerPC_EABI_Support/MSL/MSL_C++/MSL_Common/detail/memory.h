#ifndef _MSL_DETAILS_MEMORY
#define _MSL_DETAILS_MEMORY

#include <MSL_C++/typeinfo>
#include "MSL_C++/MSL_Common/detail/pair.h"

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

    namespace tr1 {
        namespace detail {

            class shared_ptr_deleter_common {
            public:
                virtual ~shared_ptr_deleter_common() = 0;
                // Return type is most definitely not correct
                virtual void *get_deleter(const std::type_info &info) = 0;

            protected:
                virtual void dispose() = 0;

            public:
                __attribute__((never_inline)) void release() {
                    if (--m_RefCount == 0) {
                        dispose();
                        if (--m_ActiveCount == 0) {
                            delete this;
                        }
                    }
                }

                int m_RefCount;
                int m_ActiveCount;
            };

            template <typename T, typename Deleter = std::detail::default_delete<T> >
            class shared_ptr_deleter : public shared_ptr_deleter_common {
            public:
                shared_ptr_deleter(T *ptr) : m_Ptr(ptr) {}
                ~shared_ptr_deleter() {}

                void *get_deleter(const std::type_info &info) {
                    if (info == typeid(Deleter)) {
                        return &m_Ptr.second();
                    }

                    return nullptr;
                }

            protected:
                void dispose() { m_Ptr.second()(m_Ptr.first()); }

            private:
                Metrowerks::compressed_pair<T *, Deleter> m_Ptr;
            };

        }
    }

    namespace detail {

        template <typename T>
        class __ptr_base {
        protected:
            __ptr_base(T *ptr, tr1::detail::shared_ptr_deleter_common *deleter)
                : m_Ptr(ptr), m_Deleter(deleter) {}

        public:
            ~__ptr_base() throw() {
                if (m_Deleter) {
                    m_Deleter->release();
                }
            }

            T *get() const { return m_Ptr; }

        protected:
            T *m_Ptr;
            tr1::detail::shared_ptr_deleter_common *m_Deleter;
        };

        template <typename T>
        class shared_ptr : public __ptr_base<T> {
        public:
            shared_ptr() throw();

            template <typename Y>
            explicit shared_ptr(Y *ptr)
                : __ptr_base(ptr, new tr1::detail::shared_ptr_deleter<Y>(ptr)) {}
        };

    }
}

#endif
