#include "TextFile.h"
#include "MakeString.h"
#include "System.h"
#include "obj/Utl.h"
#include "symbols.hpp"
#include "Debug.h"

void TextFile::SetName(const char* c, ObjectDir* dir){
    Hmx::Object::SetName(c, dir);
    delete mFile;
    mFile = 0;
}

void TextFile::Print(const char* str){
    char kCRLF[2] = { '\r', '\n' };
    char *p = (char *)str;
    while (*p != '\0') {
        if (*p == '\n' && p[1] != '\r'){
            mFile->V_Unk5(kCRLF, 2);
        }
        else mFile->V_Unk5(p, 1);
        mFile->Flush();
        p++;
    }
}

DataNode TextFile::Handle(DataArray* _msg, bool _warn){
    Symbol match = _msg->Sym(1);
    if(match == SymPrint){
        DataNode print = OnPrint(_msg);
        if(print.Type() != kDataUnhandled) return DataNode(print);
    }
    static Symbol SymPrintf("printf");
    if(match == SymPrintf){
        DataNode node_printf = OnPrintf(_msg);
        if(node_printf.Type() != kDataUnhandled) return DataNode(node_printf);
    }
    if(match == SymReflect){
        DataNode ref = OnReflect(_msg);
        if(ref.Type() != kDataUnhandled) return DataNode(ref);
    }
    // if no match, fall to here
    {
    DataNode base = Hmx::Object::Handle(_msg, false);
    if(base.Type() != kDataUnhandled) return DataNode(base);
    }
    if(_warn) PathName(this);
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

extern Debug TheDebug;

DataNode TextFile::OnReflect(DataArray* array){
    if(mFile != 0){
        TextStream* idk = TheDebug.SetReflect(this);
        for(int i = 2; i < array->Size(); i++){
            array->Command(i)->Execute();
        }
        TheDebug.SetReflect(idk);
    }
    return DataNode(0);
}
