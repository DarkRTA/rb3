#ifndef MIDI_MIDICONSTANTS_H
#define MIDI_MIDICONSTANTS_H
#include "os/Debug.h"

unsigned char MidiGetStatus(unsigned char uc){
    
}

unsigned char MidiGetType(unsigned char uc){
    return uc & 0xF0;
}

bool MidiIdk(unsigned char uc){
    return (MidiGetType(uc) & 0xF0) == 0xF0;
}

unsigned char MidiGetChannel(unsigned char uc){

}

// MidiReader::ReadEvent(BinStream&)
// debug
//   else {
//     bVar1 = false;
//     if (-1 < (char)local_27[0]) {
//       pcVar3 = ::MakeString(kAssertStr,@STRING@MidiGetType__FUc_80BFB4D8,0x2f,
//                             @STRING@MidiGetType__FUc@0_80BFB4C0);
//       Debug::Fail((Debug *)TheDebug,pcVar3);
//     }
//     if (((byte)MVar2 & 0xf0) != 0xf0) {
//       this[0x30] = local_27[0];
//     }
//   }

// retail
//   else {
//     bVar1 = false;
//     iVar2 = fn_8048DBE8(local_17[0]);
//     if (iVar2 == 0) {
//       *(uchar *)(param_1 + 0x30) = local_17[0];
//     }
//   }

#endif
