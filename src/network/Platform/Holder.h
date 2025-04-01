#pragma once

namespace Quazal {
    template <class T>
    class Holder {
    public:
        Holder(T *ptr = nullptr) : mPtr(ptr) {}
        T *mPtr; // 0x0
    };

    template <class T1, class T2>
    class AnyObjectHolder : public Holder<T1> {
    public:
        AnyObjectHolder(T1 *ptr = nullptr) : Holder(ptr) {}
        virtual ~AnyObjectHolder() {}
    };
}