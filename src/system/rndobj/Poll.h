#ifndef RNDOBJ_DRAW_H
#define RNDOBJ_DRAW_H
#include "obj/Object.h"
#include <list>

class RndPollable : public virtual Hmx::Object {
public:
    RndPollable(){}
    OBJ_CLASSNAME(Poll);
    OBJ_SET_TYPE(Poll);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll(){}
    virtual void Enter();
    virtual void Exit();
    virtual void ListPollChildren(std::list<RndPollable*>&) const {}
    virtual ~RndPollable(){}
};

#endif
