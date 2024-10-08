#pragma once
#include "meta_band/OvershellPanel.h"
#include "game/Defines.h"
#include "ui/UIListProvider.h"

class BandUser;

class OvershellPartSelectProvider : public UIListProvider, public Hmx::Object {
public:
    class PartSelectEntry {
    public:
        Symbol unk0;
        TrackType unk4;
        char unk8;
    };

    OvershellPartSelectProvider(OvershellPanel*);
    virtual ~OvershellPartSelectProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;

    void Clear();
    void Reload(ControllerType, BandUser*);
    void AddPart(Symbol, TrackType, const char*);

    ControllerType mControllerType; // 0x20
    std::vector<PartSelectEntry> mPartSelections; // 0x24
    BandUser* mUser; // 0x2c
    OvershellPanel* mOvershell; // 0x30
};