#pragma once
#include "obj/Object.h"

class MusicLibraryNetSetlists : public Hmx::Object {
public:
    MusicLibraryNetSetlists();
    virtual ~MusicLibraryNetSetlists() {}
    virtual DataNode Handle(DataArray *, bool);

    void Poll();
    void CleanUp();
};