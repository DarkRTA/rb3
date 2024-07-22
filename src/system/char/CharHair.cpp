#include "char/CharHair.h"
#include "char/CharCollide.h"
#include "rndobj/Trans.h"
#include "rndobj/Wind.h"
#include "char/Character.h"
#include "math/MathFuncs.h"
#include "math/Rot.h"
#include "world/Dir.h"
#include <cmath>
#include "utl/Symbols.h"

INIT_REVS(CharHair)
CharHair* gHair;
CharHair::Strand* gStrand;

#pragma push
#pragma dont_inline on
// fn_804D49F8
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

void CharHair::Enter(){
    mReset = 1;
    RndPollable::Enter();
    Hookup();
}

void CharHair::SetName(const char* cc, ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<Character*>(dir);
    bool pp = false;
    if(mMe || dynamic_cast<WorldDir*>(dir)) pp = true;
    mUsePostProc = pp;
}

#pragma push
#pragma dont_inline on
// fn_804D6590
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
                    if(lensq < sidelensq){
                        vRes *= (sidelensq / (sidelensq + lensq) - 0.5f);
                        thisPoint.pos += vRes;
                        modPoint.pos -= vRes;
                    }
                    else {
                        float maxslacklen = thisPoint.sideLength + mMaxSlack;
                        float maxslacklensq = maxslacklen * maxslacklen;
                        if(maxslacklen > maxslacklensq){
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
                        CharCollide* thisCollide = *it;
                        Vector3 v164;
                        float collideRad = thisCollide->GetRadius(thisPoint.pos, v164);
                        switch(thisCollide->GetShape()){
                            case CharCollide::kPlane: // 0
                                if(maxRad > collideRad){
                                    ScaleAddEq(thisPoint.pos, thisCollide->Axis(), maxRad - collideRad);
                                }
                                break;
                            case CharCollide::kCigar: // 3
                            case CharCollide::kSphere: // 1
                                float v164sq = LengthSquared(v164);
                                float sumRad = collideRad + maxRad;
                                if(v164sq < sumRad * sumRad){
                                    if(diffRad > 0.0f){
                                        float v164sqrecip = RecipSqrtAccurate(v164sq);
                                        float cluster = v164sq * v164sqrecip;
                                        float othersumRad = collideRad + thisPoint.radius;
                                        v164 *= -v164sqrecip;
                                        if(cluster < othersumRad){
                                            m128.z = v164;
                                            ScaleAddEq(thisPoint.pos, v164, cluster - othersumRad);
                                        }
                                        else Interp(m128.z, v164, (sumRad - cluster) / diffRad, m128.z);
                                    }
                                    else ScaleAddEq(thisPoint.pos, v164, sumRad * RecipSqrtAccurate(v164sq) - 1.0f);
                                }
                                break;
                            case CharCollide::kInsideCigar: // 4
                            case CharCollide::kInsideSphere: // 2
                                float v164sq42 = LengthSquared(v164);
                                float minusRad = collideRad - maxRad;
                                if(v164sq42 > minusRad * minusRad){
                                    if(diffRad > 0.0f){
                                        float v164sqrecip = RecipSqrtAccurate(v164sq42);
                                        float cluster = v164sq42 * v164sqrecip;
                                        float othersumRad = collideRad - thisPoint.radius;
                                        v164 *= -v164sqrecip;
                                        if(cluster > othersumRad){
                                            m128.z = v164;
                                            ScaleAddEq(thisPoint.pos, v164, cluster - othersumRad);
                                        }
                                        else Interp(m128.z, v164, (cluster - minusRad) / diffRad, m128.z);
                                    }
                                    else ScaleAddEq(thisPoint.pos, v164, minusRad * RecipSqrtAccurate(v164sq42) - 1.0f);
                                }
                                break;
                            default: break;
                        }
                    }

                    Scale(m128.y, rsa, t100.m.y);
                    Cross(t100.m.y, m128.z, t100.m.x);
                    t100.m.x *= RecipSqrtAccurate(LengthSquared(t100.m.x));
                    Normalize(t100.m.x, t100.m.x);
                    Cross(t100.m.x, t100.m.y, t100.m.z);
                    thisPoint.lastZ = t100.m.z;
                    if(thisPoint.bone) thisPoint.bone->SetWorldXfm(t100);
                    Subtract(v158, thisPoint.pos, thisPoint.force);
                    Vector3 v170;
                    Subtract(thisPoint.lastFriction, thisPoint.force, v170);
                    thisPoint.lastFriction = thisPoint.force;
                    thisPoint.force *= 1.0f - powed;
                    ScaleAddEq(thisPoint.force, v170, -mFriction);
                    Vector3 v17c;
                    Subtract(thisPoint.pos, v140, v17c);
                    ScaleAddEq(thisPoint.force, v17c, mInertia);
                    t100.v = thisPoint.pos;
                }
            }
        }
    }
}
#pragma pop

