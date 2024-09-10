#include "bandobj/BandCharacter.h"

void BandCharacter::Init(){ Register(); }
void BandCharacter::Terminate(){}

BandCharacter::BandCharacter() : unk450(0), unk454(this, 0), unk460(0), unk464(0), unk528(0), unk529(1), unk52c(this, 0), unk538(this, 0), unk544("medium"), unk548(0),
    unk550(this, 0), unk55c(this, 0), unk568(this, 0), unk574(0), unk578(this, 0), unk584("rocker"), unk588("small_club"), unk58c(0), unk590("none"), unk594(this, 0),
    unk5a0(0), unk5a1(0), unk5a2(0), unk5a3(0), unk5a4(this, 0), unk5b0(this, kObjListNoNull), unk5c0(this, kObjListNoNull), unk5d0(this, kObjListNoNull),
    unk5e0(this, kObjListNoNull), unk5f0(this, kObjListNoNull), unk600(this, kObjListNoNull), unk610(this, kObjListNoNull), unk620(this, kObjListNoNull),
    unk630(this, kObjListNoNull), unk640(this, kObjListNoNull), unk650(this, kObjListNoNull), unk660(this, kObjListNoNull), unk670(this, kObjListNoNull),
    unk680(this, 0), unk68c(this, 0), unk698(this, 0), unk6a4(this, 0), unk6b0(this, 0), unk6bc(0), unk6bd(1), unk6c0(this, 0), unk6d4(0), unk6d8(0), unk6ec(0),
    unk738(0), unk73c(this, kObjListNoNull), unk74c(this, kObjListNoNull) {

}

#pragma push
#pragma dont_inline on
BandCharacter::~BandCharacter(){
    TheRnd->CompressTextureCancel(this);
}
#pragma pop