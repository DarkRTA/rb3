#pragma once
#include "bandobj/ScoreDisplay.h"

class AppScoreDisplay : public ScoreDisplay {
public:
    AppScoreDisplay(){}
    OBJ_CLASSNAME(AppScoreDisplay);
    OBJ_SET_TYPE(AppScoreDisplay);
    virtual ~AppScoreDisplay(){}
    virtual void UpdateDisplay();
};