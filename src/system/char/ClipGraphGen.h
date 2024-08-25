#ifndef CHAR_CLIPGRAPHGENERATOR_H
#define CHAR_CLIPGRAPHGENERATOR_H
#include "obj/Object.h"
#include "char/ClipDistMap.h"

class ClipGraphGenerator : public Hmx::Object {
public:
    ClipGraphGenerator();
    virtual ~ClipGraphGenerator();
    virtual DataNode Handle(DataArray*, bool);
    
    ClipDistMap* GeneratePair(CharClip*, CharClip*, ClipDistMap::Node*, ClipDistMap::Node*);
    DataNode OnGenerateTransitions(DataArray*);

    DataArray* unk1c;
    ClipDistMap* mDmap; // 0x20
    CharClip* mClipA; // 0x24
    CharClip* mClipB; // 0x28
};

#endif
