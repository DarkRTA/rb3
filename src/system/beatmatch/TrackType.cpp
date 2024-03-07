#include "beatmatch/TrackType.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"

Symbol TrackTypeToSym(TrackType type){
    return DataGetMacro("TRACK_SYMBOLS")->Sym(type);
}

TrackType SymToTrackType(Symbol sym){
    for(int i = 0; i < 11; i++){
        if(sym == DataGetMacro("TRACK_SYMBOLS")->Sym(i)){
            return (TrackType)i;
        }
    }
    MILO_ASSERT(false, 0x1B);
    return kTrackNone;
}

// int SymToTrackType(Symbol param_1)

// {
//   Symbol SVar1;
//   DataArray *this;
//   DataNode *this_00;
//   int iVar2;
//   char *pcVar3;
//   int iVar4;
//   Symbol aSStack_18 [2];
  
//   iVar4 = 0;
//   do {
//     SVar1.mStr = (char *)Symbol::Symbol(aSStack_18,@stringBase0);
//     this = (DataArray *)DataGetMacro(SVar1);
//     this_00 = (DataNode *)DataArray::Node(this,iVar4);
//     iVar2 = DataNode::Sym(this_00,this);
//     if (*(int *)param_1.mStr == iVar2) {
//       return iVar4;
//     }
//     iVar4 = iVar4 + 1;
//   } while (iVar4 < 0xb);
//   pcVar3 = MakeString(kAssertStr,s_TrackType.cpp_80bfc8c6,0x1b,s_false_80bfc8d4);
//   Debug::Fail((Debug *)TheDebug,pcVar3);
//   return 10;
// }
