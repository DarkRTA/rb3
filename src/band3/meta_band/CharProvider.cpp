#include "meta_band/CharProvider.h"

CharProvider::CharProvider(LocalBandUser* u, bool b1, bool b2) : unk20(u), unk2c(b1), unk2d(b2), unk30(-1) {

}

CharProvider::~CharProvider(){
    Clear();
}

void CharProvider::Clear(){
    mCharacters.clear();
}

Symbol CharProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x102);
    return mCharacters[data].unk8;
}

bool CharProvider::IsActive(int data) const {
    if(mCharacters.empty()) return false;
    else {
        MILO_ASSERT(( 0) <= (data) && (data) < ( mCharacters.size()), 0x117);
        return mCharacters[data].unk0;
    }
}

bool CharProvider::IsIndexNewChar(int idx){
    if(mCharacters.empty()) return false;
    else {
        MILO_ASSERT(( 0) <= (idx) && (idx) < ( mCharacters.size()), 0x134);
        return mCharacters[idx].unk0 == 1;
    }
}

BEGIN_HANDLERS(CharProvider)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x176)
END_HANDLERS