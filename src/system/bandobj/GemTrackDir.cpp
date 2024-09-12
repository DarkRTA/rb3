#include "bandobj/GemTrackDir.h"

#pragma push
#pragma dont_inline on
GemTrackDir::GemTrackDir() : BandTrack(this), unk484(1), unk488(-1), unk48c(-1), unk490(0), unk494(0), unk498(2.25f), unk49c(0), unk4a0(0), unk4a4(this, 0),
    unk4b0(this, 0), unk4bc(this, 0), unk4c8(this, 0), unk4d4(this, 0), unk4e0(this, 0), unk4ec(this, 0), unk4f8(this, 0), unk504(this, 0), unk510(this, 0),
    unk51c(this, 0), unk528(this, 0), unk534(this, 0), unk540(this, 0), unk54c(this, 0), unk558(this, 0), unk564(this, 0), unk5a8(this, 0), unk5b4(this, 0),
    unk5c0(this, 0), unk5cc(this, 0), unk5d8(this, 0), unk5e4(this, 0), unk5f0(this, kObjListNoNull), unk600(this, 0), unk60c(this, 0), unk618(this, 0),
    unk624(this, 0), unk630(this, 0), unk63c(this, 0), unk648(this, 0), unk654(this, 0), unk660(this, 0), unk66c(this, 0), unk678(-1.0f), unk67c(-1.0f),
    unk698(0), unk6a4(0), unk6a8(this, 0), unk6e4(0), unk6e8(0), unk6e9(0), unk6ea(0), unk6ec(0x96) {
    ObjPtr<RndPropAnim, ObjectDir> propAnim(this, 0);
    ObjPtr<EventTrigger, ObjectDir> trig(this, 0);
    for(int i = 0; i < 6; i++){
        unk570.push_back(propAnim);
        unk578.push_back(propAnim);
        unk580.push_back(propAnim);
        unk588.push_back(propAnim);
        unk590.push_back(std::make_pair(trig, trig));
        unk598.push_back(std::make_pair(trig, trig));
    }
    for(int i = 0; i < 3; i++){
        unk5a0.push_back(trig);
    }
    for(int i = 0; i < 5; i++){
        unk69c.push_back(0);
    }
    DataArray* cfg = SystemConfig();
    DataArray* arr = cfg->FindArray("fake_finger_shape", false);
    if(arr){
        for(int i = 0; i < 6; i++){
            unk6f0.FretDown(i, arr->Int(i + 1));
        }
        unk6e9 = true;
        if(arr->Size() > 7) unk6ea = arr->Int(7);
    }
}

GemTrackDir::~GemTrackDir(){
    RELEASE(unk698);
}
#pragma pop