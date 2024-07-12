#include "char/CharHair.h"
#include "char/CharCollide.h"
#include "rndobj/Trans.h"
#include "rndobj/Wind.h"
#include "char/Character.h"
#include "math/MathFuncs.h"
#include "math/Rot.h"
#include <cmath>

INIT_REVS(CharHair)

#pragma push
#pragma dont_inline on
void CharHair::Strand::SetRoot(RndTransformable* trans){
    mRoot = trans;
    if(!mRoot) mPoints.resize(0);
    else {
        float len = mPoints.size() != 0 ? mPoints.back().length : 0;
        mBaseMat = mRoot->LocalXfm().m;
        SetAngle(mAngle);
        
        // i hate the way these are structured, i'd rather just make for loops but nooo
        int depth = 0;
        RndTransformable* it = mRoot;
        while(true){
            depth++;
            if(it->TransChildren().empty()) break;
            it = it->TransChildren().front();
        }
        mPoints.resize(depth);

        depth = 0;
        it = mRoot;
        while(true){
            mPoints[depth].bone = it;
            if(it->TransChildren().empty()) break;
            it = it->TransChildren().front();
            depth++;
        }

        Point* pt = 0;
        for(int i = 1; i < mPoints.size(); i++){
            pt = &mPoints[i - 1];
            RndTransformable* bone = mPoints[i].bone;
            pt->length = bone->LocalXfm().v.y;
            pt->pos = bone->WorldXfm().v;
        }
        
        Point* backpt = &mPoints.back();
        if(!len){
            if(pt) len = pt->length;
            else len = 5.0f;
        }
        backpt->length = len;

        ScaleAdd(backpt->bone->WorldXfm().v, backpt->bone->WorldXfm().m.y, backpt->length, backpt->pos);
    }
}
#pragma pop

CharHair::CharHair() : mStiffness(0.04f), mTorsion(0.1f), mInertia(0.7f), mGravity(1.0f), mWeight(0.5f), mFriction(0.3f), mMinSlack(0.0f), mMaxSlack(0.0f),
    mStrands(this), mReset(1), mSimulate(1), mUsePostProc(1), mMe(this, 0), mWind(this, 0), mCollide(this, kObjListNoNull), unk6c(0) {

}

CharHair::Strand::~Strand(){
    
}

CharHair::~CharHair(){

}

