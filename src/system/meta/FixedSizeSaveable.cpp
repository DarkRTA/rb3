#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"

int FixedSizeSaveable::sSaveVersion = -1;
int FixedSizeSaveable::sMaxSymbols = -1;

FixedSizeSaveable::FixedSizeSaveable() : mSaveSizeMethod(0) {
    
}

FixedSizeSaveable::~FixedSizeSaveable(){
    
}

void FixedSizeSaveable::Init(int i1, int i2){
    sSaveVersion = i1;
    sMaxSymbols = i2;
}

void FixedSizeSaveable::PadStream(FixedSizeSaveableStream& stream, int i){
    char buf[1024];
    memset(buf, 0, 1024);
    for(; i > 0x400; i -= 0x400){
        stream.Write(buf, 0x400);
    }
    if(i > 0){
        stream.Write(buf, i);
    }
}

void FixedSizeSaveable::DepadStream(FixedSizeSaveableStream& stream, int i){
    char buf[1024];
    for(; i > 0x400; i -= 0x400){
        stream.Read(buf, 0x400);
    }
    if(i > 0){
        stream.Read(buf, i);
    }
}

#define kSymbolSize 0x32
#define kStringSize 0x80

void FixedSizeSaveable::SaveFixedSymbol(FixedSizeSaveableStream& fixedStream, const Symbol& sym){
    int start = fixedStream.Tell();
    fixedStream << sym;
    MILO_ASSERT(fixedStream.Tell()-start <= kSymbolSize, 0x5B);
    PadStream(fixedStream, start + (kSymbolSize - fixedStream.Tell()));
}

void FixedSizeSaveable::LoadFixedSymbol(FixedSizeSaveableStream& fixedStream, Symbol& sym){
    int start = fixedStream.Tell();
    fixedStream >> sym;
    MILO_ASSERT(fixedStream.Tell()-start <= kSymbolSize, 0x5B);
    DepadStream(fixedStream, start + (kSymbolSize - fixedStream.Tell()));
}

void FixedSizeSaveable::SaveFixedString(FixedSizeSaveableStream& fixedStream, const String& str){
    int start = fixedStream.Tell();
    fixedStream << str;
    MILO_ASSERT(fixedStream.Tell()-start <= kStringSize, 0x5B);
    PadStream(fixedStream, start + (kStringSize - fixedStream.Tell()));
}

void FixedSizeSaveable::LoadFixedString(FixedSizeSaveableStream& fixedStream, String& str){
    int start = fixedStream.Tell();
    fixedStream >> str;
    MILO_ASSERT(fixedStream.Tell()-start <= kStringSize, 0x5B);
    DepadStream(fixedStream, start + (kStringSize - fixedStream.Tell()));
}