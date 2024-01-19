#include "quazal/unk_800A515C.hpp"
#include "unknown.hpp"

// ------------------------------------
// fn_800A515C
// ------------------------------------
Quazal::ProductSpecifics::ProductSpecifics() {
}

// ------------------------------------
// fn_800A516C
// ------------------------------------
Quazal::ProductSpecifics::~ProductSpecifics() {
}

// // ------------------------------------
// // fn_800A51AC
// // ------------------------------------

// extern "C" int fn_800179A8(int, int*, int);
// extern "C" void fn_800A49A0(int**, int);
// extern "C" int fn_800A5278();
// extern "C" int** fn_800A51AC(int**);

// extern int lbl_8082A608[]; // Quazal::NetZ vtable
// extern int lbl_8082A650[]; // NetZ.cpp

// int** fn_800A51AC(int** arg0) {
//     int temp_r3;
//     int var_r4;

//     temp_r3 = fn_800179A8(4, &lbl_8082A650[0], 0x15);
//     var_r4 = temp_r3;
//     if (temp_r3 != 0) {
//         var_r4 = fn_800A5278(); // NetZSpecifics ctor
//     }

//     // looks like another ctor
//     fn_800A49A0(arg0, var_r4);
//     *arg0 = &lbl_8082A608[0];
//     return arg0;
// }

// // ------------------------------------
// // fn_800A5214
// // ------------------------------------

// extern "C" void fn_800A4C84(int, int*);
// extern "C" int** fn_800A5214(int**,int);
// extern int lbl_8082A608[];

// int** fn_800A5214(int** arg0, int arg1) {
//     if (arg0 != '\0') {
//         *arg0 = &lbl_8082A608[0];
//         fn_800A4C84(0, &lbl_8082A608[0]);
//         if (arg1 > 0) {
//             fn_80017A8C(); // operator delete
//         }
//     }
//     return arg0;
// }

// ------------------------------------
// fn_800A5278
// ------------------------------------
Quazal::NetZSpecifics::NetZSpecifics() {
}

// ------------------------------------
// fn_800A52B4
// ------------------------------------
Quazal::NetZSpecifics::~NetZSpecifics() {
}

// ------------------------------------
// fn_800A530C
// ------------------------------------
int Quazal::NetZSpecifics::fn_800A530C() {
    return 1;
}

// ------------------------------------
// fn_800A5314
// ------------------------------------
void Quazal::NetZSpecifics::fn_800A5314() {
    fn_80083734(); // fn_80051350(&lbl_808F357C)
    fn_8007DFD0(); // fn_80051350(&lbl_808F33B4)
    // fn_80051350 decomp: https://decomp.me/scratch/EAChy
}

// ------------------------------------
// fn_800A5338
// ------------------------------------
void Quazal::NetZSpecifics::fn_800A5338() {
    fn_80083174();
    lbl_808E2DA0 = 0;
    fn_8007E3C0();
    fn_80084160();
}

Quazal::unk_53B0 lbl_53B0();