#pragma push
#pragma dont_inline on
void CharHair::SimulateInternal(float f){
    float sixtyover = 60.0f / f;
    float f19 = (1.0f / f) * sixtyover;
    float powed = std::pow(1.0f - mStiffness, sixtyover * sixtyover);
    Vector3 vec134(0,0,0);
    if(mWind){
        if(mStrands[0].Root()){
            float secs = TheTaskMgr.Seconds(TaskMgr::b);
            mWind->GetWind(mStrands[0].Root()->WorldXfm().v, secs, vec134);
            vec134 *= f19 * 0.5f;
        }
    }
    vec134.z = vec134.z + mGravity * f19 * -3.858268f;

    for(int i = 0; i < mStrands.size(); i++){
        Strand& modStrand = mStrands[Mod(i + 1, mStrands.size())];
        Strand& thisStrand = mStrands[i];
        if(thisStrand.Root() && thisStrand.Root()->TransParent()){
            Transform t100;
            t100.v = thisStrand.Root()->WorldXfm().v;
            Multiply(thisStrand.RootMat(), thisStrand.Root()->TransParent()->WorldXfm().m, t100.m);
            ObjVector<Point>& points = thisStrand.Points();
            for(int j = 0; j < points.size(); j++){
                Point& thisPoint = points[j];
                Vector3 v140(thisPoint.pos);
                thisPoint.pos += thisPoint.force;
                thisPoint.pos.x += vec134.x;
                thisPoint.pos.y += vec134.y;
                thisPoint.pos.z += vec134.z;
                if(thisPoint.sideLength >= 0.0f){
                    Vector3 vRes;
                    Point& modPoint = modStrand.Points()[j];
                    Subtract(thisPoint.pos, modPoint.pos, vRes);
                    float lensq = LengthSquared(vRes);
                    float sidelen = thisPoint.sideLength - mMinSlack;
                    float sidelensq = sidelen * sidelen;
                    if(sidelensq > lensq){
                        vRes *= (sidelensq / (sidelensq + lensq) - 0.5f);
                        thisPoint.pos += vRes;
                        modPoint.pos -= vRes;
                    }
                    else {
                        float maxslacklen = thisPoint.sideLength + mMaxSlack;
                        float maxslacklensq = maxslacklen * maxslacklen;
                        if(maxslacklensq < maxslacklen){
                            vRes *= (maxslacklensq / (maxslacklensq + lensq) - 0.5f);
                            thisPoint.pos += vRes;
                            modPoint.pos -= vRes;
                        }
                    }
                }
                Hmx::Matrix3 m128;
                Subtract(thisPoint.pos, t100.v, m128.y);
                float rsa = RecipSqrtAccurate(LengthSquared(m128.y));
                float rsalen = thisPoint.length * rsa - 1.0f;
                if(j > 0){
                    ScaleAddEq(points[j - 1].force, m128.y, -sixtyover * 0.5f * rsalen);
                }
                ScaleAddEq(thisPoint.pos, m128.y, rsalen);
                Vector3 v158;
                ScaleAdd(t100.v, t100.m.y, thisPoint.length, v158);
                Interp(thisPoint.lastZ, t100.m.z, mTorsion, m128.z);
                if(thisPoint.collides.size() != 0){
                    float diffRad = thisPoint.outerRadius - thisPoint.radius;
                    float maxRad = Max(thisPoint.radius, thisPoint.outerRadius);
                    for(ObjPtrList<CharCollide, ObjectDir>::iterator it = thisPoint.collides.begin(); it != thisPoint.collides.end(); ++it){

                    }
                }
            }

        //   iVar3 = ObjPtrList<>::size((ObjPtrList<> *)&this_03[5].y);
        //   if (iVar3 != 0) {
        //     fVar1 = this_03[7].x - this_03[6].z;
        //     fVar19 = Max(this_03[6].z,this_03[7].x);
        //     dVar17 = (double)fVar19;
        //     local_184 = ObjPtrList<>::begin((ObjPtrList<> *)&this_03[5].y);
        //     ObjPtrList<>::iterator::iterator(aiStack_180,(iterator *)&local_184);
        //     while( true ) {
        //       local_188 = ObjPtrList<>::end((ObjPtrList<> *)&this_03[5].y);
        //       iVar3 = ObjPtrList<>::iterator::operator_!=(aiStack_180,&local_188);
        //       if (iVar3 == 0) break;

        //       this_05 = (CharCollide *)ObjPtrList<>::iterator::operator*(aiStack_180);
        //       Vector3::Vector3(&VStack_164);
        //       dVar14 = (double)CharCollide::GetRadius(this_05,this_03,&VStack_164);
        //       iVar3 = CharCollide::GetShape(this_05);
        
        //       if (iVar3 == 0) {
        //         if (dVar14 < dVar17) {
        //           pVVar9 = (Vector3 *)CharCollide::Axis(this_05);
        //           ScaleAddEq(this_03,pVVar9,(float)(dVar17 - dVar14));
        //         }
        //       }
        //       else if ((iVar3 == 3) || (iVar3 == 1)) {
        //         dVar15 = (double)LengthSquared(&VStack_164);
        //         dVar18 = (double)(float)(dVar14 + dVar17);
        //         if (dVar15 < (double)(float)(dVar18 * dVar18)) {
        //           if (fVar1 <= 0.0) {
        //             dVar14 = (double)RecipSqrtAccurate((float)dVar15);
        //             ScaleAddEq(this_03,&VStack_164,(float)(dVar18 * dVar14 - 1.0));
        //           }
        //           else {
        //             dVar16 = (double)RecipSqrtAccurate((float)dVar15);
        //             dVar15 = (double)(float)(dVar15 * dVar16);
        //             dVar14 = (double)(float)(dVar14 + (double)this_03[6].z);
        //             Vector3::operator*=(&VStack_164,(float)-dVar16);
        //             if (dVar14 <= dVar15) {
        //               Interp(&MStack_128.z,&VStack_164,(float)(dVar18 - dVar15) / fVar1,
        //                      &MStack_128.z);
        //             }
        //             else {
        //               Vector3::operator_=(&MStack_128.z,&VStack_164);
        //               ScaleAddEq(this_03,&VStack_164,(float)(dVar15 - dVar14));
        //             }
        //           }
        //         }
        //       }
        //       else if ((iVar3 == 4) || (iVar3 == 2)) {
        //         dVar15 = (double)LengthSquared(&VStack_164);
        //         dVar18 = (double)(float)(dVar14 - dVar17);
        //         if ((double)(float)(dVar18 * dVar18) < dVar15) {
        //           if (fVar1 <= 0.0) {
        //             dVar14 = (double)RecipSqrtAccurate((float)dVar15);
        //             ScaleAddEq(this_03,&VStack_164,(float)(dVar18 * dVar14 - 1.0));
        //           }
        //           else {
        //             dVar16 = (double)RecipSqrtAccurate((float)dVar15);
        //             dVar15 = (double)(float)(dVar15 * dVar16);
        //             dVar14 = (double)(float)(dVar14 - (double)this_03[6].z);
        //             Vector3::operator*=(&VStack_164,(float)-dVar16);
        //             if (dVar15 <= dVar14) {
        //               Interp(&MStack_128.z,&VStack_164,(float)(dVar15 - dVar18) / fVar1,
        //                      &MStack_128.z);
        //             }
        //             else {
        //               Vector3::operator_=(&MStack_128.z,&VStack_164);
        //               ScaleAddEq(this_03,&VStack_164,(float)(dVar15 - dVar14));
        //             }
        //           }
        //         }
        //       }
        //       ObjPtrList<>::iterator::operator_++(aiStack_180);
        //     }
        //   }



        //   Scale(&MStack_128.y,(float)dVar13,&TStack_100.m.y);
        //   Cross(&TStack_100.m.y,&MStack_128.z,(Vector3 *)&TStack_100);
        //   dVar13 = (double)LengthSquared((Vector3 *)&TStack_100);
        //   dVar13 = (double)RecipSqrtAccurate((float)dVar13);
        //   Vector3::operator*=((Vector3 *)&TStack_100,(float)dVar13);
        //   Normalize((Vector3 *)&TStack_100,(Vector3 *)&TStack_100);
        //   Cross((Vector3 *)&TStack_100,&TStack_100.m.y,&TStack_100.m.z);
        //   Vector3::operator_=(this_03 + 3,&TStack_100.m.z);
        //   iVar3 = ObjPtr<>::__opP16RndTransformable((ObjPtr<> *)(this_03 + 4));
        //   if (iVar3 != 0) {
        //     pRVar5 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this_03 + 4));
        //     RndTransformable::SetWorldXfm(pRVar5,&TStack_100);
        //   }
        //   Subtract(&VStack_158,this_03,this_03 + 1);
        //   Vector3::Vector3(&VStack_170);
        //   Subtract(this_03 + 2,this_03 + 1,&VStack_170);
        //   Vector3::operator_=(this_03 + 2,this_03 + 1);
        //   Vector3::operator*=(this_03 + 1,(float)(1.0 - dVar12));
        //   ScaleAddEq(this_03 + 1,&VStack_170,-*(float *)(this + 0x24));
        //   Vector3::Vector3(&VStack_17c);
        //   Subtract(this_03,&VStack_140,&VStack_17c);
        //   ScaleAddEq(this_03 + 1,&VStack_17c,*(float *)(this + 0x18));
        //   Vector3::operator_=(&TStack_100.v,this_03);
        // }
        }
    }

    // for(ObjPtrList<CharCollide, ObjectDir>::iterator it = mCollide.begin(); it != mCollide.end(); ++it){
    //     (*it);
    // }
}
#pragma pop

CharHair::Strand::Strand(Hmx::Object* o) : mShowSpheres(0), mShowCollide(0), mShowPose(0), mRoot(o, 0), mAngle(0.0f), mPoints(o), mHookupFlags(0) {
    mBaseMat.Identity();
    mRootMat.Identity();
}

void CharHair::Strand::Load(BinStream& bs){
    bs >> mRoot;
    bs >> mAngle;
    bs >> mPoints;
    bs >> mBaseMat >> mRootMat;
    if(CharHair::gRev > 2){
        bs >> mHookupFlags;
    }
    else mHookupFlags = 0;
}

SAVE_OBJ(CharHair, 0x41B)

void CharHair::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(11, 0);
    Hmx::Object::Load(bs);
    bs >> mStiffness >> mTorsion >> mInertia >> mGravity >> mWeight >> mFriction;
    if(gRev < 8){
        mMinSlack = 0.0f;
        mMaxSlack = 0.0f;
    }
    else bs >> mMinSlack >> mMaxSlack;
    bs >> mStrands;
    bs >> mSimulate;
    if(gRev > 10) bs >> mWind;
}