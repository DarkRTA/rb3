#ifndef CHAR_CLIPDISTMAP_H
#define CHAR_CLIPDISTMAP_H
#include "char/CharClip.h"
#include <vector>

class ClipDistMap {
public:
    class Node {
    public:
    };

    ClipDistMap(CharClip*, CharClip*, float, float, int, const DataArray*);
    void FindDists(float, DataArray*);
    void FindNodes(float, float, float);
    void SetNodes(Node*, Node*);

    CharClip* unk0;
    CharClip* unk4;
    DataArray* unk8;
    int unkc;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    float unk20;
    float unk24;
    int unk28;
    int unk2c;
    float unk30;
    float unk34;
    int unk38;
    int unk3c;
    int unk40;
    std::vector<int> unk44;
};

#endif