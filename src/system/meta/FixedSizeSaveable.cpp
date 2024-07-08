#define STL_NODE_ALLOC_DEBUG
#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"
#include <typeinfo>
#include "decomp.h"

int FixedSizeSaveable::sCurrentMemcardLoadVer = -1;
int FixedSizeSaveable::sSaveVersion = -1;
int FixedSizeSaveable::sMaxSymbols = -1;
bool FixedSizeSaveable::sPrintoutsEnabled;

DECOMP_FORCEACTIVE(FixedSizeSaveable,
    "Classes implementing FixedSizeSaveable should have their own implementations of SaveSize!",
    __FILE__
)

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
    MILO_ASSERT(fixedStream.Tell()-start <= kSymbolSize, 0x62);
    DepadStream(fixedStream, start + (kSymbolSize - fixedStream.Tell()));
}

void FixedSizeSaveable::SaveFixedString(FixedSizeSaveableStream& fixedStream, const String& str){
    int start = fixedStream.Tell();
    fixedStream << str;
    MILO_ASSERT(fixedStream.Tell()-start <= kStringSize, 0x6C);
    PadStream(fixedStream, start + (kStringSize - fixedStream.Tell()));
}

void FixedSizeSaveable::LoadFixedString(FixedSizeSaveableStream& fixedStream, String& str){
    int start = fixedStream.Tell();
    fixedStream >> str;
    MILO_ASSERT(fixedStream.Tell()-start <= kStringSize, 0x73);
    DepadStream(fixedStream, start + (kStringSize - fixedStream.Tell()));
}

void FixedSizeSaveable::SaveSymbolID(FixedSizeSaveableStream& stream, Symbol sym){
    int id;
    if(stream.HasSymbol(sym)) id = stream.GetID(sym);
    else id = stream.AddSymbol(sym);
    stream << id;
}

void FixedSizeSaveable::LoadSymbolFromID(FixedSizeSaveableStream& stream, Symbol& sym){
    int id = 0;
    stream >> id;
    sym = stream.GetSymbol(id);
}

void FixedSizeSaveable::SaveSymbolTable(FixedSizeSaveableStream& fs, int i, int j){
    std::map<Symbol, int>& symMap = fs.GetSymbolToIDMap();
    int map_size = symMap.size();
    fs << map_size;
    for(std::map<Symbol,int>::iterator it = symMap.begin(); it != symMap.end(); it++){
        SaveFixedSymbol(fs, it->first);
        fs << it->second;
    }
    if(i > map_size) PadStream(fs, j * (i - map_size));
}

void FixedSizeSaveable::LoadSymbolTable(FixedSizeSaveableStream& fs, int i, int j){
    int size;
    fs >> size;
    for(int x = 0; x < size; x++){
        Symbol s;
        LoadFixedSymbol(fs, s);
        int someInt;
        fs >> someInt;
        fs.SetSymbolID(s, someInt);
    }
    if(i > size){
        DepadStream(fs, j * (i - size));
    }
}

void FixedSizeSaveable::SaveStd(FixedSizeSaveableStream& fs, const std::vector<Symbol>& vec, int i){
    int size = vec.size();
    fs << size;
    for(std::vector<Symbol>::const_iterator it = vec.begin(); it != vec.end(); it++){
        SaveSymbolID(fs, *it);
    }
    if(i > size) PadStream(fs, (i - size) * 4);
}

void FixedSizeSaveable::LoadStd(FixedSizeSaveableStream& fs, std::vector<Symbol>& vec, int i){
    int size;
    fs >> size;
    vec.resize(size);
    for(int x = 0; x < size; x++){
        LoadSymbolFromID(fs, vec[x]);
    }
    if(i > size) DepadStream(fs, (i - size) * 4);
}

void FixedSizeSaveable::SaveStd(FixedSizeSaveableStream& fs, const std::list<Symbol>& list, int i){
    int size = list.size();
    fs << size;
    for(std::list<Symbol>::const_iterator it = list.begin(); it != list.end(); it++){
        SaveSymbolID(fs, *it);
    }
    if(i > size) PadStream(fs, (i - size) * 4);
}

void FixedSizeSaveable::LoadStd(FixedSizeSaveableStream& fs, std::list<Symbol>& list, int i){
    int size;
    fs >> size;
    for(int idx = 0; idx < size; idx++){
        Symbol s;
        LoadSymbolFromID(fs, s);
        list.push_back(s);
    }
    if(i > size) DepadStream(fs, (i - size) * 4);
}

void FixedSizeSaveable::SaveStd(FixedSizeSaveableStream& fs, const std::set<Symbol>& set, int i){
    int size = set.size();
    fs << size;
    for(std::set<Symbol>::const_iterator it = set.begin(); it != set.end(); it++){
        SaveSymbolID(fs, *it);
    }
    if(i > size) PadStream(fs, (i - size) * 4);
}

void FixedSizeSaveable::LoadStd(FixedSizeSaveableStream& fs, std::set<Symbol>& set, int i){
    int size;
    fs >> size;
    for(int idx = 0; idx < size; idx++){
        Symbol s;
        LoadSymbolFromID(fs, s);
        set.insert(s);
    }
    if(i > size) DepadStream(fs, (i - size) * 4);
}

void FixedSizeSaveable::EnablePrintouts(bool b){ sPrintoutsEnabled = b; }

FixedSizeSaveableStream& operator<<(FixedSizeSaveableStream& fs, const FixedSizeSaveable& saveable){
    MILO_ASSERT(FixedSizeSaveable::sSaveVersion >= 0, 0xFF);
    MILO_ASSERT(FixedSizeSaveable::sMaxSymbols >= 0, 0x100);

    int oldtell = fs.Tell();
    saveable.SaveFixed(fs);
    int newtell = fs.Tell();

    MILO_ASSERT_FMT(!fs.Fail(), "FixedSizeSaveableStream operator<< fixedStream failed!");
    MILO_ASSERT_FMT(saveable.mSaveSizeMethod, "You must set the save size method of a FixedSizeSaveable object by            using the SETSAVESIZE macro in its constructor!");

    if(newtell != oldtell + saveable.mSaveSizeMethod(FixedSizeSaveable::GetSaveVersion())){
        MILO_FAIL("Bad save file size!  %s wrote %d instead of the expected %d",
            typeid(saveable).name(),
            newtell - oldtell,
            saveable.mSaveSizeMethod(FixedSizeSaveable::GetSaveVersion())
        );
    }

    return fs;
}

FixedSizeSaveableStream& operator>>(FixedSizeSaveableStream& fs, FixedSizeSaveable& saveable){
    MILO_ASSERT(FixedSizeSaveable::sSaveVersion >= 0, 0x125);
    MILO_ASSERT(FixedSizeSaveable::sMaxSymbols >= 0, 0x126);
    MILO_ASSERT(FixedSizeSaveable::sCurrentMemcardLoadVer > 0, 0x127);

    int asdf = FixedSizeSaveable::sCurrentMemcardLoadVer;

    int oldtell = fs.Tell();
    saveable.LoadFixed(fs, asdf);
    int newtell = fs.Tell();

    MILO_ASSERT_FMT(saveable.mSaveSizeMethod, "You must set the save size method of a FixedSizeSaveable object by            using the SETSAVESIZE macro in its constructor!");

    if(newtell != oldtell + saveable.mSaveSizeMethod(asdf)){
        MILO_FAIL("Bad load!  %s read %d instead of the expected %d!",
            typeid(saveable).name(),
            newtell - oldtell,
            saveable.mSaveSizeMethod(asdf)
        );
    }

    return fs;
}
