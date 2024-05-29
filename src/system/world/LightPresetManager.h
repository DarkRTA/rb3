#ifndef WORLD_LIGHTPRESETMANAGER_H
#define WORLD_LIGHTPRESETMANAGER_H
#include "obj/Data.h"
// #include <hash_map>

class WorldDir;

class LightPresetManager {
public:
    LightPresetManager(WorldDir*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~LightPresetManager();

    bool unk4;
    // std::hash_map<int, int> unk8;
    int unk8, unkc, unk10;
    int unk14;
    int unk18;
    Symbol unk1c;
    WorldDir* mParent; // 0x20
    int unk24;
    int unk28;
    int unk2c;
    float unk30;
    float unk34;
    float unk38;
    bool unk3c;
    float unk40;
    float unk44;
    int unk48;
    bool unk4c;
};

#endif
