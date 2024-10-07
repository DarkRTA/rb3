#pragma once
#include "game/BandUser.h"
#include "game/Defines.h"
#include "bandobj/CrowdAudio.h" // for the ExcitementLevel enum

class CrowdRating {
public:
    CrowdRating(BandUser*, Difficulty);
    virtual ~CrowdRating(){}
    virtual ExcitementLevel GetExcitement() const; // ExcitementLevel?

    void Reset();
    void Configure(BandUser*, Difficulty);

    bool unk4;
    float unk8;
    float unkc;
    float unk10;
};