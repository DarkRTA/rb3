#ifndef RB3_OBJOWNERPTR_HPP
#define RB3_OBJOWNERPTR_HPP
#include "objref.hpp"
#include "hmx/object.hpp"

template <class T1, class T2> class ObjOwnerPtr : public ObjRef {
public:

    ObjOwnerPtr(Hmx::Object* o, T1* item){
        owner = o;
        obj = item;
        if(item != nullptr) item->AddRef(o);
    }

    virtual ~ObjOwnerPtr(){
        if(obj != nullptr) obj->Release(owner);
    }

    virtual Hmx::Object* RefOwner(){ return owner; } // returns the Hmx::Object* owner down there
    virtual void Replace(Hmx::Object*, Hmx::Object*); // links to fn_8076F540, which returns void


    // void operator=(const ObjOwnerPtr<T1, T2>& const_owner_ptr){
    //     operator=(const_owner_ptr.obj);
    // }


    // void operator=(T1* smelly){
    //     Hmx::Object* theObj = obj;
    //     if(smelly != theObj){
    //         if(theObj != nullptr){
    //             theObj->Release(owner);
    //         }
    //         obj = smelly;
    //         if(smelly != nullptr){
    //             smelly->AddRef(owner);
    //         }
    //     }
    // }

    Hmx::Object* owner;
    T1* obj;
};

#endif
