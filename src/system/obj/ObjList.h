#ifndef OBJ_OBJLIST_H
#define OBJ_OBJLIST_H
#include <list>
#include "utl/BinStream.h"
#include "obj/Object.h"

template <class T> class ObjList : public std::list<T> {
public:
    ObjList(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner;

    Hmx::Object* Owner(){ return mOwner; }
    void operator=(const ObjList<T>& oList);
};

template <class T> BinStream& operator>>(BinStream& bs, ObjList<T>& oList) {
    // unsigned int length;
    // bs >> length;
    // oList.resize(length); // TODO: implement the ObjVector::resize override

    // for(std::vector<T1, T2>::iterator it = vec.begin(); it != vec.end(); it++){
    //     // it->Load(bs);
    //     bs >> *it;
    // }

    return bs;
}

#endif