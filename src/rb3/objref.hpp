#ifndef RB3_OBJREF_HPP
#define RB3_OBJREF_HPP

namespace Hmx { class Object; }

class ObjRef {
public:
    ObjRef();
    virtual ~ObjRef(); // fn_8000DD10
    virtual void RefOwner() = 0;
    virtual void Replace(Hmx::Object*, Hmx::Object*) = 0;
    virtual int IsDirPtr(); // links to fn_8077BAA0, which returns 0
};

#endif
