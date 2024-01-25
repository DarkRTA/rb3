#ifndef RB3_OBJOWNERPTR_HPP
#define RB3_OBJOWNERPTR_HPP
#include "hmx/object.hpp"

template <class T1, class T2> class ObjOwnerPtr : public ObjRef {
public:

    ObjOwnerPtr(Hmx::Object* o, T1* item){
        parent = o;
        child = item;
        if(item != nullptr) item->AddRef(o);
    }

    virtual ~ObjOwnerPtr(){
        if(child != nullptr) child->Release(parent);
    }

    virtual Hmx::Object* RefOwner(){ 
        return parent; 
    }

    virtual void Replace(Hmx::Object*, Hmx::Object*){
        
    } // StubVoid

    virtual int IsDirPtr(){
        return 0; // StubZero
    }

    Hmx::Object* parent;
    T1* child;
};

#endif
