#pragma once
#include "char/CharDriver.h"

/** "Uses an event list made from a parser to player animation on self." */
class CharDriverMidi : public CharDriver {
public:
    CharDriverMidi();
    virtual ~CharDriverMidi() {}
    OBJ_CLASSNAME(CharDriverMidi);
    OBJ_SET_TYPE(CharDriverMidi);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual void Enter();
    virtual void Exit();

    DataNode OnMidiParser(DataArray *);
    DataNode OnMidiParserFlags(DataArray *);
    DataNode OnMidiParserGroup(DataArray *);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharDriverMidi)
    static void Init() { REGISTER_OBJ_FACTORY(CharDriverMidi) }

    Symbol mParser; // 0x8c
    Symbol mFlagParser; // 0x90
    int mClipFlags; // 0x94
    /** "Blend override- set between 0-1 to change clip blending strategy" */
    float mBlendOverridePct; // 0x98
};
