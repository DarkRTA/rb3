#include "world/LightPresetManager.h"
#include "world/Dir.h"
#include "utl/Symbols.h"

// fn_805B04EC
LightPresetManager::LightPresetManager(WorldDir* dir) : mParent(dir), mPresetOverride(0), mPresetNew(0), mPresetPrev(0), unk30(0), unk34(0), unk38(0),
    unk3c(0), mBlend(1.0f), unk44(0), unk48(0), mIgnoreLightingEvents(0) {
    MILO_ASSERT(mParent, 0x21);
}

LightPresetManager::~LightPresetManager(){
    
}

// fn_805B0898 ?
void LightPresetManager::SyncObjects(){
    mPresets.clear();
    for(ObjDirItr<LightPreset> it(mParent, true); it != 0; ++it){
        if(it->PlatformOk()){
            mPresets[it->Category()].push_back(it);
        }
    }
}

void LightPresetManager::SendLightingMessage(Symbol s){
    char buf[0x100];
    static Message msg("");
    strcpy(buf, "lighting_");
    strcpy(buf, s.Str());
    msg.SetType(buf);
    mParent->Handle(msg, false);
}

void LightPresetManager::Reset(){
    mPresetNew = 0;
    mPresetPrev = 0;
    mPresetOverride = 0;
    unk30 = 0;
    unk34 = 0;
    unk38 = 0;
    unk3c = false;
    mLastCategory = Symbol();
    mIgnoreLightingEvents = false;
    mBlend = 1.0f;
    unk48 = 0;
    unk44 = 0;
}

void LightPresetManager::Enter(){ Reset(); }

void LightPresetManager::Poll(){
    LightPreset* pnew = mPresetNew;
    LightPreset* pprev = mPresetPrev;
    float u30 = unk30;
    float u34 = unk34;
    float blend = mBlend;
    if(mPresetOverride){
        float time = TheTaskMgr.Time(mPresetOverride->Units());
        float f7 = 1.0f;
        if(unk44 > 0.0f){
            f7 = (time - unk38) / unk44;
        }
        f7 = Clamp(0.0f, 1.0f, f7);
        if(unk48 == 1){
            f7 = 1.0f - f7;
        }
        if(f7 > 0.0f){
            pprev = pnew;
            pnew = mPresetOverride;
            u34 = u30;
            u30 = unk38;
            blend = f7;
        }
        else if(unk48 == 1){
            mPresetOverride = 0;
            unk38 = 0;
            unk44 = 0;
            unk48 = 0;
        }
    }
    if(pnew){
        float time = TheTaskMgr.Time(pprev->Units());
        float fpu = pnew->FramesPerUnit();
        float max = Max(0.0f, (time - u30) * fpu);
        if(pprev && pprev != pnew){
            float time2 = TheTaskMgr.Time(pprev->Units());
            float fpu2 = pprev->FramesPerUnit();
            float max2 = Max(0.0f, (time2 - u34) * fpu2);
            pprev->SetFrameEx(max2, 1.0f - blend, false);
            pnew->SetFrameEx(max, blend, false);
            unk3c = false;
        }
        else {
            pnew->SetFrameEx(max, 1.0f, unk3c);
            unk3c = true;
        }
    }
    UpdateOverlay();
}

void LightPresetManager::StartPreset(LightPreset* preset, bool b){
    MILO_ASSERT(preset, 0xAE);
    LightPreset* toSet = b ? mPresetNew : mPresetPrev;
    toSet = preset;
    preset->StartAnim();
    float time = TheTaskMgr.Time(preset->Units());
    if(b) unk30 = time;
    else unk34 = time;
    unk3c = false;
    UpdateOverlay();
}

void LightPresetManager::SetPresetsEquivalent(bool b){
    if(b){
        mPresetPrev = mPresetNew;
        unk34 = unk30;
    }
    else {
        mPresetNew = mPresetPrev;
        unk30 = mPresetPrev ? TheTaskMgr.Time(mPresetPrev->Units()) : 0;
        unk34 = mPresetPrev ? TheTaskMgr.Time(mPresetPrev->Units()) : 0;
    }
}

void LightPresetManager::SchedulePstKey(LightPreset::KeyframeCmd cmd){
    if(!mIgnoreLightingEvents){
        if(mPresetNew) mPresetNew->OnKeyframeCmd(cmd);
        UpdateOverlay();
    }
}

#pragma push
#pragma pool_data off
void LightPresetManager::Interp(Symbol s1, Symbol s2, float f){
    mBlend = f;
    if(!mPresetNew){
        SendLightingMessage(s2);
        SetLighting(s2, true);
    }
    if(!mPresetPrev){
        SetLighting(s1, false);
    }
    if(!mBlend){
        SetPresetsEquivalent(false);
    }
    if(!mPresetNew || !mPresetPrev){
        if(!mPresetNew && !mPresetPrev){ 
            MILO_NOTIFY_ONCE("No light preset for categories %s, %s", s1.Str(), s2.Str());
            return;
        }
        MILO_NOTIFY_ONCE("No light preset for category %s", mPresetNew ? s2.Str() : s1.Str());
    }
    else {
        Symbol prev_cat = mPresetPrev->Category();
        if(prev_cat != s1 && mPresetNew->Category() == s1){
            SetPresetsEquivalent(true);
        }
        else if(mPresetNew->Category() != s2 && prev_cat == s2){
            SetPresetsEquivalent(false);
        }
        if(mPresetNew->Category() != s2){
            SendLightingMessage(s2);
            SetLighting(s2, true);
        }
        if(mPresetPrev->Category() != s1){
            SetLighting(s1, false);
        }
    }
}
#pragma pop

