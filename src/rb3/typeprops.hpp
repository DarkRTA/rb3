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

    void ClearAll();
    void ReleaseObjects();
    void RemoveArrayValue(Symbol, int, DataArray*);
    DataNode* KeyValue(Symbol, bool);
};

#endif
