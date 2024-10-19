#pragma once
#include "game/BandUser.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/TexLoadPanel.h"
#include "os/JoypadMsgs.h"
#include "stl/_algo.h"
#include "ui/UIGridProvider.h"
#include "ui/UILabel.h"
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
    virtual int NumData() const { return mGoals.size(); }
    virtual UIComponent::State ComponentStateOverride(int, int, UIComponent::State s) const;

    int GoalIndex(Symbol s) const {
        int idx = 0;
        for(std::vector<Symbol>::const_iterator it = mGoals.begin(); it != mGoals.end(); ++it, idx++){
            if(s == *it) return idx;
        }
        return 0;
    }

    void Update(Symbol s){
        mGoals.clear();
        std::set<Symbol>* symset = TheAccomplishmentMgr->GetAccomplishmentSetForCategory(s);
        if(symset){
            for(std::set<Symbol>::iterator it = symset->begin(); it != symset->end(); ++it){
                Symbol key = *it;
                if(TheAccomplishmentMgr->IsAvailableToView(key)) mGoals.push_back(key);
            }
            std::stable_sort(mGoals.begin(), mGoals.end(), AccomplishmentCmp(TheAccomplishmentMgr));
        }
    }

    std::vector<Symbol> mGoals; // 0x20
    int unk28; // 0x28
};

class AccomplishmentGroupProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentGroupProvider(){}
    virtual ~AccomplishmentGroupProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return mGroups.size(); }

    int GroupIndex(Symbol s) const {
        int idx = 0;
        for(std::vector<Symbol>::const_iterator it = mGroups.begin(); it != mGroups.end(); ++it, idx++){
            if(s == *it) return idx;
        }
        return 0;
    }

    void Update(){
        mGroups.clear();
        const std::map<Symbol, AccomplishmentGroup*>& groups = TheAccomplishmentMgr->GetGroups();
        for(std::map<Symbol, AccomplishmentGroup*>::const_iterator it = groups.begin(); it != groups.end(); ++it){
            Symbol key = it->first;
            if(TheAccomplishmentMgr->GetNumAccomplishmentsInGroup(key) > 0) mGroups.push_back(key);
        }
        std::stable_sort(mGroups.begin(), mGroups.end(), AccomplishmentGroupCmp(TheAccomplishmentMgr));
    }

    int unk20; // 0x20
    std::vector<Symbol> mGroups; // 0x24
};

class AccomplishmentCategoryProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentCategoryProvider(){}
    virtual ~AccomplishmentCategoryProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return mCategories.size(); }

    int CategoryIndex(Symbol s) const {
        int idx = 0;
        for(std::vector<Symbol>::const_iterator it = mCategories.begin(); it != mCategories.end(); ++it, idx++){
            if(s == *it) return idx;
        }
        return 0;
    }

    void Update(Symbol);

    std::vector<Symbol> mCategories; // 0x20
};

class AccomplishmentEntryProvider : public UIListProvider, public Hmx::Object {
public:
    AccomplishmentEntryProvider(){}
    virtual ~AccomplishmentEntryProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const { return unk24.size(); }

    void Update(Accomplishment*);

    Accomplishment* m_pAccomplishment; // 0x20
    std::vector<Symbol> unk24; // 0x24
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
    Symbol GetMusicLibraryBackScreen();
    Symbol GetMusicLibraryNextScreen();
    void SelectGoal(Symbol);
    void SelectCategory(Symbol);
    void SelectGroup(Symbol);
    void RefreshGroupList();
    void RefreshHeader();
    int GetTotalAccomplishments();
    int GetNumCompleted();
    bool IsUserOnCorrectInstrument();
    bool HasCorrectPlayerCount();
    Symbol GetSelectedDetailsEntry();
    Symbol GetAccomplishmentName();
    bool IsSecret() const;
    Symbol GetAccomplishmentDescription();
    Symbol GetAccomplishmentFanValueToken();
    Symbol GetAccomplishmentFlavor();
    bool HasAward() const;
    bool ShouldShowProgress() const;
    bool HasProgress() const;
    bool GetCurrentShouldShowDenominator() const;
    Symbol GetCurrentUnits(int) const;
    int GetCurrentValue() const;
    int GetMaxValue() const;
    bool ShouldShowBest() const;
    void LaunchSelectedEntry(LocalBandUser*);
    void BuildSelectedEntrySetList();
    void ClearCareerState();
    CareerState GetCareerState() const;
    void SetSelectedGoal(Symbol);
    void SetSelectedCategory(Symbol);
    void SetSelectedGroup(Symbol);
    void UpdateCampaignMeterProgressLabel(UILabel*);
    void UpdateHeaderLabel(UILabel*);
    void RefreshAll();
    void FakeEarnSelected();
    void FakeEarnSelectedGoal();
    void FakeEarnSelectedGroup();
    void FakeEarnSelectedCategory();

    DataNode OnMsg(const UIComponentScrollMsg&);
    DataNode Group_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode Category_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode Goal_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode Details_HandleButtonDownMsg(const ButtonDownMsg&);
    DataNode OnMsg(const ButtonDownMsg&);

    int unk4c; // career state
    Symbol mGoal; // 0x50
    Symbol mGroup; // 0x54
    Symbol mCategory; // 0x58
    AccomplishmentEntryProvider* mAccomplishmentEntryProvider; // 0x5c
    AccomplishmentProvider* mAccomplishmentProvider; // 0x60
    AccomplishmentCategoryProvider* mAccomplishmentCategoryProvider; // 0x64
    AccomplishmentGroupProvider* mAccomplishmentGroupProvider; // 0x68
    UIGridProvider* mAccomplishmentGridProvider; // 0x6c
    LocalBandUser* unk70; // 0x70
};

bool IsAccomplishmentSecret(Accomplishment*, const BandProfile*);
bool IsAccomplished(Symbol, const BandProfile*);