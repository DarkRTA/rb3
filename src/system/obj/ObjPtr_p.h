#ifndef OBJ_OBJPTR_H
#define OBJ_OBJPTR_H
#include "obj/Object.h"
#include "os/Debug.h"
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

    // T1* operator T1*() const { return mPtr; }
    T1* operator->() const { return mPtr; }

    void operator=(T1* t){
        if(t != mPtr){
            if(mPtr != 0) mPtr->Release(this);
            mPtr = t;
            if(t != 0) t->AddRef(this);
        }
    }

    void operator=(const ObjPtr<T1, T2>& oPtr){
        *this = oPtr.operator->();
    }

    operator bool() const {
        return mPtr != 0;
    }

    Hmx::Object* mOwner;
    T1* mPtr;
};

template <class T> BinStream& operator>>(BinStream&, ObjPtr<T, ObjectDir>&);

template <class T1, class T2> class ObjOwnerPtr : public ObjRef {
public:

    ObjOwnerPtr(Hmx::Object* obj, T1* cls): mOwner(obj), mPtr(cls) {
        if(mPtr != 0) mPtr->AddRef(mOwner);
    }

    virtual ~ObjOwnerPtr(){
        if(mPtr != 0) mPtr->Release(mOwner);
    }

    virtual Hmx::Object* RefOwner(){ return mOwner; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){ 
        MILO_FAIL("Should go to owner");
    }
    virtual bool IsDirPtr(){ return 0; }

    T1* operator->() const { return mPtr; }

    void operator=(T1* t){
        if(t != mPtr){
            if(mPtr != 0) mPtr->Release(mOwner);
            mPtr = t;
            if(t != 0) t->AddRef(mOwner);
        }
    }

    void operator=(const ObjOwnerPtr<T1, T2>& oPtr){
        *this = oPtr.operator->();
    }

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

    class iterator {
    public:
        // if you wanna check the iterator methods in objdiff, go to CharHair.cpp
        // CharHair.cpp has plenty of ObjPtr and ObjPtrList methods for you to double check
        
        iterator() : mNode(0) {}
        iterator(Node* node) : mNode(node) {}
        iterator(const ObjPtrList<T1, T2>::iterator& it){ mNode = it.mNode; }
        T1* operator*(){ return mNode->obj; }

        iterator& operator++(){
            mNode = mNode->next;
            return *this;
        }

        bool operator!=(ObjPtrList<T1, T2>::iterator it){ return mNode != it.mNode; }

        // insert__36ObjPtrList<11RndDrawable,9ObjectDir>F Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 8iterator P11RndDrawable
        void insert(T1*);

        // link__36ObjPtrList<11RndDrawable,9ObjectDir>F Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 8iterator P Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 4Node
        void link(Node*);

        struct Node* mNode;
    };

    Node* mNodes;
    Hmx::Object* mOwner;
    ObjListMode mMode;    

    ObjPtrList(Hmx::Object* obj, ObjListMode mode) : mNodes(0), mOwner(obj), mMode(mode) {}

    virtual ~ObjPtrList() { }
    // sample ObjPtrList dtor from RB3 retail
    // /* __thiscall ObjPtrList<Fader,ObjectDir>::~ObjPtrList(void) */

    // ObjPtrList<> * __thiscall ObjPtrList<>::~ObjPtrList(ObjPtrList<> *this)

    // {
    // int in_r4;
    
    // if (this != (ObjPtrList<> *)0x0) {
    //     *(undefined ***)this = &__vtable;
    //     fn_806703D0(); // presumably pop_back?
    //     fn_8000DD10(this,0); // generic dtor
    //     if (0 < in_r4) {
    //     delete(this);
    //     }
    // }
    // return this;
    // }

    virtual Hmx::Object* RefOwner(){ return mOwner; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){
        
    }
    virtual bool IsDirPtr(){ return 0; }

    // found from RB2
    // Load, link, insert, Set, unlink, pop_back
    // empty, size, front, begin, end, push_back
    // __as

    // see pop_back__36ObjPtrList<11RndDrawable,9ObjectDir>Fv for reference
    // https://decomp.me/scratch/UBBvV
    void pop_back(){
        MILO_ASSERT(mNodes, 0x16D);

        Node* n = mNodes->prev;
        unlink(n);

        // n = pivar4 here
        if(n == mNodes){
            if(mNodes->next != 0){
                mNodes->next->prev = mNodes->prev;
                mNodes = mNodes->next;
            }
            else {
                mNodes = 0;
            }
        }
        else if(n == mNodes->prev){
            mNodes->prev = mNodes->prev->prev;
            mNodes->prev->next = 0;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;
        }

        *(int*)&mMode = (((*(int*)&mMode >> 8) - 1) * 0x100) | (*(int*)&mMode & 0xff);
        // mMode = (mMode == kObjListNoNull) ? kObjListAllowNull : kObjListOwnerControl;
        // mMode = kObjListAllowNull;
        // some sort of ObjListMode modification
        // *(uint *)(this + 0xc) = (((int)*(uint *)(this + 0xc) >> 8) + -1) * 0x100 | *(uint *)(this + 0xc) & 0xff;
        _PoolFree(0xc, FastPool, n);
    }    

    // unlink__36ObjPtrList<11RndDrawable,9ObjectDir>F P Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 4Node
    void unlink(Node* n){
        MILO_ASSERT(n && mNodes, 0x24D);
        if(n->obj) n->obj->Release(this);
    }

    T1* back() const {
        MILO_ASSERT(mNodes, 0x16C);
        return mNodes->prev->obj;
    }

    bool empty() const {
        return (mMode >> 8) == kObjListNoNull;
    }

    iterator begin() const {
        iterator it(mNodes);
        return it;
    }

    iterator end() const {
        return 0;
    }

    int size() const {
        return mMode >> 8;
    }

    // // Range: 0x80377A54 -> 0x80377ABC
    // class RndTransformable * ObjPtrList::front(const class ObjPtrList * const this /* r31 */) {
    //     // References
    //     // -> class Debug TheDebug;
    //     /

    //     // Range: 0x8040DBA4 -> 0x8040DEF0
    // void ObjPtrList::__as(class ObjPtrList * const this /* r29 */, const class ObjPtrList & x /* r30 */) {
    //     // Local variables
    //     struct Node * to; // r28
    //     struct Node * from; // r31

    //     // References
    //     // -> class Debug TheDebug;
    //     // -> const char * kAssertStr;
    // }
};

#endif
