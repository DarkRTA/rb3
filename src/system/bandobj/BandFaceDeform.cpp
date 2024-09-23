#include "bandobj/BandFaceDeform.h"
#include "utl/Symbols.h"

BandFaceDeform::BandFaceDeform(){

}

BandFaceDeform::~BandFaceDeform(){
    
}

BEGIN_HANDLERS(BandFaceDeform)
    HANDLE_ACTION(set_from_meshanim, SetFromMeshAnim(_msg->Obj<RndMeshAnim>(2), _msg->Obj<RndMeshAnim>(3), 0, -1))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x145)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(BandFaceDeform::DeltaArray)
    SYNC_PROP_SET(verts, o.NumVerts(), )
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandFaceDeform)
    SYNC_PROP(frames, mFrames)
    SYNC_PROP_SET(size, TotalSize(), )
END_PROPSYNCS