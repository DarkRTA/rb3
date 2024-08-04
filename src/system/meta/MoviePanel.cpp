#include "meta/MoviePanel.h"
#include "os/PlatformMgr.h"
#include "rndobj/Rnd.h"
#include "ui/UI.h"
#include "obj/Task.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

float gTempBS = 0.55263156f;

MoviePanel::MoviePanel() : mSubtitlesLoader(0), mSubtitles(0), unk68(0), unk6c(1), mSubtitleLabel(0), mPauseHintAnim(0), unk78(0), mTimeShowHintStarted(0.0f), mShowMenu(0), unk81(0) {

}

void MoviePanel::SetTypeDef(DataArray* da){
    if(TypeDef() != da){
        UIPanel::SetTypeDef(da);
        da->FindData("preload", mPreload, true);
        da->FindData("audio", mAudio, true);
        da->FindData("loop", mLoop, true);
    }
}

void MoviePanel::Load(){
    UIPanel::Load();
    mMovies.clear();
    DataArray* arr = SystemConfig("videos", Property("videos", true)->Str(0))->FindArray("files", true);
    for(int i = 1; i < arr->Size(); i++){
        mMovies.push_back(arr->Str(i));
    }
}

bool MoviePanel::IsLoaded() const {
    if(!mMovie.Ready()) return false;
    else if(!mSubtitlesLoader || mSubtitlesLoader->IsLoaded()) return UIPanel::IsLoaded();
    else return false;
}

void MoviePanel::FinishLoad(){
    UIPanel::FinishLoad();
    if(mSubtitlesLoader){
        mSubtitles = mSubtitlesLoader->Data();
        mSubtitles->AddRef();
        delete mSubtitlesLoader;
        mSubtitlesLoader = 0;
        if(mDir) mSubtitleLabel = mDir->Find<UILabel>("subtitles.lbl", false);
    }
    else mSubtitles = 0;
    if(mDir) mPauseHintAnim = mDir->Find<RndAnimatable>("fade_pausehint.anim", true);
}

void MoviePanel::Enter(){
    UIPanel::Enter();
    ThePlatformMgr.mDiscErrorMgr->RegisterCallback(this);
    ThePlatformMgr.SetHomeMenuEnabled(false);
}

void MoviePanel::Exit(){
    UIPanel::Exit();
    if(!mPreload) mMovie.End();
    mShowMenu = false;
    ThePlatformMgr.mDiscErrorMgr->UnregisterCallback(this);
    ThePlatformMgr.SetHomeMenuEnabled(true);
    if(TheRnd->GetAspect() != Rnd::kWidescreen){
        TheRnd->SetAspect(Rnd::kLetterbox);
    }
}

void MoviePanel::Unload(){
    UIPanel::Unload();
    if(mPreload) mMovie.End();
    if(mSubtitles){
        mSubtitles->Release();
        mSubtitles = 0;
    }
}

void MoviePanel::Poll(){
    UIPanel::Poll();
    if(mState == kUnloaded) return;
    if(!mMovie.Poll() && TheUI->GetTransitionState() == kTransitionNone){
        DataNode handled = HandleType(movie_done_msg);
        if(handled == DataNode(kDataUnhandled, 0)){
            mMovie.End();
            PlayMovie();
        }
    }
    else if(mSubtitles && mSubtitleLabel){
        int frame = mMovie.GetFrame();
        DataArray* arr = mSubtitles->Array(unk68);
        if(unk6c){
            if(arr->Int(0) <= frame){
                mSubtitleLabel->SetSubtitle(arr);
                unk6c = false;
            }
        }
        if(arr->Int(1) < frame){
            DataArray* thisarr = 0;
            if(mSubtitles->Size() > unk68 + 1){
                thisarr = mSubtitles->Array(unk68 + 1);
            }
            if(thisarr){
                if(thisarr->Int(0) <= frame){
                    mSubtitleLabel->SetSubtitle(thisarr);
                    unk6c = false;
                    unk68++;
                    goto lol;
                }
            }
            if(!unk6c){
                mSubtitleLabel->SetTextToken(gNullStr);
                unk6c = true;
            }
        }
    }
lol:
    if(unk78){
        float secs = TheTaskMgr.UISeconds();
        if(secs < mTimeShowHintStarted){
            mTimeShowHintStarted = secs;
        }
        if(secs - mTimeShowHintStarted >= 3.0f){
            HideHint();
        }
    }
    return;
}

void MoviePanel::Draw(){
    if(mState != kUnloaded){
        if(TheRnd->GetAspect() != Rnd::kWidescreen){
            mMovie.SetAspect(gTempBS);
        }
        mMovie.Draw();
    }
    UIPanel::Draw();
}

void MoviePanel::ChooseMovie(){
    MILO_ASSERT(!mMovies.empty(), 0x13A);
}

void MoviePanel::PlayMovie(){
    unk68 = 0;
    unk6c = true;
    if(TheRnd->GetAspect() != Rnd::kWidescreen){
        TheRnd->SetAspect(Rnd::kRegular);
    }
    mMovie.Begin(MakeString("videos/%s", unk48), 0.0f, mAudio == 0, mLoop, mPreload, mFillWidth, unk44, 0);
}

void MoviePanel::SetPaused(bool b){ mMovie.SetPaused(b); }

void MoviePanel::ShowMenu(bool b){
    mShowMenu = b;
    if(mShowMenu) HideHint();
}

void MoviePanel::HideHint(){
    unk78 = false;
    float frame = mPauseHintAnim->mFrame;
    mPauseHintAnim->Animate(frame, mPauseHintAnim->StartFrame(), mPauseHintAnim->Units(), 0.0f, 0.0f);
}

void MoviePanel::ShowHint(){
    if(mPauseHintAnim){
        unk78 = true;
        float secs = TheTaskMgr.UISeconds();
        mTimeShowHintStarted = secs;
        float frame = mPauseHintAnim->mFrame;
        mPauseHintAnim->Animate(frame, mPauseHintAnim->EndFrame(), mPauseHintAnim->Units(), 0.0f, 0.0f);
    }
}

void MoviePanel::DiscErrorStart(){}
void MoviePanel::DiscErrorEnd(){}

void MoviePanel::HomeMenuOpen(bool b){
    if(mMovie.Paused()) unk81 = true;
    else {
        unk81 = false;
        SetPaused(true);
    }
}

void MoviePanel::HomeMenuClose(bool b){
    if(!unk81) SetPaused(false);
}

BEGIN_HANDLERS(MoviePanel)
    HANDLE_ACTION(set_paused, SetPaused(_msg->Int(2)))
    HANDLE_ACTION(set_menu_shown, ShowMenu(_msg->Int(2)))
    HANDLE_EXPR(is_menu_shown, mShowMenu)
    HANDLE_ACTION(show_hint, ShowHint())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x1B9)
END_HANDLERS

BEGIN_PROPSYNCS(MoviePanel)
    SYNC_PROP(show_menu, mShowMenu)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS
