#include "NameGenerator.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/Symbols3.h"
#include "math/Rand.h"

NameGenerator *TheNameGenerator = NULL;

NameGenerator::NameGenerator(DataArray* x) {
    MILO_ASSERT(!TheNameGenerator, 19);
    TheNameGenerator = this;
    SetName("name_generator", ObjectDir::Main());
    Init(x);
}

NameGenerator::~NameGenerator() {
    TheNameGenerator = NULL;
    Cleanup();
}

void NameGenerator::Cleanup() {
    m_mapNameLists.clear();
}

void NameGenerator::Init(DataArray* x) { ConfigureNameData(x); }

void NameGenerator::ConfigureNameData(DataArray* Root) {
    MILO_ASSERT(m_mapNameLists.empty(), 48);

    for (int i = 1; i < Root->Size(); i++) {
        DataArray* i_pNameArray = Root->Array(i);
        MILO_ASSERT(i_pNameArray, 55);

        Symbol ListName = i_pNameArray->Sym(0);
        bool List = GetNameList(ListName);
        if (List != false) {
            MILO_WARN("Name Generator found duplicate name list: %s\n", ListName.mStr);
            continue;
        }

        m_mapNameLists[ListName] = i_pNameArray;
    }
}

DataArray *NameGenerator::GetNameList(Symbol sym) const {
    std::map<Symbol, DataArray *>::const_iterator NameList = m_mapNameLists.find(sym);
    if (NameList != m_mapNameLists.end()) {
        return NameList->second;
    }

    return NULL;
}

Symbol NameGenerator::GetRandomNameFromList(Symbol x) {
    DataArray* pNameArray = GetNameList(x);
    MILO_ASSERT(pNameArray, 92);

    int iNameCount = pNameArray->mSize - 1;
    MILO_ASSERT(iNameCount > 0, 95);

    int index = RandomInt(0, iNameCount);
    return pNameArray->Sym(index + 1);
}

BEGIN_HANDLERS(NameGenerator)
    HANDLE_EXPR(get_random_name, GetRandomNameFromList(_msg->Sym(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(110)
END_HANDLERS
