#pragma once
#include <revolution/OS.h>
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"
#include "rndobj/ColorXfm.h"
#include "rndobj/DOFProc.h"
#include "rndobj/Draw.h"
#include "math/Vec.h"

class ProcCounter {
public:
    ProcCounter();
    void SetProcAndLock(bool);
    void SetEvenOddDisabled(bool);
    int ProcCommands();

    bool mProcAndLock;
    int mCount;
    int mSwitch;
    int mOdd;
    int mFPS;
    bool mEvenOddDisabled;
    bool mTriFrameRendering;
};

class PostProcessor {
public:
    PostProcessor() {}
    virtual ~PostProcessor() {}
    virtual void BeginWorld() {}
    virtual void EndWorld() {}
    virtual void DoPost() {}
    virtual void OnGPHangRecover() {
        OSReport("Base PostProcessor::OnGPHangRecover called.\n");
    }
    virtual float Priority() { return 1.0f; }
};

/** "A PostProc drives post-processing effects." */
class RndPostProc : public Hmx::Object, public PostProcessor {
public:
    RndPostProc();
    virtual ~RndPostProc();
    OBJ_CLASSNAME(PostProc);
    OBJ_SET_TYPE(PostProc);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    virtual void Select();
    virtual void Unselect();
    virtual void EndWorld() {}
    virtual void DoPost();
    virtual void OnGPHangRecover() {}
    virtual void SetPriority(float f) { mPriority = f; }
    virtual float Priority() { return mPriority; }
    virtual void QueueMotionBlurObject(RndDrawable *) {}
    virtual void SetBloomColor() {}
    virtual void OnSelect();
    virtual void OnUnselect();

    float BloomIntensity() const;
    bool DoGradientMap() const;
    bool DoRefraction() const;
    bool DoVignette() const;
    bool HallOfTime() const;
    void UpdateTimeDelta();
    void UpdateColorModulation();
    void UpdateBlendPrevious();
    void Interp(const RndPostProc *, const RndPostProc *, float);
    void LoadRev(BinStream &, int);
    DataNode OnAllowedNormalMap(const DataArray *);
    bool BlendPrevious() const;
    float EmulateFPS() const { return mEmulateFPS; }

