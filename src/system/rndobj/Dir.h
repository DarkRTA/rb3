#ifndef RNDOBJ_DIR_H
#define RNDOBJ_DIR_H
#include "obj/MsgSource.h" // MsgSource : public virtual Object
#include "rndobj/Poll.h" // RndPollable : public virtual Object
#include "rndobj/Trans.h" // RndTransformable : public virtual RndHighlightable
#include "rndobj/Anim.h" // RndAnimatable : public virtual Object
#include "rndobj/Draw.h" // RndDrawable : public virtual RndHighlightable
#include "obj/Dir.h" // ObjectDir : public virtual Object
#include <vector>
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Env.h"

class RndDir : public ObjectDir, public RndDrawable, public RndAnimatable, public RndTransformable, public RndPollable, public MsgSource {
public:
    RndDir();
    virtual ~RndDir(){}
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(RndDir)
    OBJ_SET_TYPE(RndDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void SetSubDir(bool);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void RemovingObject(Hmx::Object*);
    virtual void OldLoadProxies(BinStream&, int);
    virtual void Export(DataArray*, bool);
    virtual void Highlight();
    
    std::vector<RndDrawable*> mDraws;
    std::vector<RndAnimatable*> mAnims;
    std::vector<RndPollable*> mPolls;
    ObjPtr<RndEnviron, ObjectDir> mEnv;
    Symbol mTestEvent;

    DELETE_OVERLOAD
};

#endif
