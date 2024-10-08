#include "net_band/DataResults.h"

DataResultList::DataResultList() : unk4(0) {
    unk8 = new Quazal::String();
    unk14 = 0;
}

DataResultList::~DataResultList(){
    delete unk8;
}