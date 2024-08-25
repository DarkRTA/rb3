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

// NOTE(AndrewB):
// Marking this as static like all(?) the other singletons
// causes linking errors w/ a TU (CharacterCreatorPanel.o)
// that hasn't been matched yet, no idea if this could cause
// issues in the future when that TU *is* matched
// but it links fine like this right now, so...
extern NameGenerator *TheNameGenerator;

#endif // METABAND_NAMEGEN_H
