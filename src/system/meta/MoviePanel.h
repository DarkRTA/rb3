#ifndef META_MOVIEPANEL_H
#define META_MOVIEPANEL_H
#include "movie/Movie.h"
#include "ui/UIPanel.h"
#include "os/HomeMenu_Wii.h"
#include "os/DiscErrorMgr_Wii.h"
#include "obj/DataFile.h"
#include "ui/UILabel.h"

class MoviePanel : public UIPanel, public DiscErrorMgrWii::Callback, public HomeMenu::Callback {
public:
    MoviePanel();
    OBJ_CLASSNAME(MoviePanel);
    OBJ_SET_TYPE(MoviePanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~MoviePanel(){}
    virtual void SetTypeDef(DataArray *);
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void SetPaused(bool);
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void DiscErrorStart();
    virtual void DiscErrorEnd();
    virtual void HomeMenuOpen(bool);
    virtual void HomeMenuClose(bool);

    void PlayMovie();
    void ShowHint();
    void HideHint();
    void ChooseMovie();
    void ShowMenu(bool);

    static bool sUseSubtitles;

    bool mPreload; // 0x40
    bool mAudio; // 0x41
    bool mLoop; // 0x42
    bool mFillWidth; // 0x43
    int mLanguage; // 0x44
    const char* mCurrentMovie; // 0x48
    std::vector<const char*> mMovies; // 0x4c
    std::list<const char*> mRecent; // 0x54
    Movie mMovie; // 0x5c
    DataLoader* mSubtitlesLoader; // 0x60
    DataArray* mSubtitles; // 0x64
    int mCurrentSubtitleIndex; // 0x68
    bool mSubtitleCleared; // 0x6c
    UILabel* mSubtitleLabel; // 0x70
    RndAnimatable* mPauseHintAnim; // 0x74
    bool mShowHint; // 0x78
    float mTimeShowHintStarted; // 0x7c
    bool mShowMenu; // 0x80
    bool unk81; // 0x81
};

#endif
