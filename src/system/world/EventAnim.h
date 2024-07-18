#ifndef WORLD_EVENTANIM_H
#define WORLD_EVENTANIM_H
#include "rndobj/Anim.h"
#include "obj/ObjList.h"

class EventAnim : public RndAnimatable {
public:
    EventAnim();
    OBJ_CLASSNAME(EventAnim);
    OBJ_SET_TYPE(EventAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~EventAnim();
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float frame, float blend);
    virtual float StartFrame();
    virtual float EndFrame();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(EventAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(EventAnim)
    }
    
    ObjList<int> unk10;
    ObjList<int> unk1c;
    ObjList<int> unk28;
    bool unk34;
    float unk38;
};

#endif
