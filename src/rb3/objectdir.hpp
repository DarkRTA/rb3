#ifndef RB3_OBJECTDIR_HPP
#define RB3_OBJECTDIR_HPP
#include "objref.hpp"
#include "hmx/object.hpp"

class Hmx::Object;

class ObjectDir : ObjRef, Hmx::Object {
public:
    ObjectDir(int);
};

#endif
