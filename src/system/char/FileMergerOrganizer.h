#pragma once
#include "obj/Object.h"
#include "utl/Loader.h"

class FileMergerOrganizer : public Hmx::Object, Loader::Callback {
public:
    FileMergerOrganizer();

    static void Init();
};