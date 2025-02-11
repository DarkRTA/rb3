#pragma once
#include "obj/Object.h"
#include "meta/FixedSizeSaveable.h"
#include "bandtrack/VocalStyle.h"
#include "types.h"

class GameplayOptions : public virtual Hmx::Object, public FixedSizeSaveable {
public:
    GameplayOptions();
    virtual ~GameplayOptions() {}
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);
    virtual DataNode Handle(DataArray *, bool);
    virtual void SetLefty(bool);
    virtual bool GetLefty() const { return mLefty; }
    virtual void SetVocalStyle(VocalStyle);
    virtual VocalStyle GetVocalStyle() const { return mVocalStyle; }
    virtual void SetVocalVolume(int, int);
    virtual int GetVocalVolume(int) const;

    static int SaveSize(int);

    int mVocalVolume;
    bool mLefty;
    VocalStyle mVocalStyle;
    mutable u8 mDirty;
};
