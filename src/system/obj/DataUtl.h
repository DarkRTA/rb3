/**
 * @file DataUtl.h
 * @brief DataNode/DataArray helper functions.
 */

#pragma once
#include "obj/Data.h"
#include "utl/Loader.h"
#include <map>
#include "obj/Dir.h"

extern std::map<Symbol, DataArray *> gMacroTable;

/** The directory gDataThis is stored in. */
extern class ObjectDir *gDataDir;

/** The Hmx::Object represented by the `$this` variable. */
extern Hmx::Object *gDataThis;

Loader *DataFactory(const FilePath &, LoaderPos);
void DataInit();
void DataTerminate();
void DataMacroWarning(bool);

/** Sets the macro `macro_name` to the value `macro_val`. */
void DataSetMacro(Symbol macro_name, DataArray *macro_val);

/** Returns the value of a Data macro. */
DataArray *DataGetMacro(Symbol macro_name);

/** Returns the name of a Data macro by its integer value. */
Symbol DataGetMacroByInt(int macro_val, const char *prefix);

/** Sets gDataThis to `new_this` and returns the old value. */
Hmx::Object *DataSetThis(Hmx::Object *new_this);

/** Returns gDataThis. */
Hmx::Object *DataThis();
void DataMergeTags(DataArray *, DataArray *);
void DataReplaceTags(DataArray *, DataArray *);
void DataPushVar(DataNode *);
void DataPopVar();

void DataAppendStackTrace(char *msg);
