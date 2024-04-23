#ifndef RNDOBJ_EVENTTRIGGER_H
#define RNDOBJ_EVENTTRIGGER_H

#include "rndobj/Anim.h"

class EventTrigger : public RndAnimatable {
public:
    EventTrigger();
    virtual void Load(BinStream&);
    virtual void Save(BinStream&);

    virtual void SetName(const char*, ObjectDir*);
    virtual void Trigger(); // 0x50


    NEW_OBJ(EventTrigger)
    static void Init();
};

#endif // RNDOBJ_EVENTTRIGGER_H