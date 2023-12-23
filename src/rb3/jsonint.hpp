#ifndef RB3_JSONINT_HPP
#define RB3_JSONINT_HPP
#include "jsonobject.hpp"

class JsonInt : public JsonObject {
public:
    JsonInt(int); // fn_800A65D4
    virtual ~JsonInt(); // fn_800A6628

    int GetInt(); // fn_800A6680
};

#endif
