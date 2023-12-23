#ifndef RB3_TYPEPROPS_HPP
#define RB3_TYPEPROPS_HPP
#include "binstream.hpp"
#include "types.h"
#include "data.hpp"

namespace Hmx {
    class Object;
}
class DataArray;

class TypeProps {
public:
    DataArray *data;

    void Save(BinStream &, Hmx::Object *);
    void Load(BinStream &, u16, Hmx::Object *);
};

#endif
