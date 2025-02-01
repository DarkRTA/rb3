#include "os/CommerceMgr_Wii.h"

WiiCommerceMgr::WiiCommerceMgr() {}

WiiCommerceMgr::~WiiCommerceMgr() {}

unsigned long long WiiCommerceMgr::MakeDataTitleId(const char *cc) {
    return (unsigned long long)cc;
}