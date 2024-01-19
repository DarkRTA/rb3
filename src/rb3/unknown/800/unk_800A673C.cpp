#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "string.h"
#include "jsonconverter.hpp"
#include "jsonconverter.hpp"
#include "binstream.hpp"
#include "bufstream.hpp"
#include "matchmakingsettings.hpp"
#include "symbol.hpp"
#include "memstream.hpp"
#include "json-c/printbuf.h"
#include "data.hpp"

// fn_800A8410
int DataArray::GetIntAtIndex(int i) const {
    DataNode *dn = GetNodeAtIndex(i);
    return dn->Int(this);
}

// fn_800A6E18
// probably inline
unsigned int String::length() const {
    return strlen(text);
}

// fn_800A6BD0

unsigned short UnknownJsonConverterMember::GetUnk4() {
    return unk4;
}


extern "C" UnknownJsonConverterMember *fn_800A6A38(UnknownJsonConverterMember *, Dummy *);

// fn_800A673C
JsonConverter::JsonConverter() {
    Dummy i;
    fn_800A6A38(&mem, &i);
}

extern "C" UnknownJsonConverterMember *fn_800A67E8(UnknownJsonConverterMember *, int);

// fn_800A6790
UnknownJsonConverterMember::~UnknownJsonConverterMember() {
    fn_800A67E8(this, -1);
}

extern "C" UnknownJsonConverterMember *fn_800A6868(UnknownJsonConverterMember *, int);

// fn_800A67E8
UnknownJsonConverterMember *fn_800A67E8(UnknownJsonConverterMember *mem, int i) {
    fn_800A6868(mem, 0);
    return mem;
}

extern "C" UnknownJsonConverterMember *fn_800A6868(UnknownJsonConverterMember *, int);
extern "C" void fn_800A6940(UnknownJsonConverterMember *, JsonObject **, unsigned short);
extern "C" UnknownJsonConverterMember *fn_800A68E8(UnknownJsonConverterMember *, int);

// fn_800A6868
UnknownJsonConverterMember *fn_800A6868(UnknownJsonConverterMember *mem, int i) {
    if (mem->unk0 != 0) {
        fn_800A6940(mem, mem->unk0, mem->unk6);
    }
    mem->unk0 = nullptr;
    mem->unk4 = 0;
    mem->unk6 = 0;
    fn_800A68E8(mem, -1);
    return mem;
}

extern "C" UnknownJsonConverterMember *fn_800A6A78(UnknownJsonConverterMember *, Dummy *);

// fn_800A6A38
UnknownJsonConverterMember *fn_800A6A38(UnknownJsonConverterMember *mem, Dummy *d) {
    Dummy j;
    fn_800A6A78(mem, &j);
    return mem;
}

extern "C" UnknownJsonConverterMember *fn_800A6AA8(UnknownJsonConverterMember *, Dummy *);

// fn_800A6A78
UnknownJsonConverterMember *fn_800A6A78(UnknownJsonConverterMember *mem, Dummy *d) {
    fn_800A6AA8(mem, d);
    return mem;
}

extern "C" void fn_800A6AE8(UnknownJsonConverterMember *, Dummy *, JsonObject **);

// fn_800A6AA8
UnknownJsonConverterMember *fn_800A6AA8(UnknownJsonConverterMember *mem, Dummy *d) {
    fn_800A6AE8(mem, d, nullptr);
    mem->unk4 = 0;
    mem->unk6 = 0;
    return mem;
}

// fn_800A6AE8
void fn_800A6AE8(UnknownJsonConverterMember *mem, Dummy *d, JsonObject **j) {
    mem->unk0 = j;
}

extern "C" JsonObject **fn_800A6BBC(UnknownJsonConverterMember *, int);

// fn_800A6AF0
JsonConverter::~JsonConverter() {
    short var_r31;
    JsonObject **o;
    if (mem.GetUnk4() != 0) {
        var_r31 = mem.GetUnk4() - 1;
        while (var_r31 >= 0) {
            o = fn_800A6BBC(&mem, var_r31);
            if (o) {
            }
            var_r31--;
        }
    }
}

extern "C" JsonObject **fn_800A6BC0(UnknownJsonConverterMember *, int);

// fn_800A6BBC
JsonObject **fn_800A6BBC(UnknownJsonConverterMember *mem, int i) {
    return fn_800A6BC0(mem, i);
}

// fn_800A6BC0
JsonObject **fn_800A6BC0(UnknownJsonConverterMember *mem, int i) {
    return &mem->unk0[i];
}

// ---------------------------------------------------------------

extern "C" void fn_800A6EA8(JsonConverter *, JsonObject *);

// fn_800A6BD8
JsonArray *JsonConverter::ToJsonArray() {
    JsonArray *j = new JsonArray();
    fn_800A6EA8(this, j);
    return j;
}

// fn_800A6C34
JsonString *JsonConverter::ToJsonString(const char *c) {
    JsonString *j = new JsonString(c);
    fn_800A6EA8(this, j);
    return j;
}

// fn_800A6C98
JsonInt *JsonConverter::ToJsonInt(int i) {
    JsonInt *j = new JsonInt(i);
    fn_800A6EA8(this, j);
    return j;
}

