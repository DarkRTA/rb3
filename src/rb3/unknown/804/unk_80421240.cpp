#include "data.hpp"
#include "makestring.hpp"

extern char* DataVarName(const DataNode*);
extern Symbol DataFuncName(DataFunc*);

const char* DataToString(const DataNode& dn){
    switch(dn.GetType()){
        case kDataInt:
            return MakeString<int>("%d", dn.Int(0));
        case kDataFloat:
            return MakeString<float>("%f", dn.Float(0));
        case kDataVariable:
            return MakeString<const char*>("%s", DataVarName(dn.Var(0)));
        case kDataFunc:
            return MakeString<Symbol>("%s", DataFuncName(dn.Func(0)));
        case kDataObject:
            if(dn.NotNull()){
                return MakeString<const char*>("%s", dn.GetObj(0)->Name());
            }
            else {
                return MakeString("<null>");
            }
        case kDataSymbol:
            return dn.Sym(0);
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