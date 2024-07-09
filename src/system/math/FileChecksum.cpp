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
    // don't question it, okay? it works lol
    std::vector<ChecksumData>::iterator itEnd;
    FileChecksum* sumEnd;
    std::vector<ChecksumData>::iterator it;
    FileChecksum* sum;
    const char* fname;

    fname = b ? FileGetName(cc) : FileLocalize(cc, 0);
    it = gChecksumData.begin();
    itEnd = gChecksumData.end();
    for(; it != itEnd; it++){
        sum = (*it).start;
        sumEnd = (*it).end;
        for(; sum != sumEnd; sum++){
            if(strcmp(sum->file, fname) == 0){
                return sum->checksum;
            }
        }
    }
    return 0;
}