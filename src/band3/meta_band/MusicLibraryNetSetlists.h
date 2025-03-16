#pragma once
#include "obj/Object.h"
#include "rndobj/Tex.h"

class MusicLibraryNetSetlists : public Hmx::Object {
public:
    class SetlistArtRecord {};
    MusicLibraryNetSetlists();
    virtual ~MusicLibraryNetSetlists() {}
    virtual DataNode Handle(DataArray *, bool);

    void Poll();
    void CleanUp();
    void RefreshSetlists();
    bool IsSetlistArtReady(Symbol) const;
    RndTex *GetSetlistArt(Symbol) const;
    void RefreshSetlistArt();
};