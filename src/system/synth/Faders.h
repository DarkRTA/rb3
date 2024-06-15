#ifndef SYNTH_FADERS_H
#define SYNTH_FADERS_H
#include "obj/Object.h"
#include "math/Interp.h"
#include "obj/ObjPtr_p.h"
#include <set>

class FaderGroup;

class Fader : public Hmx::Object {
public:
    enum Mode {
        kLinear,
        kExp,
        kInvExp
    };

    Fader();
    virtual ~Fader();
    OBJ_CLASSNAME(Fader);
    OBJ_SET_TYPE(Fader);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void SetVal(float);
    float GetTargetDb() const;
    void DoFade(float, float);
    void CancelFade();
    void UpdateValue(float);
    void SetMode(Mode);
    bool IsFading() const;
    void AddClient(FaderGroup*);
    void RemoveClient(FaderGroup*);
    void Check();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    float mVal; // 0x1c
    class FaderTask* mFaderTask; // 0x20
    Symbol mLocalName; // 0x24
    std::set<FaderGroup*> mClients; // 0x28
    Mode mMode; // 0x40
};

class FaderTask {
public:
    FaderTask();
    ~FaderTask();

    static std::list<FaderTask*> sTasks;

    Timer mTimer; // 0x0
    Interpolator* mInterp; // 0x30
    Fader* mFader; // 0x34
    bool mDone; // 0x38
};

class FaderGroup {
public:
    FaderGroup(Hmx::Object*);
    ~FaderGroup();
    Fader* AddLocal(Symbol);
    Fader* FindLocal(Symbol, bool);
    void Add(Fader*);
    void Remove(Fader*);
    bool Dirty();
    void SetDirty();
    void ClearDirty();
    float GetVal();
    void Print(TextStream&);
    void Load(BinStream&);

    ObjPtrList<Fader, class ObjectDir> mFaders;
    bool mDirty;
};

bool PropSync(FaderGroup&, DataNode&, DataArray*, int, PropOp);

#endif
