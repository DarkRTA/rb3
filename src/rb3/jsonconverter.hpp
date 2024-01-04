#ifndef RB3_JSONCONVERTER_HPP
#define RB3_JSONCONVERTER_HPP
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

class Dummy {
public:
    ~Dummy();
    int lol;
};

class UnknownJsonConverterMember {
public:
    JsonObject **unk0;
    unsigned short unk4;
    unsigned short unk6;

    ~UnknownJsonConverterMember(); // fn_800A6790
    bool fn_800AFE60();
    unsigned short GetUnk4(); // fn_800A6BD0
    JsonObject **fn_800A6A24(); // fn_800A6A24
    void fn_800A6FA4(unsigned short); // fn_800A6FA4
    // void fn_801CEDFC(String*);
};

class JsonConverter : public JsonArray {
public:
    JsonConverter(); // fn_800A673C
    virtual ~JsonConverter(); // fn_800A6AF0

    UnknownJsonConverterMember mem;

    JsonArray *ToJsonArray(); // fn_800A6BD8
    JsonString *ToJsonString(const char *); // fn_800A6C34
    JsonInt *ToJsonInt(int); // fn_800A6C98
    JsonDouble *ToJsonDouble(double); // fn_800A6CFC
};

#endif
