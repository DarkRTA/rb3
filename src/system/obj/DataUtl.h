#ifndef OBJ_DATAUTL_H
#define OBJ_DATAUTL_H
#include "obj/Data.h"

void DataInit();
void DataTerminate();
void DataMacroWarning(bool);
void DataSetMacro(Symbol, DataArray*);
DataArray* DataGetMacro(Symbol);
Symbol DataGetMacroByInt(int, const char*);
Hmx::Object* DataSetThis(Hmx::Object*);
Hmx::Object* DataThis();
void DataMergeTags(DataArray*, DataArray*);
void DataReplaceTags(DataArray*, DataArray*);
void DataPushVar(DataNode*);
void DataPopVar();

#endif
