#ifndef CHAR_CHARDRIVERMIDI_H
#define CHAR_CHARDRIVERMIDI_H
#include "char/CharDriver.h"

class CharDriverMidi : public CharDriver {
public:
    CharDriverMidi();
    virtual ~CharDriverMidi(){}
    OBJ_CLASSNAME(CharDriverMidi);
    OBJ_SET_TYPE(CharDriverMidi);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void Exit();

    DECLARE_REVS;

    Symbol mParser; // 0x8c
    Symbol mFlagParser; // 0x90
    int mClipFlags; // 0x94
    float mBlendOverridePct; // 0x98
};

#endif
