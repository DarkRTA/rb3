#include "rndobj/Morph.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "utl/TextStream.h"

RndMorph::RndMorph() : mPoses(this), mTarget(this, 0), mNormals(0), mSpline(0), mIntensity(1.0f) {

}

BEGIN_COPYS(RndMorph)
    CREATE_COPY_AS(RndMorph, f)
    MILO_ASSERT(f, 0xA8);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(f, mPoses)
    COPY_MEMBER_FROM(f, mTarget)
    COPY_MEMBER_FROM(f, mNormals)
    COPY_MEMBER_FROM(f, mSpline)
    COPY_MEMBER_FROM(f, mIntensity)
END_COPYS

TextStream& operator<<(TextStream& ts, const RndMorph::Pose& pose){
    ts << "mesh:" << pose.mesh << " weightKeys:" << pose.weights;
    return ts;
}

void RndMorph::Print(){
    TextStream& ts = TheDebug;
    ts << "   poses: " << mPoses << "\n";
    ts << "   target: " << mTarget << "\n";
    ts << "   normals: " << mNormals << "\n";
    ts << "   spline: " << mSpline << "\n";
    ts << "   intensity: " << mIntensity << "\n";
}

SAVE_OBJ(RndMorph, 0xCB);