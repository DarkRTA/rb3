#pragma once
#include "obj/Data.h"
#include "rndobj/Group.h"
#include "ui/UILabel.h"
#include "ui/UIPanel.h"

class NextSongPanel : public UIPanel {
public:
    NextSongPanel(){}
    OBJ_CLASSNAME(NextSongPanel);
    OBJ_SET_TYPE(NextSongPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~NextSongPanel(){}
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void FinishLoad();

    void DeterminePerformanceAwards(int);
    void HideAllDetailComponents(int);
    void FillExpandedDetails(int);
    void ScrollExpandedDetails(int, int, bool);
    int GetMaxScrollPage(int);
    bool CanChangeSongReview(int) const;
    void InitializeSongReviewDisplay(int);
    void IncrementSongReview(int);
    void SetReviewDisplayValue(int, int);
    void UpdateScrollArrows(int, bool);
    void SetScrollExpandedDetails(int, int);
    int CountOrCreateExpandedDetails(int, DataArrayPtr&, bool);
    void SetupDetailLine(DataArray*, int, const char*, float);
    Symbol GetPerformanceAward(int);

    float mEnterTime; // 0x38
    std::map<Symbol, int> mDetailCounts; // 0x3c
    float mDetailsPageSize; // 0x54
    float mDetailsFooterSize; // 0x58
    float mDetailsScrollStep; // 0x5c
    float mDetailsHeight[4]; // 0x60
    int unk70[4];
    bool unk80[4];
    bool unk84[4];
    RndGroup* mScrollGroups[4]; // 0x88
    bool unk98; // 0x98
    std::vector<UILabel*> mDetailLabels; // 0x9c
};