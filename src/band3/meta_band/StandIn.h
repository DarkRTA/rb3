#include "system/meta/FixedSizeSaveable.h"
#include "system/utl/HxGuid.h"

class StandIn : public FixedSizeSaveable {
public:
    StandIn();
    ~StandIn();
    void SetNone();
    void SetName(Symbol);
    void SetGuid(HxGuid);
    bool IsNone() const;
    bool IsPrefabCharacter() const;
    bool IsCustomCharacter() const;
    void SaveSize(int);
    void SaveFixed(FixedSizeSaveableStream&) const;
    void LoadFixed(FixedSizeSaveableStream&, int);
};
