#include "math/Striper.h"
#include <string.h>
#include "os/Debug.h"
#include "utl/MemMgr.h"

STRIPERRESULT::STRIPERRESULT() : NbStrips(0), StripLengths(0), StripRuns(0) {

}

STRIPERRESULT::STRIPERRESULT(const STRIPERRESULT& res) : NbStrips(0), StripLengths(0), StripRuns(0) {
    Copy(res);
}

STRIPERRESULT::~STRIPERRESULT(){
    FreeLengthsAndRuns();
    NbStrips = 0;
}

STRIPERRESULT& STRIPERRESULT::operator=(const STRIPERRESULT& res){
    Copy(res);
    return *this;
}

void STRIPERRESULT::Copy(const STRIPERRESULT& res){
    FreeLengthsAndRuns();
    NbStrips = res.NbStrips;
    if(res.NbStrips != 0){
        bool b = false;
        if(res.StripLengths && res.StripRuns) b = true;
        if(!b) MILO_FAIL("Corrupt STRIPERRESULT");
        int i = res.StripLengths[res.NbStrips - 1];
        AllocLengthsAndRuns(NbStrips, i);
        memcpy(StripLengths, res.StripLengths, NbStrips * 4);
        memcpy(StripRuns, res.StripRuns, i * 2);
    }
}

void STRIPERRESULT::AllocLengthsAndRuns(int i, int j){
    if(StripLengths) MILO_WARN("\n###\n###STRIPERRESULT::StripLengths(0x%08x) about to be leaked!\n###\n", StripLengths);
    StripLengths = (unsigned int*)_MemAlloc(i * 4 + j * 2, 0);
    StripRuns = &StripLengths[i];
}

void STRIPERRESULT::FreeLengthsAndRuns(){
    if(StripLengths){
        _MemFree(StripLengths);
        StripLengths = 0;
    }
    StripRuns = 0;
}
