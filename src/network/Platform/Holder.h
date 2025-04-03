#pragma once

namespace Quazal {
    template <class T>
    class Holder {
    public:
        Holder(T *ptr = 0) : mPtr(ptr) {}
        ~Holder() {
            if (mPtr)
                delete mPtr;
        }
        Holder &operator=(T *item) {
            if (mPtr)
                delete mPtr;
            mPtr = item;
            return *this;
        }

        operator T *() { return mPtr; }
        T *operator->() { return mPtr; }
        T *Ptr() { return mPtr; }

        T *mPtr; // 0x0
    };

    template <class T1, class T2>
    class AnyObjectHolder : public Holder<T1> {
    public:
        AnyObjectHolder(T1 *ptr = 0) : Holder(ptr) {}
        virtual ~AnyObjectHolder() {}

        AnyObjectHolder &operator=(T1 *item) {
            Holder<T1>::operator=(item);
            return *this;
        }
    };
}