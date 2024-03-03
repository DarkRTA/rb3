#include "NameGenerator.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/Symbols3.h"
#include "math/Rand.h"

NameGenerator::NameGenerator(DataArray* x) {
    MILO_ASSERT(!TheNameGenerator, 19);
    TheNameGenerator = this;
    SetName("name_generator", ObjectDir::sMainDir);
    Init(x);
}

NameGenerator::~NameGenerator() {
    TheNameGenerator = NULL;
    Cleanup();
}

void NameGenerator::Cleanup() {
    if (m_mapNameLists.size())
    m_mapNameLists.erase(m_mapNameLists.end());
}

void NameGenerator::Init(DataArray* x) { ConfigureNameData(x); }

void NameGenerator::ConfigureNameData(DataArray* x) {
    MILO_ASSERT(m_mapNameLists.empty(), 48);
    for (int i; i < x->Size(); i++) {
        DataArray* i_pNameArray = x->Array(i);
        MILO_ASSERT(i_pNameArray, 55);
        Symbol dingus = i_pNameArray->Sym(0);
        DataArray* test = GetNameList(dingus);
        if (test == NULL) {
            // TODO fill in
        } else MILO_WARN("Name Generator found duplicate name list: %s\n", dingus.mStr);
    }
}

DataArray* NameGenerator::GetNameList(Symbol) const {

}

Symbol NameGenerator::GetRandomNameFromList(Symbol x) {
    DataArray* pNameArray = GetNameList(x);
    MILO_ASSERT(pNameArray, 92);
    int iNameCount = pNameArray->Size();
    MILO_ASSERT(iNameCount > 0, 95);
    return pNameArray->Sym(RandomInt(0, iNameCount - 1));
}

BEGIN_HANDLERS(NameGenerator)
HANDLE_EXPR(get_random_name, GetRandomNameFromList(_msg->Sym(2)))
HANDLE_SUPERCLASS(Hmx::Object)
HANDLE_CHECK(110)
END_HANDLERS
