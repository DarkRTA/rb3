#pragma once
#include "bandobj/BandLabel.h"
#include "meta_band/CharData.h"

class AppLabel : public BandLabel {
public:
    AppLabel(){}
    // TODO: fill out all the virtual methods where appropriate

    void SetFromCharacter(const CharData*);
    void SetSongName(Symbol, bool);
    void SetSongNameWithNumber(int, int, const char*);
};