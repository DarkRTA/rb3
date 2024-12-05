#include "rndobj/BoxMap.h"
#include "rndobj/Lit.h"

Vector3 BoxMapLighting::sAxisDir[6] = {
    Vector3(1,0,0),
    Vector3(-1,0,0),
    Vector3(0,1,0),
    Vector3(0,-1,0),
    Vector3(0,0,1),
    Vector3(0,0,-1)
};

BoxMapLighting::BoxMapLighting(){
    Clear();
}

void BoxMapLighting::Clear(){
    mQueued_Directional.Clear();
    mQueued_Point.Clear();
    mQueued_Spot.Clear();
}

bool BoxMapLighting::QueueLight(RndLight* light, float colorScale){
    if(light->Showing()){
        Hmx::Color lightColor(light->GetColor());
        lightColor.red *= colorScale;
        lightColor.green *= colorScale;
        lightColor.blue *= colorScale;
        switch(light->GetType()){
            case RndLight::kDirectional:
            case RndLight::kFakeSpot:
                LightParams_Directional* paramsDirectional;
                if(ParamsAt(paramsDirectional)){
                    paramsDirectional->mColor = lightColor;
                    Negate(light->WorldXfm().m.y, paramsDirectional->mDirection);
                    return true;
                }
                break;
            case RndLight::kPoint:
                LightParams_Point* paramsPoint;
                if(ParamsAt(paramsPoint)){
                    paramsPoint->unk0 = light->WorldXfm().v;
                    paramsPoint->mColor = lightColor;
                    paramsPoint->mRange = light->Range();
                    paramsPoint->mFalloffStart = light->FalloffStart();
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

void BoxMapLighting::ApplyQueuedLights(Hmx::Color* color, const Vector3* v3) const {
    for(int i = 0; i < mQueued_Directional.NumElements(); i++){
        ApplyLight(color, mQueued_Directional[i]);
    }
    if(v3){
        for(int i = 0; i < mQueued_Point.NumElements(); i++){
            ApplyLight(color, mQueued_Point[i], *v3);
        }
        if(mQueued_Spot.NumElements() != 0){
            ApplyLight(color, mQueued_Spot, *v3);
        }
    }
}

bool BoxMapLighting::CacheData(BoxMapLighting::LightParams_Spot& spot){
    if(spot.unk44 > 0){
        float f1 = spot.unk48;
        if(spot.unk4c >= f1 && (spot.mColor.red > 0.003921569f || spot.mColor.green > 0.003921569f || spot.mColor.blue > 0.003921569f)){
            f1 = (f1 * spot.unk44) / (spot.unk4c - f1);
            Vector3 v58;
            Scale(spot.unk0, f1, v58);
            Vector3 v4c;
            Subtract(spot.unk38, v58, v4c);
            float f2 = spot.unk4c / (spot.unk44 + f1);
            f2 *= f2;
            float f3 = 1.0f / (spot.unk44 * 2.0f);
            f2 = (1.0f - f2) / (f2 + 1.0f);
            spot.unk1c = v4c;
            spot.unk28 = f2;
            spot.unk30 = f3;
            spot.unk34 = f1 * f3;
            spot.unk2c = 1.0f / (1.0f - f2);
            return true;
        }
    }
    mQueued_Spot.RemoveEntry();
    return 0;
}