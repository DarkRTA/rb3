#include "quazal/unk_800A515C.hpp"
#include "unknown.hpp"

// ------------------------------------
// fn_800A515C
// ------------------------------------
Quazal::ProductSpecifics::ProductSpecifics()
{
}

// ------------------------------------
// fn_800A516C
// ------------------------------------
Quazal::ProductSpecifics::~ProductSpecifics()
{
}

// // ------------------------------------
// // fn_800A51AC
// // ------------------------------------

// extern "C" s32 fn_800179A8(s32, s32*, s32);
// extern "C" void fn_800A49A0(s32**, s32);
// extern "C" s32 fn_800A5278();
// extern "C" s32** fn_800A51AC(s32**);
// extern s32 lbl_8082A608[];
// extern s32 lbl_8082A650[];

// s32** fn_800A51AC(s32** arg0) {
//     s32 temp_r3;
//     s32 var_r4;

//     temp_r3 = fn_800179A8(4, &lbl_8082A650[0], 0x15);
//     var_r4 = temp_r3;
//     if (temp_r3 != 0) {
//         var_r4 = fn_800A5278(); // NetZ ctor
//     }

//     // looks like another ctor
//     fn_800A49A0(arg0, var_r4);
//     *arg0 = &lbl_8082A608[0];
//     return arg0;
// }

// // ------------------------------------
// // fn_800A5214
// // ------------------------------------

// extern "C" void fn_800A4C84(s32, s32*);
// extern "C" s32** fn_800A5214(s32**,s32);
// extern s32 lbl_8082A608[];

// s32** fn_800A5214(s32** arg0, s32 arg1) {
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
Quazal::NetZSpecifics::NetZSpecifics()
{
}

// ------------------------------------
// fn_800A52B4
// ------------------------------------
Quazal::NetZSpecifics::~NetZSpecifics()
{
}

// // ------------------------------------
// // fn_800A530C
// // ------------------------------------
s32 Quazal::NetZSpecifics::fn_800A530C()
{
	return 1;
}

// ------------------------------------
// fn_800A5314
// ------------------------------------
void Quazal::NetZSpecifics::fn_800A5314(void)
{
	fn_80083734();
	fn_8007DFD0();
}

// ------------------------------------
// fn_800A5338
// ------------------------------------
void Quazal::NetZSpecifics::fn_800A5338(void)
{
	fn_80083174();
	lbl_808E2DA0 = 0;
	fn_8007E3C0();
	fn_80084160();
}
