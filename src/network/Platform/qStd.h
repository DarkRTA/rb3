#pragma once
#include "network/Platform/qMemAllocator.h"
#include "Platform/RootObject.h"
#include "utl/VectorSizeDefs.h"
#include <vector>
#include <list>
#include <map>

namespace Quazal {

    template <class T VECTOR_SIZE_DFLT_PARAM>
    class qVector : public std::vector<T VECTOR_SIZE_ARG, MemAllocator<T> > {
    public:
    };

    template <class T>
    class qList : public std::list<T, MemAllocator<T> >, public RootObject {
    public:
    };

    template <class T1, class T2>
    class qMap
        : public std::map<T1, T2, std::less<T1>, MemAllocator<std::pair<const T1, T2> > >,
          public RootObject {
    public:
    };

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