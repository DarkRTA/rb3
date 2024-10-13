#pragma once
#include "ui/UILabel.h"
#include "ui/UIPanel.h"

class TourChallengeResultsPanel : public UIPanel {
public:
    TourChallengeResultsPanel();
    OBJ_CLASSNAME(TourChallengeResultsPanel);
    OBJ_SET_TYPE(TourChallengeResultsPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourChallengeResultsPanel(){}
    virtual void Enter();
    
    int GetPreGigTotalStars() const;
    int GetTotalTourStars() const;
    int GetGigTotalStars() const;
    int GetGigMaxStars() const;
    Symbol GetChallengeName() const;
    void UpdateSetlistLabel(UILabel*);
    void UpdateSongName(int, UILabel*);
    int GetSongTotalStars(int);
    int GetSongStars(int);
    int GetChallengeStars(int);
    int GetSongCount();
};