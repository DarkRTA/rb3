#include "meta/MoviePanel.h"

#include "math/Rand.h"
#include "obj/Task.h"
#include "os/File.h"
#include "os/PlatformMgr.h"
#include "rndobj/Rnd.h"
#include "ui/UI.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

bool MoviePanel::sUseSubtitles;

MoviePanel::MoviePanel()
    : mSubtitlesLoader(0), mSubtitles(0), mCurrentSubtitleIndex(0),
      mSubtitleCleared(true), mSubtitleLabel(0), mPauseHintAnim(0), mShowHint(false),
      mTimeShowHintStarted(0.0f), mShowMenu(0), unk81(0) {}

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

    DataArray* config = SystemConfig("videos", Property("videos", true)->Str(0));

    DataArray* files = config->FindArray("files", true);
    for(int i = 1; i < files->Size(); i++){
        mMovies.push_back(files->Str(i));
    }

    mFillWidth = false;
    config->FindData("fill_width", mFillWidth, false);

    bool localize = false;
    config->FindData("localize", localize, false);
    if (localize) {
        Symbol language = SystemLanguage();
        DataArray* supported = SupportedLanguages(false);

        int i = 0;
        for (; i < supported->Size(); i++) {
            if (supported->Sym(i) == language) {
                break;
            }
        }

        if (i >= supported->Size()) {
            i = 0;
        }

        mLanguage = i + 1;
    } else {
        mLanguage = 0;
    }

    if (sUseSubtitles && mMovies.size() == 1) {
        char pathBuffer[256];
        sprintf(pathBuffer, "ui/subtitles/eng/%s_keep.dta", FileGetBase(mMovies[0], nullptr));

        const char *subtitlesPath;
        bool local = FileIsLocal(pathBuffer);
        bool cd = UsingCD();
        if (cd && !local) {
            subtitlesPath = MakeString("%s/gen/%s.dtb", FileGetPath(pathBuffer, nullptr), FileGetBase(pathBuffer, nullptr));
        } else {
            subtitlesPath = pathBuffer;
        }

        if (FileExists(subtitlesPath, 0)) {
            // bug? pathBuffer should probably be subtitlesPath
            mSubtitlesLoader = new DataLoader(FilePath(pathBuffer), kLoadFront, true);
        }
    }

    ChooseMovie();
}

bool MoviePanel::IsLoaded() const {
    if (!mMovie.Ready()) {
        return false;
    }

    if (mSubtitlesLoader && !mSubtitlesLoader->IsLoaded()) {
        return false;
    }

    return UIPanel::IsLoaded();
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
        DataArray* arr = mSubtitles->Array(mCurrentSubtitleIndex);
        if(mSubtitleCleared){
            if(arr->Int(0) <= frame){
                mSubtitleLabel->SetSubtitle(arr);
                mSubtitleCleared = false;
            }
        }
        if(arr->Int(1) < frame){
            DataArray* thisarr = 0;
            if(mSubtitles->Size() > mCurrentSubtitleIndex + 1){
                thisarr = mSubtitles->Array(mCurrentSubtitleIndex + 1);
            }
            if(thisarr){
                if(thisarr->Int(0) <= frame){
                    mSubtitleLabel->SetSubtitle(thisarr);
                    mSubtitleCleared = false;
                    mCurrentSubtitleIndex++;
                    goto lol;
                }
            }
            if(!mSubtitleCleared){
                mSubtitleLabel->SetTextToken(gNullStr);
                mSubtitleCleared = true;
            }
        }
    }
lol:
    if(mShowHint){
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

float gTempBS = 0.55263156f;

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

    std::list<const char*>::iterator it;
    do {
        int random = RandomInt(0, mMovies.size());
        mCurrentMovie = mMovies[random];
        for (it = mRecent.begin(); (it != mRecent.end() && (*it != mCurrentMovie)); ++it) {}
    } while (it != mRecent.end());

    const char* current = mCurrentMovie;
    mRecent.push_back(current);

    if (mRecent.size() == mMovies.size()) {
        while (mRecent.size() > (mMovies.size() / 2)) {
            mRecent.pop_front();
        }
    }

    PlayMovie();
}

void MoviePanel::PlayMovie(){
    mCurrentSubtitleIndex = 0;
    mSubtitleCleared = true;
    if(TheRnd->GetAspect() != Rnd::kWidescreen){
        TheRnd->SetAspect(Rnd::kRegular);
    }
    mMovie.Begin(MakeString("videos/%s", mCurrentMovie), 0.0f, mAudio == 0, mLoop, mPreload, mFillWidth, mLanguage, 0);
}

void MoviePanel::SetPaused(bool b){ mMovie.SetPaused(b); }

void MoviePanel::ShowMenu(bool b){
    mShowMenu = b;
    if(mShowMenu) HideHint();
}

void MoviePanel::HideHint(){
    mShowHint = false;
    float frame = mPauseHintAnim->mFrame;
    mPauseHintAnim->Animate(frame, mPauseHintAnim->StartFrame(), mPauseHintAnim->Units(), 0.0f, 0.0f);
}

void MoviePanel::ShowHint(){
    if(mPauseHintAnim){
        mShowHint = true;
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
