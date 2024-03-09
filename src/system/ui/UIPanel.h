#ifndef UI_UIPANEL_H
#define UI_UIPANEL_H
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "utl/Str.h"

class PanelDir;
class DirLoader;

enum State {
    kUnloaded = 0,
    kUp = 1,
    kDown = 2,
};

class UIPanel : public virtual Hmx::Object {
public:
    UIPanel();
    OBJ_CLASSNAME(UIPanel);
    OBJ_SET_TYPE(UIPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIPanel();
    virtual void Load(BinStream&);
    virtual void SetTypeDef(DataArray *);
    virtual class ObjectDir* DataDir();

    virtual void Draw();
    virtual void Enter();
    virtual bool Entering() const;
    virtual void Exit();
    virtual bool Exiting() const;
    virtual bool Unloading() const;
    virtual void Poll();
    virtual void SetPaused(bool);
    virtual void FocusIn(){ }
    virtual void FocusOut(){ }
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();

    void CheckLoad();
    void CheckUnload();
    bool CheckIsLoaded();
    void UnsetLoadedDir();
    DataNode OnLoad(DataArray*);

    class PanelDir* mDir;
    DirLoader* mLoader;
    class String mFocusName;
    State mState;
    bool mLoaded;
    bool mPaused;
    bool mShowing;
    bool mForceExit;
    int mLoadRefs;
    FilePath mFilePath;
    int mPanelId;

    static int sMaxPanelId;
};

#endif