    static void Reset();
    static RndPostProc *sCurrent;
    static RndPostProc *Current();
    static DOFOverrideParams sDOFOverride;
    static DOFOverrideParams &DOFOverrides() { return sDOFOverride; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS
    NEW_OBJ(RndPostProc)
    static void Init() { REGISTER_OBJ_FACTORY(RndPostProc) }

    float mPriority; // 0x20
    /** "Color tint for bloom effect" */
    Hmx::Color mBloomColor; // 0x24
    /** "Luminance intensity at which to bloom" */
    float mBloomThreshold; // 0x34
    /** "Bloom intensity" */
    float mBloomIntensity; // 0x38
    /** "Whether or not to use the glare effect" */
    bool mBloomGlare; // 0x3C
    /** "Whether or not to use directional light streaks" */
    bool mBloomStreak; // 0x3D
    /** "Attenuation (scattering amount) of light streak.\n0.9 to 0.95 is the sweet spot.". Ranges from -2 to 2. */
    float mBloomStreakAttenuation; // 0x40
    /** "Angle for light streak". Ranges from -360 to 360. */
    float mBloomStreakAngle; // 0x44
    /** "Luminance map" */
    ObjPtr<RndTex> mLuminanceMap; // 0x48
    bool mForceCurrentInterp; // 0x54
    /** "Hue: -180 to 180, 0.0 is neutral" */
    /** "Saturation: -100 to 100, 0.0 is neutral" */
    /** "Lightness: -100 to 100, 0.0 is neutral" */
    /** "Contrast: -100 to 100, 0.0 is neutral" */
    /** "Brightness: -100 to 100, 0.0 is neutral" */
    /** "Input low end" */
    /** "Input high end" */
    /** "Output low end" */
    /** "Output high end" */
    RndColorXfm mColorXfm; // 0x58
    /** "Number of levels for posterization, 0 turns off". Ranges from 0 to 255. */
    float mPosterLevels; // 0xdc
    /** "Minimum intensity to posterize, 1.0 is posterize all". Ranges from 0 to 1. */
    float mPosterMin; // 0xe0
    /** "Kaleidoscope settings" */
        /** "Number of slices in kaleidoscope, 0 turns off, 2 for vertical mirror". Ranges from 0 to 64. */
        float mKaleidoscopeComplexity; // 0xe4
        /** "Smaller size means more repeated areas, but each area is smaller". Ranges from 1.0e-2 to 64. */
        float mKaleidoscopeSize; // 0xe8
        /** "Additional clockwise degrees of rotation around center.". Ranges from 0 to 360. */
        float mKaleidoscopeAngle; // 0xec
        /** "Additional distance from center". Ranges from -0.5 to 0.5. */
        float mKaleidoscopeRadius; // 0xf0
        /** "Flip texture UV coords when reflect" */
        bool mKaleidoscopeFlipUVs; // 0xf4
    /** "Min and max intensity range [0..1], 0.0 to disable" */
    Vector2 mFlickerModBounds; // 0xf8
    /** "Min and max number of seconds for a light to dark cycle" */
    Vector2 mFlickerTimeBounds; // 0x100
    Vector2 mFlickerSeconds; // 0x108
    float mColorModulation; // 0x110
    /** "X and Y tiling of the noise map" */
    Vector2 mNoiseBaseScale; // 0x114
    float mNoiseTopScale; // 0x11c
    /** "intensity of the noise, 0.0 to disable". Ranges from -10 to 10. */
    float mNoiseIntensity; // 0x120
    /** "keep the noise map static over the screen" */
    bool mNoiseStationary; // 0x124
    /** "Applies the noise using at mid-tones of the scene, using an Overlay blend mode." */
    bool mNoiseMidtone; // 0x125
    /** "Optional noise bitmap" */
    ObjPtr<RndTex> mNoiseMap; // 0x128
    /** "Min pixel value to leave trails [0..1]". Ranges from 0 to 1. */
    float mTrailThreshold; // 0x134
    /** "Seconds for the trails to last" */
    float mTrailDuration; // 0x138
    Vector3 mBlendVec; // 0x13c
    /** "Frame rate to emulate, e.g. 24 for film. 0 disables emulation.". Ranges from 0 to 60. */
    float mEmulateFPS; // 0x148
    float mLastRender; // 0x14c
    float mDeltaSecs; // 0x150
    /** "Video feedback effect" */
        /** "Should the effect be blended, or should it produce solid colors?". Options are kHOTBlended, kHOTSolidRingsDepth, kHOTSolidRingsAlpha */
        int mHallOfTimeType; // 0x154
        /** "Speed of effect.  0 is off.  1 is regular speed.". Ranges from -10 to 10. */
        float mHallOfTimeRate; // 0x158
        /** "Seconds for the trails to last." */
        Hmx::Color mHallOfTimeColor; // 0x15c
        /** "Amount of color to blend. 0 is no color, 1 is solid color. Not applicable if solid rings checked.". Ranges from 0 to 1. */
        float mHallOfTimeMix; // 0x16c
    /** "Motion blur settings" */
        /** "The weighting for individual color channels in the previous frame blend." */
        /** The color's alpha field: "The weighting for bright pixels in the previous frame blend.". Ranges from 0 to 1. */
        Hmx::Color mMotionBlurWeight; // 0x170
        /** "The amount of the previous frame to blend into the current frame. This can be used to efficiently simulate motion blur or other effects. Set to zero to disable.". Ranges from 0 to 1. */
        float mMotionBlurBlend; // 0x180
        /** "Whether or not to use the velocity motion blur effect. Should be enabled almost all the time." */
        bool mMotionBlurVelocity; // 0x184
    /** "Gradient map settings" */
        /** "Gradient map; this texture should be layed out horizontally such that the color to use when the pixel is black is on the left and white is on the right." */
        ObjPtr<RndTex> mGradientMap; // 0x188
        /** "The opacity of the gradient map effect.". Ranges from 0 to 1. */
        float mGradientMapOpacity; // 0x194
        /** "This indexes veritically into the gradient map texture. This is useful for storing multiple gradient map textures in a single texture, and to blend between them.". Ranges from 0 to 1. */
        float mGradientMapIndex; // 0x198
        /** "The depth where the gradient map will begin to take effect.". Ranges from 0 to 1. */
        float mGradientMapStart; // 0x19c
        /** "The depth where the gradient map will no longer take effect.". Ranges from 0 to 1. */
        float mGradientMapEnd; // 0x1a0
    /** "Full-screen refraction settings" */
        /** "This is a normal map used to distort the screen." */
        ObjPtr<RndTex> mRefractMap; // 0x1a4
        /** "The distance to refract each pixel of the screen. This can also be negative to reverse the direction. Set to zero to disable." */
        float mRefractDist; // 0x1b0
        /** "This scales the refraction texture before distorting the screen, in the X and Y directions." */
        Vector2 mRefractScale; // 0x1b4
        /** "The amount to offset the refraction texture, in the X and Y directions. This is a fixed amount to offset the refraction effect." */
        Vector2 mRefractPanning; // 0x1bc
        /** "The velocity to scroll the refraction texture, in the X and Y directions. The value is specified in units per second, and will offset the refraction effect over time." */
        Vector2 mRefractVelocity; // 0x1c4
        /** "The angle to rotate the refraction texture, in degrees.". Ranges from 0 to 360. */
        float mRefractAngle; // 0x1cc
    /** "Chromatic sharpen will sharpen the image, while chromatic aberration is an artifact where color channels are slightly shifted. This is useful to simulate old cameras, poor quality video, or underwater scenes." */
        /** "The size, in pixels, of the chromatic aberration or sharpen effect." */
        float mChromaticAberrationOffset; // 0x1d0
        /** "Whether to sharpen the chromatic image or apply the aberration effect." */
        bool mChromaticSharpen; // 0x1d4
    /** "Color tint for vignette effect" */
    Hmx::Color mVignetteColor; // 0x1d8
    /** "0 for no effect, 1 for normal, less than one for smaller effect, 2 is full color". Ranges from 0 to 2. */
    float mVignetteIntensity; // 0x1e8
};
