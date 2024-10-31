#pragma once
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/Object.h"
#include "ui/UIListProvider.h"
#include <algorithm>

class GoalCmp {
public:
    GoalCmp(const AccomplishmentManager*);
    bool operator()(Symbol, Symbol) const;

    const AccomplishmentManager* m_pAccomplishmentMgr; // 0x0
};

class CampaignGoalsLeaderboardChoiceProvider : public UIListProvider, public Hmx::Object {
public:
    CampaignGoalsLeaderboardChoiceProvider(BandProfile* profile, const std::vector<DynamicTex*>& vec) : mIcons(vec) {
        mEntries.clear();
        std::map<Symbol, int> lbData;
        AccomplishmentProgress* prog = profile->GetAccomplishmentProgress();
        prog->InqGoalLeaderboardData(lbData);
        for(std::map<Symbol, int>::iterator it = lbData.begin(); it != lbData.end(); ++it){
            Symbol key = it->first;
            mEntries.push_back(key);
        }
        std::stable_sort(mEntries.begin(), mEntries.end(), GoalCmp(TheAccomplishmentMgr));
    }
    virtual ~CampaignGoalsLeaderboardChoiceProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return mEntries.size(); }

    RndMat* GetIconMat(const String& str) const {
        std::vector<DynamicTex*>::const_iterator it = std::find(mIcons.begin(), mIcons.end(), str);
        if(it != mIcons.end()) return (*it)->mMat;
        else return nullptr;
    }

    std::vector<Symbol> mEntries; // 0x20
    const std::vector<DynamicTex*>& mIcons; // 0x28
};

class CampaignGoalsLeaderboardChoicePanel : public TexLoadPanel {
public:
    CampaignGoalsLeaderboardChoicePanel();
    OBJ_CLASSNAME(CampaignGoalsLeaderboardChoicePanel);
    OBJ_SET_TYPE(CampaignGoalsLeaderboardChoicePanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CampaignGoalsLeaderboardChoicePanel(){}
    virtual void Enter();
    virtual void Load();
    virtual void Unload();

    Symbol SelectedGoal();
    void LoadIcons();

    CampaignGoalsLeaderboardChoiceProvider* mCampaignGoalsLeaderboardChoiceProvider; // 0x4c
};