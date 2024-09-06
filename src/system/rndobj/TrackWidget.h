#ifndef RNDOBJ_TRACKWIDGET_H
#define RNDOBJ_TRACKWIDGET_H

#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Draw.h"

class TrackWidget : public RndDrawable {
    bool mWasActive;

    ObjPtrList<RndMesh, ObjectDir> mMeshes;
    bool mWideWidget;
    ObjPtrList<RndMesh, ObjectDir> mMeshesLeft;
    ObjPtrList<RndMesh, ObjectDir> mMeshesSpan;
    ObjPtrList<RndMesh, ObjectDir> mMeshesRight;
    ObjPtr<void, ObjectDir> mEnv;
    float mBaseLength;
    float mBaseWidth;
    bool mAllowRotation;
    int mMaxMeshes;
    float mOffsetX;
    float mOffsetY;
    float mOffsetZ;
    bool mAllowShift;
};

#endif // RNDOBJ_TRACKWIDGET_H