#pragma once

#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "ui/UIPanel.h"

class FadePanel : public UIPanel {
public:
    FadePanel();
    virtual ~FadePanel(){}
    OBJ_CLASSNAME(FadePanel)
    OBJ_SET_TYPE(FadePanel)
    virtual DataNode Handle(DataArray*, bool);

    virtual void Unload();
    virtual void Enter();
    virtual void Poll();
    virtual void Draw();

    void StartFade(float, const Hmx::Color& color, bool fade_synth, bool fade_out);
    DataNode OnStartFade(DataArray*);

    u8 unk_0x38;
    Timer mTimer; // 0x40
    float mVolume; // 0x70
    Hmx::Color mColor; // 0x74
    float unk_0x84;

    /** Whether this panel should also fade audio. */
    bool mFadeSynth; // 0x88

    /** The original master volume pre-fade. */
    float mSavedVolume; // 0x8C
    bool mFadeOut; // 0x90
};