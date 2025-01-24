#pragma once
#include "rndobj/Mat.h"

class WiiMat : public RndMat {
public:
    // TODO: fill out fields

    static void SetOverrideAlphaWrite(bool set){
        sOverrideAlphaWrite = set;
    }
    static bool sOverrideAlphaWrite;
};