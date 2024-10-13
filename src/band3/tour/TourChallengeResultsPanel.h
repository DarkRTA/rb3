#pragma once
#include "ui/UIPanel.h"

class TourChallengeResultsPanel : public UIPanel {
public:
    TourChallengeResultsPanel();
    OBJ_CLASSNAME(TourChallengeResultsPanel);
    OBJ_SET_TYPE(TourChallengeResultsPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourChallengeResultsPanel(){}
    virtual void Enter();
    
};