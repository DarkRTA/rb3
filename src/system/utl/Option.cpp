#include "utl/Option.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/System.h"
#include "os/Debug.h"

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

static char** FindOption(const char* option){
    std::vector<char*>::iterator it;
    for(it = TheSystemArgs.begin(); it != TheSystemArgs.end(); it++){
        if(**it == '-' && (strcmp(*it + 1, option) == 0)) break;
    }
    return it;
}

bool OptionBool(const char* option, bool def){
    char** opt = FindOption(option);
    if(opt == TheSystemArgs.end()) return def;
    else {
        TheSystemArgs.erase(opt);
        return !def;
    }
}

const char* OptionStr(const char* option, const char* def){
    char** i = FindOption(option);
    if(i == TheSystemArgs.end()) return def;
    else {
        char** erased = TheSystemArgs.erase(i);
        MILO_ASSERT(i != TheSystemArgs.end(), 0x5C);
        def = *i;
        TheSystemArgs.erase(erased);
        return def;
    }
}

static char* dummy1 = "%llx";
static char* dummy2 = "Unprocessed option %s\n";
