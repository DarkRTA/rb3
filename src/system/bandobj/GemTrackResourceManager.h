#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"

class GemTrackResourceManager : public Hmx::Object {
public:
    GemTrackResourceManager(ObjectDir*);
    virtual ~GemTrackResourceManager();

    void InitSmasherPlates();

    ObjPtr<ObjectDir, ObjectDir> unk1c; // 0x1c
    std::vector<int> unk28; // 0x28
};