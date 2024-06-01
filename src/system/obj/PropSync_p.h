#ifndef OBJ_PROPSYNC_H
#define OBJ_PROPSYNC_H
#include "math/Color.h"
#include "math/Sphere.h"
#include "math/Mtx.h"
#include "math/Vec.h"
#include "utl/FilePath.h"
#include "utl/Symbol.h"
#include "os/Debug.h"
#include "math/Geo.h"
#include <list>

enum PropOp {
    kPropGet = 1,
    kPropSet = 2,
    kPropInsert = 4,
    kPropRemove = 8,
    kPropSize = 16,
    kPropHandle = 32,
};

// forward declarations
template<class T1, class T2> class ObjPtr;
template<class T1, class T2> class ObjOwnerPtr;
template<class T1, class T2> class ObjPtrList;
template<class T1, class T2 = u16> class ObjVector;

bool PropSync(class String&, DataNode&, DataArray*, int, PropOp);
bool PropSync(FilePath&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Color&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Matrix3&, DataNode&, DataArray*, int, PropOp);
bool PropSync(class Sphere&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector2&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector3&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Transform&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Rect&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Box&, DataNode&, DataArray*, int, PropOp);

inline bool PropSync(float& f, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x17);
    if(op == kPropGet) node = DataNode(f);
    else f = node.Float(0);
    return true;
}

inline bool PropSync(int& iref, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x2C);
    if(op == kPropGet) node = DataNode(iref);
    else iref = node.Int(0);
    return true;
}

inline bool PropSync(bool& b, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x40);
    if(op == kPropGet) node = DataNode(b);
    else b = node.Int(0) != 0;
    return true;
}

inline bool PropSync(Symbol& sym, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x4A);
    if(op == kPropGet) node = DataNode(sym);
    else sym = node.Str(0);
    return true;
}

template <class T> inline bool PropSync(T*& obj, DataNode& node, DataArray* prop, int i, PropOp op){
    if((int)op == 0x40) return false;
    else {
        MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x58);
        if(op == kPropGet) node = DataNode((Hmx::Object*)obj);
        else obj = node.Obj<T>(0);
        return true;
    }
}

template <class T> bool PropSync(ObjPtr<T, class ObjectDir>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if((int)op == 0x40) return false;
    else {
        MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x125);
        if(op == kPropGet) node = DataNode(ptr.Ptr());
        else ptr = node.Obj<T>(0);
        return true;
    }
}

template <class T> bool PropSync(ObjOwnerPtr<T, class ObjectDir>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if((int)op == 0x40) return false;
    else {
        MILO_ASSERT(op <= kPropInsert, 0x132);
        if(op == kPropGet) node = DataNode(ptr.Ptr());
        else ptr = node.Obj<T>(0);
        return true;
    }
}

// fn_805E3988 - PropSync(ObjPtrList<Sequence>&) - used in EventTrigger.cpp
// fn_80642860 - PropSync(ObjPtrList&, ...)
template <class T> bool PropSync(ObjPtrList<T, class ObjectDir>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if((int)op == 0x40) return ptr.mMode == kObjListNoNull;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x146);
        node = DataNode(ptr.size());
        return true;
    }
    else {
        ObjPtrList<T, class ObjectDir>::iterator it = ptr.begin();
        for(int cnt = prop->Int(i++); cnt >= 0; cnt--) ++it;
        MILO_ASSERT(i == prop->Size(), 0x150);
        if(op == kPropGet){
            // return PropSync(*it, node, prop, i, kPropGet); // supposed to call the Object PropSync template on line 67 but it doesn't for whatever reason
        }
        else if(op == kPropSet){

        }
        else if(op == kPropRemove){

        }
        else if(op == kPropInsert){

        }
        else return false;
    }
}

template <class T> bool PropSync(std::list<T>& pList, DataNode& node, DataArray* prop, int i, PropOp op)  {
    if((int)op == 0x40) return false;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 146);
        node = DataNode((int)pList.size());
        return true;
    }
    else {
        std::list<T>::iterator it = pList.begin();
        for(int count = prop->Int(i++); count > 0; count--){
            it++;
        }
        if(i < prop->Size() || op & 0x13){
            return PropSync(*it, node, prop, i, op);
        }
        else if(op == kPropRemove){
            pList.erase(it);
            return true;
        }
        else if(op == kPropInsert){
            T item;
            if(PropSync(item, node, prop, i, op)){
                pList.insert(it, item);
                return true;
            }
        }
        return false;
    }
}

template <class T, typename T2> bool PropSync(std::vector<T, T2>& vec, DataNode& node, DataArray* prop, int i, PropOp op)  {
    if((int)op == 0x40) return false;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 146);
        node = DataNode((int)vec.size());
        return true;
    }
    else {
        std::vector<T, T2>::iterator it = vec.begin() + prop->Int(i++);
        if(i < prop->Size() || op & 0x13){
            return PropSync(*it, node, prop, i, op);
        }
        else if(op == kPropRemove){
            vec.erase(it);
            return true;
        }
        else if(op == kPropInsert){
            T item;
            if(PropSync(item, node, prop, i, op)) vec.insert(it, item);
            return true;
        }
        else return false;
    }
}

template <class T, typename T2> bool PropSync(ObjVector<T, T2>& objVec, DataNode& node, DataArray* prop, int i, PropOp op)  {
    if((int)op == 0x40) return false;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x17F);
        node = DataNode((int)objVec.size());
        return true;
    }
    else {
        std::vector<T, T2>::iterator it = objVec.begin() + prop->Int(i++);
        if(i < prop->Size() || op & 0x13){
            return PropSync(*it, node, prop, i, op);
        }
        else if(op == kPropRemove){
            objVec.erase(it);
            return true;
        }
        else if(op == kPropInsert){
            T item(objVec.Owner());
            if(PropSync(item, node, prop, i, kPropInsert)){
                objVec.insert(it, item);
                return true;
            }
        }
        return false;
    }
}

#endif
