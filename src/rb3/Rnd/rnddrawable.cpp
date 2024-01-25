#include "rnddrawable.hpp"
#include "rb3/data.hpp"

RndDrawable::RndDrawable() : mShowing(mShowing | 0x80), mBoundSphere(), mDrawOrder(0.0f) {
    mBoundSphere.Zero();
}

extern char* PathName(const Hmx::Object*);

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);

void RndDrawable::SetType(Symbol s){
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

Symbol RndDrawable::StaticClassName() {
    static Symbol name("Draw");
    return name;
}
Symbol RndDrawable::ClassName() const {
    return StaticClassName();
}

