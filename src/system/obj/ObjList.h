#ifndef OBJ_OBJLIST_H
#define OBJ_OBJLIST_H
#include <list>
#include "utl/BinStream.h"

namespace Hmx { class Object; }

template <class T> class ObjList : public std::list<T> {
public:
    ObjList(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner;

    Hmx::Object* Owner(){ return mOwner; }
    void operator=(const ObjList<T>& oList);
};

template <class T> BinStream& operator>>(BinStream& bs, ObjList<T>& oList) {
    unsigned int length;
    bs >> length;
    oList.resize(length, T(oList.mOwner));

    for(std::list<T>::iterator it = oList.begin(); it != oList.end(); ++it){
        bs >> *it;
    }
    return bs;
}

#endif