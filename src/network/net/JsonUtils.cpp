#include "JsonUtils.h"
#include "json-c/printbuf.h"
#include "system/os/Debug.h"

JsonObject::JsonObject() {
    mObject = nullptr;
}

JsonObject::~JsonObject() {
    json_object_put(mObject);
}

const char *JsonObject::GetObjectAsString() const {
    return json_object_get_string(mObject);
}

enum json_type JsonObject::GetType() const {
    return json_object_get_type(mObject);
}

JsonArray::JsonArray() {
    mObject = json_object_new_array();
}

JsonArray::~JsonArray() {
    for (int len = json_object_array_length(mObject) - 1; len >= 0; len--) {
        json_object_put(json_object_array_get_idx(mObject, len));
    }
}

void JsonArray::AddMember(JsonObject *obj) {
    json_object_get(obj->GetObject());
    json_object_array_add(mObject, obj->GetObject());
}

// TODO: This is getting eliminated due to the inline,
// but it needs to be inline for JsonConverter::GetElement()
inline int JsonArray::GetSize() const {
    return json_object_array_length(mObject);
}

JsonString::JsonString(const char *s) {
    mObject = json_object_new_string(s);
}

JsonString::~JsonString() {
}

const char *JsonString::GetValue() const {
    return json_object_get_string(mObject);
}

JsonInt::JsonInt(int i) {
    mObject = json_object_new_int(i);
}

JsonInt::~JsonInt() {
}

int JsonInt::GetValue() const {
    return json_object_get_int(mObject);
}

JsonDouble::JsonDouble(double d) {
    mObject = json_object_new_double(d);
}

JsonDouble::~JsonDouble() {
}

double JsonDouble::GetValue() const {
    return json_object_get_double(mObject);
}

JsonConverter::JsonConverter() {
}

JsonConverter::~JsonConverter() {
    if (objects.size() != 0) {
        int count = objects.size() - 1;
        while (count >= 0) {
            JsonObject *o = objects[count];
            delete o;
            count--;
        }
    }
}

JsonArray *JsonConverter::NewArray() {
    JsonArray *jArray = new JsonArray();
    PushObject(jArray);
    return jArray;
}

JsonString *JsonConverter::NewString(const char *c) {
    JsonString *jStr = new JsonString(c);
    PushObject(jStr);
    return jStr;
}

JsonInt *JsonConverter::NewInt(int i) {
    JsonInt *jInt = new JsonInt(i);
    PushObject(jInt);
    return jInt;
}

JsonDouble *JsonConverter::NewDouble(double d) {
    JsonDouble *jDouble = new JsonDouble(d);
    PushObject(jDouble);
    return jDouble;
}

JsonObject *JsonConverter::LoadFromString(const String &str) {
    JsonObject *obj = new JsonObject();
    printbuf *pb = printbuf_new();
    if (pb == 0)
        return nullptr;

    printbuf_memappend(pb, str.c_str(), str.length());
    obj->mObject = json_tokener_parse(pb->buf);
    printbuf_free(pb);
    PushObject(obj);
    return obj;
}

JsonObject *JsonConverter::GetElement(JsonArray *inArray, int inIdx) {
    MILO_ASSERT(0 <= inIdx && inIdx <= inArray->GetSize(), 187);
    JsonObject *obj = new JsonObject();
    obj->mObject = json_object_array_get_idx(inArray->GetObject(), inIdx);
    PushObject(obj);
    return obj;
}

void JsonConverter::PushObject(JsonObject *obj) {
    json_object_get(obj->GetObject());
    objects.push_back(obj);
}
