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

    T1* Ptr(){ return mPtr; }
    operator T1*() const { return mPtr; }
    T1* operator->() const { return mPtr; }

    void operator=(T1* t){
        if(t != mPtr){
            if(mPtr != 0) mPtr->Release(this);
            mPtr = t;
            if(mPtr != 0) mPtr->AddRef(this);
        }
    }

    void operator=(const ObjPtr<T1, T2>& oPtr){ *this = (T1*)oPtr; }
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

template <class T1> BinStream& operator>>(BinStream& bs, ObjPtr<T1, class ObjectDir>& ptr){
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

    T1* Ptr(){ return mPtr; }
    operator T1*() const { return mPtr; }
    T1* operator->() const {
        MILO_ASSERT(mPtr, 0xAB);
        return mPtr;
    }

    void operator=(T1* t){
        if(t != mPtr){
            if(mPtr != 0) mPtr->Release(mOwner);
            mPtr = t;
            if(mPtr != 0) mPtr->AddRef(mOwner);
        }
    }

    void operator=(const ObjOwnerPtr<T1, T2>& oPtr){ *this = (T1*)oPtr; }

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

template <class T1> BinStream& operator>>(BinStream& bs, ObjOwnerPtr<T1, class ObjectDir>& ptr){
    ptr.Load(bs, true, 0);
    return bs;
}

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

        void operator delete(void* v){
            _PoolFree(sizeof(Node), FastPool, v);
        }
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
    int mSize : 24;
    ObjListMode mMode : 8;
    
    ObjPtrList(Hmx::Object* owner, ObjListMode mode) : mNodes(0), mOwner(owner), mSize(0), mMode(mode) {
        if(mode == kObjListOwnerControl){
            MILO_ASSERT(owner, 0xFC);
        }
    }

    virtual ~ObjPtrList() { clear(); }
    virtual Hmx::Object* RefOwner(){ return mOwner; }

    virtual void Replace(Hmx::Object* from, Hmx::Object* to){
        if(mMode == kObjListOwnerControl){
            mOwner->Replace(from, to);
            return;
        }
        else {
            Node* it = mNodes;
            while(it != 0){
                if(it->obj == from){
                    if(mMode == kObjListNoNull && !to){
                        Node* next = unlink(it);
                        delete it;
                        it = next;
                        continue;
                    }
                    else {
                        from->Release(this);
                        it->obj = dynamic_cast<T1*>(to);
                        if(to) to->AddRef(this);
                    }
                }
                it = it->next;
            }
        }
    }

    virtual bool IsDirPtr(){ return 0; }

    void clear(){ while(mSize != 0) pop_back(); }

    // found from RB2
    // Set, __as

    // https://decomp.me/scratch/ESkuY
    // push_back__36ObjPtrList<11RndDrawable,9ObjectDir>FP11RndDrawable
    // fn_8049C424 - push_back
    void push_back(T1* obj){
        iterator it;
        insert(it, obj);
    }

    void pop_back(){
        MILO_ASSERT(mNodes, 0x16D);
        remove(mNodes->prev);
    }

    iterator remove(iterator it){
        Node* unlinked = unlink(it.mNode);
        delete it.mNode;
        return unlinked;
    }

    // unlink__36ObjPtrList<11RndDrawable,9ObjectDir>F P Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 4Node
    // fn_80389E34 in RB3 retail
    Node* unlink(Node* n){
        MILO_ASSERT(n && mNodes, 0x24D);
        if(n->obj) n->obj->Release(this);
        if(n == mNodes){
            if(mNodes->next != 0){
                mNodes->next->prev = mNodes->prev;
                mNodes = mNodes->next;
            }
            else mNodes = 0;
            n = mNodes;
        }
        else if(n == mNodes->prev){
            mNodes->prev = mNodes->prev->prev;
            mNodes->prev->next = 0;
            n = mNodes->prev;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            n = n->next;
        }
        mSize--;
        return n;
    }

    T1* front() const {
        MILO_ASSERT(mNodes, 0x167);
        return mNodes->obj;
    }

    T1* back() const {
        MILO_ASSERT(mNodes, 0x16C);
        return mNodes->prev->obj;
    }

    bool empty() const { return mSize == 0; }
    iterator& begin() const { return *reinterpret_cast<iterator*>(mNodes); }
    iterator& end() const { return *reinterpret_cast<iterator*>(0); }
    int size() const { return mSize; }

    // insert__36ObjPtrList<11RndDrawable,9ObjectDir>F Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 8iterator P11RndDrawable
    // fn_8049C470 - insert
    iterator& insert(iterator it, T1* obj) {
        if(mMode == kObjListNoNull)  MILO_ASSERT(obj, 0x15A);
        Node* node = new (_PoolAlloc(0xc, 0xc, FastPool))(Node);
        node->obj = obj;
        link(it, node);
        return it;
    }

    // link__36ObjPtrList<11RndDrawable,9ObjectDir>F Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 8iterator P Q2 36ObjPtrList<11RndDrawable,9ObjectDir> 4Node
    void link(iterator it, Node* n) {
        Node*& itNode = it.mNode;
        
        if (n->obj) {
            n->obj->AddRef(this);
        }
        n->next = itNode;

        if (itNode == mNodes) { // mNodes = ivar1, itNode = ivar2

            if (mNodes) {
                n->prev = mNodes->prev;
                mNodes->prev = n;
            } else {
                n->prev = n;
            }

            mNodes = n;
        } else if (!itNode) {
            n->prev = mNodes->prev;
            mNodes->prev->next = n;
            mNodes->prev = n;
        } else {
            n->prev = itNode->prev;
            itNode->prev->next = n;
            itNode->prev = n;
        }

        int size = mSize;
        int tmpSize = size + 1;
        MILO_ASSERT(tmpSize < 8388607, 0x244);
        mSize = size + 1;
    }

    // ObjPtrList<EventTrigger, ObjectDir>::operator=(const ObjPtrList<EventTrigger, ObjectDir>&)
    // ObjPtrList<RndPartLauncher, ObjectDir>::operator=(const ObjPtrList<RndPartLauncher, ObjectDir>&)
    // fn_80453DC4 in retail
    // Set__37ObjPtrList<12EventTrigger,9ObjectDir> F Q2 37ObjPtrList<12EventTrigger,9ObjectDir> 8iterator P12EventTrigger
    // ObjPtrList::Set(iterator, T1*)
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

    void Set(iterator it, T1* obj){
        if(mMode == kObjListNoNull) MILO_ASSERT(obj, 0x14E);
        if(it.mNode->obj) it.mNode->obj->Release(this);
        it.mNode->obj = obj;
        if(it.mNode->obj) it.mNode->obj->AddRef(this);
    }

    void operator=(const ObjPtrList<T1, T2>& x){
        if(this == &x) return;
        while(size() > x.size()) pop_back();
        Node* otherNodes = x.mNodes;
        for(Node* curNodes = mNodes; curNodes != 0; curNodes = curNodes->next){
            Set(curNodes, otherNodes->obj);
            otherNodes = otherNodes->next;
        }
        for(; otherNodes != 0; otherNodes = otherNodes->next){
            push_back(otherNodes->obj);
        }
    }

    // fn_8049C308 in retail
    bool Load(BinStream& bs, bool b){
        bool ret = true;
        clear();
        int count;
        bs >> count;
        class ObjectDir* dir = 0;
        if(mOwner) dir = mOwner->Dir();
        MILO_ASSERT(dir, 0x207);
        for(; count != 0; count--){
            char buf[0x80];
            bs.ReadString(buf, 0x80);
            if(dir){
                T1* casted = dynamic_cast<T1*>(dir->FindObject(buf, false));
                if(!casted && buf[0] != '\0'){
                    if(b) MILO_WARN("%s couldn't find %s in %s", PathName(mOwner), buf, PathName(dir));
                    ret = false;
                }
                else if(casted){
                    push_back(casted);
                }
            }
        }
        return ret;
    }

};

// __rs<Q23Hmx6Object>__F R9BinStream R36ObjPtrList<Q23Hmx6Object,9ObjectDir> _R9BinStream
// fn_8049C2CC in retail
template <class T1> BinStream& operator>>(BinStream& bs, ObjPtrList<T1, class ObjectDir>& ptr){
    ptr.Load(bs, true);
    return bs;
}

// END OBJPTRLIST TEMPLATE -----------------------------------------------------------------------------

#endif
