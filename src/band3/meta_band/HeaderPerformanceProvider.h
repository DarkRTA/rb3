#pragma once
#include "bandobj/ScoreDisplay.h"
#include "game/Defines.h"
#include "meta_band/BandProfile.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "utl/Str.h"

class SetlistScoresProvider : public UIListProvider, public Hmx::Object {
public:
    SetlistScoresProvider();
    virtual ~SetlistScoresProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;    
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;    
    virtual int NumData() const;    
    virtual UIListWidgetState ElementStateOverride(int, int, UIListWidgetState s) const;
    virtual DataNode Handle(DataArray*, bool);

    void SetProfile(BandProfile*);
    void SetScoreType(ScoreType);
    void RefreshScores();
    
    std::vector<int> unk20; // 0x20
    std::vector<int> unk28; // 0x28
    std::vector<unsigned short> unk30; // 0x30
    std::vector<String> unk38; // 0x38
    BandProfile* mProfile; // 0x40
    ScoreType mScoreType; // 0x44
};