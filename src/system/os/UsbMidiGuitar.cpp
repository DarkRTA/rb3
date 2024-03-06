#include "os/UsbMidiGuitar.h"

UsbMidiGuitar* TheGuitar;
bool UsbMidiGuitar::mUsbMidiGuitarExists = false;

UsbMidiGuitar::UsbMidiGuitar(){
    if(!mUsbMidiGuitarExists){
        mUsbMidiGuitarExists = true;
        int i7 = 0;
        for(int i = 4; i != 0; i--){
            mStringVelocity[1][5] = 0;
            mStringVelocity[2][3] = 0;
            mStringVelocity[3][1] = 0;
            mStringVelocity[3][i7 + 4] = 0;
            mStringVelocity[4][0] = 0;

//       pUVar2 = (UsbMidiGuitar *)(pUVar2->mStringStrummed[0] + 4);
//       pUVar3->mStringStrummed[0][0] = false;
//       *(undefined4 *)pUVar4->mStringStrummed[4] = 0;
//       pUVar4->mStringFret[3][0] = 0;
//       pUVar4->mStringVelocity[4][4] = 0;
//       pUVar3->mStringStrummed[0][1] = false;
//       *(undefined4 *)(pUVar4->mStringStrummed[4] + 4) = 0;
//       pUVar4->mStringFret[3][1] = 0;
//       pUVar4->mStringVelocity[4][5] = 0;
//       pUVar3->mStringStrummed[0][2] = false;
//       *(undefined4 *)(pUVar4->mStringStrummed[5] + 2) = 0;
//       pUVar4->mStringFret[3][2] = 0;
//       pUVar4->mStringVelocity[5][0] = 0;
//       pUVar3->mStringStrummed[0][3] = false;
//       *(undefined4 *)pUVar4->mStringStrummed[6] = 0;
//       pUVar4->mStringFret[3][3] = 0;
//       pUVar4->mStringVelocity[5][1] = 0;
//       pUVar3->mStringStrummed[0][4] = false;
//       *(undefined4 *)(pUVar4->mStringStrummed[6] + 4) = 0;
//       pUVar4->mStringFret[3][4] = 0;
//       pUVar4->mStringVelocity[5][2] = 0;
//       pUVar3->mStringStrummed[0][5] = false;
//       pUVar3 = (UsbMidiGuitar *)(pUVar3->mStringStrummed + 1);
//       *(undefined4 *)(pUVar4->mStringStrummed[7] + 2) = 0;
//       pUVar4->mStringFret[3][5] = 0;
//       pUVar4->mStringVelocity[5][3] = 0;
//       pUVar4 = (UsbMidiGuitar *)(pUVar4->mStringStrummed + 4);
//       *(undefined *)pUVar5->mStringFret[7] = 0;
//       *(undefined *)((int)pUVar5->mStringFret[7] + 1) = 0;
//       *(undefined *)((int)pUVar5->mStringFret[7] + 2) = 0;
//       *(undefined *)((int)pUVar5->mStringFret[7] + 3) = 0;
//       *(undefined *)(pUVar5->mStringFret[7] + 1) = 0;
//       pUVar5 = (UsbMidiGuitar *)(pUVar5->mStringStrummed[0] + 5);
//       pUVar6->mStringFret[7][5] = 0;
//       pUVar6->mStringVelocity[0][0] = 0;
//       pUVar6->mStringVelocity[0][1] = 0;
//       pUVar6 = (UsbMidiGuitar *)(pUVar6->mStringStrummed + 2);
//       iVar8 = iVar8 + -1;
//       iVar7 = iVar7 + 1;
        }
    }
    mTimer.Init();
}

// UsbMidiGuitar * __thiscall UsbMidiGuitar::UsbMidiGuitar(UsbMidiGuitar *this)

// {
//   bool bVar1;
//   UsbMidiGuitar *pUVar2;
//   UsbMidiGuitar *pUVar3;
//   UsbMidiGuitar *pUVar4;
//   UsbMidiGuitar *pUVar5;
//   UsbMidiGuitar *pUVar6;
//   int iVar7;
//   int iVar8;
//   undefined4 in_TBLr;
  
