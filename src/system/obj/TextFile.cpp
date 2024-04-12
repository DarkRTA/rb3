#include "obj/TextFile.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/MakeString.h"
#include "obj/MessageTimer.h"
#include "utl/Symbols.h"
#include "obj/Dir.h"

extern bool UsingHolmes(int);

inline void TextFile::GetAppendFile(const char* c, const char* tok, int tokLen) {
    const char* s = strstr(c, tok);
    if(s){
        char buf[0x100];
        strcpy(buf, c);
        char* ptr = &buf[s - c];
        strncpy(ptr, ptr + tokLen, strlen(s) - (tokLen - 1));
        mFile = NewFile(buf, 0x304);
    }
    else {
        mFile = NewFile(c, 0xA04);
    }
}

void TextFile::SetName(const char* c, class ObjectDir* dir){
    Hmx::Object::SetName(c, dir);
    delete mFile;
    mFile = 0;

    bool holmes = UsingHolmes(4);
    if(c != 0 && *c != '\0' && holmes){
        GetAppendFile(c, "_append", sizeof("_append") - 1);
    }
}

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

// FIXME: in order for this TU to link, the bss for "_s" needs to come BEFORE the bss for SetType's "types"
BEGIN_HANDLERS(TextFile);
    HANDLE(print, OnPrint);
    {
        static Symbol _s("printf");
        HANDLE(_s, OnPrintf);
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

void MoveDtorUp(TextFile* tf){
    delete tf;
}

void MoveSetTypeUp(TextFile* tf){
    tf->SetType(Symbol());
}
