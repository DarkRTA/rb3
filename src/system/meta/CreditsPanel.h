#ifndef META_CREDITSPANEL_H
#define META_CREDITSPANEL_H
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"
#include "synth/Stream.h"
#include "obj/DataFile.h"

class CreditsPanel : public UIListProvider, public UIPanel {
public:
    CreditsPanel();
    virtual ~CreditsPanel();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;
    OBJ_CLASSNAME(CreditsPanel);
    OBJ_SET_TYPE(CreditsPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Load();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();
    virtual void Unload();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();

    void SetAutoScroll(bool);

    bool mCheatOn; // 0x3c
    DataLoader* mLoader; // 0x40
    DataArray* mNames; // 0x44
    UIList* mList; // 0x48
    Stream* mStream; // 0x4c
    bool mAutoScroll; // 0x50
    float mSavedSpeed; // 0x54
    bool mPaused; // 0x58
};

#endif
