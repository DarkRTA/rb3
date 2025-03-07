#pragma once
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"
#include "synth/Stream.h"
#include "obj/DataFile.h"
#include "os/JoypadMsgs.h"

/** A panel of the game's credits. */
class CreditsPanel : public UIListProvider, public UIPanel {
public:
    CreditsPanel();
    virtual ~CreditsPanel();
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const;
    OBJ_CLASSNAME(CreditsPanel);
    OBJ_SET_TYPE(CreditsPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Load();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();
    virtual void Unload();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();

    void SetAutoScroll(bool);
    void PausePanel(bool);
    void DebugToggleAutoScroll();
    DataNode OnMsg(const ButtonDownMsg &);
    NEW_OBJ(CreditsPanel);
    static void Init() { REGISTER_OBJ_FACTORY(CreditsPanel); }

#ifdef MILO_DEBUG
    bool mCheatOn; // 0x3c
#endif
    DataLoader *mLoader; // 0x40
    DataArray *mNames; // 0x44
    UIList *mList; // 0x48
    Stream *mStream; // 0x4c
    bool mAutoScroll; // 0x50
    float mSavedSpeed; // 0x54
    /** Whether or not the panel is paused. */
    bool mPaused; // 0x58
};
