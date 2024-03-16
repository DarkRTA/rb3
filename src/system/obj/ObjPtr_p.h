#ifndef OBJ_OBJPTR_H
#define OBJ_OBJPTR_H
#include "obj/Object.h"
#include "os/Debug.h"
#include "obj/Dir.h"
#include "utl/BinStream.h"

// BEGIN OBJPTR TEMPLATE -------------------------------------------------------------------------------

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
        if (mPtr == o1) *this = dynamic_cast<T1*>(o2);
    }

    virtual bool IsDirPtr(){ return 0; }

    operator T1*() const { return mPtr; }
    T1* operator->() const { return mPtr; }

    void operator=(T1* t){
        if(t != mPtr){
            if(mPtr != 0) mPtr->Release(this);
            mPtr = t;
            if(mPtr != 0) mPtr->AddRef(this);
        }
    }

    void operator=(const ObjPtr<T1, T2>& oPtr){ *this = oPtr.operator->(); }
    operator bool() const { return mPtr != 0; }

    bool Load(BinStream& bs, bool b, ObjectDir* dir){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if(!dir && mOwner) dir = mOwner->Dir();
        if(mOwner && dir){
            *this = dynamic_cast<T1*>(dir->FindObject(buf, false));
            if(mPtr == 0 && buf[0] != '\0' && b){
                MILO_WARN("%s couldn't find %s in %s", PathName(mOwner), buf, PathName(dir));
            }
            return false;
        }
        else {
            *this = 0;
            if(buf[0] != '\0') MILO_WARN("No dir to find %s", buf);
        }
        return true;
    }

    Hmx::Object* mOwner;
    T1* mPtr;
};

template <class T1> BinStream& operator>>(BinStream& bs, ObjPtr<T1, ObjectDir>& ptr){
    ptr.Load(bs, true, 0);
    return bs;
}

// END OBJPTR TEMPLATE ---------------------------------------------------------------------------------

// BEGIN OBJOWNERPTR TEMPLATE --------------------------------------------------------------------------

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

// END OBJOWNERPTR TEMPLATE ----------------------------------------------------------------------------

// BEGIN OBJPTRLIST TEMPLATE ---------------------------------------------------------------------------

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
            return *reinterpret_cast<iterator*>(mNode);
        }

        bool operator!=(ObjPtrList<T1, T2>::iterator it){ return mNode != it.mNode; }

        struct Node* mNode;
    };

    Node* mNodes;
    Hmx::Object* mOwner;
    int mMask;
    // ObjListMode mMode;

    // https://decomp.me/scratch/OIOhV
    ObjPtrList(Hmx::Object* owner, ObjListMode mode) : mNodes(0), mOwner(owner) {
        mMask = (mode & 0xFF) | (mMask & 0xFFFFFF00);
        if(mode == kObjListOwnerControl){
            MILO_ASSERT(owner, 0xFC);
        }
    }

    virtual ~ObjPtrList() { 
        while(!empty()) pop_back();
    }

    virtual Hmx::Object* RefOwner(){ return mOwner; }
    virtual void Replace(Hmx::Object*, Hmx::Object*){
        
    }
    virtual bool IsDirPtr(){ return 0; }

    // found from RB2
    // Load, link, insert, Set
    // __as

    // push_back__36ObjPtrList<11RndDrawable,9ObjectDir>FP11RndDrawable
    // insert and link are inlined somewhere in here
    void push_back(T1* obj){
        // insert?
        if((mMask << 0x18 | (mMask >> 8) >> 0x18) == 0){
            MILO_ASSERT(obj, 0x15A);
        }
        Node* node = new (_PoolAlloc(0xc, 0xc, FastPool)) (Node);
        node->obj = obj;
        if(obj) obj->AddRef(this);
        node->next = 0;

        if(mNodes){
            node->prev = mNodes->prev;
            mNodes->prev->next = node;
            mNodes->prev = node;
        }
        else {
            node->prev = node;
            mNodes = node;
        }

        // link?
        int tmpSize = (mMask >> 8) + 1;
        MILO_ASSERT(tmpSize < 8388607, 0x244);
        mMask = ((((mMask >> 8) + 1) << 8) & 0xFFFFFF00) | (mMask & 0xFF);
    }

    // see pop_back__36ObjPtrList<11RndDrawable,9ObjectDir>Fv for reference
    // https://decomp.me/scratch/UBBvV
    void pop_back(){
        MILO_ASSERT(mNodes, 0x16D);
        Node* n = mNodes->prev;
        unlink(n);

        if(n == mNodes){
            if(mNodes->next != 0){
                mNodes->next->prev = mNodes->prev;
                mNodes = mNodes->next;
            }
            else mNodes = 0;
        }
        else if(n == mNodes->prev){
            mNodes->prev = mNodes->prev->prev;
            mNodes->prev->next = 0;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;
        }
        
        // decrease the size part of the bitmask by 1?
        // r0 = ((mMask >> 8) - 1)
        // r7 = ((r0<< 8) & 0xFFFFFF00) | (r7 & 0xFF);
        mMask = ((((mMask >> 8) - 1) << 8) & 0xFFFFFF00) | (mMask & 0xFF);
        // mMask = (((mMask >> 8) - 1) * 0x100) | (mMask & 0xFF);
        _PoolFree(0xc, FastPool, n);
    }    

    // unlink__36ObjPtrList<11RndDrawable,9ObjectDir>F P Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 4Node
    void unlink(Node* n){
        MILO_ASSERT(n && mNodes, 0x24D);
        if(n->obj) n->obj->Release(this);
    }

    T1* front() const {
        MILO_ASSERT(mNodes, 0x167);
        return mNodes->obj;
    }

    T1* back() const {
        MILO_ASSERT(mNodes, 0x16C);
        return mNodes->prev->obj;
    }

    bool empty() const {
        return (mMask >> 8) == 0;
    }

    iterator& begin() const {
        return *reinterpret_cast<iterator*>(mNodes);
    }

    iterator& end() const {
        return *reinterpret_cast<iterator*>(0);
    }

    int size() const {
        return mMask >> 8;
    }

    // insert__36ObjPtrList<11RndDrawable,9ObjectDir>F Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 8iterator P11RndDrawable
    void insert(iterator, T1*);

    // link__36ObjPtrList<11RndDrawable,9ObjectDir>F Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 8iterator P Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 4Node
    void link(iterator, Node*);

    // ObjPtrList<EventTrigger, ObjectDir>::operator=(const ObjPtrList<EventTrigger, ObjectDir>&)
    // ObjPtrList<RndPartLauncher, ObjectDir>::operator=(const ObjPtrList<RndPartLauncher, ObjectDir>&)
    // __as__37ObjPtrList<12EventTrigger,9ObjectDir>FRC37ObjPtrList<12EventTrigger,9ObjectDir>
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

// END OBJPTRLIST TEMPLATE -----------------------------------------------------------------------------

#endif
