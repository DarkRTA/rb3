#include "char/CharClipDisplay.h"
#include "rndobj/Rnd.h"
#include "obj/MsgSource.h"

float CharClipDisplay::sEm;
ObjectDir* CharClipDisplay::sDir;

void CharClipDisplay::Init(ObjectDir* dir){
    sDir = dir;
    sEm = TheRnd->DrawString("", Vector2(0,0), Hmx::Color(1.0f, 0.0f, 0.0f), false).y;
}

MsgSource* CharClipDisplay::FindSource(Hmx::Object* o){
    for(ObjDirItr<MsgSource> it(ObjectDir::Main(), false); it != 0; ++it){
        for(std::list<MsgSource::Sink>::iterator lit = it->mSinks.begin(); lit != it->mSinks.end(); ++lit){
            if((*lit).obj == o) return it;
        }
    }
    return 0;
}

void CharClipDisplay::SetClip(CharClip* clip, bool b){
    unk0 = clip;
    SetText(clip->Name());
    SetStartEnd(clip->StartBeat(), clip->EndBeat(), b);
}

void CharClipDisplay::SetText(const char* text){
    strcpy(unk24, text);
    unk14 = TheRnd->DrawString(text, Vector2(0,0), Hmx::Color(1.0f, 0.0f, 0.0f), false).x + sEm;
}

float CharClipDisplay::LineSpacing(){ return sEm * 2.0f; }