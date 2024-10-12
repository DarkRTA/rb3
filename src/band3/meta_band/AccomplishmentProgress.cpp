#include "meta_band/AccomplishmentProgress.h"

AccomplishmentProgress::AccomplishmentProgress(BandProfile* profile) : unk3c(profile), unk84(0), unk644(1), unk648(0) {
    Clear();
    mSaveSizeMethod = &SaveSize;
}

AccomplishmentProgress::~AccomplishmentProgress(){

}