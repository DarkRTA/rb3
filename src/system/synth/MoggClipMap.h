#ifndef SYNTH_MOGGCLIPMAP_H
#define SYNTH_MOGGCLIPMAP_H
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "synth/MoggClip.h"

class MoggClipMap : public Hmx::Object {
public:
    MoggClipMap(Hmx::Object*);
    virtual ~MoggClipMap(){}
    void myLoad(BinStream&);

    static int sRev;

    ObjPtr<MoggClip, ObjectDir> mClipPtr;
    float unk28; // something to do with panning
    float unk2c; // something else to do with panning
    float unk30; // volume?
    bool unk34; // dual channel?
};

BinStream& operator>>(BinStream&, MoggClipMap&);

#endif
