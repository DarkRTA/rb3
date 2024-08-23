#include "char/CharInterest.h"
#include "math/MathFuncs.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/DataUtl.h"
#include "obj/PropSync_p.h"
#include "rndobj/Cam.h"
#include "rndobj/Trans.h"
#include "rndobj/Graph.h"
#include "utl/Symbols.h"

INIT_REVS(CharInterest)

CharInterest::CharInterest() : mMaxViewAngle(20.0f), mPriority(1.0f), mMinLookTime(1.0f), mMaxLookTime(3.0f), mRefractoryPeriod(6.1f), mDartOverride(this, 0), mCategoryFlags(0), mOverrideMinTargetDistance(0), mMinTargetDistanceOverride(35.0f) {
    SyncMaxViewAngle();
}

CharInterest::~CharInterest(){
    
}

void CharInterest::SyncMaxViewAngle(){
    mMaxViewAngleCos = cos_f(mMaxViewAngle * 0.017453292f);
}

// https://decomp.me/scratch/ekyoO retail scratch
void CharInterest::Highlight(){
    RndGraph* oneframe = RndGraph::GetOneFrame();
    oneframe->AddSphere(WorldXfm().v, 1.0f, Hmx::Color(1.0f, 0.0f, 0.0f));
    Vector2 vec2;
    float wts = RndCam::sCurrent->WorldToScreen(WorldXfm().v, vec2);
    if(wts > 0.0f){
        vec2.x = vec2.x * TheRnd->Width();
        vec2.y = vec2.y * TheRnd->Height();
        vec2.y += 15.0;
        vec2.x -= 30.0;
        oneframe->AddString(MakeString("%s", Name()), vec2, Hmx::Color(1.0f,1.0f,1.0f));
    }
    if(mDartOverride){
        DataNode* minrad = mDartOverride->Property("min_radius", false);
        DataNode* maxrad = mDartOverride->Property("max_radius", false);
        if(minrad && maxrad){
            oneframe->AddSphere(WorldXfm().v, minrad->Float(0), Hmx::Color(0.7f, 0.7f, 0.7f));
            oneframe->AddSphere(WorldXfm().v, maxrad->Float(0), Hmx::Color(1.0f, 1.0f, 1.0f));
        }
    }
}

SAVE_OBJ(CharInterest, 0x52);

BEGIN_LOADS(CharInterest)
    LOAD_REVS(bs)
    ASSERT_REVS(6, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    bs >> mMaxViewAngle;
    bs >> mPriority;
    bs >> mMinLookTime;
    bs >> mMaxLookTime;
    bs >> mRefractoryPeriod;
    u32 temp = gRev + 0x10000;
    if (u16(temp - 2) <= 3) {
        ObjPtr<Hmx::Object, ObjectDir> obj(this, NULL);
        bs >> obj;
    } else if (temp > 5) { bs >> mDartOverride; } 
    if (gRev > 2) {
        bs >> mCategoryFlags;
        if (gRev == 3) {
            u8 x;
            bs >> x;
        } 
    }
    if (gRev > 4) {
        bs >> mOverrideMinTargetDistance;
        bs >> mMinTargetDistanceOverride;
    }
    SyncMaxViewAngle();
END_LOADS

BEGIN_COPYS(CharInterest)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(CharInterest)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMaxViewAngle)
        COPY_MEMBER(mPriority)
        COPY_MEMBER(mMinLookTime)
        COPY_MEMBER(mMaxLookTime)
        COPY_MEMBER(mRefractoryPeriod)
        COPY_MEMBER(mDartOverride)
        COPY_MEMBER(mCategoryFlags)
        COPY_MEMBER(mOverrideMinTargetDistance)
        COPY_MEMBER(mMinTargetDistanceOverride)
        SyncMaxViewAngle();
    END_COPYING_MEMBERS
END_COPYS

CharEyeDartRuleset* CharInterest::GetDartRulesetOverride() const { return mDartOverride; }

