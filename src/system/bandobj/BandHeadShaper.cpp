#include "bandobj/BandHeadShaper.h"
#include "os/Debug.h"

std::vector<int> gHeadMaleMapping;
std::vector<int> gHeadFemaleMapping;
ObjDirPtr<ObjectDir> gVisemes[4]; // ???

BandHeadShaper::BandHeadShaper() : mBones(0) {

}

BandHeadShaper::~BandHeadShaper(){
    MILO_ASSERT(!mBones, 0xD6);
}