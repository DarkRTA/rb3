#ifndef OBJ_OBJVECTOR_H
#define OBJ_OBJVECTOR_H
#include "types.h"
#include <vector>
#include "utl/BinStream.h"

namespace Hmx { class Object; }

template <class T1, typename T2 = u16> class ObjVector : public std::vector<T1, T2> {
public:
    ObjVector(Hmx::Object* o) : mOwner(o) {}
    Hmx::Object* mOwner;
    
    Hmx::Object* Owner(){ return mOwner; }
    
    void resize(unsigned long ul){
        std::vector<T1, T2>::resize(ul, T1(mOwner));
    }

    void push_back(const T1& t){
        resize(size() + 1);
        T1* last = &back();
        *last = t;
    }

    void operator=(const ObjVector<T1, T2>& vec){
        if(this != &vec){
            resize(vec.size());
            std::vector<T1,T2>::operator=((std::vector<T1,T2>&)vec);
        }
    }

};

template <class T1, class T2> BinStream& operator>>(BinStream& bs, ObjVector<T1, T2>& vec) {
    unsigned int length;
    bs >> length;
    vec.resize(length); // TODO: implement the ObjVector::resize override

    for(std::vector<T1, T2>::iterator it = vec.begin(); it != vec.end(); it++){
        // it->Load(bs);
        bs >> *it;
    }

    return bs;
}

#endif
