#include "math/FileChecksum.h"
#include <vector>

std::vector<ChecksumData> gChecksumData;

void SetFileChecksumData(FileChecksum* fc, int i){
    ChecksumData data;
    data.start = fc;
    data.end = &fc[i];
    gChecksumData.push_back(data);
}

void ClearFileChecksumData(){
    gChecksumData.clear();
}

bool HasFileChecksumData(){
    return false;
}
