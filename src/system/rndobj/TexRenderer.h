#ifndef RNDOBJ_TEXRENDERER_H
#define RNDOBJ_TEXRENDERER_H
#include "rndobj/Draw.h"
#include "rndobj/Anim.h"
#include "rndobj/Poll.h"

class RndTexRenderer : public RndDrawable, public RndAnimatable, public RndPollable {
public:
    RndTexRenderer();
    OBJ_CLASSNAME(TexRenderer);
    OBJ_SET_TYPE(TexRenderer);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void DrawPreClear();
    virtual void UpdatePreClearState();
    virtual ~RndTexRenderer();
    virtual void Enter();
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual void DrawBefore(){}
    virtual void DrawAfter(){}

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTexRenderer)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTexRenderer)
    }
};

#endif
