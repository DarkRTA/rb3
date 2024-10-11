#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "meta_band/BandProfile.h"

class StandInProvider : public UIListProvider, public Hmx::Object {
public:
    StandInProvider(BandProfile*);
    virtual ~StandInProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const { return 4; }

    void Reload(BandProfile*);

    BandProfile* mProfile; // 0x20
};