#include "math/FileChecksum.h"
#include "os/File.h"
#include <vector>

std::vector<ChecksumData> gChecksumData;

void SetFileChecksumData(FileChecksum* fc, int i){
    gChecksumData.push_back(ChecksumData(fc, &fc[i]));
}

void ClearFileChecksumData(){
    gChecksumData.clear();
}

bool HasFileChecksumData(){
    return false;
}

unsigned char* GetFileChecksum(const char* cc, bool b){
    const char* fname = b ? FileGetName(cc) : FileLocalize(cc, 0);
    std::vector<ChecksumData>::iterator it = gChecksumData.begin();
    std::vector<ChecksumData>::iterator itEnd = gChecksumData.end();
    for(; it != itEnd; it++){
        FileChecksum* sum = (*it).start;
        FileChecksum* sumEnd = (*it).end;
        for(; sum != sumEnd; sum++){
            if(strcmp(sum->file, fname) == 0){
                return sum->checksum;
            }
        }
    }
    return 0;
}