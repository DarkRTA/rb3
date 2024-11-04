#pragma once
#include "game/ProTrainerPanel.h"

class RKTrainerPanel : public ProTrainerPanel {
public:
    RKTrainerPanel();
    OBJ_CLASSNAME(RKTrainerPanel);
    OBJ_SET_TYPE(RKTrainerPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~RKTrainerPanel();
    virtual bool IsSongSectionComplete(BandProfile*, int, Difficulty, int);
    virtual void SetSongSectionComplete(BandProfile*, int, Difficulty, int);
};