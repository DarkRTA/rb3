#ifndef BANDOBJ_CROWDAUDIO_H
#define BANDOBJ_CROWDAUDIO_H

#include "obj/Object.h"
#include "rndobj/Poll.h"
#include "synth/BinkClip.h"
#include "synth/Faders.h"

class CrowdAudio : public RndPollable {
    CrowdAudio();
    virtual ~CrowdAudio();

    static void Init();

    OBJ_CLASSNAME(CrowdAudio)
    OBJ_SET_TYPE(CrowdAudio)
    NEW_OBJ(CrowdAudio);

    ObjPtr<BinkClip, ObjectDir> mClip;
    ObjPtr<BinkClip, ObjectDir> mClip2;
    ObjPtr<BinkClip, ObjectDir> mClip3;
    Fader* mFader;
    bool unk_30;
    float unk_34, unk_38;
    Fader* unk_3c;
    float unk_40;
    Fader* unk_44;
};

#endif // BANDOBJ_CROWDAUDIO_H