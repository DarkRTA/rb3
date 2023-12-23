#ifndef RB3_JSONARRAY_HPP
#define RB3_JSONARRAY_HPP
#include "jsonobject.hpp"

class JsonArray : public JsonObject {
public:
    JsonArray(); // fn_800A63EC
    virtual ~JsonArray(); // fn_800A6430

    void Append(JsonObject *); // fn_800A64C4
    int Length(); // fn_800A6518
};

#endif