void LightPresetManager::ForcePreset(LightPreset* p, float f){
    if(p){
        if(mPresetOverride != p || unk48 == 1){
            mPresetOverride = p;
            unk38 = TheTaskMgr.Time(p->Units());
            unk44 = f;
            unk48 = 0;
        }
        return;
    }
    else if(mPresetOverride){
        unk38 = TheTaskMgr.Time(mPresetOverride->Units());
        unk44 = f;
        unk48 = 1;
    }
}

void LightPresetManager::ForcePresets(LightPreset* p1, LightPreset* p2, float f){
    if(p1 && p2 && p1 != p2){
        StartPreset(p1, false);
        StartPreset(p2, true);
        mBlend = 0.5f;
    }
    else ForcePreset(p1, f);
}

void LightPresetManager::StompPresets(LightPreset* presetA, LightPreset* presetB){
    if(presetA && presetB && presetA != presetB){
        StartPreset(presetA, false);
        StartPreset(presetB, true);
        mBlend = 0.5f;
        MILO_ASSERT(mPresetPrev = presetA, 0x157);
        MILO_ASSERT(mPresetNew = presetB, 0x158);
    }
    else if(presetA && presetA == presetB){
        StartPreset(presetA, true);
        SetPresetsEquivalent(true);
        mBlend = 1.0f;
        MILO_ASSERT(mPresetPrev = presetA, 0x160);
        MILO_ASSERT(mPresetNew = presetA, 0x161);
    }
}

DataNode LightPresetManager::OnToggleLightingEvents(DataArray* da){
    mIgnoreLightingEvents = mIgnoreLightingEvents == 0;
    return DataNode(mIgnoreLightingEvents);
}

DataNode LightPresetManager::OnForcePreset(DataArray* da){
    LightPreset* p = da->Obj<LightPreset>(2);
    ForcePreset(p, da->Size() > 2 ? da->Float(3) : 0);
    return DataNode(0);
}

DataNode LightPresetManager::OnForceTwoPresets(DataArray* da){
    LightPreset* p1 = da->Obj<LightPreset>(2);
    LightPreset* p2 = da->Obj<LightPreset>(3);
    ForcePresets(p1, p2, da->Size() > 3 ? da->Float(4) : 0);
    return DataNode(0);
}

void LightPresetManager::SelectPreset(LightPreset* p, bool b){
    if(p) StartPreset(p, b);
    else {
        ReportError();
        if(TheLoadMgr.EditMode()){
            if(b) mPresetNew = 0;
            else mPresetPrev = 0;
        }
    }
}

void LightPresetManager::SetLighting(Symbol s, bool b){
    if(!mIgnoreLightingEvents){
        Symbol thes = s;
        mLastCategory = thes;
        SelectPreset(PickRandomPreset(thes), b);
    }
}

void LightPresetManager::ReportError(){
    String str;
    str += " Category (";
    str += mLastCategory.Str();
    str += ")";
    MILO_NOTIFY_ONCE("%s Can't find light preset %s", TheTaskMgr.GetMBT(), str.c_str());
}

void PrintPreset(const char* str, LightPreset* preset){
    if(preset){
        MILO_LOG("%s: %s ", str, preset->Name());
        if(preset->Manual()){
            MILO_LOG("Manual (Keyframe: %d), frame %f\n", preset->GetCurrentKeyframe(), preset->mFrame);
        }
        else {
            MILO_LOG("Animated (Keyframe: %d), frame %f\n", preset->GetCurrentKeyframe(), preset->mFrame);
        }
    }
    else MILO_LOG("%s: [NONE]\n", str);
}

void LightPresetManager::UpdateOverlay(){
    RndOverlay* o = RndOverlay::Find("light_preset", true);
    TextStream* ts = TheDebug.mReflect;
    if(o->Showing()){
        TheDebug.SetReflect(o);
        MILO_LOG("Last Category: %s\n", mLastCategory);
        PrintPreset("PresetNew", mPresetNew);
        PrintPreset("PresetPrev", mPresetPrev);
        PrintPreset("PresetOverride", mPresetOverride);
        MILO_LOG("Blend: %f\n", mBlend);
    }
    TheDebug.SetReflect(ts);
}

void LightPresetManager::GetPresets(LightPreset*& prevl, LightPreset*& newl){
    prevl = mPresetPrev;
    newl = mPresetNew;
}


DataNode LightPresetManager::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? dynamic_cast<Hmx::Object*>(this) : 0, sym);
    HANDLE(toggle_lighting_events, OnToggleLightingEvents)
    HANDLE(force_preset, OnForcePreset)
    HANDLE(force_two_presets, OnForceTwoPresets)
    HANDLE_ACTION(reset_presets, Reset())
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, 0x1F3, PathName(dynamic_cast<Hmx::Object*>(this)), sym);
END_HANDLERS