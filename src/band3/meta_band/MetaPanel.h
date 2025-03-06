#pragma once
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "ui/UIPanel.h"

class MetaPanel : public UIPanel {
public:
    MetaPanel();
    OBJ_CLASSNAME(MetaPanel);
    OBJ_SET_TYPE(MetaPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~MetaPanel();

    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();

    static bool sUnlockAll;
    static bool sIsPlaytest;
    static bool sLaunchedGoalMsgsOnly;
    static void Init();
    NEW_OBJ(MetaPanel);
    static void Register() { REGISTER_OBJ_FACTORY(MetaPanel); }
    static DataNode ToggleUnlockAll(DataArray *);
    static DataNode ToggleIsPlaytest(DataArray *);
    static DataNode ToggleLaunchedGoalMsgsOnly(DataArray *);
};