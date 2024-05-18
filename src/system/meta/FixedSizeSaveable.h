#ifndef META_FIXEDSIZESAVEABLE_H
#define META_FIXEDSIZESAVEABLE_H
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "meta/FixedSizeSaveableStream.h"

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
    static void SaveFixedString(FixedSizeSaveableStream&, const String&);
    static void LoadFixedString(FixedSizeSaveableStream&, String&);
    static void SaveSymbolID(FixedSizeSaveableStream&, Symbol);
    static void LoadSymbolFromID(FixedSizeSaveableStream&, Symbol&);

    static int sSaveVersion;
    static int sMaxSymbols;
    static bool sPrintoutsEnabled;
    SaveSizeMethodFunc* mSaveSizeMethod;
};

BinStream& operator<<(BinStream&, const FixedSizeSaveable&);
BinStream& operator>>(BinStream&, FixedSizeSaveable&);

#endif
