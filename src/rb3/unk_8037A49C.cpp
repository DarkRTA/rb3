#include "textfilestream.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"
#include "simpletempomap.hpp"

// fn_8037A58C - TextFileStream ctor
TextFileStream::TextFileStream(const char* c, bool b){
    
}

// fn_8037A5F8
void TextFileStream::Print(const char* c){
    // while(*c != '\0'){
    //     if(*c == '\n'){
    //         if(c[1] == '\r') 
    //     }
    // }
}

// fn_8037A4FC
double SimpleTempoMap::TickToTime(float f) const {
    return f * ms_per_tick;
}

// fn_8037A508
double SimpleTempoMap::TimeToTick(float f) const {
    return f / ms_per_tick;
}

extern float lbl_807F04A4; // 480.0f

// fn_8037A514
float SimpleTempoMap::GetTempo(int i) const {
    return lbl_807F04A4 * ms_per_tick;
}

extern float lbl_807F04A8; // 60000.0f

// fn_8037A528
double SimpleTempoMap::GetTempoBPM(int i) const {
    return lbl_807F04A8 / (lbl_807F04A4 * ms_per_tick);
}

extern float lbl_807F00D0; // 1000.0f

// fn_8037A548
int SimpleTempoMap::V_Unk5(int i){
    return GetTempo(i) * lbl_807F00D0;
}