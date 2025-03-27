#ifndef NET_JSONUTILS_H
#define NET_JSONUTILS_H

#include "json-c/json.h"
#include "system/utl/Str.h"
#include <vector>

class JsonObject {
public:
    JsonObject();
    virtual ~JsonObject();

    enum JsonType {
        kType_Null = 0,
        kType_Boolean = 1,
        kType_Double = 2,
        kType_Int = 3,
        kType_Object = 4,
        kType_Array = 5,
        kType_String = 6
    };

    json_object *GetObject() { return mObject; }
    const char *GetObjectAsString() const;
    JsonType GetType() const;

    friend class JsonConverter;

protected:
    json_object *mObject;
};

class JsonArray : public JsonObject {
public:
    JsonArray();
    virtual ~JsonArray();

    void AddMember(JsonObject *);
    int GetSize() const;
};

class JsonString : public JsonObject {
public:
    JsonString(const char *);
    virtual ~JsonString();

    const char *GetValue() const;
};

class JsonInt : public JsonObject {
public:
    JsonInt(int);
    virtual ~JsonInt();

    int GetValue() const;
};

class JsonDouble : public JsonObject {
public:
    JsonDouble(double);
    virtual ~JsonDouble();

    double GetValue() const;
};

class JsonConverter : public JsonArray {
public:
    JsonConverter();
    virtual ~JsonConverter();

    std::vector<JsonObject *> objects;

    JsonArray *NewArray();
    JsonString *NewString(const char *value);
    JsonInt *NewInt(int value);
    JsonDouble *NewDouble(double value);

    JsonObject *LoadFromString(const String &str);
    JsonObject *GetElement(JsonArray *array, int index);

private:
    void PushObject(JsonObject *obj);
};

#endif
