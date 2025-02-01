#pragma once

#include "meta/FixedSizeSaveable.h"
#include "obj/Object.h"

class SavedSetlist : public FixedSizeSaveable, public virtual Hmx::Object {};

class LocalSavedSetlist : public SavedSetlist {
public:
    static int SaveSize(int);
};
