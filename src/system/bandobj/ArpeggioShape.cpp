#include "bandobj/ArpeggioShape.h"
#include "utl/Symbols.h"

ArpeggioShape::ArpeggioShape(
    RndGroup *grp,
    RndMesh *mesh,
    RndText *txt1,
    RndText *txt2,
    RndMat *mat,
    RndMatAnim *manim
)
    : unk0(Hmx::Object::New<RndTransformable>()), mParentGroup(grp),
      mChordShapeMesh(Hmx::Object::New<RndMesh>()),
      mFretNumbersChord(Hmx::Object::New<RndText>()),
      mChordLabel(Hmx::Object::New<RndText>()),
      mChordShapeMat(Hmx::Object::New<RndMat>()),
      mFadeMatAnim(Hmx::Object::New<RndMatAnim>()) {
    mChordShapeMesh->Copy(mesh, Hmx::Object::kCopyDeep);
    mFretNumbersChord->Copy(txt1, Hmx::Object::kCopyDeep);
    mChordLabel->Copy(txt2, Hmx::Object::kCopyDeep);
    mChordShapeMat->Copy(mat, Hmx::Object::kCopyDeep);
    mFadeMatAnim->Copy(manim, Hmx::Object::kCopyDeep);
    mChordShapeMesh->SetTransParent(unk0, false);
    mFretNumbersChord->SetTransParent(unk0, false);
    mChordLabel->SetTransParent(unk0, false);
    mFadeMatAnim->SetMat(mChordShapeMat);
    mChordShapeMesh->SetMat(mChordShapeMat);
}

ArpeggioShape::~ArpeggioShape() {
    UnhookFromParentGroup();
    RELEASE(mChordShapeMesh);
    RELEASE(mFretNumbersChord);
    RELEASE(mChordLabel);
    RELEASE(unk0);
    RELEASE(mChordShapeMat);
    RELEASE(mFadeMatAnim);
}

void ArpeggioShape::HookupToParentGroup() {
    if (mChordLabel->Showing()) {
        mParentGroup->AddObjectAtFront(mChordLabel);
    }
    if (mFretNumbersChord->Showing()) {
        mParentGroup->AddObjectAtFront(mFretNumbersChord);
    }
    if (mChordShapeMesh->Showing()) {
        mParentGroup->AddObjectAtFront(mChordShapeMesh);
    }
}

void ArpeggioShape::UnhookFromParentGroup() {
    if (mChordLabel->Showing()) {
        mParentGroup->RemoveObject(mChordLabel);
    }
    if (mFretNumbersChord->Showing()) {
        mParentGroup->RemoveObject(mFretNumbersChord);
    }
    if (mChordShapeMesh->Showing()) {
        mParentGroup->RemoveObject(mChordShapeMesh);
    }
}

void ArpeggioShape::SetChordShape(RndMesh *mesh) {
    mChordShapeMesh->SetGeomOwner(mesh ? mesh : mChordShapeMesh);
    mChordShapeMesh->SetShowing(true);
}

void ArpeggioShape::Reset() {
    UnhookFromParentGroup();
    mChordShapeMesh->SetGeomOwner(mChordShapeMesh);
    mChordShapeMesh->SetShowing(false);
    mFretNumbersChord->SetText("");
    mFretNumbersChord->SetShowing(false);
    mChordLabel->SetText("");
    mChordLabel->SetShowing(false);
    mFadeMatAnim->StopAnimation();
    mFadeMatAnim->SetFrame(0, 1.0f);
}

void ArpeggioShape::FadeOutChordShape() {
    static float period = 0.1f;
    if (mChordShapeMesh->Showing() || mFretNumbersChord->Showing()) {
        mFadeMatAnim->Animate(
            0.0f, false, 0.0f, RndAnimatable::k30_fps, 0.0f, 1.0f, period, 1.0f, dest
        );
        mFretNumbersChord->SetShowing(false);
    }
}

void ArpeggioShape::ShowChordShape(bool show) {
    mChordShapeMesh->SetShowing(show);
    mFretNumbersChord->SetShowing(show);
}

void ArpeggioShape::SetChordLabel(const String &str, float f, bool b) {
    mChordLabel->SetText(str.c_str());
    Vector3 v(mChordLabel->mLocalXfm.v);
    v.x = f;
    mChordLabel->SetLocalPos(v);
    mChordLabel->SetShowing(str != "");
    if (b) {
        RndText::Alignment a = mChordLabel->GetAlignment();
        if (a != RndText::kBottomLeft)
            mChordLabel->SetAlignment(RndText::kBottomLeft);
    } else {
        RndText::Alignment a = mChordLabel->GetAlignment();
        if (a != RndText::kBottomRight)
            mChordLabel->SetAlignment(RndText::kBottomRight);
    }
}

void ArpeggioShape::SetFretNumber(const String &str, const Vector3 &vec) {
    mFretNumbersChord->SetText(str.c_str());
    mFretNumbersChord->SetLocalPos(vec);
    mFretNumbersChord->SetShowing(str != "");
}

void ArpeggioShape::SetYPos(float f) {
    Transform tf;
    tf.Reset();
    tf.v.y = f;
    unk0->SetWorldXfm(tf);
}

float ArpeggioShape::GetYPos() const {
    return unk0->WorldXfm().v.y;
}

ArpeggioShapePool::ArpeggioShapePool(ObjectDir *dir, RndGroup *shapes, int i)
    : mChordShapeMesh(dir->Find<RndMesh>("chord_shape.mesh", true)),
      mFretNumbersChord(dir->Find<RndText>("fret_numbers_chord.txt", true)),
      mChordLabel(dir->Find<RndText>("chord_label.txt", true)), mShapesGroup(shapes),
      mChordShapeMat(dir->Find<RndMat>("chord_shape.mat", true)),
      mFadeMatAnim(dir->Find<RndMatAnim>("fade.mnm", true)), mInitialPoolSize(i),
      mCurrentPoolSize(0) {
    for (int n = 0; n < mInitialPoolSize; n++)
        CreateArpeggioShape();
}

ArpeggioShapePool::~ArpeggioShapePool() {
    for (std::list<ArpeggioShape *>::iterator it = mShapes.begin(); it != mShapes.end();
         it++) {
        RELEASE(*it);
    }
}

void ArpeggioShapePool::CreateArpeggioShape() {
    mShapes.push_back(new ArpeggioShape(
        mShapesGroup,
        mChordShapeMesh,
        mFretNumbersChord,
        mChordLabel,
        mChordShapeMat,
        mFadeMatAnim
    ));
    mCurrentPoolSize++;
}

ArpeggioShape *ArpeggioShapePool::GetArpeggioShape() {
    if (mShapes.empty()) {
        CreateArpeggioShape();
        TheDebug.Notify(MakeString(
            "Created new ArpeggioShape on the fly; initial pool size should be increased from %d to %d; report this incident to Matt Sharpe",
            mInitialPoolSize,
            mCurrentPoolSize
        ));
    }
    ArpeggioShape *shape = mShapes.front();
    mShapes.pop_front();
    return shape;
}