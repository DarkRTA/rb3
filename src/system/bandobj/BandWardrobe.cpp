#include "bandobj/BandWardrobe.h"

BandWardrobe* TheBandWardrobe;
const char* gGenres[4] = { "rocker", "dramatic", "banger", "spazz" };

BandWardrobe::BandWardrobe() : unk8(0), unk14(0), unk20(this, 0), unk64(&unk54), unk80(0), unk84(gGenres[0]), unk88("medium"), unk90(this, 0), unk9c(1), unk9d(0), unka0("") {
    static DataNode& bandwardrobe = DataVariable("bandwardrobe");
    if(TheBandWardrobe) MILO_WARN("Trying to make > 1 BandWardrobe, which should be single");
    bandwardrobe = DataNode(this);
    TheBandWardrobe = this;
}