bool CharInterest::IsWithinViewCone(const Vector3& v1, const Vector3& v2){
    Vector3 v1c;
    v1c = WorldXfm().v;
    Vector3 v28;
    Subtract(v1c, v1, v28);
    Normalize(v28, v28);
    if(Dot(v2, v28) >= mMaxViewAngleCos) return true;
    else return false;
}

bool CharInterest::IsMatchingFilterFlags(int mask){
    if(mCategoryFlags != (mCategoryFlags & mask)) return false;
    if(mCategoryFlags == 0) return false;
    return true;
}

// retail scratch: https://decomp.me/scratch/JpD0G
float CharInterest::ComputeScore(const Vector3& v1, const Vector3& v2, const Vector3& v3, float f, int i, bool b){
    float neg99 = -0.99f;
    bool b2 = false;
    if(IsMatchingFilterFlags(i) || (b && mCategoryFlags == 0)){
        b2 = true;
    }
    if(!b2) return -1.0f;
    Vector3 v7c(WorldXfm().v);
    Vector3 v88;
    Subtract(v7c, v2, v88);
    float lensq = LengthSquared(v88);
    Normalize(v88, v88);
    
    float dot = Dot(v1, v88);
    float f1 = 0.0f;
    if(dot >= mMaxViewAngleCos) f1 = 1.0f;
    
    float dot2 = Dot(v3, v88);
    float f2 = 0.0f;
    if(dot2 >= mMaxViewAngleCos) f2 = 1.0f;
    
    float f7 = -(lensq * f - 1.0f);
    if(IsNaN(f7)){
        f7 = 0.2f;
    }
    
    float f4 = f7 + f1 + f2 + neg99;
    if(f4 >= 0.0f){
        f4 = f4 + RandomFloat(-0.25f, 0.25);
    }
    f4 *= mPriority;
    return f4;
}

BEGIN_PROPSYNCS(CharInterest)
    SYNC_PROP_MODIFY(max_view_angle, mMaxViewAngle, SyncMaxViewAngle())
    SYNC_PROP(priority, mPriority)
    SYNC_PROP(min_look_time, mMinLookTime)
    SYNC_PROP(max_look_time, mMaxLookTime)
    SYNC_PROP(refractory_period, mRefractoryPeriod)
    SYNC_PROP(dart_ruleset_override, mDartOverride)
    {
        static Symbol _s("category_flags");
        if(sym == _s){
            int plusone = _i + 1;
            if(plusone < _prop->Size()){
                DataNode& node = _prop->Node(plusone);
                int flags = 0;
                switch(node.Type()){
                    case kDataInt:
                        flags = node.Int(0);
                        break;
                    case kDataSymbol:
                        const char* str = node.Sym(0).Str();
                        if(strncmp("BIT_", str, 4) != 0){
                            MILO_FAIL("%s does not begin with BIT_", str);
                        }
                        Symbol bitsym(str + 4);
                        DataArray* macro = DataGetMacro(bitsym);
                        if(!macro){
                            MILO_FAIL("PROPERTY_BITFIELD %s could not find macro %s", _s, bitsym);
                        }
                        flags = macro->Int(0);
                        break;
                    default:
                        MILO_ASSERT(0, 0x138);
                        break;
                }
                MILO_ASSERT(_op <= kPropInsert, 0x138);
                if(_op == kPropGet){
                    _val = DataNode(mCategoryFlags & flags);
                }
                else {
                    int themask = _val.Int(0);
                    if(themask != 0) mCategoryFlags |= themask;
                    else mCategoryFlags &= ~themask;
                }
                return true;
            }
            else return PropSync(mCategoryFlags, _val, _prop, _i + 1, _op);
        }
    }
    SYNC_PROP(overrides_min_target_dist, mOverrideMinTargetDistance)
    SYNC_PROP(min_target_dist_override, mMinTargetDistanceOverride)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS

BEGIN_HANDLERS(CharInterest)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x141)
END_HANDLERS
