#include "char/CharWeightable.h"

CharWeightable::CharWeightable() : mWeight(1.0f), mWeightOwner(this, this) {

}

SAVE_OBJ(CharWeightable, 0x21)

BEGIN_HANDLERS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x43)
END_HANDLERS
