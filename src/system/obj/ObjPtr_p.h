#ifndef OBJ_OBJPTR_H
#define OBJ_OBJPTR_H
#include "obj/Object.h"
#include "utl/BinStream.h"

template <class T1, class T2> class ObjPtr : public ObjRef {
public:

    ObjPtr(Hmx::Object* obj, T1* cls) : mOwner(obj), mPtr(cls) {
        if(mPtr != 0) mPtr->AddRef(this);
    }

    virtual ~ObjPtr(){
        if(mPtr != 0) mPtr->Release(this);
    }

    virtual Hmx::Object* RefOwner(){ return mOwner; }

    virtual void Replace(Hmx::Object* o1, Hmx::Object* o2){
        if (mPtr == o1)
            *this = dynamic_cast<T1*>(o2);
    }

    virtual bool IsDirPtr(){ return 0; }

    void operator=(T1* t){
        if(t != mPtr){
            if(mPtr != 0) mPtr->Release(this);
            mPtr = t;
            if(t != 0) t->AddRef(this);
        }
    }

    Hmx::Object* mOwner;
    T1* mPtr;
};

template <class T> BinStream& operator>>(BinStream&, ObjPtr<T, ObjectDir>&);

template <class T1, class T2> class ObjOwnerPtr : public ObjRef {
public:

    ObjOwnerPtr(Hmx::Object* obj, T1* cls): mOwner(obj), mPtr(cls) {
        if(mPtr != 0) mPtr->AddRef(this);
    }

    virtual ~ObjOwnerPtr(){
        if(mPtr != 0) mPtr->Release(mOwner);
    }

    virtual Hmx::Object* RefOwner(){ return mOwner; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){ }
    virtual bool IsDirPtr(){ return 0; }

    Hmx::Object* mOwner;
    T1* mPtr;
};

enum ObjListMode {
    kObjListNoNull,
    kObjListAllowNull,
    kObjListOwnerControl
};

template <class T1, class T2> class ObjPtrList : public ObjRef {
public:
    struct Node {
        T1* obj;
        struct Node* next;
        struct Node* prev;
    };

    int mSize;
    Node* mNodes;
    Hmx::Object* mOwner;
    ObjListMode mMode;    

    // ObjPtrList(Hmx::Object* obj, T2* cls): mPtr(cls) { }
    // virtual ~ObjPtrList() { }

    // virtual Hmx::Object* RefOwner(){ return NULL; }
    // virtual void Replace(Hmx::Object*, Hmx::Object*){ }
    // virtual bool IsDirPtr(){ return 0; }
};

#endif
