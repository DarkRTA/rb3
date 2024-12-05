#include "rndobj/BoxMap.h"
#include "rndobj/Lit.h"

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
                    paramsPoint->unk1c = light->Range();
                    paramsPoint->unk20 = light->FalloffStart();
                    return true;
                }
                break;
            default:
                break;
        }
    }
    return false;
}