// fn_800A6CFC
JsonDouble *JsonConverter::ToJsonDouble(double d) {
    JsonDouble *j = new JsonDouble(d);
    fn_800A6EA8(this, j);
    return j;
}

extern "C" JsonObject *fn_800A6D68(JsonConverter *, String);

// fn_800A6D68
JsonObject *fn_800A6D68(JsonConverter *jc, String str) {
    JsonObject *obj = new JsonObject();
    printbuf *pb = printbuf_new();
    if (pb == 0)
        return nullptr;
    printbuf_memappend(pb, str.c_str(), str.length());
    obj->json_object_struct = json_tokener_parse(pb->buf);
    printbuf_free(pb);
    fn_800A6EA8(jc, obj);
    return obj;
}

extern "C" JsonObject *fn_800A6E20(JsonConverter *, JsonArray *, int);

// fn_800A6E20 - GetJsonObjectAtJsonArrayIndex
JsonObject *fn_800A6E20(JsonConverter *jc, JsonArray *ja, int i) {
    if (i >= 0)
        ja->Length();
    JsonObject *obj = new JsonObject();
    obj->json_object_struct = json_object_array_get_idx(ja->GetJsonObjectStruct(), i);
    fn_800A6EA8(jc, obj);
    return obj;
}

extern "C" void fn_800A6EF4(UnknownJsonConverterMember *, JsonObject *);

// fn_800A6EA8
void fn_800A6EA8(JsonConverter *jc, JsonObject *obj) {
    json_object_get(obj->GetJsonObjectStruct());
    fn_800A6EF4(&jc->mem, obj);
}

extern "C" void fn_800A6F1C(UnknownJsonConverterMember *, JsonObject **);


// fn_800A6A24
JsonObject **UnknownJsonConverterMember::fn_800A6A24() {
    return &unk0[unk4];
}


// fn_800A6EF4
void fn_800A6EF4(UnknownJsonConverterMember *mem, JsonObject *obj) {
    JsonObject *j = obj;
    fn_800A6F1C(mem, &j);
}

extern "C" void fn_800A6FB4(JsonObject **, JsonObject **);
extern void
fn_800A6FC8(UnknownJsonConverterMember *, JsonObject **, JsonObject **, char *, int, int);

// fn_800A6F1C
void fn_800A6F1C(UnknownJsonConverterMember *mem, JsonObject **obj) {
    char c;
    if (mem->unk4 != mem->unk6) {
        JsonObject **x = mem->fn_800A6A24();
        fn_800A6FB4(x, obj);
        mem->fn_800A6FA4(1);
        return;
    }
    JsonObject **tmp = mem->fn_800A6A24();
    c = 0;
    fn_800A6FC8(mem, tmp, obj, &c, 1, 1);
}

// fn_800A6FA4
void UnknownJsonConverterMember::fn_800A6FA4(unsigned short i) {
    unk4 += i;
}

// fn_800A6FB4
void fn_800A6FB4(JsonObject **j1, JsonObject **j2) {
    if (j1 == nullptr)
        return;
    else
        *j1 = *j2;
}

// both UnknownJsonConverterMember methods

extern "C" void fn_800A7108(UnknownJsonConverterMember *, unsigned short);

// fn_800A7108
void fn_800A7108(UnknownJsonConverterMember *mem, unsigned short us) {
    mem->unk4 = us;
}

extern "C" void fn_800A7100(UnknownJsonConverterMember *, unsigned short);

// fn_800A7100
void fn_800A7100(UnknownJsonConverterMember *mem, unsigned short us) {
    mem->unk6 = us;
}

// fn_800A71B0

// ---------------------------------------------------------------

// fn_800A7638
BinStream &BinStream::operator<<(unsigned int ui) {
    WriteEndian(&ui, 4);
    return *this;
}

// fn_800A77B4
BinStream &BinStream::operator>>(unsigned int &ui) {
    ReadEndian(&ui, 4);
    return *this;
}

// fn_800A9C70
int BufStream::Tell() {
    return fpos;
}


// fn_800A7730
BinStream &BinStream::operator>>(unsigned char &c) {
    Read(&c, 1);
    return *this;
}


// fn_800A7764
BinStream &BinStream::operator>>(bool &b) {
    unsigned char c;
    *this >> c;
    b = (c != 0);
    return *this;
}

// fn_800A7844
MatchmakingSettings::~MatchmakingSettings() {
}

// fn_800A71BC
void MatchmakingSettings::SetMode(Symbol s, int i) {
    unk4 = s;
    unk8 = i;
}

// fn_800A7DE0
void MatchmakingSettings::SetRanked(bool b) {
    unkc = b;
}

// fn_800A71FC
void MatchmakingSettings::AddCustomSetting(int i, int j) {
}

// fn_800A75FC
BinStream &BinStream::operator<<(char c) {
    Write(&c, 1);
    return *this;
}

// fn_800A7DE8
bool MemStream::Fail() {
    return failed;
}

extern char *lbl_808540E0; // RB2 marks this as gNullStr

// fn_800A7C40
Symbol::Symbol() {
    m_string = lbl_808540E0;
}

// fn_800A7B30
MatchmakingSettings::MatchmakingSettings() {
}
