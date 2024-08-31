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
    kPropUnknown0x40 = 64,
};

// forward declarations
template<class T1, class T2> class ObjPtr;
template<class T1, class T2> class ObjOwnerPtr;
template<class T1, class T2> class ObjPtrList;
template<class T> class ObjDirPtr;

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

inline bool PropSync(unsigned char& uc, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x21);
    if(op == kPropGet) node = DataNode(uc);
    else uc = node.Int(0);
    return true;
}

inline bool PropSync(int& iref, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x2C);
    if(op == kPropGet) node = DataNode(iref);
    else iref = node.Int(0);
    return true;
}

inline bool PropSync(short& s, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x36);
    if(op == kPropGet) node = DataNode(s);
    else s = node.Int(0);
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
    if(op == kPropUnknown0x40) return false;
    else {
        MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x58);
        if(op == kPropGet) node = DataNode((Hmx::Object*)obj);
        else obj = dynamic_cast<T*>(node.GetObj(0));
        return true;
    }
}

template <class T> bool PropSync(ObjPtr<T, class ObjectDir>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if(op == kPropUnknown0x40) return false;
    else {
        MILO_ASSERT(i == prop->Size() && op <= kPropInsert, 0x125);
        if(op == kPropGet) node = DataNode(ptr.Ptr());
        else ptr = dynamic_cast<T*>(node.GetObj(0));
        return true;
    }
}

template <class T> bool PropSync(ObjOwnerPtr<T, class ObjectDir>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if(op == kPropUnknown0x40) return false;
    else {
        MILO_ASSERT(op <= kPropInsert, 0x132);
        if(op == kPropGet) node = DataNode(ptr.Ptr());
        else ptr = dynamic_cast<T*>(node.GetObj(0));
        return true;
    }
}

// fn_805E3988 - PropSync(ObjPtrList<Sequence>&) - used in EventTrigger.cpp
// fn_80642860 - PropSync(ObjPtrList&, ...)
template <class T> bool PropSync(ObjPtrList<T, class ObjectDir>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if(op == kPropUnknown0x40) return ptr.Mode() == kObjListNoNull;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x146);
        node = DataNode(ptr.size());
        return true;
    }
    else {
        ObjPtrList<T, class ObjectDir>::iterator it = ptr.begin();
        for(int cnt = prop->Int(i++); cnt > 0; cnt--) it++;
        MILO_ASSERT(i == prop->Size(), 0x150);
        switch(op){
            case kPropGet: {
                T* item = *it;
                return PropSync(item, node, prop, i, op);
            }
            case kPropSet: {
                T* objToSet = 0;
                if(PropSync(objToSet, node, prop, i, op)){
                    ptr.Set(it, objToSet);
                    return true;
                }
                break;
            }
            case kPropRemove: {
                ptr.erase(it);
                return true;
            }
            case kPropInsert: {
                T* objToInsert = 0;
                if(PropSync(objToInsert, node, prop, i, op)){
                    ptr.insert(it, objToInsert);
                    return true;
                }
                break;
            }
        }
        return false;
    }
}

// fn_805C3A80 - PropSync for ObjDirPtr
template <class T> inline bool PropSync(ObjDirPtr<T>& ptr, DataNode& node, DataArray* prop, int i, PropOp op){
    if(op == kPropGet){
        node = DataNode(ptr.GetFile());
    }
    else {
        FilePath fp(node.Str(0));
        ptr.LoadFile(fp, false, true, kLoadFront, false);
    }
    return true;
}

template <class T> bool PropSync(std::list<T>& pList, DataNode& node, DataArray* prop, int i, PropOp op)  {
    if(op == kPropUnknown0x40) return false;
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
        if(i < prop->Size() || op & (kPropGet|kPropSet|kPropSize)){
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
    if(op == kPropUnknown0x40) return false;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0xB9);
        node = DataNode((int)vec.size());
        return true;
    }
    else {
        std::vector<T, T2>::iterator it = vec.begin() + prop->Int(i++);
        if(i < prop->Size() || op & (kPropGet|kPropSet|kPropSize)){
            return PropSync(*it, node, prop, i, op);
        }
        else if(op == kPropRemove){
            vec.erase(it);
            return true;
        }
        else if(op == kPropInsert){
            T item;
            if(PropSync(item, node, prop, i, op)){
                vec.insert(it, item);
                return true;
            }
        }
        return false;
    }
}

#include "obj/ObjVector.h"
template <class T, typename T2> bool PropSync(ObjVector<T, T2>& objVec, DataNode& node, DataArray* prop, int i, PropOp op)  {
    if(op == kPropUnknown0x40) return false;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x17F);
        node = DataNode((int)objVec.size());
        return true;
    }
    else {
        std::vector<T, T2>::iterator it = objVec.begin() + prop->Int(i++);
        if(i < prop->Size() || op & (kPropGet|kPropSet|kPropSize)){
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

#include "obj/ObjList.h"
template <class T> bool PropSync(ObjList<T>& objList, DataNode& node, DataArray* prop, int i, PropOp op){
    if(op == kPropUnknown0x40) return false;
    else if(i == prop->Size()){
        MILO_ASSERT(op == kPropSize, 0x1A6);
        node = DataNode((int)objList.size());
        return true;
    }
    else {
        int count = prop->Int(i++);
        std::list<T>::iterator it = objList.begin();
        for(; count != 0; count--){
            it++;
        }
        if(i < prop->Size() || op & (kPropGet|kPropSet|kPropSize)){
            return PropSync(*it, node, prop, i, op);
        }
        else if(op == kPropRemove){
            objList.erase(it);
            return true;
        }
        else if(op == kPropInsert){
            T item(objList.Owner());
            if(PropSync(item, node, prop, i, kPropInsert)){
                objList.insert(it, item);
                return true;
            }
        }
        return false;
    }
}

#endif
