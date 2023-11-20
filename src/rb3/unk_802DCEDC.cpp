#include "rand.hpp"
#include "common.hpp"

extern unsigned int gMainThreadID;
extern "C" unsigned int OSGetCurrentThread();

bool MainThread(){
    bool ret = true;
    if((gMainThreadID != 0) && (gMainThreadID != OSGetCurrentThread())) ret = false;
    return ret;
}