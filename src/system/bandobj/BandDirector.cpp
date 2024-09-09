#include "bandobj/BandDirector.h"

BandDirector::BandDirector() : unk34(this, 0), unk40(this, 0), unk4c(this, 0), unk58(0), unk74(this, 0), unk80(this, 0), unk8c(this, 0), unk98(this, 0),
    unka4(0), unkb0(0), unkb4(1), unkb5(0), unkb6(0), unkb8(this, 0), unkc4(this, 0), unkd0(this, 0), unke0(-1e+30f), unke4(0), unke5(1), unk108(-1.0f), unk10c(0),
    unk110(0), unk114(0) {
    static DataNode& banddirector = DataVariable("banddirector");
    banddirector = DataNode(this);
    unkb6 = !TheLoadMgr.EditMode();
    if(TheBandDirector){
        MILO_WARN("Trying to make > 1 BandDirector, which should be single");
    }
    else TheBandDirector = this;
    unke8.reserve(100);
}