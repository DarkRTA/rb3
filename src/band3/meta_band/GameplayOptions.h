#ifndef METABAND_GAMEPLAYOPTIONS_H
#define METABAND_GAMEPLAYOPTIONS_H

#include "obj/Object.h"
#include "meta/FixedSizeSaveable.h"
#include "types.h"

enum VocalStyle {
    kVocStyle0,
    kVocStyle1
};

class GameplayOptions : public virtual Hmx::Object, public FixedSizeSaveable {
    public:
    GameplayOptions();
    virtual ~GameplayOptions() {}
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    virtual DataNode Handle(DataArray*, bool);
    virtual void SetLefty(bool);
    virtual bool GetLefty() const { return mLefty; }
    virtual void SetVocalStyle(VocalStyle);
    virtual VocalStyle GetVocalStyle() const;
    virtual void SetVocalVolume(int, int);
    virtual int GetVocalVolume(int) const;

    static int SaveSize(int);

    int mVocalVolume;
    bool mLefty;
    VocalStyle mVocalStyle;
    u8 unk_0x18;
};

#endif // METABAND_GAMEPLAYOPTIONS_H