#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "tempomap.hpp"
#include "multitempotempomap.hpp"
#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"

#pragma dont_inline on
// fn_8035824C
TempoMap::TempoMap() {
}
#pragma dont_inline reset

extern void fn_803581AC(int *);

// fn_80357E10
MultiTempoTempoMap::MultiTempoTempoMap() {
    fn_803581AC(unk4);
}

// fn_80358FA8
MultiTempoTempoMap::~MultiTempoTempoMap() {
}

// fn_803583A8
double MultiTempoTempoMap::TickToTime(float f) const {
}

// fn_80358528
double MultiTempoTempoMap::TimeToTick(float f) const {
}

// fn_8035825C
float MultiTempoTempoMap::GetTempo(int i) const {
}

// fn_803582F8
int MultiTempoTempoMap::GetTempoUSecs(int i) {
}

extern float lbl_807F04A8;

// fn_80358370
double MultiTempoTempoMap::GetTempoBPM(int i) const {
    return lbl_807F04A8 / GetTempo(i);
}

extern int fn_800A6BD0(void *);

// fn_80358AB4
int MultiTempoTempoMap::GetNumTempoChangePoints() const {
    return fn_800A6BD0(unk4);
}

// extern int fn_801046C0(String*);

// fn_80358ABC
int MultiTempoTempoMap::GetTempoChangePoint(int) const {
    // fn_800A6BD0(unk4);
    // return fn_801046C0(unk4);
}

// fn_80358B08
void MultiTempoTempoMap::V_Unk9() {
}

extern float lbl_807F02D0;

// fn_80358864
void MultiTempoTempoMap::V_Unk10() {
    unk18 = unk14 = unk10 = unkc = lbl_807F02D0;
}

extern float lbl_807F00C0;

// fn_80358880
void MultiTempoTempoMap::V_Unk11(int a, int b) {
    unkc = a;
    unk10 = b;
    unk14 = TickToTime(lbl_807F00C0);
    unk18 = TickToTime(unk10);
}

extern float lbl_807F00B4;

// fn_80358914
int MultiTempoTempoMap::V_Unk12(int a, int *b) {
    float temp_f4, temp_f5;
    int temp_r3, temp_r3_2;

    temp_f4 = unkc;
    if (temp_f4 < lbl_807F00B4)
        return a;

    temp_f5 = unk10;
    temp_r3_2 = temp_f4;
    *b = 0;
    if ((a < temp_f5) || (temp_f4 == temp_f5))
        return a;
    temp_r3 = temp_r3_2 + ((a - temp_r3_2) % (int)(temp_f5 - temp_r3_2));
    *b = a - temp_r3;
    return temp_r3;
}

// fn_803589B8
int MultiTempoTempoMap::V_Unk13(int a, int *b) {
    return V_Unk12(a, b);
}

// fn_803589E8
void MultiTempoTempoMap::V_Unk14() {
}