//   this->mAccelerometer[1][1] = 0;
//   if (mUsbMidiGuitarExists == '\0') {
//     mUsbMidiGuitarExists = '\x01';
//     iVar8 = 4;
//     pUVar2 = this;
//     pUVar3 = this;
//     pUVar4 = this;
//     pUVar5 = this;
//     pUVar6 = this;
//     iVar7 = 0;
//     do {
//       pUVar2->mStringVelocity[1][5] = 0;
//       pUVar2->mStringVelocity[2][3] = 0;
//       pUVar2->mStringVelocity[3][1] = 0;
//       *(undefined *)((int)this->mStringVelocity[3] + iVar7 + 0x14) = 0;
//       pUVar2->mStringVelocity[4][0] = 0;
//       pUVar2 = (UsbMidiGuitar *)(pUVar2->mStringStrummed[0] + 4);
//       pUVar3->mStringStrummed[0][0] = false;
//       *(undefined4 *)pUVar4->mStringStrummed[4] = 0;
//       pUVar4->mStringFret[3][0] = 0;
//       pUVar4->mStringVelocity[4][4] = 0;
//       pUVar3->mStringStrummed[0][1] = false;
//       *(undefined4 *)(pUVar4->mStringStrummed[4] + 4) = 0;
//       pUVar4->mStringFret[3][1] = 0;
//       pUVar4->mStringVelocity[4][5] = 0;
//       pUVar3->mStringStrummed[0][2] = false;
//       *(undefined4 *)(pUVar4->mStringStrummed[5] + 2) = 0;
//       pUVar4->mStringFret[3][2] = 0;
//       pUVar4->mStringVelocity[5][0] = 0;
//       pUVar3->mStringStrummed[0][3] = false;
//       *(undefined4 *)pUVar4->mStringStrummed[6] = 0;
//       pUVar4->mStringFret[3][3] = 0;
//       pUVar4->mStringVelocity[5][1] = 0;
//       pUVar3->mStringStrummed[0][4] = false;
//       *(undefined4 *)(pUVar4->mStringStrummed[6] + 4) = 0;
//       pUVar4->mStringFret[3][4] = 0;
//       pUVar4->mStringVelocity[5][2] = 0;
//       pUVar3->mStringStrummed[0][5] = false;
//       pUVar3 = (UsbMidiGuitar *)(pUVar3->mStringStrummed + 1);
//       *(undefined4 *)(pUVar4->mStringStrummed[7] + 2) = 0;
//       pUVar4->mStringFret[3][5] = 0;
//       pUVar4->mStringVelocity[5][3] = 0;
//       pUVar4 = (UsbMidiGuitar *)(pUVar4->mStringStrummed + 4);
//       *(undefined *)pUVar5->mStringFret[7] = 0;
//       *(undefined *)((int)pUVar5->mStringFret[7] + 1) = 0;
//       *(undefined *)((int)pUVar5->mStringFret[7] + 2) = 0;
//       *(undefined *)((int)pUVar5->mStringFret[7] + 3) = 0;
//       *(undefined *)(pUVar5->mStringFret[7] + 1) = 0;
//       pUVar5 = (UsbMidiGuitar *)(pUVar5->mStringStrummed[0] + 5);
//       pUVar6->mStringFret[7][5] = 0;
//       pUVar6->mStringVelocity[0][0] = 0;
//       pUVar6->mStringVelocity[0][1] = 0;
//       pUVar6 = (UsbMidiGuitar *)(pUVar6->mStringStrummed + 2);
//       iVar8 = iVar8 + -1;
//       iVar7 = iVar7 + 1;
//     } while (iVar8 != 0);
//     Timer::Init((Timer *)this);
//     bVar1 = DAT_80cab59c == 0;
//     DAT_80cab59c = DAT_80cab59c + 1;
//     if (bVar1) {
//       mTimer = in_TBLr;
//     }
//   }
//   return this;
// }
