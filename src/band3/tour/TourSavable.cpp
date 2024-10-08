#include "tour/TourSavable.h"

TourSavable::TourSavable() : unk8(1), unk9(1), unka(0), unk11(1), unk12(1) {
    DateTime dt;
    GetDateAndTime(dt);
    unsigned int diff = dt.ToCode() - 0xe10;
    unkb = diff;
}