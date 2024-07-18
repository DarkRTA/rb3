#ifndef META_PRELOADPANEL_H
#define META_PRELOADPANEL_H
#include "ui/UIPanel.h"
#include "os/ContentMgr.h"
#include "os/FileCache.h"

class PreloadPanel : public UIPanel, public ContentMgr::Callback {
public:
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
    
    static FileCache* sCache;

    int unk3c; // some kind of state?
    std::vector<String> unk40;
    bool unk48;
    std::vector<Symbol> unk4c;
    Hmx::Object* mAppReadFailureHandler; // 0x54
    bool unk58;
    String unk5c;
    bool unk68;
};

#endif