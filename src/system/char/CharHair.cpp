#include "obj/ObjPtr_p.h"
#include "char/CharCollide.h"
#include "rndobj/Trans.h"
#include "rndobj/Wind.h"

// ObjPtrList<CharCollide, ObjectDir>::iterator::iterator(const ObjPtrList<CharCollide, ObjectDir>::iterator&)

#pragma dont_inline on
static void asdf(const ObjPtrList<CharCollide, ObjectDir>::iterator& it){
    ObjPtrList<CharCollide, ObjectDir>::iterator localIt(it);
    *localIt;
    ++localIt;
    localIt != it;
}

static void rndtranslisttest(ObjPtr<RndTransformable, ObjectDir>& ptr){
    RndTransformable* trans;
    ptr = trans;
    (RndTransformable*)ptr;
    ptr.operator->();
}

static void objptrlisttest(ObjPtrList<CharCollide, ObjectDir>& ptrlist){
    ptrlist.begin();
    ptrlist.end();
    ptrlist.size();
}

static void rndwindptrtest(RndWind* wind, BinStream& bs){
    ObjPtr<RndWind, ObjectDir> ptr(wind, 0);
    ptr.operator->();
    (RndWind*)ptr;
    bs >> ptr;
}
#pragma dont_inline reset
