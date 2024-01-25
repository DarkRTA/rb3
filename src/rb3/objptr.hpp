#ifndef RB3_OBJPTR_HPP
#define RB3_OBJPTR_HPP
#include "hmx/object.hpp"

template <class T1, class T2> class ObjPtr : public ObjRef {
public:

    ObjPtr(Hmx::Object* obj, T1* cls){
        owner = obj;
        unk8 = cls;
        if(cls != 0){
            cls->AddRef(this);
        }
    }

    virtual ~ObjPtr(){
        if(unk8 != 0) unk8->Release(this);
    }

    virtual Hmx::Object* RefOwner(){ 
        return owner; 
    }

    virtual void Replace(Hmx::Object* o1, Hmx::Object* o2){
        if (unk8 == o1) {
            *this = dynamic_cast<T1*>(o2);
        }
    }

    virtual int IsDirPtr(){
        return 0; // StubZero
    }

    void operator=(T1* t){
        if(unk8 != t){
            if(unk8 != 0) unk8->Release(this);
            unk8 = t;
            if(t != 0) t->AddRef(this);
        }
    }

    Hmx::Object* owner;
    T1* unk8;
};

#endif
