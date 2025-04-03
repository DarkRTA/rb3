#pragma once
#include "Platform/RootObject.h"

namespace Quazal {

    template <class T>
    class DefaultChainPolicy {
    public:
    };

    template <class T, class X = DefaultChainPolicy<T> >
    class qChain : public RootObject {
    public:
        class iterator {
        public:
            iterator() : mLink(0) {}

            T mLink; // 0x0
        };

        qChain() : mNBLinks(0) {}
        ~qChain() { clear(); }

        void clear();
        void erase(iterator);
        void push_back(const T &item) {
            if (mItFirst.mLink == mItEnd.mLink) {
                mItFirst.mLink = item;
                mItLast.mLink = item;
            } else {
                mItFirst.mLink = item;
            }
            mNBLinks++;
        }
        void push_front(const T &);

        iterator mItFirst; // 0x0
        iterator mItLast; // 0x4
        iterator mItEnd; // 0x8
        unsigned long mNBLinks; // 0xc
    };
}