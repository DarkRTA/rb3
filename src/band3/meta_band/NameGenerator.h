#ifndef METABAND_NAMEGEN_H
#define METABAND_NAMEGEN_H

#include "obj/Data.h"
#include "obj/Object.h"
#include "utl/Symbol.h"
#include <map>
#include <vector>

class NameGenerator : public Hmx::Object { // 0x34
public:
    NameGenerator(DataArray*);
    virtual ~NameGenerator();
    virtual DataNode Handle(DataArray*, bool);

    void Cleanup();
    void Init(DataArray*);
    void ConfigureNameData(DataArray*);
    DataArray* GetNameList(Symbol) const; // i think????
    Symbol GetRandomNameFromList(Symbol);

    std::map<Symbol, DataArray*> m_mapNameLists;
};

static NameGenerator* TheNameGenerator = 0;

#endif // METABAND_NAMEGEN_H
