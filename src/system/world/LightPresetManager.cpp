#include "world/LightPresetManager.h"
#include "world/Dir.h"

// fn_805B04EC
LightPresetManager::LightPresetManager(WorldDir* dir) : mParent(dir), mPresetOverride(0), mPresetNew(0), mPresetPrev(0), unk30(0), unk34(0), unk38(0),
    unk3c(0), mBlend(1.0f), unk44(0), unk48(0), unk4c(0) {
    MILO_ASSERT(mParent, 0x21);
}

LightPresetManager::~LightPresetManager(){
    
}

// fn_805B0898 ?
void LightPresetManager::SyncObjects(){
    mPresets.clear();
    for(ObjDirItr<LightPreset> it(mParent, true); it != 0; ++it){
        if(it->PlatformOk()){
            std::map<Symbol, std::vector<LightPreset*> >::iterator mapIt = mPresets.find(it->Category());
            if(mapIt != mPresets.end()){
                mapIt->second.push_back(it);
            }
        }
    }
}

void LightPresetManager::SendLightingMessage(Symbol s){
    char buf[0x100];
    static Message msg("");
    strcpy(buf, "lighting_");
    strcpy(buf, s.Str());
    msg->Node(1) = DataNode(Symbol(buf));
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
    unk4c = false;
    mBlend = 1.0f;
    unk48 = 0;
    unk44 = 0;
}

void LightPresetManager::Enter(){ Reset(); }

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