#ifndef RB3_UIPANEL_HPP
#define RB3_UIPANEL_HPP
#include "hmx/object.hpp"
#include "string.hpp"
#include "filepath.hpp"

class UIPanel : public virtual Hmx::Object {
public:
    UIPanel();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIPanel();
    virtual void Load(BinStream&);
    virtual void SetTypeDef(DataArray *);
    virtual void DataDir();

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
    int unk1c;
    bool loaded;
    bool paused;
    bool showing;
    bool forceExit;
    int refCount;
    FilePath fpath;
    int unk34;
};

#endif
