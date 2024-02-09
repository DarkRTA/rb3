#ifndef OBJ_OBJPTR_H
#define OBJ_OBJPTR_H
#include "Object.h"

template <class T1, class T2> class ObjPtr : public ObjRef {
public:

    ObjPtr(Hmx::Object* obj, T1* cls) : mOwner(obj), mPtr(cls) {
        if(cls != 0) cls->AddRef(this);
    }

    virtual ~ObjPtr(){
        if(mPtr != 0) mPtr->Release(this);
    }

    virtual Hmx::Object* RefOwner(){ return mOwner; }

    virtual void Replace(Hmx::Object* o1, Hmx::Object* o2){
        if (mPtr == o1)
            *this = dynamic_cast<T1*>(o2);
    }

    virtual bool IsDirPtr(){ return 0; } // StubZero

    void operator=(T1* t){
        if(mPtr != t){
            if(mPtr != 0) mPtr->Release(this);
            mPtr = t;
            if(t != 0) t->AddRef(this);
        }
    }

    Hmx::Object* mOwner;
    T1* mPtr;
};

template <class T1, class T2> class ObjOwnerPtr : public ObjRef {
public:

    ObjOwnerPtr(Hmx::Object* obj, T1* cls): mOwner(obj), mPtr(cls) {
        if(cls != nullptr) cls->AddRef(obj);
    }

    virtual ~ObjOwnerPtr(){
        if(mPtr != nullptr) mPtr->Release(mOwner);
    }

    virtual Hmx::Object* RefOwner(){ return mOwner; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){ } // StubVoid
    virtual bool IsDirPtr(){ return 0; } // StubZero

    Hmx::Object* mOwner;
    T1* mPtr;
};

#endif
