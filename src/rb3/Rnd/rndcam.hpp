#ifndef RND_RNDCAM_HPP
#define RND_RNDCAM_HPP
#include <rb3/hmx/object.hpp>
#include <rb3/binstream.hpp>
#include "rndtransformable.hpp"


/** A camera.
 * Can define a target texture, what part of the screen to render to, etc. */
class RndCam : public RndTransformable { // 0x2A4
public:
    RndCam::RndCam();
    virtual Symbol ClassName();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty();
    virtual void Save(BinStream&);
    virtual void Copy(Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual RndCam::~RndCam();
    // RndTransformable::Replace();
    // RndTransformable::Highlight();
    // RndTransformable::Print();
    virtual void UpdatedWorldXfm();
    virtual void Select();
    virtual void ProjectZ();

    Symbol StaticClassName();
};
#endif
