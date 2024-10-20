#pragma once
#include "meta_band/TexLoadPanel.h"
#include "tour/TourPerformer.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class QuestFilterProvider : public UIListProvider, public Hmx::Object {
public:
    QuestFilterProvider(){}
    virtual ~QuestFilterProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return unk24.size(); }
    virtual UIComponent::State ComponentStateOverride(int, int, UIComponent::State s) const;
    
    int unk20;
    std::vector<Symbol> unk24; // 0x24
    int unk2c;
    int unk30;
};

class QuestFilterPanel : public TexLoadPanel {
public:
    QuestFilterPanel();
    OBJ_CLASSNAME(QuestFilterPanel);
    OBJ_SET_TYPE(QuestFilterPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~QuestFilterPanel(){}
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

    Symbol m_symQuest; // 0x4c
    QuestFilterProvider* m_pQuestFilterProvider; // 0x50
};
