#pragma once
#include "ui/UIPanel.h"

class PracticePanel : public UIPanel {
public:
    bool PlayAllTracks() const;
};

extern PracticePanel *ThePracticePanel;