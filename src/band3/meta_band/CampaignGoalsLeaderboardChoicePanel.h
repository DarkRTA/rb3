#pragma once
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class GoalCmp {
public:
    GoalCmp(const AccomplishmentManager*);
    bool operator()(Symbol, Symbol) const;

    const AccomplishmentManager* m_pAccomplishmentMgr; // 0x0
};

class CampaignGoalsLeaderboardChoiceProvider : public UIListProvider, public Hmx::Object {
public:
    CampaignGoalsLeaderboardChoiceProvider(BandProfile* profile, const std::vector<DynamicTex*>& vec) : mIcons(vec) {
        unk20.clear();
    //   stlpmtx_std::vector<><>::clear((vector<><> *)(param_1 + 0x20));
    //   stlpmtx_std::map<><>::map(amStack_28);
    //   uVar1 = BandProfile::GetAccomplishmentProgress(param_2);
    //   fn_801AB7CC(uVar1,amStack_28);
    //   fn_801EA5DC(auStack_34,amStack_28);
    //   fn_8000FA38(a_Stack_2c,auStack_34);
    //   while( true ) {
    //     fn_8018DF40(auStack_3c,amStack_28);
    //     uVar1 = fn_8000FA38(auStack_38,auStack_3c);
    //     iVar3 = ObjPtrList<>::iterator::operator_!=((iterator *)a_Stack_2c,uVar1);
    //     if (iVar3 == 0) break;
    //     pSVar2 = (Symbol *)stlpmtx_std::_Rb_tree_iterator<>::operator_->(a_Stack_2c);
    //     Symbol::Symbol(aSStack_30,pSVar2);
    //     stlpmtx_std::vector<><>::push_back((vector<><> *)(param_1 + 0x20),aSStack_30);
    //     fn_801A96B4(a_Stack_2c,0);
    //   }
    //   puVar4 = (undefined4 *)fn_801EA170(auStack_44,TheAccomplishmentMgr);
    //   local_40 = *puVar4;
    //   uVar1 = stlpmtx_std::_Vector_impl<><>::end((_Vector_impl<><> *)(param_1 + 0x20));
    //   fn_801EA8C0(*(undefined4 *)(param_1 + 0x20),uVar1,&local_40);
    //   stlpmtx_std::map<><>::~map(amStack_28);
    }
    virtual ~CampaignGoalsLeaderboardChoiceProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return unk20.size(); }

    std::vector<Symbol> unk20; // 0x20
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

    CampaignGoalsLeaderboardChoiceProvider* mCampaignGoalsLeaderboardChoiceProvider; // 0x4c
};