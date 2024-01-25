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
        
    }

    virtual int IsDirPtr(); // StubZero

    ObjPtr* operator=(T1* t){
        return this;
    }

    Hmx::Object* owner;
    T1* unk8;
};

#endif
