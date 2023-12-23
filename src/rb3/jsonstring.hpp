#ifndef RB3_JSONSTRING_HPP
#define RB3_JSONSTRING_HPP
#include "jsonobject.hpp"

class JsonString : public JsonObject {
public:
    JsonString(const char *); // fn_800A6520
    virtual ~JsonString(); // fn_800A6574

    const char *GetString(); // fn_800A65CC
};

#endif
