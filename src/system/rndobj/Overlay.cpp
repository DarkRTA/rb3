#include "rndobj/Overlay.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Rnd.h"

bool RndOverlay::sTopAligned = true;
std::list<RndOverlay*> RndOverlay::sOverlays;

void RndOverlay::Init(){
    DataArray* cfg = SystemConfig("rnd");
    DataArray* overlaysArr = cfg->FindArray("overlays", true);
    for(int i = 1; i < overlaysArr->Size(); i++){
        sOverlays.push_back(new RndOverlay(overlaysArr->Array(i)));
    }
}

void RndOverlay::Terminate() {
    for (std::list<RndOverlay*>::iterator i = sOverlays.begin(); i != sOverlays.end(); i){
        delete *i;
        i = sOverlays.erase(i);
    }
}

RndOverlay::~RndOverlay(){

}

void RndOverlay::DrawAll(bool b){
    float toUse = sTopAligned ? 0.0212f : 0.9788;
    for(std::list<RndOverlay*>::iterator it = sOverlays.begin(); it != sOverlays.end(); it++){
        RndOverlay* cur = (*it);
        if(!b || cur->mModal){
            if(sTopAligned) cur->Draw(toUse);
            else {
                int numstrings = 0;
                for(std::list<String>::iterator lit = cur->mLines.begin(); lit != cur->mLines.end(); lit++){
                    numstrings++;
                }
                float drawn = TheRnd->DrawStringScreen("", Vector2(0,0), cur->mTextColor, true);
            }
        }
    }
}

void RndOverlay::TogglePosition(){
    sTopAligned = !sTopAligned;
}

RndOverlay* RndOverlay::Find(Symbol s, bool fail){
    for(std::list<RndOverlay*>::iterator it = sOverlays.begin(); it != sOverlays.end(); it++){
        if(s == (*it)->mName) return *it;
    }
    if(fail) MILO_FAIL("Could not find overlay \"%s\"", s);
    return 0;
}

RndOverlay::RndOverlay(const DataArray* da) : mShowing(0), mLines(), mLine(), mBackColor(0.0f, 0.0f, 0.0f, 0.2f), mTextColor(), 
    mCursorChar(-1), mCallback(0), mTimer(), mTimeout(0.0f), mModal(0), mDumpCount(0) {
    mName = da->Str(0);
    int lines = 1;
    da->FindData("lines", lines, false);
    SetLines(lines);
    da->FindData("showing", mShowing, false);
    da->FindData("color", mBackColor, false);
    da->FindData("modal", mModal, false);
    da->FindData("text_color", mTextColor, false);
}

void RndOverlay::SetLines(int lines) {
    MILO_ASSERT(lines >= 1, 117);
    unsigned int linesize = 0;
    for(std::list<String>::iterator it = mLines.begin(); it != mLines.end(); it++) linesize++;
    if(lines != linesize){
        mLines.resize(lines);
        mLine = mLines.begin();
    }
}

void RndOverlay::SetTimeout(float f){
    mTimeout = f * 1000.0f + SystemMs();
}

String& RndOverlay::CurrentLine(){
    if(mLine == mLines.begin()){
        String newstr;
        mLine = mLines.erase(mLine);
        mLines.insert(mLine, newstr);
        (*mLine).reserve(0x7F);
    }
    return *mLine;
}

void RndOverlay::Clear(){
    for(std::list<String>::iterator it = mLines.begin(); it != mLines.end(); it++){
        (*it).erase();
    }
    mLine = mLines.begin();
    mCursorChar = -1;
}
