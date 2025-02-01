#pragma once
#include "meta_band/TexLoadPanel.h"
#include "tour/TourPerformer.h"
#include "tour/TourProgress.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class QuestFilterProvider : public UIListProvider, public Hmx::Object {
public:
    QuestFilterProvider(
        const std::vector<DynamicTex *> &texes, TourProgress &tp, UIList *uil
    )
        : m_rIcons(texes), m_rProgress(tp), unk30(uil) {}
    virtual ~QuestFilterProvider() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return m_vQuestFilters.size(); }
    virtual UIComponent::State
    ComponentStateOverride(int, int, UIComponent::State s) const;

    void Update() {
        m_vQuestFilters.clear();
        for (int i = 0; i < 3; i++) {
            m_vQuestFilters.push_back(m_rProgress.GetQuestFilter(i));
        }
    }

    const std::vector<DynamicTex *> &m_rIcons; // 0x20
    std::vector<Symbol> m_vQuestFilters; // 0x24
    TourProgress &m_rProgress; // 0x2c
    UIList *unk30; // 0x30
};

class QuestFilterPanel : public TexLoadPanel {
public:
    QuestFilterPanel();
    OBJ_CLASSNAME(QuestFilterPanel);
    OBJ_SET_TYPE(QuestFilterPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~QuestFilterPanel() {}
    virtual void Enter();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();

    Symbol GetSelectedFilter();
    TourSetlistType GetSelectedSetlistType();
    void LoadIcons();
    void Refresh();
    void UpdateFilters();
    Symbol GetBackScreen();
    Symbol GetSongSelectScreen();
    Symbol GetDiffSelectScreen();
    void HandleFilterSelected();
    Symbol GetGigFilter();
    void CheatWinQuest();
    void CheatCycleChallenge();
    void CheatCycleSetlist();
    void HandleLeaderToggledFilters(bool);
    bool AreCurrentFiltersValid();

    Symbol m_symQuest; // 0x4c
    QuestFilterProvider *m_pQuestFilterProvider; // 0x50
};
