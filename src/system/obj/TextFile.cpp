#include "obj/TextFile.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/MakeString.h"
#include "obj/MessageTimer.h"
#include "utl/Symbols.h"
#include "obj/Dir.h"

extern bool UsingHolmes(int);

void TextFile::SetName(const char* c, class ObjectDir* dir){
    Hmx::Object::SetName(c, dir);
    delete mFile;
    mFile = 0;
    if(c != 0 && *c != '\0' && UsingHolmes(4)){
        char* s = strstr(c, "_append");
        if(s){
            char* buf;
            strcpy(buf, c);
            strncpy(s + (buf - c), s, strlen(s) - 6);
            mFile = NewFile(buf, 0x304);
        }
        else mFile = NewFile(c, 0xA04);
    }
}

// void __thiscall TextFile::SetName(TextFile *this,char *param_1,ObjectDir *param_2)

// {
//   int *piVar1;
//   int iVar2;
//   char *__s;
//   size_t sVar3;
//   undefined4 uVar4;
//   char acStack_118 [7];
//   char acStack_111 [261];
  
//   Hmx::Object::SetName((Object *)this,param_1,param_2);
//   piVar1 = *(int **)(this + 0x20);
//   if (piVar1 != (int *)0x0) {
//     (**(code **)(*piVar1 + 8))(piVar1,1);
//   }
//   *(undefined4 *)(this + 0x20) = 0;
//   iVar2 = UsingHolmes(4);
//   if (((param_1 != (char *)0x0) && (*param_1 != '\0')) && (iVar2 != 0)) {
//     __s = strstr(param_1,::@stringBase0);
//     if (__s == (char *)0x0) {
//       uVar4 = NewFile(param_1,0xa04);
//       *(undefined4 *)(this + 0x20) = uVar4;
//     }
//     else {
//       strcpy(acStack_118,param_1);
//       sVar3 = strlen(__s);
//       strncpy(__s + (int)(acStack_118 + -(int)param_1),__s + (int)(acStack_111 + -(int)param_1),
//               sVar3 - 6);
//       uVar4 = NewFile(acStack_118,0x304);
//       *(undefined4 *)(this + 0x20) = uVar4;
//     }
//   }
//   return;
// }

void TextFile::Print(const char* str){
    MILO_ASSERT(mFile, 0x2F);
    char kCRLF[2] = { '\r', '\n' };
    char *p = (char *)str;
    while (*p != '\0') {
        if (*p == '\n' && p[1] != '\r'){
            mFile->Write(kCRLF, 2);
        }
        else mFile->Write(p, 1);
        mFile->Flush();
        p++;
    }
}

BEGIN_HANDLERS(TextFile);
    HANDLE(print, OnPrint);
    static Symbol _s("printf");
    if(sym == _s){
        DataNode node_printf = OnPrintf(_msg);
        if(node_printf.Type() != kDataUnhandled) return DataNode(node_printf);
    }
    HANDLE(reflect, OnReflect);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x4D);
END_HANDLERS;

DataNode TextFile::OnPrint(DataArray* array){
    if(mFile != 0){
        for(int i = 2; i < array->Size(); i++){
            array->Evaluate(i).Print(*this, true);
        }
    }
    return DataNode(0);
}

DataNode TextFile::OnPrintf(DataArray* array){
    if(mFile != 0){
        FormatString fs(array->Str(2));
        for(int i = 3; i < array->Size(); i++){
            fs << array->Evaluate(i);
        }
        Print(fs.Str());
    }
    return DataNode(0);
}

DataNode TextFile::OnReflect(DataArray* array){
    if(mFile){
        TextStream* idk = TheDebug.SetReflect(this);
        for(int i = 2; i < array->Size(); i++){
            array->Command(i)->Execute();
        }
        TheDebug.SetReflect(idk);
    }
    return DataNode(0);
}
