#pragma once
#include <list>
#include "utl/BinStream.h"

namespace Hmx {
    class Object;
}

template <class T>
class ObjList : public std::list<T> {
    typedef typename std::list<T> Base;

public:
    ObjList(Hmx::Object *o) : mOwner(o) {}
    Hmx::Object *mOwner;

    Hmx::Object *Owner() { return mOwner; }

    void resize(unsigned long ul) {
        Base &me = *this;
        me.resize(ul, T(mOwner));
    }

    void push_back() { resize(size() + 1); }

    void push_back(const T &t) {
        push_back();
        T &last = back();
        last = t;
    }

    void operator=(const ObjList &oList) {
        if (this != &oList) {
            resize(oList.size());
            Base::operator=((Base &)oList);
        }
    }
};

template <class T>
BinStream &operator>>(BinStream &bs, ObjList<T> &oList) {
    unsigned int length;
    bs >> length;
    oList.resize(length);

    for (std::list<T>::iterator it = oList.begin(); it != oList.end(); ++it) {
        bs >> *it;
    }
    return bs;
}
