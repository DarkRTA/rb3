#pragma once
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "os/ContentMgr.h"
#include "os/FileCache.h"
#include "meta/SongMgr.h"

class PreloadPanel : public UIPanel, public ContentMgr::Callback {
public:
    enum PreloadResult {
        kPreloadInProgress = 0,
        kPreloadSuccess = 1,
        kPreloadFailure = 2
    };

    PreloadPanel();
    OBJ_CLASSNAME(PreloadPanel);
    OBJ_SET_TYPE(PreloadPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~PreloadPanel();
    virtual void SetTypeDef(DataArray *);
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();
    virtual const char* ContentDir();
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentFailed(const char*);

    void CheckTypeDef(Symbol);
    Symbol CurrentSong() const;
    void StartCache();
    bool CheckFileCached(const char*);
    void OnContentMountedOrFailed(const char*, bool);

    DataNode OnMsg(const ContentReadFailureMsg&);
    DataNode OnMsg(const UITransitionCompleteMsg&);

    SongMgr* SongMgr() const;
    
    static FileCache* sCache;
    NEW_OBJ(PreloadPanel)
    static void Init(){
        REGISTER_OBJ_FACTORY(PreloadPanel)
    }

    PreloadResult mPreloadResult; // 0x3c
    std::vector<String> mPreloadedFiles; // 0x40
    bool mMounted; // 0x48
    std::vector<Symbol> mContentNames; // 0x4c
    Hmx::Object* mAppReadFailureHandler; // 0x54
    bool unk58; // 0x58
    String unk5c; // 0x5c
    bool unk68; // 0x68

};
