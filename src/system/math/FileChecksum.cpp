#include "math/FileChecksum.h"
#include <vector>

std::vector<ChecksumData> gChecksumData;

void ClearFileChecksumData(){
    gChecksumData.clear();
}

bool HasFileChecksumData(){
    return false;
}