CharHair::Strand::Strand(Hmx::Object* o) : mShowSpheres(0), mShowCollide(0), mShowPose(0), mRoot(o, 0), mAngle(0.0f), mPoints(o), mHookupFlags(0) {
    mBaseMat.Identity();
    mRootMat.Identity();
}

void CharHair::Hookup(){
    if(unk6c) return;
    ObjPtrList<CharCollide, ObjectDir> colList(this, kObjListNoNull);
    for(ObjDirItr<CharCollide> it(Dir(), true); it != 0; ++it){
        colList.push_back(it);
    }
    Hookup(colList);
}

BinStream& operator>>(BinStream& bs, CharHair::Point& pt){
    bs >> pt.pos;
    bs >> pt.bone;
    bs >> pt.length;
    if(CharHair::gRev < 3){
        int i;
        char buf[0x100];
        bs >> i;
        bs.ReadString(buf, 0xff);
    }
    else if(CharHair::gRev == 3){
        int i;
        bs >> i;
    }
    bs >> pt.radius;
    if(CharHair::gRev > 1) bs >> pt.outerRadius;
    else pt.outerRadius = 0;
    if(CharHair::gRev == 6 || CharHair::gRev == 7 || CharHair::gRev == 8){
        float f;
        bs >> f;
        pt.radius += f;
        pt.outerRadius += f;
    }
    if(CharHair::gRev == 6){
        char buf[0x100];
        bs.ReadString(buf, 0xff);
    }
    if(CharHair::gRev < 8){
        pt.sideLength = -1.0f;
        if(CharHair::gRev > 5){
            int i;
            bs >> i >> i;
        }
    }
    else {
        bool b = false;
        if(CharHair::gRev < 9) bs >> b;
        bs >> pt.sideLength;
        if(CharHair::gRev < 9 && !b){
            pt.sideLength = -1.0f;
        }
    }
    if(CharHair::gRev > 9){
        bs >> pt.collide;
        bs >> pt.unk60;
        bs >> pt.unk64;
    }
    pt.collides.clear();
    pt.force.Zero();
    pt.lastFriction.Zero();
    pt.lastZ.Zero();
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

BinStream& operator>>(BinStream& bs, CharHair::Strand& strand){
    strand.Load(bs);
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

BEGIN_HANDLERS(CharHair)
    HANDLE_ACTION(reset, mReset = _msg->Int(2))
    HANDLE_ACTION(hookup, Hookup())
    HANDLE_ACTION(set_cloth, SetCloth(_msg->Int(2)))
    HANDLE_ACTION(freeze_pose, FreezePose())
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x46F)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharHair::Point)
    SYNC_PROP(bone, o.bone)
    SYNC_PROP(length, o.length)
    SYNC_PROP(collides, o.collides)
    SYNC_PROP(radius, o.radius)
    SYNC_PROP(outer_radius, o.outerRadius)
    SYNC_PROP(side_length, o.sideLength)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(CharHair::Strand)
    gStrand = &o;
    SYNC_PROP_SET(root, o.mRoot, o.SetRoot(_val.Obj<RndTransformable>(0)))
    SYNC_PROP_SET(angle, o.mAngle, o.SetAngle(_val.Float(0)))
    SYNC_PROP(points, o.mPoints)
    SYNC_PROP(hookup_flags, o.mHookupFlags)
    SYNC_PROP(show_spheres, o.mShowSpheres)
    SYNC_PROP(show_collide, o.mShowCollide)
    SYNC_PROP(show_pose, o.mShowPose)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharHair)
    gHair = this;
    SYNC_PROP(stiffness, mStiffness)
    SYNC_PROP(torsion, mTorsion)
    SYNC_PROP(inertia, mInertia)
    SYNC_PROP(gravity, mGravity)
    SYNC_PROP(weight, mWeight)
    SYNC_PROP(friction, mFriction)
    SYNC_PROP(min_slack, mMinSlack)
    SYNC_PROP(max_slack, mMaxSlack)
    SYNC_PROP(strands, mStrands)
    SYNC_PROP(simulate, mSimulate)
    SYNC_PROP(wind, mWind)
END_PROPSYNCS