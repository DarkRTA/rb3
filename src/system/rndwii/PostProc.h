#pragma once

#include "rndobj/PostProc.h"

class WiiPostProc : public RndPostProc {
public:
    WiiPostProc();
    virtual ~WiiPostProc();

    void PrepareFinalTEV();
    void ClearFinalTEV();
    void DrawKaleidoscope();
};
