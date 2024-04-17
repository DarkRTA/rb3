#include "CrowdAudio.h"

void CrowdAudio::Init() { Hmx::Object::RegisterFactory(StaticClassName(), NewObject); }

CrowdAudio::CrowdAudio() : mClip(NULL, NULL), mClip2(NULL, NULL), mClip3(NULL, NULL) {
    mFader = Hmx::Object::New<Fader>();
    unk_30 = false;
    unk_34 = 0;
    unk_38 = 1000;
    unk_3c = Hmx::Object::New<Fader>();
    unk_40 = 1000;
    unk_44 = Hmx::Object::New<Fader>();
}