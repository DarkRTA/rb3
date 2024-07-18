#include "char/CharCollide.h"

CharCollide::CharCollide() : mShape(kSphere), mFlags(0), mMesh(this, 0) {

}

//   ObjPtr<>::ObjPtr((ObjPtr<> *)(this + 0x98),(Object *)pCVar1,(RndMesh *)0x0);
//   pCVar1 = this + 0xb8;
//   do {
//     RSONotifyModuleLoaded(pCVar1);
//     pCVar1 = pCVar1 + 0x10;
//   } while (pCVar1 < this + 0x138);
//   Transform::Transform(this + 0x148);
//   this[0x188] = (CharCollide)0x0;
//   iVar3 = 2;
//   iVar2 = 0;
//   do {
//     *(undefined4 *)(this + iVar2 + 0x140) = 0;
//     *(undefined4 *)(this + iVar2 + 0x138) = 0;
//     iVar3 = iVar3 + -1;
//     iVar2 = iVar2 + 4;
//   } while (iVar3 != 0);
//   fn_804C3484(this); // copy original to cur
//   iVar2 = 0;
//   iVar3 = 0;
//   do {
//     *(undefined4 *)(this + iVar3 + 0xb8) = 0;
//     Vector3::Zero((Vector3 *)(this + iVar3 + 0xbc));
//     iVar2 = iVar2 + 1;
//     iVar3 = iVar3 + 0x10;
//   } while (iVar2 < 8);

//   Transform::Reset(this + 0x148);

//   *(undefined4 *)(this + 0xb8) = 0;
//   *(float *)(this + 0xc4) = 0.0;
//   *(float *)(this + 0xc0) = 0.0;
//   *(float *)(this + 0xbc) = 0.0;

//   *(undefined4 *)(this + 0xc8) = 0;
//   *(float *)(this + 0xd4) = 0.0;
//   *(float *)(this + 0xd0) = 0.0;
//   *(float *)(this + 0xcc) = 0.0;

//   *(undefined4 *)(this + 0xd8) = 0;
//   *(float *)(this + 0xe4) = 0.0;
//   *(float *)(this + 0xe0) = 0.0;
//   *(float *)(this + 0xdc) = 0.0;

//   *(undefined4 *)(this + 0xe8) = 0;
//   *(float *)(this + 0xf4) = 0.0;
//   *(float *)(this + 0xf0) = 0.0;
//   *(float *)(this + 0xec) = 0.0;

//   *(undefined4 *)(this + 0xf8) = 0;
//   *(float *)(this + 0x104) = 0.0;
//   *(float *)(this + 0x100) = 0.0;
//   *(float *)(this + 0xfc) = 0.0;

//   *(undefined4 *)(this + 0x108) = 0;
//   *(float *)(this + 0x114) = 0.0;
//   *(float *)(this + 0x110) = 0.0;
//   *(float *)(this + 0x10c) = 0.0;

//   *(undefined4 *)(this + 0x118) = 0;
//   *(float *)(this + 0x124) = 0.0;
//   *(float *)(this + 0x120) = 0.0;
//   *(float *)(this + 0x11c) = 0.0;

//   *(undefined4 *)(this + 0x128) = 0;
//   *(float *)(this + 0x134) = 0.0;
//   *(float *)(this + 0x130) = 0.0;
//   *(float *)(this + 0x12c) = 0.0;

CharCollide::~CharCollide(){
    
}