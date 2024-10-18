#pragma once
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/TexLoadPanel.h"
#include "os/JoypadMsgs.h"
#include "ui/UIGridProvider.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "ui/UIMessages.h"

class AccomplishmentGroupCmp {
public:
    AccomplishmentGroupCmp(const AccomplishmentManager*);
    bool operator()(Symbol, Symbol) const;

    const AccomplishmentManager* mAccomplishmentMgr; // 0x0
};

class AccomplishmentCategoryCmp {
public:
    AccomplishmentCategoryCmp(const AccomplishmentManager*);
    bool operator()(Symbol, Symbol) const;

    const AccomplishmentManager* mAccomplishmentMgr; // 0x0
};

class AccomplishmentCmp {
public:
    AccomplishmentCmp(const AccomplishmentManager*);
    bool operator()(Symbol, Symbol) const;

    const AccomplishmentManager* mAccomplishmentMgr; // 0x0
};

class AccomplishmentProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentProvider(){}
    virtual ~AccomplishmentProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual UIComponent::State ComponentStateOverride(int, int, UIComponent::State s) const;

    std::vector<int> unk20; // 0x20
    int unk28; // 0x28
};

class AccomplishmentGroupProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentGroupProvider(){}
    virtual ~AccomplishmentGroupProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    int unk20; // 0x20
    std::vector<int> unk24; // 0x24
};

class AccomplishmentCategoryProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentCategoryProvider(){}
    virtual ~AccomplishmentCategoryProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    std::vector<int> unk20; // 0x20
};

class AccomplishmentEntryProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentEntryProvider(){}
    virtual ~AccomplishmentEntryProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const;

    int unk20; // 0x20
    std::vector<int> unk24; // 0x24
};

enum CareerState {

};

class AccomplishmentPanel : public TexLoadPanel {
public:
    AccomplishmentPanel();
    OBJ_CLASSNAME(AccomplishmentPanel);
    OBJ_SET_TYPE(AccomplishmentPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~AccomplishmentPanel(){}
    virtual void Enter();
    virtual void Exit();
    virtual void Load();
    virtual void Unload();

    void SetCareerState(CareerState, bool);
    void Refresh();
    Symbol SelectedAccomplishment() const;
    Symbol SelectedAccomplishmentCategory() const;
    Symbol SelectedAccomplishmentGroup() const;
    void LoadCampaignIcons();
    void RefreshCategoryList();
    void UpdateForGroupSelection();
    void RefreshGoalList();
    void UpdateForCategorySelection();
    void UpdateForGoalSelection();
    void UpdateDetailsListState();
    void HandleSoundSelect(LocalUser*);
    void HandleSoundBack(LocalUser*);
    void HandleSoundToggle(LocalUser*);
    bool CanLaunchGoal() const;
    bool CanNavigateList() const;
    bool HasLeaderboard() const;
    bool CanLaunchSelectedEntry() const;
    void BuildSetList();
    void FillSetlistWithAccomplishmentSongs(Symbol, int);
    void CreateAndSubmitMusicLibraryTask();
    void LaunchGoal(LocalBandUser*);

    DataNode OnMsg(const UIComponentScrollMsg&);
    DataNode Group_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode Category_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode Goal_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode Details_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode OnMsg(const ButtonDownMsg&);

    int unk4c; // career state
    Symbol unk50; // 0x50
    Symbol unk54; // 0x54
    Symbol unk58; // 0x58
    AccomplishmentEntryProvider* mAccomplishmentEntryProvider; // 0x5c
    AccomplishmentProvider* mAccomplishmentProvider; // 0x60
    AccomplishmentCategoryProvider* mAccomplishmentCategoryProvider; // 0x64
    AccomplishmentGroupProvider* mAccomplishmentGroupProvider; // 0x68
    UIGridProvider* mAccomplishmentGridProvider; // 0x6c
    int unk70;
};

bool IsAccomplishmentSecret(Accomplishment*, const BandProfile*);
bool IsAccomplished(Symbol, const BandProfile*);