#include "os/DiscErrorMgr_Wii.h"
#include "os/Debug.h"
#include "revolution/SC.h"

bool gInDiscError;

void DiscErrorMgrWii::InitDiscError(){
    const char* lang = "eng";
    switch(SCGetLanguage()){
        case 3: lang = "fre"; break;
        case 5: lang = "ita"; break;
        case 2: lang = "deu"; break;
        case 4: lang = "esl"; break;
        case 6: lang = "nld"; break;
        default: break;
    }
    char buf[128];
    unsigned long ul = 0;
    sprintf(buf, "DiscError/InsertDisc_%s.tpl", lang);
    mEjectErrorTpl = (TPLPalette*)LoadFile(buf, ul);
    if(mEjectErrorTpl){
        TPLBind(mEjectErrorTpl);
        DCStoreRange(mEjectErrorTpl, ul);
    }
    else OSReturnToMenu();
    sprintf(buf, "DiscError/RetryError_%s.tpl", lang);
    mRetryErrorTpl = (TPLPalette*)LoadFile(buf, ul);
    if(mRetryErrorTpl){
        TPLBind(mRetryErrorTpl);
        DCStoreRange(mRetryErrorTpl, ul);
    }
    else OSReturnToMenu();
}

DiscErrorMgrWii::DiscErrorMgrWii() : mDiscError(0), mRetryError(0), mMovieReadError(0), mActive(0), mEjectErrorTpl(0), mRetryErrorTpl(0) {

}

void DiscErrorMgrWii::Init(){
    if(!mEjectErrorTpl) InitDiscError();
}

void DiscErrorMgrWii::SetDiscError(bool err){
    if(mDiscError != err) mDiscError = err;
}

void DiscErrorMgrWii::LoopUntilNoDiscError(DVDFileInfo*, bool){
    MILO_WARN("LoopUntilNoDiscError");
}

void DiscErrorMgrWii::RegisterCallback(Callback* cb){
    mCallbacks.push_back(cb);
}

void DiscErrorMgrWii::UnregisterCallback(Callback* cb){
    mCallbacks.remove(cb);
}

void DiscErrorMgrWii::NotifyCallbacksStart(){
    MILO_ASSERT(!gInDiscError, 0x128);
    gInDiscError = true;
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->DiscErrorStart();
    }
}

void DiscErrorMgrWii::NotifyCallbacksEnd(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->DiscErrorEnd();
    }
    MILO_ASSERT(gInDiscError, 0x133);
    gInDiscError = false;
}

void DiscErrorMgrWii::NotifyCallbacksDiscDraw(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        if(mRetryError) (*it)->DiscErrorDraw(mRetryErrorTpl);
        else (*it)->DiscErrorDraw(mEjectErrorTpl);
    }
}