#ifndef RNDOBJ_PART_H
#define RNDOBJ_PART_H
#include "math/Color.h"
#include "math/Vec.h"
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Anim.h"

struct RndParticle {
    Hmx::Color col;
    Hmx::Color colVel;
    Vector4 pos;
    Vector4 vel;
    float deathFrame;
    float birthFrame;
    float size;
    float sizeVel;
    float angle;
    float swingArm;
    RndParticle* prev;
    RndParticle* next;
};

class RndParticleSys : public RndAnimatable, public RndPollable, public RndTransformable, public RndDrawable {
public:
    enum Type {

    };

    RndParticleSys();
    OBJ_CLASSNAME(ParticleSys);
    OBJ_SET_TYPE(ParticleSys);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndParticleSys();
    virtual void SetFrame(float, float);
    virtual float EndFrame();

    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Enter();
    virtual void Poll();
    virtual void DrawShowing();
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void SetPreserveParticles(bool);
    virtual void SetPool(int, Type);
    virtual void SetPersistentPool(int, Type);
    virtual void Highlight();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndParticleSys)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndParticleSys)
    }
};

void InitParticleSystem();

#endif // RNDOBJ_PART_H
