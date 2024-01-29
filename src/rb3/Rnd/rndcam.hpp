#ifndef RND_RNDCAM_HPP
#define RND_RNDCAM_HPP
#include <rb3/hmx/object.hpp>
#include <rb3/hmx/quat.hpp>
#include <vector2.hpp>
#include <rb3/binstream.hpp>
#include "rndtransformable.hpp"


/** A camera.
 * Can define a target texture, what part of the screen to render to, etc. */
class RndCam : public RndTransformable { // 0x2A4
public:
    char too_much_padding[0x238]; // i swear there's stuff here but the ctors got stubbed
    float a; // TODO figure out
    float b;
    float c;
    float d;
    Vector2 huh;

    /** What part of the screen to render to.
     * This is in screen-space coordinates, i.e. top left is 0,0
     * and bottom right is 1,1. This is a Quaternion cause it works fine.
     */
    Hmx::Quat screen_space_render;
    // ObjPtr<RndTex> target_tex;
    void* target_tex;

    Symbol StaticClassName();

    RndCam();
    virtual Symbol ClassName() {return StaticClassName();}
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty();
    virtual void Save(BinStream&);
    virtual void Copy(Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndCam();
    // RndTransformable::Replace();
    // RndTransformable::Highlight();
    // RndTransformable::Print();
    virtual void UpdatedWorldXfm();
    virtual void Select();
    virtual void ProjectZ();

    RndCam* NewObject();
    RndCam* fn_803F8F64();
    void fn_805CD500();
    void Init();

    static RndCam* sCurrent;
};
#endif
