#include "data.hpp"
#include "symbol.hpp"

extern "C" void DataRegisterFunc(Symbol, DataNode (*)(DataArray*));

// fn_80320470
extern DataNode DataReplaceObject(DataArray*);
// fn_8032056C
extern DataNode DataNextName(DataArray*);
// fn_8031B6C0
extern DataNode DataPrintf(DataArray*);
// fn_8031B62C
extern DataNode DataSprintf(DataArray*);
// fn_8031B7DC
extern DataNode DataSprint(DataArray*);
// fn_8031B504
// extern DataNode DataFuncObj::New(DataArray*);
// fn_8031DC40
extern DataNode DataGetElem(DataArray*);
// fn_8031DCA4
extern DataNode DataGetLastElem(DataArray*);
// fn_8031DA1C
extern DataNode DataForEach(DataArray*);
// fn_8031DB20
extern DataNode DataForEachInt(DataArray*);
// fn_8031CA14
extern DataNode DataMin(DataArray*);
// fn_8031CAF0
extern DataNode DataMax(DataArray*);
// fn_8031CBCC
extern DataNode DataAbs(DataArray*);
// fn_8031CC5C
extern DataNode DataAdd(DataArray*);
// fn_8031CD70
extern DataNode DataAddEq(DataArray*);
// fn_8031CDF4
extern DataNode DataSub(DataArray*);
// fn_8031D0FC
extern DataNode DataSubEq(DataArray*);

// fn_80320CDC
void DataInitFuncs(){
    DataRegisterFunc(Symbol("replace_object"), DataReplaceObject);
    DataRegisterFunc(Symbol("next_name"), DataNextName);
    DataRegisterFunc(Symbol("printf"), DataPrintf);
    DataRegisterFunc(Symbol("sprintf"), DataSprintf);
    DataRegisterFunc(Symbol("sprint"), DataSprint);
    // DataRegisterFunc(Symbol("func"), DataFuncObj::New);
    DataRegisterFunc(Symbol("elem"), DataGetElem);
    DataRegisterFunc(Symbol("last_elem"), DataGetLastElem);
    DataRegisterFunc(Symbol("foreach"), DataForEach);
    DataRegisterFunc(Symbol("foreach_int"), DataForEachInt);
    DataRegisterFunc(Symbol("min"), DataMin);
    DataRegisterFunc(Symbol("max"), DataMax);
    DataRegisterFunc(Symbol("abs"), DataAbs);
    DataRegisterFunc(Symbol("+"), DataAdd);
    DataRegisterFunc(Symbol("+="), DataAddEq);
    DataRegisterFunc(Symbol("-"), DataSub);
    DataRegisterFunc(Symbol("-="), DataSubEq);
}