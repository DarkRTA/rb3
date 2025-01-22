#pragma once
#include "obj/Object.h"
#include "utl/Loader.h"
#include "char/FileMerger.h"

class FileMergerOrganizer : public Hmx::Object, Loader::Callback {
public:
    FileMergerOrganizer();

    void AddFileMerger(FileMerger*);

    static void Init();
};

bool FileMergerSort(const FileMerger::Merger*, const FileMerger::Merger*);

extern FileMergerOrganizer* TheFileMergerOrganizer;