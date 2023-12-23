#ifndef RB3_OBJDIRPTR_HPP
#define RB3_OBJDIRPTR_HPP
#include "objref.hpp"
#include "hmx/object.hpp"

template <class T> class ObjDirPtr : public ObjRef {
public:
    ObjDirPtr(); // fn_8000ECF4
    virtual ~ObjDirPtr(); // fn_8000E844
    virtual void RefOwner(); // links to fn_8077BAA0, which returns 0
    virtual void Replace(); // fn_8000F8A0
    virtual int IsDirPtr(); // links to fn_8000F90C, which returns 1

    Hmx::Object *obj; // i've also seen this used as an ObjectDir*?
    int loader; // should be a Loader*
};

#endif
