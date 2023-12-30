#include "data.hpp"
#include "makestring.hpp"
#include "beatmatchcontroller.hpp"

extern char *DataVarName(const DataNode *);
extern Symbol DataFuncName(DataFunc *);

const char *DataToString(const DataNode &dn) {
    switch (dn.GetType()) {
    case kDataInt:
        return MakeString<int>("%d", dn.Int(0));
    case kDataFloat:
        return MakeString<float>("%f", dn.Float(0));
    case kDataVariable:
        return MakeString<const char *>("%s", DataVarName(dn.Var(0)));
    case kDataFunc:
        return MakeString<Symbol>("%s", DataFuncName(dn.Func(0)));
    case kDataObject:
        if (dn.NotNull()) {
            return MakeString<const char *>("%s", dn.GetObj(0)->Name());
        } else {
            return MakeString("<null>");
        }
    case kDataSymbol:
        return dn.Sym(0).m_string;
    case kDataArray:
        return MakeString("<array>");
    case kDataCommand:
        return MakeString("<command>");
    case kDataString:
        return dn.Str(0);
    case kDataProperty:
        return MakeString("<property>");
    case kDataGlob:
        return MakeString("<glob>");
    default:
        return MakeString("unhandled");
    }
}

BeatMatchController::BeatMatchController(User* u, const DataArray* da, bool b){
    user = u;
    forceMercury = -1;
    unk24 = b;
    unk25 = false;
    unk28 = 0;
    unk2c = 0;
    slotsArray = da->FindArray("slots", true);
    leftySlotsArray = da->FindArray("lefty_slots", false);
    rightySlotsArray = da->FindArray("righty_slots", false);
    da->FindData("force_mercury", forceMercury, false);
}