#pragma once
#include "obj/Object.h"
#include <list>

/**
* @brief: An object that can be polled.
* Original _objects description:
* "Abstract base class for pollable RND objects"
*/
class RndPollable : public virtual Hmx::Object {
public:
    RndPollable(){}
    OBJ_CLASSNAME(Poll);
    OBJ_SET_TYPE(Poll);
    virtual DataNode Handle(DataArray*, bool);
    /** Poll this object. */
    virtual void Poll(){}
    virtual void Enter();
    virtual void Exit();
    /** Get the list of this Object's children that are pollable. */
    virtual void ListPollChildren(std::list<RndPollable*>&) const {}
    virtual ~RndPollable(){}
};