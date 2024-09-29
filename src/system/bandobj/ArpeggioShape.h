#pragma once
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "rndobj/Text.h"
#include "rndobj/Mat.h"
#include "rndobj/MatAnim.h"
#include "rndobj/Trans.h"

class ArpeggioShape {
public:
    ArpeggioShape(RndGroup *, RndMesh *, RndText *, RndText *, RndMat *, RndMatAnim *);
    ~ArpeggioShape();

    void HookupToParentGroup();
    void UnhookFromParentGroup();
    void SetChordShape(RndMesh *);
    void Reset();
    void FadeOutChordShape();
    void ShowChordShape(bool);
    void SetChordLabel(const String &, float, bool);
    void SetFretNumber(const String &, const Vector3 &);
    void SetYPos(float);
    float GetYPos() const;

    RndTransformable *unk0; // 0x0
    RndGroup *mParentGroup; // 0x4
    RndMesh *mChordShapeMesh; // 0x8
    RndText *mFretNumbersChord; // 0xc
    RndText *mChordLabel; // 0x10
    RndMat *mChordShapeMat; // 0x14
    RndMatAnim *mFadeMatAnim; // 0x18
};

class ArpeggioShapePool {
public:
    ArpeggioShapePool(ObjectDir *, RndGroup *, int);
    ~ArpeggioShapePool();

    void CreateArpeggioShape();
    ArpeggioShape *GetArpeggioShape();
    void ReleaseArpeggioShape(ArpeggioShape *&);

    std::list<ArpeggioShape *> mShapes; // 0x0
    RndMesh *mChordShapeMesh; // 0x8
    RndText *mFretNumbersChord; // 0xc
    RndText *mChordLabel; // 0x10
    RndGroup *mShapesGroup; // 0x14
    RndMat *mChordShapeMat; // 0x18
    RndMatAnim *mFadeMatAnim; // 0x1c
    int mInitialPoolSize; // 0x20
    int mCurrentPoolSize; // 0x24
};