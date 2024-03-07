#include "utl/Option.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"

static DataNode DataOptionStr(DataArray* arr){
    const char* str = OptionStr(arr->Str(1), 0);
    if(str){
        *arr->Var(2) = DataNode(str);
        return DataNode(1);
    }
    else return DataNode(0);
}

static DataNode DataOptionSym(DataArray* arr){
    const char* str = OptionStr(arr->Str(1), 0);
    Symbol s(str);
    if(s.IsNull()) return DataNode(0);
    else {
        *arr->Var(2) = DataNode(s);
        return DataNode(1);
    }
}

static DataNode DataOptionBool(DataArray* arr){
    return DataNode(OptionBool(arr->Str(1), false));
}

void OptionInit() {
    DataRegisterFunc("option_bool", DataOptionBool);
    DataRegisterFunc("option_str", DataOptionStr);
    DataRegisterFunc("option_sym", DataOptionSym);
}
