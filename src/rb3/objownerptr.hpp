#ifndef RB3_OBJOWNERPTR_HPP
#define RB3_OBJOWNERPTR_HPP
#include "objref.hpp"
#include "hmx/object.hpp"

template <class T> class ObjOwnerPtr : public ObjRef {
public:
    ObjOwnerPtr();
    virtual ~ObjOwnerPtr();
    virtual void RefOwner(); // returns the Hmx::Object* obj down there
    virtual void Replace(Hmx::Object*, Hmx::Object*); // links to fn_8076F540, which returns void

    Hmx::Object* obj;
    T* item;
};

#endif
