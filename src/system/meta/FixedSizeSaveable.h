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

    static int GetMaxSymbols(){
        MILO_ASSERT(sMaxSymbols >= 0, 0x1C0);
        return sMaxSymbols;
    }

    static int sCurrentMemcardLoadVer;
    static int sSaveVersion;
    static int sMaxSymbols;
    static bool sPrintoutsEnabled;
    SaveSizeMethodFunc* mSaveSizeMethod;
};

FixedSizeSaveableStream& operator<<(FixedSizeSaveableStream&, const FixedSizeSaveable&);
FixedSizeSaveableStream& operator>>(FixedSizeSaveableStream&, FixedSizeSaveable&);

#endif
