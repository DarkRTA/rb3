#include "obj/TextFile.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/MakeString.h"
#include "obj/MessageTimer.h"
#include "utl/Symbols.h"
// #include "obj/Dir.h"

// void TextFile::SetName(const char* c, ObjectDir* dir){
//     Hmx::Object::SetName(c, dir);
//     delete mFile;
//     mFile = 0;
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

DataNode TextFile::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);
    if(sym == print){
        DataNode printed = OnPrint(_msg);
        if(printed.Type() != kDataUnhandled) return DataNode(printed);
    }
    static Symbol s("printf");
    if(sym == s){
        DataNode node_printf = OnPrintf(_msg);
        if(node_printf.Type() != kDataUnhandled) return DataNode(node_printf);
    }
    if(sym == reflect){
        DataNode ref = OnReflect(_msg);
        if(ref.Type() != kDataUnhandled) return DataNode(ref);
    }
    {
        DataNode handled = Hmx::Object::Handle(_msg, false);
        if(handled.Type() != kDataUnhandled){
            return DataNode(handled);
        }
    }
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, 0x3A, PathName(this), sym);
    return DataNode(kDataUnhandled, 0);
}

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

// DataNode TextFile::OnReflect(DataArray* array){
//     if(mFile != 0){
//         TextStream* idk = TheDebug.SetReflect(this);
//         for(int i = 2; i < array->Size(); i++){
//             array->Command(i)->Execute();
//         }
//         TheDebug.SetReflect(idk);
//     }
//     return DataNode(0);
// }
