#include "char/CharEyes.h"
#include "char/CharFaceServo.h"
#include "char/CharWeightSetter.h"
#include "char/CharLookAt.h"
#include "char/CharInterest.h"
#include "obj/DataFile.h"
#include "obj/DataUtl.h"
#include "utl/Symbols.h"

bool CharEyes::sDisableEyeDart;
bool CharEyes::sDisableEyeJitter;
bool CharEyes::sDisableInterestObjects;
bool CharEyes::sDisableProceduralBlink;
bool CharEyes::sDisableEyeClamping;

CharEyes::CharEyes() : mEyes(this), mInterests(this), mFaceServo(this, 0), mCamWeight(this, 0), mViewDirection(this, 0), mHeadLookAt(this, 0),
    unkc8(this, 0), unkd4(this, 0) {

}

BEGIN_CUSTOM_PROPSYNC(CharEyes::EyeDesc)
    SYNC_PROP(eye, o.mEye)
    SYNC_PROP(upper_lid, o.mUpperLid)
    SYNC_PROP(lower_lid, o.mLowerLid)
    SYNC_PROP(upper_lid_blink, o.mUpperLidBlink)
    SYNC_PROP(lower_lid_blink, o.mLowerLidBlink)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(CharEyes::CharInterestState)
    SYNC_PROP(interest, o.mInterest)
END_CUSTOM_PROPSYNC

// (DataNode& _val, DataArray* _prop, int _i, PropOp _op)
BEGIN_PROPSYNCS(CharEyes)
    SYNC_PROP(eyes, mEyes)
    SYNC_PROP(view_direction, mViewDirection)
    SYNC_PROP(interests, mInterests)
    SYNC_PROP(face_servo, mFaceServo)
    SYNC_PROP(camera_weight, mCamWeight)
    {
        static Symbol _s("default_interest_categories");
        if(sym == _s){
            if(_i++ < _prop->Size()){
                int res = 0;
                DataNode& node = _prop->Node(_i);
                switch(node.Type()){
                    case kDataInt:
                        res = node.Int(0);
                        break;
                    case kDataSymbol:
                        const char* bitstr = node.Sym(0).Str();
                        if(strncmp("BIT_", bitstr, 4) != 0){
                            MILO_FAIL("%s does not begin with BIT_", bitstr);
                        }
                        Symbol bitsym(bitstr);
                        DataArray* macro = DataGetMacro(bitsym);
                        if(!macro){
                            MILO_FAIL("PROPERTY_BITFIELD %s could not find macro %s", _s, bitsym);
                        }
                        res = macro->Int(0);
                        break;
                    default:
                        MILO_ASSERT(0, 0x67B);
                        break;
                }
                if(_op == kPropGet){
                    _val = DataNode(unk64 & res);
                }
                else {
                    if(_val.Int(0) != 0) unk64 |= res;
                    else unk64 &= ~res;
                }
            }
            else return PropSync(unk64, _val, _prop, _i, _op);
        }
    }
    SYNC_PROP(head_lookat, mHeadLookAt)
    SYNC_PROP(max_extrapolation, mMaxExtrapolation)
    SYNC_PROP(disable_eye_dart, sDisableEyeDart)
    SYNC_PROP(disable_eye_jitter, sDisableEyeJitter)
    SYNC_PROP(disable_interest_objects, sDisableInterestObjects)
    SYNC_PROP(disable_procedural_blink, sDisableProceduralBlink)
    SYNC_PROP(disable_eye_clamping, sDisableEyeClamping)
    {
        static Symbol _s("interest_filter_testing");
        if(sym == _s){
            if(_i++ < _prop->Size()){
                int res = 0;
                DataNode& node = _prop->Node(_i);
                switch(node.Type()){
                    case kDataInt:
                        res = node.Int(0);
                        break;
                    case kDataSymbol:
                        const char* bitstr = node.Sym(0).Str();
                        if(strncmp("BIT_", bitstr, 4) != 0){
                            MILO_FAIL("%s does not begin with BIT_", bitstr);
                        }
                        Symbol bitsym(bitstr);
                        DataArray* macro = DataGetMacro(bitsym);
                        if(!macro){
                            MILO_FAIL("PROPERTY_BITFIELD %s could not find macro %s", _s, bitsym);
                        }
                        res = macro->Int(0);
                        break;
                    default:
                        MILO_ASSERT(0, 0x67B);
                        break;
                }
                if(_op == kPropGet){
                    _val = DataNode(unka0 & res);
                }
                else {
                    if(_val.Int(0) != 0) unka0 |= res;
                    else unka0 &= ~res;
                }
                return true;
            }
            else return PropSync(unka0, _val, _prop, _i, _op);
        }
    }
    SYNC_PROP(min_target_dist, unk84)
    SYNC_PROP(ulid_track_up, unk88)
    SYNC_PROP(ulid_track_down, unk8c)
    SYNC_PROP(llid_track_up, unk90)
    SYNC_PROP(llid_track_down, unk94)
    SYNC_PROP(llid_track_rotate, unk98)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS