#ifndef NET_JSONUTILS_H
#define NET_JSONUTILS_H

#include "json-c/json.h"

class JsonObject {
public:
    JsonObject();
    virtual ~JsonObject();

    json_object *json_object_struct;
    json_object *GetJsonObjectStruct();
    const char *GetString();
    enum json_type Type();
};

class JsonArray : public JsonObject {
public:
    JsonArray();
    virtual ~JsonArray();

    void Append(JsonObject *);
    int Length();
};

class JsonString : public JsonObject {
public:
    JsonString(const char *);
    virtual ~JsonString();

    const char *GetString();
};

class JsonInt : public JsonObject {
public:
    JsonInt(int);
    virtual ~JsonInt();

    int GetInt();
};

class JsonDouble : public JsonObject {
public:
    JsonDouble(double);
    virtual ~JsonDouble();

    double GetDouble();
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

    ~UnknownJsonConverterMember();
    bool fn_800AFE60();
    unsigned short GetUnk4();
    JsonObject **fn_800A6A24();
    void fn_800A6FA4(unsigned short);

};

class JsonConverter : public JsonArray {
public:
    JsonConverter();
    virtual ~JsonConverter();

    UnknownJsonConverterMember mem;

    JsonArray *ToJsonArray();
    JsonString *ToJsonString(const char *);
    JsonInt *ToJsonInt(int);
    JsonDouble *ToJsonDouble(double);
};

#endif
