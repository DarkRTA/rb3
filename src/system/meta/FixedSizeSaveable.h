#ifndef META_FIXEDSIZESAVEABLE_H
#define META_FIXEDSIZESAVEABLE_H
#include "utl/BinStream.h"
#include "utl/BufStream.h"

typedef int SaveSizeMethodFunc(int);

class FixedSizeSaveableStream : public BufStream {};

class FixedSizeSaveable {
public:
    FixedSizeSaveable();
    virtual ~FixedSizeSaveable();
    virtual void SaveFixed(FixedSizeSaveableStream&) const = 0;
    virtual void LoadFixed(FixedSizeSaveableStream&, int) = 0;

    static void Init(int, int);

    static int sSaveVersion;
    static int sMaxSymbols;
    static bool sPrintoutsEnabled;
    SaveSizeMethodFunc* mSaveSizeMethod;
};

BinStream& operator<<(BinStream&, const FixedSizeSaveable&);
BinStream& operator>>(BinStream&, FixedSizeSaveable&);

#endif
