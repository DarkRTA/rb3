#include "rndobj/Anim.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

int gRateUnits[5] = {0, 1, 2, 1, 3};
float gRateFpu[5] = {30.0f, 480.0f, 30.0f, 1.0f, 30.0f};

int RndAnimatable::RateToTaskUnits(Rate myRate){
    return gRateUnits[myRate];
}

int RndAnimatable::Units() const {
    return gRateUnits[mRate];
}

float RndAnimatable::FramesPerUnit(){
    return gRateFpu[mRate];
}

bool RndAnimatable::ConvertFrames(float& f){
    f /= FramesPerUnit();
    return (Units() != 1);
}

RndAnimatable::RndAnimatable() : mFrame(0.0f), mRate(k30_fps) {
    
}

void RndAnimatable::Save(BinStream&){
    MILO_ASSERT(0, 0x7A);
}

void RndAnimatable::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    const RndAnimatable* c = dynamic_cast<const RndAnimatable*>(o);
    if(c){
        mFrame = c->mFrame;
        mRate = c->mRate;
    }
}

BEGIN_HANDLERS(RndAnimatable);
    HANDLE_ACTION(set_frame, SetFrame(_msg->Float(2), 1.0f));
    HANDLE_EXPR(frame, mFrame);
    HANDLE_ACTION(set_key, SetKey(_msg->Float(2)));
    HANDLE_EXPR(end_frame, EndFrame());
    HANDLE_EXPR(start_frame, StartFrame());
    HANDLE(animate, OnAnimate);
    HANDLE_ACTION(stop_animation, StopAnimation());
    HANDLE_EXPR(is_animating, IsAnimating());
    HANDLE(convert_frames, OnConvertFrames);
    HANDLE_CHECK(0x16C);
END_HANDLERS;

DataNode RndAnimatable::OnConvertFrames(DataArray* arr){
    float f = arr->Float(2);
    bool conv = ConvertFrames(f);
    *arr->Var(2) = DataNode(f);
    return DataNode(conv);
}

BEGIN_PROPSYNCS(RndAnimatable);
    SYNC_PROP(rate, (int&)mRate);
    // SYNC_PROP(frame, mFrame);
    if(sym == frame){
        bool synced = PropSync(mFrame, _val, _prop, _i + 1, _op);
        if(!synced) return false;
        else {
            if(!(_op & (kPropGet|kPropSize))){
                SetFrame(mFrame, 1.0f);
            }
            return true;
        }
    }
END_PROPSYNCS;
