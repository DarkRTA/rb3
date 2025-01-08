#pragma once
#include "obj/Object.h"
#include "math/Interp.h"
#include "obj/ObjPtr_p.h"
#include <set>

class FaderGroup;

/** "A fader controls the volume level of one or more sound effects." */
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
    float GetVal() const { return mVal; }
    Symbol LocalName() const { return mLocalName; }
    void SetLocalName(Symbol name){ mLocalName = name; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(Fader);
    static void Init(){
        REGISTER_OBJ_FACTORY(Fader)
    }

    /** "volume level in dB" */
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
    void PollAll();
    void Poll();

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

    ObjPtrList<Fader> mFaders; // 0x0
    bool mDirty; // 0x10
};

bool PropSync(FaderGroup&, DataNode&, DataArray*, int, PropOp);
