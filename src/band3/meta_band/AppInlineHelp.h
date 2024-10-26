#pragma once
#include "bandobj/InlineHelp.h"
#include "game/BandUser.h"

class AppInlineHelp : public InlineHelp {
public:
    AppInlineHelp();
    // virtual funcs go here...

    void SetOverrideUser(LocalBandUser*);
};