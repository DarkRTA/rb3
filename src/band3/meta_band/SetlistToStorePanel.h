#pragma once
#include "obj/Data.h"
#include "ui/UIPanel.h"
#include "utl/NetLoader.h"

class SetlistToStorePanel : public UIPanel {
public:
    SetlistToStorePanel() {}
    OBJ_CLASSNAME(SetlistToStorePanel);
    OBJ_SET_TYPE(SetlistToStorePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~SetlistToStorePanel() {}
    virtual void Enter();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();

    void GetSongsFromMusicLibrary();

    std::vector<DataNetLoader *> mLoaders; // 0x38
    DataArray *mAllMetadata; // 0x40
    std::vector<int> mSongs; // 0x44
    std::vector<String> mSongNames; // 0x4c
    int unk54; // 0x54
    Timer unk58; // 0x58
};