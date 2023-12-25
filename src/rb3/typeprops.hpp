#ifndef RB3_TYPEPROPS_HPP
#define RB3_TYPEPROPS_HPP
#include "binstream.hpp"
#include "types.h"
#include "symbol.hpp"
#include "hmx/object.hpp"

// forward declarations
class DataNode;
class DataArray;
class Hmx::Object;

class TypeProps {
public:
    DataArray *data;

    TypeProps();
    ~TypeProps();

    void Save(BinStream &, Hmx::Object *);
    void Load(BinStream &, u16, Hmx::Object *);

    void ClearAll(ObjRef*);
    void ReleaseObjects(ObjRef*);
    void InsertArrayValue(Symbol, int, const DataNode&, DataArray*, ObjRef*);
    void SetArrayValue(Symbol, int, const DataNode&, DataArray*, ObjRef*);
    void RemoveArrayValue(Symbol, int, DataArray*, ObjRef*);
    DataNode* KeyValue(Symbol, bool);
    DataArray* GetArray(Symbol, DataArray*, ObjRef*);
    void SetKeyValue(Symbol, const DataNode&, bool, ObjRef*);
};

#endif
