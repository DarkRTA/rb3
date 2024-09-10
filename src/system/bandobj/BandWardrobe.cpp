#include "bandobj/BandWardrobe.h"

BandWardrobe* TheBandWardrobe;
const char* gGenres[4] = { "rocker", "dramatic", "banger", "spazz" };

BandWardrobe::BandWardrobe() : unk8(0), unk14(0), unk20(this, 0), unk64(&unk54), mVenueDir(0), mGenre(gGenres[0]), mTempo("medium"), unk90(this, 0), mShotSetPlayMode(1), mPlayShot5(0), mDemandLoad("") {
    static DataNode& bandwardrobe = DataVariable("bandwardrobe");
    if(TheBandWardrobe) MILO_WARN("Trying to make > 1 BandWardrobe, which should be single");
    bandwardrobe = DataNode(this);
    TheBandWardrobe = this;
}

BandWardrobe::~BandWardrobe(){
    if(TheBandWardrobe == this){
        static DataNode& bandwardrobe = DataVariable("bandwardrobe");
        bandwardrobe = DataNode((Hmx::Object*)0);
        TheBandWardrobe = 0;
    }
}