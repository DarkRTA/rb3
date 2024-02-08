#include "common.hpp"
#include "symbol.hpp"
#include "message.hpp"
#include "hmx/object.hpp"

extern char *gNullStr;

// fn_800103CC
bool Symbol::IsNull() {
    return m_string == gNullStr;
}

extern DataArray *fn_8035CF9C(int, int, int);
// fn_8000E048
Message::Message(Symbol s) {
    DataArray *da = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(2);
    unk4 = da;

    unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
}

// fn_8001008C
Message::Message(Symbol s, const DataNode &dn) {
    DataArray *da = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(3);
    unk4 = da;

    unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
    unk4->GetNodeAtIndex(2)->operator=(dn);
}

// fn_8000FCA4
bool Symbol::operator==(const Symbol &sym) {
    return m_string == sym.m_string;
}

Symbol Hmx::Object::ClassName() const {
    return StaticClassName();
}

Symbol Hmx::Object::StaticClassName() {
    static Symbol name("Object");
    return name;
}

const char* Hmx::Object::Name() const {
    return name;
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);
extern char* PathName(const Hmx::Object*);

void Hmx::Object::SetType(Symbol s){
    static DataArray* types = SystemConfig(StaticClassName(), "types", "objects");
    if(s.IsNull()){
        SetTypeDef(nullptr);
    }
    else {
        DataArray* found = types->FindArray(s, false);
        if(found){
            SetTypeDef(found);
        }
        else {
            PathName(this);
            ClassName();
            SetTypeDef(nullptr);
        }
    }
}