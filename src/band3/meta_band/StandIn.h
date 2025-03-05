#include "system/meta/FixedSizeSaveable.h"
#include "system/utl/HxGuid.h"

class StandIn : public FixedSizeSaveable {
public:
    StandIn();
    virtual ~StandIn();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    void SetNone();
    void SetName(Symbol);
    void SetGuid(HxGuid);
    bool IsNone() const;
    bool IsPrefabCharacter() const;
    bool IsCustomCharacter() const;
    Symbol GetName() const { return mName; }
    const HxGuid &GetGuid() const { return mGuid; }

    static int SaveSize(int);

    Symbol mName; // 0x8
    HxGuid mGuid; // 0xc
};
