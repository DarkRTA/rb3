#include "rndobj/Cam.h"

RndCam* RndCam::sCurrent = 0;

RndCam::RndCam() : mTargetTex(0, 0) {
    
}

RndCam::~RndCam(){
    if(sCurrent == this) sCurrent = 0;
}
