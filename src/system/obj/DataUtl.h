#ifndef OBJ_DATAUTL_H
#define OBJ_DATAUTL_H
#include "obj/Data.h"
#include "utl/Loader.h"

extern std::map<Symbol, DataArray*> gMacroTable;
extern ObjectDir* gDataDir;
extern Hmx::Object* gDataThis;

Loader* DataFactory(const FilePath&, LoaderPos);
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
