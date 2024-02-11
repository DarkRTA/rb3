#ifndef UI_UIPANEL_H
#define UI_UIPANEL_H
#include "Object.h"
#include "String.h"
#include "FilePath.h"

enum State {
    kUnloaded = 0,
    kUp = 1,
    kDown = 2,
};

class UIPanel : public virtual Hmx::Object {
public:
    UIPanel();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIPanel();
    virtual void Load(BinStream&);
    virtual void SetTypeDef(DataArray *);
    virtual ObjectDir* DataDir();

    virtual void Draw();
    virtual void Enter();
    virtual int Entering();
    virtual void Exit();
    virtual int Exiting();
    virtual bool Unloading();
    virtual void Poll();
    virtual void SetPaused(bool);
    virtual void FocusIn(); // StubVoid
    virtual void FocusOut(); // StubVoid
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded();
    virtual void UnknownUIPanelMethod(); // fn_80573920
    virtual void FinishLoad();

    void CheckLoad();
    void CheckUnload();

    int panel; // should be a PanelDir*
    int unkc; // should be a DirLoader*
    String focus;
    State mState;
    bool loaded;
    bool paused;
    bool showing;
    bool forceExit;
    int refCount;
    FilePath fpath;
    int unk34;
};

#endif

// enum State {
//     kUnloaded = 0,
//     kUp = 1,
//     kDown = 2,
// };
// class UIPanel : public virtual Object {
//     // total size: 0x5C
// public:
//     void * __vptr$; // offset 0x4, size 0x4
// protected:
//     unsigned char mHomeMenuAllowed; // offset 0x8, size 0x1
//     class PanelDir * mDir; // offset 0xC, size 0x4
//     class DirLoader * mLoader; // offset 0x10, size 0x4
//     class String mFocusName; // offset 0x14, size 0xC
// private:
//     unsigned char mSharedDir; // offset 0x20, size 0x1
//     enum State mState; // offset 0x24, size 0x4
//     unsigned char mPaused; // offset 0x28, size 0x1
//     unsigned char mShowing; // offset 0x29, size 0x1
//     unsigned char mForceExit; // offset 0x2A, size 0x1
//     int mLoadRefs; // offset 0x2C, size 0x4
// };
