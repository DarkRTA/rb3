#pragma once
#include "game/Defines.h"
#include "obj/Object.h"
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"

class CampaignSourceProvider : public UIListProvider, public Hmx::Object {
public:
    CampaignSourceProvider(){}
    virtual ~CampaignSourceProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;

    void Update();

    std::vector<Symbol> unk20; // 0x20
};

class CampaignSongInfoPanel : public UIPanel {
public:
    CampaignSongInfoPanel();
    OBJ_CLASSNAME(CampaignSongInfoPanel);
    OBJ_SET_TYPE(CampaignSongInfoPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CampaignSongInfoPanel(){}
    virtual void Enter();
    virtual void Load();
    virtual void Unload();

    Symbol SelectedSource() const;
    ScoreType SelectedScoreType() const;
    void Refresh();
    void SelectDefaultInstrument();
    int GetCareerScore() const;
    int GetSongCount() const;
    int GetSongsCompleted(Difficulty) const;
    int GetStarCount() const;
    int GetStarsEarned(Difficulty) const;
    const char* GetInstrumentIcon();
    Symbol GetMusicLibraryBackScreen();
    Symbol GetMusicLibraryNextScreen();
    void CreateAndSubmitMusicLibraryTask();
    void Launch();

    CampaignSourceProvider* mCampaignSourceProvider; // 0x38
};