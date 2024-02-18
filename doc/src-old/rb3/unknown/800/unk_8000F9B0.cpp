#include "obj/Object.h"
#include "utl/Message.h"
#include "utl/Symbol.h"

#include "common.hpp"

extern char *gNullStr;

// fn_800103CC
bool Symbol::IsNull() {
    return m_string == gNullStr;
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
