#include "bandobj/ArpeggioShape.h"

ArpeggioShape::ArpeggioShape(RndGroup* grp, RndMesh* mesh, RndText* txt1, RndText* txt2, RndMat* mat, RndMatAnim* manim) : unk0(Hmx::Object::New<RndTransformable>()),
    mParentGroup(grp), unk8(Hmx::Object::New<RndMesh>()), unkc(Hmx::Object::New<RndText>()), unk10(Hmx::Object::New<RndText>()), unk14(Hmx::Object::New<RndMat>()),
    unk18(Hmx::Object::New<RndMatAnim>()) {
    unk8->Copy(mesh, Hmx::Object::kCopyDeep);
    unkc->Copy(txt1, Hmx::Object::kCopyDeep);
    unk10->Copy(txt2, Hmx::Object::kCopyDeep);
    unk14->Copy(mat, Hmx::Object::kCopyDeep);
    unk18->Copy(manim, Hmx::Object::kCopyDeep);
    unk8->SetTransParent(unk0, false);
    unkc->SetTransParent(unk0, false);
    unk10->SetTransParent(unk0, false);
    unk18->SetMat(unk14);
    unk8->SetMat(unk14);
}

ArpeggioShape::~ArpeggioShape(){
    UnhookFromParentGroup();
    RELEASE(unk8);
    RELEASE(unkc);
    RELEASE(unk10);
    RELEASE(unk0);
    RELEASE(unk14);
    RELEASE(unk18);
}

ArpeggioShapePool::ArpeggioShapePool(ObjectDir* dir, RndGroup* shapes, int i) : mChordShapeMesh(dir->Find<RndMesh>("chord_shape.mesh", true)),
    mFretNumbersChord(dir->Find<RndText>("fret_numbers_chord.txt", true)), mChordLabel(dir->Find<RndText>("chord_label.txt", true)), mShapesGroup(shapes),
    mChordShapeMat(dir->Find<RndMat>("chord_shape.mat", true)), mFadeMatAnim(dir->Find<RndMatAnim>("fade.mnm", true)), unk20(i), unk24(0) {
    for(int n = 0; n < unk20; n++) CreateArpeggioShape();
}

ArpeggioShapePool::~ArpeggioShapePool(){
    for(std::list<ArpeggioShape*>::iterator it = mShapes.begin(); it != mShapes.end(); it++){
        RELEASE(*it);
    }
}