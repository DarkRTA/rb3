#include "meta_band/SessionUsersProviders.h"

SessionUsersProvider::SessionUsersProvider(bool b1, bool b2, bool b3) : unk28(b1), unk29(b2), unk2a(b3), unk2c(0), unk30(0) {
    
}

void SessionUsersProvider::InitData(RndDir* rdir){
    if(unk28){
        unk2c = rdir->Find<RndMat>("checked.mat", false);
        unk30 = rdir->Find<RndMat>("unchecked.mat", false);
    }
}