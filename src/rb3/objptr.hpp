#ifndef RB3_OBJPTR_HPP
#define RB3_OBJPTR_HPP
#include "Object.h"

template <class T1, class T2> class ObjPtr : public ObjRef {
public:

    ObjPtr(Hmx::Object* obj, T1* cls){
        parent = obj;
        child = cls;
        if(cls != 0){
            cls->AddRef(this);
        }
    }

    virtual ~ObjPtr(){
        if(child != 0) child->Release(this);
    }

    virtual Hmx::Object* RefOwner(){ 
        return parent; 
    }

    virtual void Replace(Hmx::Object* o1, Hmx::Object* o2){
        if (child == o1) {
            *this = dynamic_cast<T1*>(o2);
        }
    }

    virtual bool IsDirPtr(){
        return 0; // StubZero
    }

    void operator=(T1* t){
        if(child != t){
            if(child != 0) child->Release(this);
            child = t;
            if(t != 0) t->AddRef(this);
        }
    }

    Hmx::Object* parent;
    T1* child;
};

#endif
