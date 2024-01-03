#ifndef RB3_JSONOBJECT_HPP
#define RB3_JSONOBJECT_HPP
#include "json-c/json.h"

// this class is 0x8 big! according to fn_800A6D68
class JsonObject {
public:
    JsonObject(); // fn_800A6360
    virtual ~JsonObject(); // fn_800A6378

    json_object *json_object_struct;
    json_object *GetJsonObjectStruct(); // fn_8000DF3C
    const char *GetString(); // fn_800A63DC
    enum json_type Type(); // fn_800A63E4
};

class JsonArray : public JsonObject {
public:
    JsonArray(); // fn_800A63EC
    virtual ~JsonArray(); // fn_800A6430

    void Append(JsonObject *); // fn_800A64C4
    int Length(); // fn_800A6518
};

class JsonString : public JsonObject {
public:
    JsonString(const char *); // fn_800A6520
    virtual ~JsonString(); // fn_800A6574

    const char *GetString(); // fn_800A65CC
};

class JsonInt : public JsonObject {
public:
    JsonInt(int); // fn_800A65D4
    virtual ~JsonInt(); // fn_800A6628

    int GetInt(); // fn_800A6680
};

class JsonDouble : public JsonObject {
public:
    JsonDouble(double); // fn_800A6688
    virtual ~JsonDouble(); // fn_800A66DC

    double GetDouble(); // fn_800A6734
};

#endif
