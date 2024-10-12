#ifndef META_FIXEDSIZESAVEABLE_H
#define META_FIXEDSIZESAVEABLE_H
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "meta/FixedSizeSaveableStream.h"
#include "os/Debug.h"
#include <set>

typedef int SaveSizeMethodFunc(int);

class FixedSizeSaveable {
public:
    FixedSizeSaveable();
    virtual ~FixedSizeSaveable();
    virtual void SaveFixed(FixedSizeSaveableStream&) const = 0;
    virtual void LoadFixed(FixedSizeSaveableStream&, int) = 0;

    static void Init(int, int);
    static void PadStream(FixedSizeSaveableStream&, int);
    static void DepadStream(FixedSizeSaveableStream&, int);
    static void SaveFixedSymbol(FixedSizeSaveableStream&, const Symbol&);
    static void LoadFixedSymbol(FixedSizeSaveableStream&, Symbol&);
    static void SaveFixedString(FixedSizeSaveableStream&, const class String&);
    static void LoadFixedString(FixedSizeSaveableStream&, class String&);
    static void SaveSymbolID(FixedSizeSaveableStream&, Symbol);
    static void LoadSymbolFromID(FixedSizeSaveableStream&, Symbol&);
    static void SaveSymbolTable(FixedSizeSaveableStream&, int, int);
    static void LoadSymbolTable(FixedSizeSaveableStream&, int, int);
    static void SaveStd(FixedSizeSaveableStream&, const std::vector<Symbol>&, int);
    static void LoadStd(FixedSizeSaveableStream&, std::vector<Symbol>&, int);
    static void SaveStd(FixedSizeSaveableStream&, const std::list<Symbol>&, int);
    static void LoadStd(FixedSizeSaveableStream&, std::list<Symbol>&, int);
    static void SaveStd(FixedSizeSaveableStream&, const std::set<Symbol>&, int);
    static void LoadStd(FixedSizeSaveableStream&, std::set<Symbol>&, int);
    static void EnablePrintouts(bool);

    // Note: `Allocator` here is actually the size/capacity type parameter on Wii.
    // The name is based on Xbox 360 symbols, which show the allocator type instead.
    template <class T, class Allocator>
    static void SaveStdFixed(FixedSizeSaveableStream& stream, const std::vector<T, Allocator>& vec, int maxsize){
        int savesize = T::SaveSize(FixedSizeSaveable::sSaveVersion);
        int vecsize = vec.size();
        if(vecsize > maxsize){
            MILO_WARN("The vector size is greater than the maximum supplied! size=%i max=%i\n", vecsize, maxsize);
            vecsize = maxsize;
        }
        stream << vecsize;
        for(int i = 0; i < vecsize; i++){
            vec[i].SaveFixed(stream);
        }
        if(maxsize > vecsize) PadStream(stream, savesize * (maxsize - vecsize));
    }

    template <class T, class Allocator>
    static void LoadStdFixed(FixedSizeSaveableStream& stream, std::vector<T, Allocator>& vec, int maxsize, int i2){
        int savesize = T::SaveSize(i2);
        if(vec.size() != 0){
            MILO_WARN("vector is not empty!");
            vec.clear();
        }
        int vecsize;
        stream >> vecsize;
        vec.resize(vecsize);
        for(int i = 0; i < vecsize; i++){
            vec[i].LoadFixed(stream, i2);
        }
        if(maxsize > vecsize) DepadStream(stream, savesize * (maxsize - vecsize));
    }

    template <class T, class Allocator>
    static void SaveStd(FixedSizeSaveableStream& stream, const std::vector<T, Allocator>& vec, int maxsize, int savesize){
        int vecsize = vec.size();
        if(vecsize > maxsize){
            MILO_WARN("The vector size is greater than the maximum supplied! size=%i max=%i\n", vecsize, maxsize);
            vecsize = maxsize;
        }
        stream << vecsize;
        for(int i = 0; i < vecsize; i++){
            stream << vec[i];
        }
        if(maxsize > vecsize) PadStream(stream, (savesize * (maxsize - vecsize)));
    }

    template <class T, class Allocator>
    static void LoadStd(FixedSizeSaveableStream& stream, std::vector<T, Allocator>& vec, int maxsize, int savesize){
        if(vec.size() != 0){
            MILO_WARN("vector is not empty!");
            vec.clear();
        }
        int vecsize;
        stream >> vecsize;
        vec.resize(vecsize);
        for(int i = 0; i < vecsize; i++){
            stream >> vec[i];
        }
        if(maxsize > vecsize) DepadStream(stream, savesize * (maxsize - vecsize));
    }

    static int GetMaxSymbols(){
        MILO_ASSERT(sMaxSymbols >= 0, 0x1C0);
        return sMaxSymbols;
    }

    static int sCurrentMemcardLoadVer;
    static int sSaveVersion;
    static int sMaxSymbols;
    static bool sPrintoutsEnabled;
    SaveSizeMethodFunc* mSaveSizeMethod;

    static int GetSaveVersion(){ return sSaveVersion; }
};

FixedSizeSaveableStream& operator<<(FixedSizeSaveableStream&, const FixedSizeSaveable&);
FixedSizeSaveableStream& operator>>(FixedSizeSaveableStream&, FixedSizeSaveable&);

#endif
