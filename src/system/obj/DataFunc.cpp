#include "obj/DataFunc.h"
#include "math/Random.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/MakeString.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include <map>

std::map<Symbol, DataFunc*> gDataFuncs;

void DataRegisterFunc(Symbol s, DataFunc* func){
    gDataFuncs[s] = func;
}
