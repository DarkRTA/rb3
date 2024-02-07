/*
    Compile unit: C:\rockband2\band2\src\band\App.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8000C280 -> 0x8000DC14
*/
class Symbol {
    // total size: 0x4
    const char * mStr; // offset 0x0, size 0x4
};
class Symbol name; // size: 0x4, address: 0x80A48E64
void (* gRealCallback)(unsigned char &, char *, unsigned char); // size: 0x4, address: 0x80A48E68
static class DataNode & kill_notifies; // size: 0x4, address: 0x80A48E70
// Range: 0x8000C280 -> 0x8000C334
static void DebugModal(unsigned char & fail /* r29 */, char * msg /* r30 */, unsigned char wait /* r31 */) {
    // References
    // -> void (* gRealCallback)(unsigned char &, char *, unsigned char);
    // -> static class DataNode & kill_notifies;
}

class ObjDirPtr : public ObjRef {
    // total size: 0xC
protected:
    class ObjectDir * mDir; // offset 0x4, size 0x4
    class DirLoader * mLoader; // offset 0x8, size 0x4
};
static class ObjDirPtr gCommonBank; // size: 0xC, address: 0x80976ACC
static class ObjDirPtr gCommonTrack; // size: 0xC, address: 0x80976AE4
static class ObjDirPtr gCommonLabel3d; // size: 0xC, address: 0x80976AFC
class App {
    // total size: 0x1
};
struct _GXTexObj {
    // total size: 0x20
    unsigned long dummy[8]; // offset 0x0, size 0x20
};
struct OSContext {
    // total size: 0x2C8
    unsigned long gpr[32]; // offset 0x0, size 0x80
    unsigned long cr; // offset 0x80, size 0x4
    unsigned long lr; // offset 0x84, size 0x4
    unsigned long ctr; // offset 0x88, size 0x4
    unsigned long xer; // offset 0x8C, size 0x4
    double fpr[32]; // offset 0x90, size 0x100
    unsigned long fpscr_pad; // offset 0x190, size 0x4
    unsigned long fpscr; // offset 0x194, size 0x4
    unsigned long srr0; // offset 0x198, size 0x4
    unsigned long srr1; // offset 0x19C, size 0x4
    unsigned short mode; // offset 0x1A0, size 0x2
    unsigned short state; // offset 0x1A2, size 0x2
    unsigned long gqr[8]; // offset 0x1A4, size 0x20
    unsigned long psf_pad; // offset 0x1C4, size 0x4
    double psf[32]; // offset 0x1C8, size 0x100
};
struct OSThreadQueue {
    // total size: 0x8
    struct OSThread * head; // offset 0x0, size 0x4
    struct OSThread * tail; // offset 0x4, size 0x4
};
struct OSThreadLink {
    // total size: 0x8
    struct OSThread * next; // offset 0x0, size 0x4
    struct OSThread * prev; // offset 0x4, size 0x4
};
struct OSMutexLink {
    // total size: 0x8
    struct OSMutex * next; // offset 0x0, size 0x4
    struct OSMutex * prev; // offset 0x4, size 0x4
};
struct OSMutex {
    // total size: 0x18
    struct OSThreadQueue queue; // offset 0x0, size 0x8
    struct OSThread * thread; // offset 0x8, size 0x4
    long count; // offset 0xC, size 0x4
    struct OSMutexLink link; // offset 0x10, size 0x8
};
struct OSMutexQueue {
    // total size: 0x8
    struct OSMutex * head; // offset 0x0, size 0x4
    struct OSMutex * tail; // offset 0x4, size 0x4
};
struct OSThread {
    // total size: 0x318
    struct OSContext context; // offset 0x0, size 0x2C8
    unsigned short state; // offset 0x2C8, size 0x2
    unsigned short attr; // offset 0x2CA, size 0x2
    long suspend; // offset 0x2CC, size 0x4
    long priority; // offset 0x2D0, size 0x4
    long base; // offset 0x2D4, size 0x4
    void * val; // offset 0x2D8, size 0x4
    struct OSThreadQueue * queue; // offset 0x2DC, size 0x4
    struct OSThreadLink link; // offset 0x2E0, size 0x8
    struct OSThreadQueue queueJoin; // offset 0x2E8, size 0x8
    struct OSMutex * mutex; // offset 0x2F0, size 0x4
    struct OSMutexQueue queueMutex; // offset 0x2F4, size 0x8
    struct OSThreadLink linkActive; // offset 0x2FC, size 0x8
    unsigned char * stackBase; // offset 0x304, size 0x4
    unsigned long * stackEnd; // offset 0x308, size 0x4
    long error; // offset 0x30C, size 0x4
    void * specific[2]; // offset 0x310, size 0x8
};
class SplashWii {
    // total size: 0x1800
    class Timer mDisplayTimer; // offset 0x0, size 0x38
    class Timer mAnimationTimer; // offset 0x38, size 0x38
    float mPreviousFrameTimeMs; // offset 0x70, size 0x4
    int mCurrentAnimFrame; // offset 0x74, size 0x4
    void * mImageData; // offset 0x78, size 0x4
    struct _GXTexObj mTexture; // offset 0x7C, size 0x20
    struct _GXTexObj mDiscErrorTexture; // offset 0x9C, size 0x20
    struct _GXTexObj mDiscRetryTexture; // offset 0xBC, size 0x20
    char mFileName[1024]; // offset 0xDC, size 0x400
    unsigned char mBeforeSplasher; // offset 0x4DC, size 0x1
    unsigned char mActivatedWPAD; // offset 0x4DD, size 0x1
    unsigned char mSkipButtonPressed; // offset 0x4DE, size 0x1
    unsigned char mDiscErrorThreadActive; // offset 0x4DF, size 0x1
    unsigned char mDiscErrorThreadStack[4096]; // offset 0x4E0, size 0x1000
    struct OSThread mDiscErrorThread; // offset 0x14E0, size 0x318
    struct OSThread * mMainThread; // offset 0x17F8, size 0x4
};
class Splash {
    // total size: 0x1360
    float mMinSplashTime; // offset 0x0, size 0x4
    class Timer mTimer; // offset 0x8, size 0x38
    class RndDir * mLastSplash; // offset 0x40, size 0x4
    struct OSThread * mMainThread; // offset 0x44, size 0x4
    struct OSThread mSplashThread; // offset 0x48, size 0x318
    unsigned char mSplashThreadStack[4096]; // offset 0x360, size 0x1000
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
enum State {
    kNormal = 0,
    kFocused = 1,
    kDisabled = 2,
    kSelecting = 3,
    kSelected = 4,
    kNumStates = 5,
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class UIComponent * mPtr; // offset 0x8, size 0x4
};
class UIComponent : public RndDrawable, public RndTransformable, public RndPollable {
    // total size: 0x170
protected:
    enum State mState; // offset 0x100, size 0x4
    class ObjPtr mNavRight; // offset 0x104, size 0xC
    class ObjPtr mNavDown; // offset 0x110, size 0xC
    class User * mSelectingUser; // offset 0x11C, size 0x4
    class UIScreen * mSelectScreen; // offset 0x120, size 0x4
    int mSelected; // offset 0x124, size 0x4
    class UIResource * mResource; // offset 0x128, size 0x4
private:
    unsigned char mLoading; // offset 0x12C, size 0x1
    unsigned char mMockSelect; // offset 0x12D, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndDir * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndDir * * _M_start; // offset 0x0, size 0x4
    class RndDir * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class FilePath * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class FilePath * _M_start; // offset 0x0, size 0x4
    class FilePath * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum JoypadAction {
    kAction_None = 0,
    kAction_Confirm = 1,
    kAction_Cancel = 2,
    kAction_Option = 3,
    kAction_Start = 4,
    kAction_ViewModify = 5,
    kAction_Up = 6,
    kAction_Right = 7,
    kAction_Down = 8,
    kAction_Left = 9,
    kAction_PageUp = 10,
    kAction_PageDown = 11,
    kAction_ExtendedOption1 = 12,
    kAction_ExtendedOption2 = 13,
    kAction_WiiHomeMenu = 14,
    kAction_Option1 = 15,
    kAction_NumActions = 16,
};
enum JoypadButton {
    kPad_L2 = 0,
    kPad_R2 = 1,
    kPad_L1 = 2,
    kPad_R1 = 3,
    kPad_Tri = 4,
    kPad_Circle = 5,
    kPad_X = 6,
    kPad_Square = 7,
    kPad_Select = 8,
    kPad_L3 = 9,
    kPad_R3 = 10,
    kPad_Start = 11,
    kPad_DUp = 12,
    kPad_DRight = 13,
    kPad_DDown = 14,
    kPad_DLeft = 15,
    kPad_LStickUp = 16,
    kPad_LStickRight = 17,
    kPad_LStickDown = 18,
    kPad_LStickLeft = 19,
    kPad_RStickUp = 20,
    kPad_RStickRight = 21,
    kPad_RStickDown = 22,
    kPad_RStickLeft = 23,
    kPad_NumButtons = 24,
    kPad_Xbox_LT = 0,
    kPad_Xbox_RT = 1,
    kPad_Xbox_LB = 2,
    kPad_Xbox_RB = 3,
    kPad_Xbox_Y = 4,
    kPad_Xbox_B = 5,
    kPad_Xbox_A = 6,
    kPad_Xbox_X = 7,
    kPad_Xbox_LS = 9,
    kPad_Xbox_RS = 10,
};
enum RequestFocus {
    kNoFocus = 0,
    kMaybeFocus = 1,
    kAlwaysFocus = 2,
};
class PanelDir : public RndDir {
    // total size: 0x290
    class UIComponent * mFocusComponent; // offset 0x1F4, size 0x4
    class ObjPtr mCam; // offset 0x1F8, size 0xC
    class list mTriggers; // offset 0x204, size 0x8
    class list mComponents; // offset 0x20C, size 0x8
    unsigned char mCanEndWorld; // offset 0x214, size 0x1
    class vector mBackPanels; // offset 0x218, size 0xC
    class vector mBackFilenames; // offset 0x224, size 0xC
    class vector mFrontPanels; // offset 0x230, size 0xC
    class vector mFrontFilenames; // offset 0x23C, size 0xC
    unsigned char mShowEditModePanels; // offset 0x248, size 0x1
};
enum State {
    kUnloaded = 0,
    kUp = 1,
    kDown = 2,
};
class UIPanel : public virtual Object {
    // total size: 0x5C
public:
    void * __vptr$; // offset 0x4, size 0x4
protected:
    unsigned char mHomeMenuAllowed; // offset 0x8, size 0x1
    class PanelDir * mDir; // offset 0xC, size 0x4
    class DirLoader * mLoader; // offset 0x10, size 0x4
    class String mFocusName; // offset 0x14, size 0xC
private:
    unsigned char mSharedDir; // offset 0x20, size 0x1
    enum State mState; // offset 0x24, size 0x4
    unsigned char mPaused; // offset 0x28, size 0x1
    unsigned char mShowing; // offset 0x29, size 0x1
    unsigned char mForceExit; // offset 0x2A, size 0x1
    int mLoadRefs; // offset 0x2C, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class UIScreen : public Object {
    // total size: 0x3C
protected:
    class list mPanelList; // offset 0x28, size 0x8
    class UIPanel * mFocusPanel; // offset 0x30, size 0x4
    class DataArray * mBack; // offset 0x34, size 0x4
    unsigned char mClearVram; // offset 0x38, size 0x1
    unsigned char mShowing; // offset 0x39, size 0x1
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UIScreen * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8000C334 -> 0x8000D238
void * App::App(class App * const this /* r29 */, int argc /* r26 */, char * * argv /* r25 */) {
    // Local variables
    class SplashWii splasherWii; // r1+0x1440
    unsigned char fast; // r0
    class Splash splasher; // r1+0xE0
    class ObjDirItr s; // r1+0xC0

    // References
    // -> void (* gRealCallback)(unsigned char &, char *, unsigned char);
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __RTTI__10BandScreen;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> class UIManager TheUI;
    // -> class BandUI * TheBandUI;
    // -> class Synth * TheSynth;
    // -> class Symbol name;
    // -> static class ObjDirPtr gCommonTrack;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> static class ObjDirPtr gCommonBank;
    // -> class EntityUploader & TheEntityUploader;
    // -> class RockCentralGateway RockCentral;
    // -> class Net TheNet;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Rnd & TheRnd;
    // -> class WiiRnd TheWiiRnd;
}

enum Aspect {
    kSquare = 0,
    kRegular = 1,
    kWidescreen = 2,
};
enum Mode {
    kDrawNormal = 0,
    kDrawShadowDepth = 1,
    kDrawExtrude = 2,
    kDrawShadowColor = 3,
    kDrawOcclusion = 4,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class RndFlare : public RndTransformable, public RndDrawable {
    // total size: 0x170
protected:
    unsigned char mPointTest; // offset 0xF4, size 0x1
    unsigned char mAreaTest; // offset 0xF5, size 0x1
    unsigned char mVisible; // offset 0xF6, size 0x1
    class Vector2 mSizes; // offset 0xF8, size 0x8
    class ObjPtr mMat; // offset 0x100, size 0xC
    class Vector2 mRange; // offset 0x10C, size 0x8
    int mSteps; // offset 0x114, size 0x4
    int mStep; // offset 0x118, size 0x4
    class Rect mArea; // offset 0x11C, size 0x10
    float mAreaVisible; // offset 0x12C, size 0x4
    unsigned char mTestDone; // offset 0x130, size 0x1
    unsigned char mLastDone; // offset 0x131, size 0x1
};
struct PointTest {
    // total size: 0x10
    int x; // offset 0x0, size 0x4
    int y; // offset 0x4, size 0x4
    unsigned int z; // offset 0x8, size 0x4
    class RndFlare * flare; // offset 0xC, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class PostProcessor {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum ProcessCmd {
    kProcessNone = 0,
    kProcessWorld = 1,
    kProcessPost = 2,
    kProcessChar = 4,
    kProcessAll = 7,
    kProcessFrame1 = 1,
    kProcessFrame2 = 4,
    kProcessPostChar = 6,
};
class ProcCounter {
    // total size: 0x18
    unsigned char mProcAndLock; // offset 0x0, size 0x1
    int mCount; // offset 0x4, size 0x4
    int mSwitch; // offset 0x8, size 0x4
    int mOdd; // offset 0xC, size 0x4
    int mFPS; // offset 0x10, size 0x4
    unsigned char mEvenOddDisabled; // offset 0x14, size 0x1
    unsigned char mTriFrameRendering; // offset 0x15, size 0x1
};
class Rnd : public Object, public Callback {
    // total size: 0x140
protected:
    class Color mClearColor; // offset 0x30, size 0x10
    int mScreenWidth; // offset 0x40, size 0x4
    int mScreenHeight; // offset 0x44, size 0x4
    int mScreenBpp; // offset 0x48, size 0x4
    int mDrawCount; // offset 0x4C, size 0x4
    class Timer mDrawTimer; // offset 0x50, size 0x38
    class RndOverlay * mTimersOverlay; // offset 0x88, size 0x4
    class RndOverlay * mRateOverlay; // offset 0x8C, size 0x4
    class RndOverlay * mHeapOverlay; // offset 0x90, size 0x4
    class RndOverlay * mStatsOverlay; // offset 0x94, size 0x4
    class RndConsole * mConsole; // offset 0x98, size 0x4
    class ParamEdit * mParamEdit; // offset 0x9C, size 0x4
    class RndMat * mDefaultMat; // offset 0xA0, size 0x4
    class RndMat * mOverlayMat; // offset 0xA4, size 0x4
    class RndCam * mDefaultCam; // offset 0xA8, size 0x4
    class RndEnviron * mDefaultEnv; // offset 0xAC, size 0x4
    class RndLight * mDefaultLit; // offset 0xB0, size 0x4
    float mRateTotal; // offset 0xB4, size 0x4
    int mRate; // offset 0xB8, size 0x4
    int mRateCount; // offset 0xBC, size 0x4
    const char * mRateGate; // offset 0xC0, size 0x4
    class DataArray * mFont; // offset 0xC4, size 0x4
    int mSync; // offset 0xC8, size 0x4
    unsigned char mGSTiming; // offset 0xCC, size 0x1
    unsigned char mSafeArea; // offset 0xCD, size 0x1
    unsigned char mDrawing; // offset 0xCE, size 0x1
    unsigned char mWorldEnded; // offset 0xCF, size 0x1
    enum Aspect mAspect; // offset 0xD0, size 0x4
    enum Mode mDrawMode; // offset 0xD4, size 0x4
    unsigned char mResourceCached; // offset 0xD8, size 0x1
    unsigned char mShowShaderCost; // offset 0xD9, size 0x1
    unsigned char mShrinkToSafeArea; // offset 0xDA, size 0x1
    unsigned char mInGame; // offset 0xDB, size 0x1
    unsigned char mDrawEnabled; // offset 0xDC, size 0x1
    unsigned char mSaveThreadLocked; // offset 0xDD, size 0x1
    class list mPointTests; // offset 0xE0, size 0x8
    class list mPostProcessors; // offset 0xE8, size 0x8
    class ObjPtrList mPreClearList; // offset 0xF0, size 0x14
    class ProcCounter mProcCounter; // offset 0x104, size 0x18
    enum ProcessCmd mProcCmds; // offset 0x11C, size 0x4
    enum ProcessCmd mLastProcCmds; // offset 0x120, size 0x4
    int mUserNumbers[4]; // offset 0x124, size 0x10
};
class Distribution {
    // total size: 0x20
    float mRes; // offset 0x0, size 0x4
    float mMin; // offset 0x4, size 0x4
    float mMax; // offset 0x8, size 0x4
    float mTotal; // offset 0xC, size 0x4
    int mCount; // offset 0x10, size 0x4
    class vector mDist; // offset 0x14, size 0xC
};
class BudgetScreen : public UIScreen {
    // total size: 0xD4
    class UIPanel * mTestPanel; // offset 0x3C, size 0x4
    float mNullCpu; // offset 0x40, size 0x4
    float mNullGs; // offset 0x44, size 0x4
    float mTime; // offset 0x48, size 0x4
    float mEndTime; // offset 0x4C, size 0x4
    float mFrameInc; // offset 0x50, size 0x4
    float mLastCpu; // offset 0x54, size 0x4
    float mLastGpu; // offset 0x58, size 0x4
    class TextFileStream * mLog; // offset 0x5C, size 0x4
    class Distribution mPollDist; // offset 0x60, size 0x20
    class Distribution mCpuDist; // offset 0x80, size 0x20
    class Distribution mGsDist; // offset 0xA0, size 0x20
    int mRecordStartTick; // offset 0xC0, size 0x4
    int mRecordEndTick; // offset 0xC4, size 0x4
    const class DataArray * mTests; // offset 0xC8, size 0x4
    int mTestIdx; // offset 0xCC, size 0x4
    unsigned char mWorstOnly; // offset 0xD0, size 0x1
};
struct LevelData {
    // total size: 0x1C
    float mRMS; // offset 0x0, size 0x4
    float mPeak; // offset 0x4, size 0x4
    float mPeakHold; // offset 0x8, size 0x4
    int mPeakAge; // offset 0xC, size 0x4
    class String mName; // offset 0x10, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct LevelData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct LevelData * _M_start; // offset 0x0, size 0x4
    struct LevelData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ByteGrinder {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Mic * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Mic * * _M_start; // offset 0x0, size 0x4
    class Mic * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct Node {
    // total size: 0xC
    class Fader * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class FaderGroup {
    // total size: 0x18
    class ObjPtrList mFaders; // offset 0x0, size 0x14
    unsigned char mDirty; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class set {
    // total size: 0x18
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class Fader : public Object {
    // total size: 0x4C
    float mVal; // offset 0x28, size 0x4
    struct FaderTask * mFaderTask; // offset 0x2C, size 0x4
    class Symbol mLocalName; // offset 0x30, size 0x4
    class set mClients; // offset 0x34, size 0x18
};
enum FXMode {
    kFXModeOff = 0,
    kFXModeRoom = 1,
    kFXModeSmallStudio = 2,
    kFXModeMedStudio = 3,
    kFXModeLargeStudio = 4,
    kFXModeHall = 5,
    kFXModeSpace = 6,
    kFXModeEcho = 7,
    kFXModeDelay = 8,
    kFXModePipe = 9,
    kFXModeChorus = 10,
    kFXModeWah = 11,
    kFXModeFlanger = 12,
};
enum Platform {
    kPlatformNone = 0,
    kPlatformPS2 = 1,
    kPlatformXBox = 2,
    kPlatformPC = 3,
    kPlatformPS3 = 4,
    kPlatformWii = 5,
};
class Synth : public Object, public Callback {
    // total size: 0x70
protected:
    class vector mLevelData; // offset 0x2C, size 0xC
private:
    class ByteGrinder mGrinder; // offset 0x38, size 0x4
    int mNumMics; // offset 0x3C, size 0x4
    class MidiSynth * mMidiSynth; // offset 0x40, size 0x4
    class vector mNullMics; // offset 0x44, size 0xC
    unsigned char mMuted; // offset 0x50, size 0x1
    class list mBanks; // offset 0x54, size 0x8
    class Fader * mMasterFader; // offset 0x5C, size 0x4
    class Fader * mSfxFader; // offset 0x60, size 0x4
    class Stream * mDebugStream; // offset 0x64, size 0x4
    class RndOverlay * mHud; // offset 0x68, size 0x4
    void (* mWavCacher)(char *); // offset 0x6C, size 0x4
};
enum Type {
    kInt = 0,
    kStr = 1,
    kFloat = 2,
    kNone = 3,
};
class FormatString {
    // total size: 0x814
    char * mBuf; // offset 0x0, size 0x4
    int mBufSize; // offset 0x4, size 0x4
    char mFmtBuf[2048]; // offset 0x8, size 0x800
    char * mFmt; // offset 0x808, size 0x4
    char * mFmtEnd; // offset 0x80C, size 0x4
    enum Type mType; // offset 0x810, size 0x4
};
// Range: 0x8000D238 -> 0x8000D2D0
void * App::~App(class App * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> class BandUI * TheBandUI;
}

class Rect {
    // total size: 0x10
public:
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
    float w; // offset 0x8, size 0x4
    float h; // offset 0xC, size 0x4
};
class Color {
    // total size: 0x10
public:
    float r; // offset 0x0, size 0x4
    float g; // offset 0x4, size 0x4
    float b; // offset 0x8, size 0x4
    float a; // offset 0xC, size 0x4
};
// Range: 0x8000D2D0 -> 0x8000D3BC
void App::DrawRegular() {
    // Local variables
    class Rect r; // r1+0x20
    class Color c; // r1+0x10

    // References
    // -> class BandUI * TheBandUI;
    // -> class CharCache * TheCharCache;
    // -> class Rnd & TheRnd;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x8000D3BC -> 0x8000D3C0
void App::Draw() {}

// Range: 0x8000D3C0 -> 0x8000D3C4
void App::Run() {}

static class Timer * _t; // size: 0x4, address: 0x80A48E74
static class Timer * _t; // size: 0x4, address: 0x80A48E7C
static class Timer * _t; // size: 0x4, address: 0x80A48E84
static class DataNode & kill_notifies; // size: 0x4, address: 0x80A48E8C
static class Object * cd; // size: 0x4, address: 0x80A48E90
class Message {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class DataArray * mData; // offset 0x4, size 0x4
};
static class Message show; // size: 0x8, address: 0x80976B18
class Timer {
    // total size: 0x38
    unsigned int mStart; // offset 0x0, size 0x4
    long long mCycles; // offset 0x8, size 0x8
    float mLastMs; // offset 0x10, size 0x4
    float mWorstMs; // offset 0x14, size 0x4
    int mWorstMsFrame; // offset 0x18, size 0x4
    int mFrame; // offset 0x1C, size 0x4
    class Symbol mName; // offset 0x20, size 0x4
    int mRunning; // offset 0x24, size 0x4
    float mBudget; // offset 0x28, size 0x4
    unsigned char mDraw; // offset 0x2C, size 0x1
    int mCount; // offset 0x30, size 0x4
    int mLastCount; // offset 0x34, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x40
public:
    class Timer _M_data; // offset 0x8, size 0x38
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class AutoTimer {
    // total size: 0x4
    class Timer * mTimer; // offset 0x0, size 0x4
};
enum TransitionState {
    kTransitionNone = 0,
    kTransitionTo = 1,
    kTransitionFrom = 2,
    kTransitionPop = 3,
};
// Range: 0x8000D3C4 -> 0x8000DB6C
void App::RunWithoutDebugging(class App * const this /* r30 */) {
    // Local variables
    class Timer t; // r1+0x68
    class AutoTimer _at; // r1+0x28
    class AutoTimer _at; // r1+0x24
    class AutoTimer _at; // r1+0x20
    float dt; // f31
    enum TransitionState state; // r0

    // References
    // -> class UIManager TheUI;
    // -> static class Message show;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Object * cd;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * sMainDir;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class DataNode & kill_notifies;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Timer * _t;
    // -> class BandUI * TheBandUI;
    // -> class NetSync * TheNetSync;
    // -> class EntityUploader & TheEntityUploader;
    // -> class RockCentralGateway RockCentral;
    // -> class Net TheNet;
    // -> static class Timer * _t;
    // -> class Synth * TheSynth;
    // -> static class Timer * _t;
}

class TextStream {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
enum DataType {
    kDataInt = 0,
    kDataFloat = 1,
    kDataVar = 2,
    kDataFunc = 3,
    kDataObject = 4,
    kDataSymbol = 5,
    kDataUnhandled = 6,
    kDataArray = 16,
    kDataCommand = 17,
    kDataString = 18,
    kDataProperty = 19,
    kDataGlob = 20,
    kDataIfdef = 7,
    kDataElse = 8,
    kDataEndif = 9,
    kDataDefine = 32,
    kDataInclude = 33,
    kDataMerge = 34,
    kDataIfndef = 35,
    kDataAutorun = 36,
    kDataUndef = 37,
};
class String : public TextStream {
    // total size: 0xC
protected:
    unsigned int mCap; // offset 0x4, size 0x4
    char * mStr; // offset 0x8, size 0x4
};
class Vector2 {
    // total size: 0x8
public:
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
};
class Vector3 {
    // total size: 0x10
public:
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
    float z; // offset 0x8, size 0x4
};
class Plane {
    // total size: 0x10
public:
    float a; // offset 0x0, size 0x4
    float b; // offset 0x4, size 0x4
    float c; // offset 0x8, size 0x4
    float d; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    int * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    int * _M_start; // offset 0x0, size 0x4
    int * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct __false_type {
    // total size: 0x1
};
struct __true_type {
    // total size: 0x1
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Vector3 * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Vector3 * _M_start; // offset 0x0, size 0x4
    class Vector3 * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Matrix3 {
    // total size: 0x30
public:
    class Vector3 x; // offset 0x0, size 0x10
    class Vector3 y; // offset 0x10, size 0x10
    class Vector3 z; // offset 0x20, size 0x10
};
class Quat {
    // total size: 0x10
public:
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
    float z; // offset 0x8, size 0x4
    float w; // offset 0xC, size 0x4
};
enum SeekType {
    kSeekBegin = 0,
    kSeekCur = 1,
    kSeekEnd = 2,
};
class BinStream {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned char mLittleEndian; // offset 0x4, size 0x1
    class Rand2 * mCrypto; // offset 0x8, size 0x4
};
class TypeProps : public ObjRef {
    // total size: 0xC
    class DataArray * mMap; // offset 0x4, size 0x4
    class Object * mOwner; // offset 0x8, size 0x4
};
struct Buf {
    // total size: 0x8
    int size; // offset 0x0, size 0x4
    char * chars; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Buf * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Buf * _M_start; // offset 0x0, size 0x4
    struct Buf * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StringTable {
    // total size: 0x14
    class vector mBuffers; // offset 0x0, size 0xC
    char * mCurChar; // offset 0xC, size 0x4
    int mCurBuf; // offset 0x10, size 0x4
};
enum LoaderPos {
    kLoadFront = 0,
    kLoadBack = 1,
    kLoadFrontStayBack = 2,
    kLoadStayBack = 3,
};
class Loader {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    enum LoaderPos mPos; // offset 0x4, size 0x4
private:
    class FilePath mFile; // offset 0x8, size 0xC
};
struct Node {
    // total size: 0xC
    class Object * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
enum ObjListMode {
    kObjListNoNull = 0,
    kObjListAllowNull = 1,
    kObjListOwnerControl = 2,
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class Callback {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class DirLoader : public Loader, public ObjRef {
    // total size: 0xA8
    void (DirLoader::* mState)(void *, void *); // offset 0x18, size 0x4
    class String mRoot; // offset 0x24, size 0xC
    unsigned char mOwnStream; // offset 0x30, size 0x1
    class BinStream * mStream; // offset 0x34, size 0x4
    int mRev; // offset 0x38, size 0x4
    int mCounter; // offset 0x3C, size 0x4
    class ObjPtrList mObjects; // offset 0x40, size 0x14
    class Callback * mCallback; // offset 0x54, size 0x4
    class ObjectDir * mDir; // offset 0x58, size 0x4
    unsigned char mPostLoad; // offset 0x5C, size 0x1
    unsigned char mLoadDir; // offset 0x5D, size 0x1
    unsigned char mDeleteSelf; // offset 0x5E, size 0x1
    const char * mProxyName; // offset 0x60, size 0x4
    class ObjectDir * mProxyDir; // offset 0x64, size 0x4
    class Timer mTimer; // offset 0x68, size 0x38
    unsigned char mAccessed; // offset 0xA0, size 0x1
    const char * mFileName; // offset 0xA4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjDirPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjDirPtr * _M_start; // offset 0x0, size 0x4
    class ObjDirPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Transform {
    // total size: 0x40
public:
    class Matrix3 m; // offset 0x0, size 0x30
    class Vector3 v; // offset 0x30, size 0x10
};
class Viewport {
    // total size: 0x40
public:
    class Transform mXfm; // offset 0x0, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Viewport * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Viewport * _M_start; // offset 0x0, size 0x4
    class Viewport * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum ViewportId {
    kPerspective = 0,
    kLeft = 1,
    kRight = 2,
    kTop = 3,
    kBottom = 4,
    kFront = 5,
    kBack = 6,
    kCustom = 7,
    kNumViewports = 8,
};
enum CopyType {
    kCopyDeep = 0,
    kCopyShallow = 1,
    kCopyFromMax = 2,
};
enum PropOp {
    kPropGet = 1,
    kPropSet = 2,
    kPropInsert = 4,
    kPropRemove = 8,
    kPropSize = 16,
    kPropHandle = 32,
};
class ObjectDir : public virtual Object {
    // total size: 0xAC
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    class KeylessHash mHashTable; // offset 0x8, size 0x20
    class StringTable mStringTable; // offset 0x28, size 0x14
    class FilePath mProxyFile; // offset 0x3C, size 0xC
    unsigned char mProxyOverride; // offset 0x48, size 0x1
    unsigned char mInline; // offset 0x49, size 0x1
    class DirLoader * mLoader; // offset 0x4C, size 0x4
    class vector mSubDirs; // offset 0x50, size 0xC
    unsigned char mIsSubDir; // offset 0x5C, size 0x1
    char * mPathName; // offset 0x60, size 0x4
    class vector mViewports; // offset 0x64, size 0xC
    enum ViewportId mCurViewport; // offset 0x70, size 0x4
    class Object * mCurAnim; // offset 0x74, size 0x4
    class Object * mCurCam; // offset 0x78, size 0x4
    const char * mDestFileName; // offset 0x7C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
struct _List_node_base {
    // total size: 0x8
    struct _List_node_base * _M_next; // offset 0x0, size 0x4
    struct _List_node_base * _M_prev; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    int _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator_base {
    // total size: 0x4
    struct _List_node_base * _M_node; // offset 0x0, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class Object : public ObjRef {
    // total size: 0x28
protected:
    class TypeProps mTypeProps; // offset 0x4, size 0xC
private:
    class DataArray * mTypeDef; // offset 0x10, size 0x4
    char * mNote; // offset 0x14, size 0x4
    const char * mName; // offset 0x18, size 0x4
    class ObjectDir * mDir; // offset 0x1C, size 0x4
    class list mRefs; // offset 0x20, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
enum SinkMode {
    kHandle = 0,
    kExport = 1,
    kType = 2,
    kExportType = 3,
};
struct Sink {
    // total size: 0x8
    class Object * obj; // offset 0x0, size 0x4
    enum SinkMode mode; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct EventSinkElem : public Sink {
    // total size: 0xC
    class Symbol handler; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct EventSink {
    // total size: 0xC
    class Symbol ev; // offset 0x0, size 0x4
    class list sinks; // offset 0x4, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class MsgSource : public virtual Object {
    // total size: 0x48
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    class list mSinks; // offset 0x8, size 0x8
    class list mEventSinks; // offset 0x10, size 0x8
    int mExporting; // offset 0x18, size 0x4
};
enum ProfileSaveState {
    kMetaProfileUnloaded = 0,
    kMetaProfileLoaded = 1,
    kMetaProfileError = 2,
    kMetaProfileDelete = 3,
    kMetaProfileUnchanged = -1,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourCharLocal * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourCharLocal * * _M_start; // offset 0x0, size 0x4
    class TourCharLocal * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourBandLocal * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourBandLocal * * _M_start; // offset 0x0, size 0x4
    class TourBandLocal * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RemoteBandData * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RemoteBandData * * _M_start; // offset 0x0, size 0x4
    class RemoteBandData * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Symbol * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Symbol * _M_start; // offset 0x0, size 0x4
    class Symbol * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct BeatData {
    // total size: 0x8
    class Symbol mBeatName; // offset 0x0, size 0x4
    int mBpm; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BeatData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BeatData * _M_start; // offset 0x0, size 0x4
    struct BeatData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct DateTime {
    // total size: 0x6
    unsigned char mSec; // offset 0x0, size 0x1
    unsigned char mMin; // offset 0x1, size 0x1
    unsigned char mHour; // offset 0x2, size 0x1
    unsigned char mDay; // offset 0x3, size 0x1
    unsigned char mMonth; // offset 0x4, size 0x1
    unsigned char mYear; // offset 0x5, size 0x1
};
class HxGuid {
    // total size: 0x10
    int mData[4]; // offset 0x0, size 0x10
};
struct BotbNewsCreds {
    // total size: 0x24
    struct DateTime mTimeStamp; // offset 0x0, size 0x6
    class HxGuid mBandId; // offset 0x8, size 0x10
    class String mCookies; // offset 0x18, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
struct _Rb_tree_node_base {
    // total size: 0x10
    unsigned char _M_color; // offset 0x0, size 0x1
    struct _Rb_tree_node_base * _M_parent; // offset 0x4, size 0x4
    struct _Rb_tree_node_base * _M_left; // offset 0x8, size 0x4
    struct _Rb_tree_node_base * _M_right; // offset 0xC, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class set {
    // total size: 0x18
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class OnlineID {
    // total size: 0x10
    class String mName; // offset 0x0, size 0xC
    unsigned char mValid; // offset 0xC, size 0x1
};
enum VocalStyle {
    kVocalStyleStatic = 0,
    kVocalStyleScrolling = 1,
    kNumVocalStyles = 2,
};
class GameplayOptions : public virtual Object {
    // total size: 0x48
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    int mMicGain; // offset 0x8, size 0x4
    int mVocalVolume; // offset 0xC, size 0x4
    unsigned char mLefty; // offset 0x10, size 0x1
    enum VocalStyle mVocalStyle; // offset 0x14, size 0x4
    unsigned char mIsDirty; // offset 0x18, size 0x1
};
class RndHighlightable : public virtual Object {
    // total size: 0x34
public:
    void * __vptr$; // offset 0x4, size 0x4
};
class Sphere {
    // total size: 0x20
public:
    class Vector3 center; // offset 0x0, size 0x10
    float radius; // offset 0x10, size 0x4
};
enum HighlightStyle {
    kHighlightWireframe = 0,
    kHighlightSphere = 1,
    kHighlightNone = 2,
    kHighlightWireframeWithNormals = 3,
    kNumHighlightStyles = 4,
};
class Segment {
    // total size: 0x20
public:
    class Vector3 start; // offset 0x0, size 0x10
    class Vector3 end; // offset 0x10, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTransformable * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum Constraint {
    kNone = 0,
    kLocalRotate = 1,
    kParentWorld = 2,
    kLookAtTarget = 3,
    kShadowTarget = 4,
    kBillboardZ = 5,
    kBillboardXZ = 6,
    kBillboardXYZ = 7,
    kFastBillboardXYZ = 8,
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTransformable * mPtr; // offset 0x8, size 0x4
};
class RndTransformable : public virtual RndHighlightable {
    // total size: 0xF0
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    class ObjOwnerPtr mParent; // offset 0x8, size 0xC
    class list mChildren; // offset 0x14, size 0x8
    class Transform mLocalXfm; // offset 0x20, size 0x40
    class Transform mWorldXfm; // offset 0x60, size 0x40
    unsigned char mDirty; // offset 0xA0, size 0x1
    enum Constraint mConstraint; // offset 0xA4, size 0x4
    unsigned char mPreserveScale; // offset 0xA8, size 0x1
    class ObjPtr mTarget; // offset 0xAC, size 0xC
};
class Frustum {
    // total size: 0x60
public:
    class Plane front; // offset 0x0, size 0x10
    class Plane back; // offset 0x10, size 0x10
    class Plane left; // offset 0x20, size 0x10
    class Plane right; // offset 0x30, size 0x10
    class Plane top; // offset 0x40, size 0x10
    class Plane bottom; // offset 0x50, size 0x10
};
enum AlphaFlag {
    kGrayscaleAlpha = 0,
    kGrayscaleWhite = 1,
    kTransparentBlack = 2,
};
class RndBitmap {
    // total size: 0x24
    unsigned short mWidth; // offset 0x0, size 0x2
    unsigned short mHeight; // offset 0x2, size 0x2
    unsigned short mRowBytes; // offset 0x4, size 0x2
    unsigned char mBpp; // offset 0x6, size 0x1
    unsigned int mOrder; // offset 0x8, size 0x4
    unsigned char * mPixels; // offset 0xC, size 0x4
    unsigned char * mPalette; // offset 0x10, size 0x4
    unsigned char * mBuffer; // offset 0x14, size 0x4
    class RndBitmap * mMip; // offset 0x18, size 0x4
    unsigned char mAlphaBpp; // offset 0x1C, size 0x1
    class RndBitmap * mAlphaBmp; // offset 0x20, size 0x4
};
enum Type {
    kRegular = 1,
    kRendered = 2,
    kMovie = 4,
    kBackBuffer = 8,
    kFrontBuffer = 24,
    kRenderedNoZ = 34,
    kShadowMap = 66,
    kDepthVolumeMap = 162,
    kDensityMap = 290,
    kDeviceTexture = 4096,
};
class File {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class FileLoader : public Loader {
    // total size: 0x24
    class File * mFile; // offset 0x14, size 0x4
    char * mBuffer; // offset 0x18, size 0x4
    int mBufLen; // offset 0x1C, size 0x4
    unsigned char mAccessed; // offset 0x20, size 0x1
};
class RndTex : public Object {
    // total size: 0x78
protected:
    class RndBitmap mBitmap; // offset 0x28, size 0x24
    float mMipMapK; // offset 0x4C, size 0x4
    enum Type mType; // offset 0x50, size 0x4
    int mMPEG; // offset 0x54, size 0x4
    int mWidth; // offset 0x58, size 0x4
    int mHeight; // offset 0x5C, size 0x4
    int mBpp; // offset 0x60, size 0x4
    class FilePath mFile; // offset 0x64, size 0xC
    int mNumMips; // offset 0x70, size 0x4
    class FileLoader * mLoader; // offset 0x74, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTex * mPtr; // offset 0x8, size 0x4
};
class Vector4 {
    // total size: 0x10
public:
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
    float z; // offset 0x8, size 0x4
    float w; // offset 0xC, size 0x4
};
class RndCam : public RndTransformable {
    // total size: 0x330
protected:
    class Transform mInvWorldXfm; // offset 0xC0, size 0x40
    class Transform mLocalProjectXfm; // offset 0x100, size 0x40
    class Transform mInvLocalProjectXfm; // offset 0x140, size 0x40
    class Transform mWorldProjectXfm; // offset 0x180, size 0x40
    class Transform mInvWorldProjectXfm; // offset 0x1C0, size 0x40
    class Frustum mLocalFrustum; // offset 0x200, size 0x60
    class Frustum mWorldFrustum; // offset 0x260, size 0x60
    float mNearPlane; // offset 0x2C0, size 0x4
    float mFarPlane; // offset 0x2C4, size 0x4
    float mYFov; // offset 0x2C8, size 0x4
    class Vector2 mZRange; // offset 0x2CC, size 0x8
    class Rect mScreenRect; // offset 0x2D4, size 0x10
    class ObjPtr mTargetTex; // offset 0x2E4, size 0xC
};
class RndDrawable : public virtual RndHighlightable {
    // total size: 0x70
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    unsigned char mShowing; // offset 0x8, size 0x1
    class Sphere mSphere; // offset 0x10, size 0x20
    float mOrder; // offset 0x30, size 0x4
};
enum Rate {
    k30_fps = 0,
    k480_fpb = 1,
    k30_fps_ui = 2,
    k1_fpb = 3,
    k30_fps_tutorial = 4,
};
class Task : public Object {
    // total size: 0x28
};
enum TaskUnits {
    kTaskSeconds = 0,
    kTaskBeats = 1,
    kTaskUISeconds = 2,
    kTaskTutorialSeconds = 3,
    kTaskNumUnits = 4,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class RndAnimatable : public virtual Object {
    // total size: 0x3C
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    float mFrame; // offset 0x8, size 0x4
    enum Rate mRate; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class RndPollable : public virtual Object {
    // total size: 0x34
public:
    void * __vptr$; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndDrawable * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndDrawable * * _M_start; // offset 0x0, size 0x4
    class RndDrawable * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndAnimatable * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndAnimatable * * _M_start; // offset 0x0, size 0x4
    class RndAnimatable * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndPollable * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndPollable * * _M_start; // offset 0x0, size 0x4
    class RndPollable * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndLight * mPtr; // offset 0x8, size 0x4
};
enum Type {
    kPoint = 0,
    kDirectional = 1,
    kFakeSpot = 2,
    kFloorSpot = 3,
    kShadowRef = 4,
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class RndLight : public RndTransformable {
    // total size: 0x150
protected:
    class Color mColor; // offset 0xC0, size 0x10
    class ObjOwnerPtr mColorOwner; // offset 0xD0, size 0xC
    float mRange; // offset 0xDC, size 0x4
    float mFalloffStart; // offset 0xE0, size 0x4
    enum Type mType; // offset 0xE4, size 0x4
    unsigned char mAnimateColorFromPreset; // offset 0xE8, size 0x1
    unsigned char mAnimatePositionFromPreset; // offset 0xE9, size 0x1
    unsigned char mShowing; // offset 0xEA, size 0x1
    float mConeSoftness; // offset 0xEC, size 0x4
    float mTopRadius; // offset 0xF0, size 0x4
    float mBotRadius; // offset 0xF4, size 0x4
    float mDisplacement; // offset 0xF8, size 0x4
    class ObjPtr mProjection; // offset 0xFC, size 0xC
    class ObjPtrList * mShadowCasters; // offset 0x108, size 0x4
    float mRadScale; // offset 0x10C, size 0x4
    float mRadOffset; // offset 0x110, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndEnviron * mPtr; // offset 0x8, size 0x4
};
class RndColorXfm {
    // total size: 0xA0
public:
    float mHue; // offset 0x0, size 0x4
    float mSaturation; // offset 0x4, size 0x4
    float mLightness; // offset 0x8, size 0x4
    float mContrast; // offset 0xC, size 0x4
    float mBrightness; // offset 0x10, size 0x4
    class Color mLevelInLo; // offset 0x20, size 0x10
    class Color mLevelInHi; // offset 0x30, size 0x10
    class Color mLevelOutLo; // offset 0x40, size 0x10
    class Color mLevelOutHi; // offset 0x50, size 0x10
    class Transform mColorXfm; // offset 0x60, size 0x40
};
class RndEnviron : public Object {
    // total size: 0x160
protected:
    class ObjPtrList mLights; // offset 0x28, size 0x14
    class Color mAmbientColor; // offset 0x40, size 0x10
    class ObjOwnerPtr mAmbientFogOwner; // offset 0x50, size 0xC
    unsigned char mFogEnable; // offset 0x5C, size 0x1
    float mFogStart; // offset 0x60, size 0x4
    float mFogEnd; // offset 0x64, size 0x4
    class Color mFogColor; // offset 0x70, size 0x10
    unsigned char mFadeOut; // offset 0x80, size 0x1
    float mFadeStart; // offset 0x84, size 0x4
    float mFadeEnd; // offset 0x88, size 0x4
    float mFadeMax; // offset 0x8C, size 0x4
    class ObjPtr mLRFadeRef; // offset 0x90, size 0xC
    class Vector4 mLRFade; // offset 0xA0, size 0x10
    class RndColorXfm mColorXfm; // offset 0xB0, size 0xA0
    unsigned char mUseColorXfm; // offset 0x150, size 0x1
    unsigned char mAnimateFromPreset; // offset 0x151, size 0x1
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndEnviron * mPtr; // offset 0x8, size 0x4
};
class RndDir : public ObjectDir, public RndDrawable, public RndAnimatable, public RndTransformable, public RndPollable, public MsgSource {
    // total size: 0x230
protected:
    class vector mDraws; // offset 0x1AC, size 0xC
    class vector mAnims; // offset 0x1B8, size 0xC
    class vector mPolls; // offset 0x1C4, size 0xC
    class ObjPtrList mCustomPolls; // offset 0x1D0, size 0x14
    class ObjPtr mEnv; // offset 0x1E4, size 0xC
    class Symbol mTestEvent; // offset 0x1F0, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndDrawable * mPtr; // offset 0x8, size 0x4
};
class RndGroup : public RndAnimatable, public RndDrawable, public RndTransformable {
    // total size: 0x1A0
protected:
    class ObjPtrList mObjects; // offset 0x108, size 0x14
    class ObjPtr mEnv; // offset 0x11C, size 0xC
    class ObjPtr mDrawOnly; // offset 0x128, size 0xC
    class ObjPtr mLod; // offset 0x134, size 0xC
    float mLodScreenSize; // offset 0x140, size 0x4
    class vector mAnims; // offset 0x144, size 0xC
    class vector mDraws; // offset 0x150, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndGroup * mPtr; // offset 0x8, size 0x4
};
class Lod {
    // total size: 0x10
protected:
    float mScreenSize; // offset 0x0, size 0x4
    class ObjPtr mGroup; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Lod * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Lod * _M_start; // offset 0x0, size 0x4
    class Lod * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ShadowBone * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ShadowBone * * _M_start; // offset 0x0, size 0x4
    class ShadowBone * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum PollState {
    kCharCreated = 0,
    kCharSyncObject = 1,
    kCharEntered = 2,
    kCharPolled = 3,
    kCharExited = 4,
};
class Character : public RndDir {
    // total size: 0x2A0
protected:
    class ObjVector mLods; // offset 0x1F4, size 0x10
    int mLastLod; // offset 0x204, size 0x4
    int mMinLod; // offset 0x208, size 0x4
    class ObjPtr mShadow; // offset 0x20C, size 0xC
    class CharDriver * mDriver; // offset 0x218, size 0x4
    class CharWalk * mWalk; // offset 0x21C, size 0x4
    unsigned char mSelfShadow; // offset 0x220, size 0x1
    unsigned char mSpotCutout; // offset 0x221, size 0x1
    unsigned char mFloorShadow; // offset 0x222, size 0x1
    class ObjOwnerPtr mSphereBase; // offset 0x224, size 0xC
    class Sphere mBounding; // offset 0x230, size 0x20
    class vector mShadowBones; // offset 0x250, size 0xC
    enum PollState mPollState; // offset 0x25C, size 0x4
    class CharacterTest * mTest; // offset 0x260, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CompositeCharacter * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class Callback {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RndOverlay : public TextStream {
    // total size: 0x80
    const char * mName; // offset 0x4, size 0x4
    unsigned char mShowing; // offset 0x8, size 0x1
    class list mLines; // offset 0xC, size 0x8
    struct _List_iterator mLine; // offset 0x14, size 0x4
    class Color mColor; // offset 0x20, size 0x10
    int mCursorChar; // offset 0x30, size 0x4
    class Callback * mCallback; // offset 0x34, size 0x4
    class Timer mTimer; // offset 0x38, size 0x38
    float mTimeout; // offset 0x70, size 0x4
};
enum Action {
    kMerge = 0,
    kReplace = 1,
    kKeep = 2,
};
class MergeFilter {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    enum Action mAction; // offset 0x4, size 0x4
};
struct Outfit {
    // total size: 0xC
    const class DataArray * data; // offset 0x0, size 0x4
    int hide; // offset 0x4, size 0x4
    int exclude; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Outfit * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Outfit * _M_start; // offset 0x0, size 0x4
    struct Outfit * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct Category {
    // total size: 0x48
    int selected; // offset 0x0, size 0x4
    const class DataArray * data; // offset 0x4, size 0x4
    int desired; // offset 0x8, size 0x4
    int shown; // offset 0xC, size 0x4
    int current; // offset 0x10, size 0x4
    unsigned char changing; // offset 0x14, size 0x1
    unsigned char changed; // offset 0x15, size 0x1
    class String path; // offset 0x18, size 0xC
    class vector outfits; // offset 0x24, size 0xC
    class ObjPtrList loaded; // offset 0x30, size 0x14
    unsigned char allow_showing; // offset 0x44, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Category * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Category * _M_start; // offset 0x0, size 0x4
    struct Category * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Object * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct LoaderDesc {
    // total size: 0x14
    class FilePath file; // offset 0x0, size 0xC
    struct Category * cat; // offset 0xC, size 0x4
    int outfit; // offset 0x10, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class OutfitLoader : public Object, public Callback, public MergeFilter {
    // total size: 0x70
protected:
    class FilePath mDirectory; // offset 0x34, size 0xC
    class vector mCategories; // offset 0x40, size 0xC
    class DataArray * mExclusions; // offset 0x4C, size 0x4
    unsigned char (* mCanShowCB)(class OutfitLoader *, struct Category *, int); // offset 0x50, size 0x4
    class ObjPtr mMergeBackObj; // offset 0x54, size 0xC
    unsigned char mAsyncLoad; // offset 0x60, size 0x1
    unsigned char mLoadingLoad; // offset 0x61, size 0x1
    class Loader * mCurLoader; // offset 0x64, size 0x4
    class list mFilesPending; // offset 0x68, size 0x8
};
enum ClipMode {
    kClipModeNone = 0,
    kClipModeMeta = 1,
    kClipModeLoadingScreen = 2,
    kClipModeRealtime = 3,
    kClipModeWorld = 4,
    kClipModeFinale = 5,
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class String * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class String * _M_start; // offset 0x0, size 0x4
    class String * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct Triangle {
    // total size: 0xC
    class vector mPoints; // offset 0x0, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Triangle * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Triangle * _M_start; // offset 0x0, size 0x4
    struct Triangle * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class CharDeform {
    // total size: 0x18
    class vector mPoints; // offset 0x0, size 0xC
    class vector mTriangles; // offset 0xC, size 0xC
};
enum Blend {
    kDest = 0,
    kSrc = 1,
    kAdd = 2,
    kSrcAlpha = 3,
    kSrcAlphaAdd = 4,
    kSubtract = 5,
    kMultiply = 6,
    kPreMultAlpha = 7,
};
enum ZMode {
    kDisable = 0,
    kNormal = 1,
    kTransparent = 2,
    kForce = 3,
    kDecal = 4,
};
enum StencilMode {
    kIgnore = 0,
    kWrite = 1,
    kTest = 2,
};
enum TexGen {
    kNone = 0,
    kXfm = 1,
    kSphere = 2,
    kProjected = 3,
    kXfmOrigin = 4,
    kEnviron = 5,
};
enum TexWrap {
    kClamp = 0,
    kRepeat = 1,
    kBorderBlack = 2,
    kBorderWhite = 3,
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMat * mPtr; // offset 0x8, size 0x4
};
struct bf {
    // total size: 0x4
private:
    unsigned int val; // offset 0x0, size 0x4
};
struct bf {
    // total size: 0x4
private:
    unsigned int val; // offset 0x0, size 0x4
};
struct bf {
    // total size: 0x4
private:
    unsigned int val; // offset 0x0, size 0x4
};
union /* @class$35686App_cpp */ {
    struct bf shaderType; // offset 0x0, size 0x4
    struct bf billboard; // offset 0x0, size 0x4
    struct bf skinned; // offset 0x0, size 0x4
    unsigned int value; // offset 0x0, size 0x4
};
struct MatShaderOptions {
    // total size: 0x4
    union { // inferred
        union /* @class$35686App_cpp */ {
            struct bf shaderType; // offset 0x0, size 0x4
            struct bf billboard; // offset 0x0, size 0x4
            struct bf skinned; // offset 0x0, size 0x4
            unsigned int value; // offset 0x0, size 0x4
        } __anon$35687; // offset 0x0, size 0x4
        struct bf shaderType; // offset 0x0, size 0x4
        struct bf billboard; // offset 0x0, size 0x4
        struct bf skinned; // offset 0x0, size 0x4
        unsigned int value; // offset 0x0, size 0x4
    };
};
class RndMat : public Object {
    // total size: 0x120
protected:
    unsigned char mIntensify; // offset 0x28, size 0x1
    enum Blend mBlend; // offset 0x2C, size 0x4
    class Color mColor; // offset 0x30, size 0x10
    unsigned char mUseEnviron; // offset 0x40, size 0x1
    enum ZMode mZMode; // offset 0x44, size 0x4
    enum StencilMode mStencilMode; // offset 0x48, size 0x4
    enum TexGen mTexGen; // offset 0x4C, size 0x4
    enum TexWrap mTexWrap; // offset 0x50, size 0x4
    class Transform mTexXfm; // offset 0x60, size 0x40
    class ObjPtr mDiffuseTex; // offset 0xA0, size 0xC
    unsigned char mPrelit; // offset 0xAC, size 0x1
    unsigned char mAlphaCut; // offset 0xAD, size 0x1
    int mAlphaThresh; // offset 0xB0, size 0x4
    unsigned char mAlphaWrite; // offset 0xB4, size 0x1
    class ObjPtr mNextPass; // offset 0xB8, size 0xC
    unsigned char mCull; // offset 0xC4, size 0x1
    unsigned char mNormalize; // offset 0xC5, size 0x1
    class ObjPtr mCustomDiffuseMap; // offset 0xC8, size 0xC
    unsigned char mTwoColor; // offset 0xD4, size 0x1
    class ObjPtr mTwoColorMask; // offset 0xD8, size 0xC
    class Color mColor1; // offset 0xF0, size 0x10
    class Color mColor2; // offset 0x100, size 0x10
    unsigned char mPointLights; // offset 0x110, size 0x1
    unsigned char mProjLights; // offset 0x111, size 0x1
    unsigned char mFog; // offset 0x112, size 0x1
    unsigned char mFadeout; // offset 0x113, size 0x1
    unsigned char mColorXfm; // offset 0x114, size 0x1
    struct MatShaderOptions mShaderOptions; // offset 0x118, size 0x4
    int mDirty; // offset 0x11C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndMat * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndMat * * _M_start; // offset 0x0, size 0x4
    class RndMat * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndCam * mPtr; // offset 0x8, size 0x4
};
class RndTexRenderer : public RndDrawable, public RndAnimatable {
    // total size: 0xB0
protected:
    unsigned char mDirty; // offset 0x44, size 0x1
    unsigned char mForce; // offset 0x45, size 0x1
    unsigned char mDrawPreClear; // offset 0x46, size 0x1
    unsigned char mDrawWorldOnly; // offset 0x47, size 0x1
    unsigned char mDrawResponsible; // offset 0x48, size 0x1
    float mImposterHeight; // offset 0x4C, size 0x4
    class ObjPtr mOutputTexture; // offset 0x50, size 0xC
    class ObjPtr mDraw; // offset 0x5C, size 0xC
    class ObjPtr mCam; // offset 0x68, size 0xC
    unsigned char mPrimeDraw; // offset 0x74, size 0x1
    unsigned char mFirstDraw; // offset 0x75, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndTexRenderer * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndTexRenderer * * _M_start; // offset 0x0, size 0x4
    class RndTexRenderer * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Color * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Color * _M_start; // offset 0x0, size 0x4
    class Color * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ColorPalette : public Object {
    // total size: 0x34
public:
    class vector mColors; // offset 0x28, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class ColorPalette * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class CharPollable : public RndPollable {
    // total size: 0x34
};
enum Shape {
    kPlane = 0,
    kSphere = 1,
    kInsideSphere = 2,
    kCigar = 3,
    kInsideCigar = 4,
};
class CharCollide : public RndTransformable {
    // total size: 0x110
protected:
    enum Shape mShape; // offset 0xB8, size 0x4
    float mRadius; // offset 0xBC, size 0x4
    float mMaxLength; // offset 0xC0, size 0x4
    float mMinLength; // offset 0xC4, size 0x4
    float mCurRadius; // offset 0xC8, size 0x4
    int mFlags; // offset 0xCC, size 0x4
};
struct Node {
    // total size: 0xC
    class CharCollide * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
struct Point {
    // total size: 0x80
    class Vector3 pos; // offset 0x0, size 0x10
    class Vector3 force; // offset 0x10, size 0x10
    class Vector3 lastFriction; // offset 0x20, size 0x10
    class Vector3 lastZ; // offset 0x30, size 0x10
    class ObjPtr bone; // offset 0x40, size 0xC
    float length; // offset 0x4C, size 0x4
    class ObjPtrList collides; // offset 0x50, size 0x14
    float radius; // offset 0x64, size 0x4
    float outerRadius; // offset 0x68, size 0x4
    float sideLength; // offset 0x6C, size 0x4
    float collide; // offset 0x70, size 0x4
    unsigned char sideCollide; // offset 0x74, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Point * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Point * _M_start; // offset 0x0, size 0x4
    struct Point * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class Strand {
    // total size: 0x90
protected:
    class ObjPtr mRoot; // offset 0x0, size 0xC
    float mAngle; // offset 0xC, size 0x4
    class ObjVector mPoints; // offset 0x10, size 0x10
    class Matrix3 mBaseMat; // offset 0x20, size 0x30
    class Matrix3 mRootMat; // offset 0x50, size 0x30
    int mHookupFlags; // offset 0x80, size 0x4
    unsigned char mShowSpheres; // offset 0x84, size 0x1
    unsigned char mShowCollide; // offset 0x85, size 0x1
    unsigned char mShowPose; // offset 0x86, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Strand * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Strand * _M_start; // offset 0x0, size 0x4
    class Strand * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CharHair : public RndHighlightable, public CharPollable {
    // total size: 0x74
protected:
    float mStiffness; // offset 0x10, size 0x4
    float mTorsion; // offset 0x14, size 0x4
    float mInertia; // offset 0x18, size 0x4
    float mGravity; // offset 0x1C, size 0x4
    float mWeight; // offset 0x20, size 0x4
    float mFriction; // offset 0x24, size 0x4
    float mMinSlack; // offset 0x28, size 0x4
    float mMaxSlack; // offset 0x2C, size 0x4
    class ObjVector mStrands; // offset 0x30, size 0x10
    int mReset; // offset 0x40, size 0x4
    unsigned char mSimulate; // offset 0x44, size 0x1
    unsigned char mUsePostProc; // offset 0x45, size 0x1
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class Vert {
    // total size: 0x40
public:
    class Vector3 p; // offset 0x0, size 0x10
    class Vector3 n; // offset 0x10, size 0x10
    class Color c; // offset 0x20, size 0x10
    class Vector2 t; // offset 0x30, size 0x8
    signed short b0; // offset 0x38, size 0x2
    signed short b1; // offset 0x3A, size 0x2
    signed short b2; // offset 0x3C, size 0x2
    signed short b3; // offset 0x3E, size 0x2
};
class VertVector {
    // total size: 0x8
    class Vert * mVerts; // offset 0x0, size 0x4
    int mNumVerts; // offset 0x4, size 0x4
};
class Face {
    // total size: 0x6
public:
    unsigned short v1; // offset 0x0, size 0x2
    unsigned short v2; // offset 0x2, size 0x2
    unsigned short v3; // offset 0x4, size 0x2
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Face * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Face * _M_start; // offset 0x0, size 0x4
    class Face * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned char * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    unsigned char * _M_start; // offset 0x0, size 0x4
    unsigned char * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMesh * mPtr; // offset 0x8, size 0x4
};
class RndBone {
    // total size: 0x50
public:
    class ObjPtr bone; // offset 0x0, size 0xC
    class Transform offset; // offset 0x10, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndBone * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndBone * _M_start; // offset 0x0, size 0x4
    class RndBone * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
enum Volume {
    kEmpty = 0,
    kTriangles = 1,
    kBSP = 2,
    kBox = 3,
};
class BSPNode {
    // total size: 0x20
public:
    class Plane plane; // offset 0x0, size 0x10
    class BSPNode * front; // offset 0x10, size 0x4
    class BSPNode * back; // offset 0x14, size 0x4
};
struct AdjEdge {
    // total size: 0xC
    unsigned int Ref0; // offset 0x0, size 0x4
    unsigned int Ref1; // offset 0x4, size 0x4
    unsigned int FaceNb; // offset 0x8, size 0x4
};
struct AdjTriangle {
    // total size: 0x18
    unsigned int VRef[3]; // offset 0x0, size 0xC
    unsigned int ATri[3]; // offset 0xC, size 0xC
};
struct ADJACENCIESCREATE {
    // total size: 0xC
    unsigned int NbFaces; // offset 0x0, size 0x4
    unsigned int * DFaces; // offset 0x4, size 0x4
    unsigned short * WFaces; // offset 0x8, size 0x4
};
class Adjacencies {
    // total size: 0x14
    unsigned int mNbEdges; // offset 0x0, size 0x4
    unsigned int mCurrentNbFaces; // offset 0x4, size 0x4
    struct AdjEdge * mEdges; // offset 0x8, size 0x4
public:
    unsigned int mNbFaces; // offset 0xC, size 0x4
    struct AdjTriangle * mFaces; // offset 0x10, size 0x4
};
struct CustomBlock {
    // total size: 0xC
    void * Addy; // offset 0x0, size 0x4
    unsigned long Size; // offset 0x4, size 0x4
    unsigned long Max; // offset 0x8, size 0x4
};
struct CustomCell {
    // total size: 0x10
    struct CustomCell * NextCustomCell; // offset 0x0, size 0x4
    struct CustomBlock Item; // offset 0x4, size 0xC
};
struct __file_modes {
    // total size: 0x4
    unsigned int open_mode : 2; // offset 0x0, size 0x4
    unsigned int io_mode : 3; // offset 0x0, size 0x4
    unsigned int buffer_mode : 2; // offset 0x0, size 0x4
    unsigned int file_kind : 3; // offset 0x0, size 0x4
    unsigned int file_orientation : 2; // offset 0x0, size 0x4
    unsigned int binary_io : 1; // offset 0x0, size 0x4
};
struct __file_state {
    // total size: 0x4
    unsigned int io_state : 3; // offset 0x0, size 0x4
    unsigned int free_buffer : 1; // offset 0x0, size 0x4
    unsigned char eof; // offset 0x1, size 0x1
    unsigned char error; // offset 0x2, size 0x1
};
struct _FILE {
    // total size: 0x50
    unsigned long handle; // offset 0x0, size 0x4
    struct __file_modes mode; // offset 0x4, size 0x4
    struct __file_state state; // offset 0x8, size 0x4
    unsigned char is_dynamically_allocated; // offset 0xC, size 0x1
    unsigned char char_buffer; // offset 0xD, size 0x1
    unsigned char char_buffer_overflow; // offset 0xE, size 0x1
    unsigned char ungetc_buffer[2]; // offset 0xF, size 0x2
    wchar_t ungetwc_buffer[2]; // offset 0x12, size 0x4
    unsigned long position; // offset 0x18, size 0x4
    unsigned char * buffer; // offset 0x1C, size 0x4
    unsigned long buffer_size; // offset 0x20, size 0x4
    unsigned char * buffer_ptr; // offset 0x24, size 0x4
    unsigned long buffer_len; // offset 0x28, size 0x4
    unsigned long buffer_alignment; // offset 0x2C, size 0x4
    unsigned long saved_buffer_len; // offset 0x30, size 0x4
    unsigned long buffer_pos; // offset 0x34, size 0x4
    int (* position_proc)(unsigned long, unsigned long *, int, void *); // offset 0x38, size 0x4
    int (* read_proc)(unsigned long, unsigned char *, unsigned long *, void *); // offset 0x3C, size 0x4
    int (* write_proc)(unsigned long, unsigned char *, unsigned long *, void *); // offset 0x40, size 0x4
    int (* close_proc)(unsigned long); // offset 0x44, size 0x4
    void * ref_con; // offset 0x48, size 0x4
    struct _FILE * next_file_struct; // offset 0x4C, size 0x4
};
class CustomArray {
    // total size: 0x1C
    struct CustomCell * mCurrentCell; // offset 0x0, size 0x4
    struct CustomCell * mInitCell; // offset 0x4, size 0x4
    void * mCollapsed; // offset 0x8, size 0x4
    void * mAddresses; // offset 0xC, size 0x4
    void * mLastAddress; // offset 0x10, size 0x4
    unsigned short mNbPushedAddies; // offset 0x14, size 0x2
    unsigned short mNbAllocatedAddies; // offset 0x16, size 0x2
    unsigned char mBitCount; // offset 0x18, size 0x1
    unsigned char mBitMask; // offset 0x19, size 0x1
};
struct STRIPERRESULT {
    // total size: 0x10
    unsigned int NbStrips; // offset 0x0, size 0x4
    unsigned int * StripLengths; // offset 0x4, size 0x4
    void * StripRuns; // offset 0x8, size 0x4
    unsigned char AskForWords; // offset 0xC, size 0x1
};
struct STRIPERCREATE {
    // total size: 0x10
    unsigned int NbFaces; // offset 0x0, size 0x4
    unsigned int * DFaces; // offset 0x4, size 0x4
    unsigned short * WFaces; // offset 0x8, size 0x4
    unsigned char AskForWords; // offset 0xC, size 0x1
    unsigned char OneSided; // offset 0xD, size 0x1
    unsigned char SGIAlgorithm; // offset 0xE, size 0x1
    unsigned char ConnectAllStrips; // offset 0xF, size 0x1
};
class Striper {
    // total size: 0x20
    class Adjacencies * mAdj; // offset 0x0, size 0x4
    unsigned char * mTags; // offset 0x4, size 0x4
    unsigned int mNbStrips; // offset 0x8, size 0x4
    class CustomArray * mStripLengths; // offset 0xC, size 0x4
    class CustomArray * mStripRuns; // offset 0x10, size 0x4
    unsigned int mTotalLength; // offset 0x14, size 0x4
    class CustomArray * mSingleStrip; // offset 0x18, size 0x4
    unsigned char mAskForWords; // offset 0x1C, size 0x1
    unsigned char mOneSided; // offset 0x1D, size 0x1
    unsigned char mSGIAlgorithm; // offset 0x1E, size 0x1
    unsigned char mConnectAllStrips; // offset 0x1F, size 0x1
};
class RndMesh : public RndDrawable, public RndTransformable {
    // total size: 0x190
protected:
    class VertVector mVerts; // offset 0xF8, size 0x8
    class vector mFaces; // offset 0x100, size 0xC
    class ObjPtr mMat; // offset 0x10C, size 0xC
    class vector mPatches; // offset 0x118, size 0xC
    class ObjOwnerPtr mGeomOwner; // offset 0x124, size 0xC
    class ObjVector mBones; // offset 0x130, size 0x10
    int mMutable; // offset 0x140, size 0x4
    enum Volume mVolume; // offset 0x144, size 0x4
    class BSPNode * mBSPTree; // offset 0x148, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
struct CharGraphNode {
    // total size: 0x8
    float curFrame; // offset 0x0, size 0x4
    float nextFrame; // offset 0x4, size 0x4
};
class NodeVector {
    // total size: 0x10
public:
    class CharClip * clip; // offset 0x0, size 0x4
    int size; // offset 0x4, size 0x4
    struct CharGraphNode nodes[1]; // offset 0x8, size 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharClip * mPtr; // offset 0x8, size 0x4
};
class FrameEvent {
    // total size: 0x8
protected:
    class Symbol mHandler; // offset 0x0, size 0x4
    float mFrame; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class FrameEvent * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class FrameEvent * _M_start; // offset 0x0, size 0x4
    class FrameEvent * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum CompressionType {
    kCompressNone = 0,
    kCompressRots = 1,
    kCompressVects = 2,
    kCompressQuats = 3,
    kCompressAll = 4,
};
struct Bone {
    // total size: 0x8
    class Symbol name; // offset 0x0, size 0x4
    float weight; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Bone * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Bone * _M_start; // offset 0x0, size 0x4
    struct Bone * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct /* @class$33364App_cpp */ {
    // total size: 0x1C
    int mPosCount; // offset 0x0, size 0x4
    int mScaleCount; // offset 0x4, size 0x4
    int mQuatCount; // offset 0x8, size 0x4
    int mRotXCount; // offset 0xC, size 0x4
    int mRotYCount; // offset 0x10, size 0x4
    int mRotZCount; // offset 0x14, size 0x4
    int mEndCount; // offset 0x18, size 0x4
};
union /* @class$33363App_cpp */ {
    int mCounts[7]; // offset 0x0, size 0x1C
    struct /* @class$33364App_cpp */ {
        // total size: 0x1C
        int mPosCount; // offset 0x0, size 0x4
        int mScaleCount; // offset 0x4, size 0x4
        int mQuatCount; // offset 0x8, size 0x4
        int mRotXCount; // offset 0xC, size 0x4
        int mRotYCount; // offset 0x10, size 0x4
        int mRotZCount; // offset 0x14, size 0x4
        int mEndCount; // offset 0x18, size 0x4
    } __anon$33365; // offset 0x0, size 0x1C
    int mPosCount; // offset 0x0, size 0x4
    int mScaleCount; // offset 0x4, size 0x4
    int mQuatCount; // offset 0x8, size 0x4
    int mRotXCount; // offset 0xC, size 0x4
    int mRotYCount; // offset 0x10, size 0x4
    int mRotZCount; // offset 0x14, size 0x4
    int mEndCount; // offset 0x18, size 0x4
};
struct /* @class$33367App_cpp */ {
    // total size: 0x20
    int mPosOffset; // offset 0x0, size 0x4
    int mScaleOffset; // offset 0x4, size 0x4
    int mQuatOffset; // offset 0x8, size 0x4
    int mRotXOffset; // offset 0xC, size 0x4
    int mRotYOffset; // offset 0x10, size 0x4
    int mRotZOffset; // offset 0x14, size 0x4
    int mEndOffset; // offset 0x18, size 0x4
    int mTotalSize; // offset 0x1C, size 0x4
};
union /* @class$33366App_cpp */ {
    int mOffsets[7]; // offset 0x0, size 0x1C
    struct /* @class$33367App_cpp */ {
        // total size: 0x20
        int mPosOffset; // offset 0x0, size 0x4
        int mScaleOffset; // offset 0x4, size 0x4
        int mQuatOffset; // offset 0x8, size 0x4
        int mRotXOffset; // offset 0xC, size 0x4
        int mRotYOffset; // offset 0x10, size 0x4
        int mRotZOffset; // offset 0x14, size 0x4
        int mEndOffset; // offset 0x18, size 0x4
        int mTotalSize; // offset 0x1C, size 0x4
    } __anon$33368; // offset 0x0, size 0x20
    int mPosOffset; // offset 0x0, size 0x4
    int mScaleOffset; // offset 0x4, size 0x4
    int mQuatOffset; // offset 0x8, size 0x4
    int mRotXOffset; // offset 0xC, size 0x4
    int mRotYOffset; // offset 0x10, size 0x4
    int mRotZOffset; // offset 0x14, size 0x4
    int mEndOffset; // offset 0x18, size 0x4
    int mTotalSize; // offset 0x1C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class CharClip * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class CharClip * * _M_start; // offset 0x0, size 0x4
    class CharClip * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum Type {
    TYPE_POS = 0,
    TYPE_SCALE = 1,
    TYPE_QUAT = 2,
    TYPE_ROTX = 3,
    TYPE_ROTY = 4,
    TYPE_ROTZ = 5,
    TYPE_END = 6,
    NUM_TYPES = 7,
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharBone * mPtr; // offset 0x8, size 0x4
};
class CharBone : public RndTransformable {
    // total size: 0x110
protected:
    unsigned char mPosition; // offset 0xB8, size 0x1
    unsigned char mScale; // offset 0xB9, size 0x1
    enum Type mRotation; // offset 0xBC, size 0x4
    float mWeight; // offset 0xC0, size 0x4
    class ObjPtr mTarget; // offset 0xC4, size 0xC
};
struct Node {
    // total size: 0xC
    class CharBone * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Symbol _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class Recenter {
    // total size: 0x3C
protected:
    class ObjPtrList mTargets; // offset 0x0, size 0x14
    class ObjPtrList mAverage; // offset 0x14, size 0x14
    unsigned char mSlide; // offset 0x28, size 0x1
    class list mTargetsSyms; // offset 0x2C, size 0x8
    class list mAverageSyms; // offset 0x34, size 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndDir * mPtr; // offset 0x8, size 0x4
};
struct BoneXfm {
    // total size: 0x50
    class ObjPtr bone; // offset 0x0, size 0xC
    class Transform xfm; // offset 0x10, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BoneXfm * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BoneXfm * _M_start; // offset 0x0, size 0x4
    struct BoneXfm * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CharClipSet : public ObjectDir, public RndDrawable, public RndAnimatable {
    // total size: 0x1F0
protected:
    class vector mClips; // offset 0xC4, size 0xC
    class list mLRU; // offset 0xD0, size 0x8
    class Recenter mRecenter; // offset 0xD8, size 0x3C
    class Symbol mOldType; // offset 0x114, size 0x4
    int mOldVersion; // offset 0x118, size 0x4
    unsigned char mBoneWeights; // offset 0x11C, size 0x1
    unsigned char mMoveSelf; // offset 0x11D, size 0x1
    unsigned char mBakeOutFacing; // offset 0x11E, size 0x1
    class list mBones; // offset 0x120, size 0x8
    class Timer mTimer; // offset 0x128, size 0x38
    class FilePath mCharFilePath; // offset 0x160, size 0xC
    class ObjPtr mPreviewChar; // offset 0x16C, size 0xC
    class ObjPtr mPreviewClip; // offset 0x178, size 0xC
    int mFilterFlags; // offset 0x184, size 0x4
    int mBpm; // offset 0x188, size 0x4
    unsigned char mPreviewWalk; // offset 0x18C, size 0x1
    class ObjPtr mStillClip; // offset 0x190, size 0xC
    class ObjVector mLoadPose; // offset 0x19C, size 0x10
};
struct ByteQuat {
    // total size: 0x4
    char x; // offset 0x0, size 0x1
    char y; // offset 0x1, size 0x1
    char z; // offset 0x2, size 0x1
    char w; // offset 0x3, size 0x1
};
struct ShortQuat {
    // total size: 0x8
    signed short x; // offset 0x0, size 0x2
    signed short y; // offset 0x2, size 0x2
    signed short z; // offset 0x4, size 0x2
    signed short w; // offset 0x6, size 0x2
};
class CharBones {
    // total size: 0x54
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    enum CompressionType mCompression; // offset 0x4, size 0x4
    class vector mBones; // offset 0x8, size 0xC
    char * mStart; // offset 0x14, size 0x4
    union { // inferred
        union /* @class$33363App_cpp */ {
            int mCounts[7]; // offset 0x0, size 0x1C
            struct /* @class$33364App_cpp */ {
                // total size: 0x1C
                int mPosCount; // offset 0x0, size 0x4
                int mScaleCount; // offset 0x4, size 0x4
                int mQuatCount; // offset 0x8, size 0x4
                int mRotXCount; // offset 0xC, size 0x4
                int mRotYCount; // offset 0x10, size 0x4
                int mRotZCount; // offset 0x14, size 0x4
                int mEndCount; // offset 0x18, size 0x4
            } __anon$33365; // offset 0x0, size 0x1C
            int mPosCount; // offset 0x0, size 0x4
            int mScaleCount; // offset 0x4, size 0x4
            int mQuatCount; // offset 0x8, size 0x4
            int mRotXCount; // offset 0xC, size 0x4
            int mRotYCount; // offset 0x10, size 0x4
            int mRotZCount; // offset 0x14, size 0x4
            int mEndCount; // offset 0x18, size 0x4
        } __anon$33369; // offset 0x18, size 0x1C
        int mCounts[7]; // offset 0x18, size 0x1C
        struct /* @class$33364App_cpp */ {
            // total size: 0x1C
            int mPosCount; // offset 0x0, size 0x4
            int mScaleCount; // offset 0x4, size 0x4
            int mQuatCount; // offset 0x8, size 0x4
            int mRotXCount; // offset 0xC, size 0x4
            int mRotYCount; // offset 0x10, size 0x4
            int mRotZCount; // offset 0x14, size 0x4
            int mEndCount; // offset 0x18, size 0x4
        } __anon$33365; // offset 0x18, size 0x1C
        struct { // inferred
            int mPosCount; // offset 0x18, size 0x4
            int mScaleCount; // offset 0x1C, size 0x4
            int mQuatCount; // offset 0x20, size 0x4
            int mRotXCount; // offset 0x24, size 0x4
            int mRotYCount; // offset 0x28, size 0x4
            int mRotZCount; // offset 0x2C, size 0x4
            int mEndCount; // offset 0x30, size 0x4
        };
    };
    union { // inferred
        union /* @class$33366App_cpp */ {
            int mOffsets[7]; // offset 0x0, size 0x1C
            struct /* @class$33367App_cpp */ {
                // total size: 0x20
                int mPosOffset; // offset 0x0, size 0x4
                int mScaleOffset; // offset 0x4, size 0x4
                int mQuatOffset; // offset 0x8, size 0x4
                int mRotXOffset; // offset 0xC, size 0x4
                int mRotYOffset; // offset 0x10, size 0x4
                int mRotZOffset; // offset 0x14, size 0x4
                int mEndOffset; // offset 0x18, size 0x4
                int mTotalSize; // offset 0x1C, size 0x4
            } __anon$33368; // offset 0x0, size 0x20
            int mPosOffset; // offset 0x0, size 0x4
            int mScaleOffset; // offset 0x4, size 0x4
            int mQuatOffset; // offset 0x8, size 0x4
            int mRotXOffset; // offset 0xC, size 0x4
            int mRotYOffset; // offset 0x10, size 0x4
            int mRotZOffset; // offset 0x14, size 0x4
            int mEndOffset; // offset 0x18, size 0x4
            int mTotalSize; // offset 0x1C, size 0x4
        } __anon$33370; // offset 0x34, size 0x20
        int mOffsets[7]; // offset 0x34, size 0x1C
        struct /* @class$33367App_cpp */ {
            // total size: 0x20
            int mPosOffset; // offset 0x0, size 0x4
            int mScaleOffset; // offset 0x4, size 0x4
            int mQuatOffset; // offset 0x8, size 0x4
            int mRotXOffset; // offset 0xC, size 0x4
            int mRotYOffset; // offset 0x10, size 0x4
            int mRotZOffset; // offset 0x14, size 0x4
            int mEndOffset; // offset 0x18, size 0x4
            int mTotalSize; // offset 0x1C, size 0x4
        } __anon$33368; // offset 0x34, size 0x20
        struct { // inferred
            int mPosOffset; // offset 0x34, size 0x4
            int mScaleOffset; // offset 0x38, size 0x4
            int mQuatOffset; // offset 0x3C, size 0x4
            int mRotXOffset; // offset 0x40, size 0x4
            int mRotYOffset; // offset 0x44, size 0x4
            int mRotZOffset; // offset 0x48, size 0x4
            int mEndOffset; // offset 0x4C, size 0x4
            int mTotalSize; // offset 0x50, size 0x4
        };
    };
};
class CharClip : public virtual Object {
    // total size: 0x7C
public:
    void * __vptr$; // offset 0x4, size 0x4
protected:
    class NodeVector * mNodeStart; // offset 0x8, size 0x4
    class NodeVector * mNodeEnd; // offset 0xC, size 0x4
    float mStartFrame; // offset 0x10, size 0x4
    float mEndFrame; // offset 0x14, size 0x4
    float mFramesPerSec; // offset 0x18, size 0x4
    int mFlags; // offset 0x1C, size 0x4
    int mPlayFlags; // offset 0x20, size 0x4
    int mSize; // offset 0x24, size 0x4
    float mBlendWidth; // offset 0x28, size 0x4
    float mRange; // offset 0x2C, size 0x4
    unsigned char mBakeOutFacing; // offset 0x30, size 0x1
    class ObjPtr mRelative; // offset 0x34, size 0xC
    class vector mFrameEvents; // offset 0x40, size 0xC
    unsigned char mDirty; // offset 0x4C, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
struct MatOption {
    // total size: 0x34
    class ObjPtr mMat; // offset 0x0, size 0xC
    class ObjPtr mPrimaryPalette; // offset 0xC, size 0xC
    class ObjPtr mSecondaryPalette; // offset 0x18, size 0xC
    class ObjVector mTexs; // offset 0x24, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
struct ColorOption {
    // total size: 0x10
    int mColorIndex; // offset 0x0, size 0x4
    class ObjList mMatOptions; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ColorOption * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ColorOption * _M_start; // offset 0x0, size 0x4
    struct ColorOption * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class OutfitConfig : public RndPollable {
    // total size: 0x44
    class ObjVector mColors; // offset 0x8, size 0x10
};
class CompositeCharacter : public Character {
    // total size: 0x460
    class ObjPtr mOtherDude; // offset 0x264, size 0xC
    class RndOverlay * mOverlay; // offset 0x270, size 0x4
    int mPlayFlags; // offset 0x274, size 0x4
    unsigned char mHandsActive; // offset 0x278, size 0x1
    unsigned char mHandsEnabled; // offset 0x279, size 0x1
    unsigned char mFrozen; // offset 0x27A, size 0x1
    class CharDriver * mFaceDriver; // offset 0x27C, size 0x4
    class CharDriver * mAddDriver; // offset 0x280, size 0x4
    class CharDriver * mActiveDriver; // offset 0x284, size 0x4
    class OutfitLoader * mOutfitLoader; // offset 0x288, size 0x4
    char mGroupName[64]; // offset 0x28C, size 0x40
    char mGroupOverride[64]; // offset 0x2CC, size 0x40
    char mFaceGroupName[64]; // offset 0x30C, size 0x40
    class Waypoint * mWaypoint; // offset 0x34C, size 0x4
    unsigned char mForceVertical; // offset 0x350, size 0x1
    enum ClipMode mClipMode; // offset 0x354, size 0x4
    class vector mDirectedCuts; // offset 0x358, size 0xC
    class CharDeform mDeform; // offset 0x364, size 0x18
    class vector mSkinMats; // offset 0x37C, size 0xC
    class vector mSkinRenders; // offset 0x388, size 0xC
    int mSkinColorIndex; // offset 0x394, size 0x4
    class ObjPtr mSkinColorPalette; // offset 0x398, size 0xC
    class ObjPtr mSkinTattooPalette; // offset 0x3A4, size 0xC
    int mEyeColorIndex; // offset 0x3B0, size 0x4
    class ObjPtr mEyeColorPalette; // offset 0x3B4, size 0xC
    int mEyebrowColorIndex; // offset 0x3C0, size 0x4
    class Symbol mGender; // offset 0x3C4, size 0x4
    class ObjPtrList mHair; // offset 0x3C8, size 0x14
    unsigned char mForceNextGroup; // offset 0x3DC, size 0x1
    unsigned char mDeformDirty; // offset 0x3DD, size 0x1
    class Symbol mTattooPrefab; // offset 0x3E0, size 0x4
    class Symbol mPrefabName; // offset 0x3E4, size 0x4
    class CharDesc * mPrefab; // offset 0x3E8, size 0x4
    unsigned char mRedrawPrefab; // offset 0x3EC, size 0x1
    unsigned char mForcePoll; // offset 0x3ED, size 0x1
    class ObjPtr mSkinShader; // offset 0x3F0, size 0xC
    float mHeight; // offset 0x3FC, size 0x4
    float mWeight; // offset 0x400, size 0x4
    unsigned char mIsH2hLeft; // offset 0x404, size 0x1
    unsigned char mIsH2hRight; // offset 0x405, size 0x1
    unsigned char mIsCoop; // offset 0x406, size 0x1
    class ObjPtrList mCuffed; // offset 0x408, size 0x14
};
class CharDesc : public virtual Object {
    // total size: 0x4C
public:
    void * __vptr$; // offset 0x4, size 0x4
protected:
    class DataArray * mCharData; // offset 0x8, size 0x4
    class HxGuid mGuid; // offset 0xC, size 0x10
private:
    int mRefs; // offset 0x1C, size 0x4
};
enum Difficulty {
    kDifficultyEasy = 0,
    kDifficultyMedium = 1,
    kDifficultyHard = 2,
    kDifficultyExpert = 3,
    kNumDifficulties = 4,
};
enum ControllerType {
    kControllerDrum = 0,
    kControllerGuitar = 1,
    kControllerVocals = 2,
    kControllerNone = 3,
    kNumControllerTypes = 3,
};
class CharData : public CharDesc {
    // total size: 0x58
protected:
    enum Difficulty mTourWinDiffs[3]; // offset 0x20, size 0xC
};
enum TrackType {
    kTrackDrum = 0,
    kTrackBass = 1,
    kTrackGuitar = 2,
    kTrackVocals = 3,
    kTrackNone = 4,
    kNumTrackTypes = 4,
};
class User : public Object {
    // total size: 0x48
protected:
    class String mUserName; // offset 0x28, size 0xC
private:
    int mUserNum; // offset 0x34, size 0x4
    unsigned int mMachineID; // offset 0x38, size 0x4
    unsigned char mReady; // offset 0x3C, size 0x1
    class OnlineID * mOnlineID; // offset 0x40, size 0x4
    unsigned char mHasOnlineID; // offset 0x44, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BandData * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BandData * * _M_start; // offset 0x0, size 0x4
    class BandData * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Profile : public virtual MsgSource {
    // total size: 0x390
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    enum ProfileSaveState mState; // offset 0x8, size 0x4
    unsigned char mIsActive; // offset 0xC, size 0x1
    unsigned char mDirty; // offset 0xD, size 0x1
    int mPadNum; // offset 0x10, size 0x4
    class vector mChars; // offset 0x14, size 0xC
    class vector mBands; // offset 0x20, size 0xC
    class vector mRemoteBands; // offset 0x2C, size 0xC
    class vector mLessonsLearned; // offset 0x38, size 0xC
    class SoloSongStatusMgr * mSoloSongs; // offset 0x44, size 0x4
    class vector mBeatsLearned; // offset 0x48, size 0xC
    struct BotbNewsCreds mBotbNewsCreds[16]; // offset 0x54, size 0x240
    class vector mUnlockedSongs; // offset 0x294, size 0xC
    class set mUnlockedModifiers; // offset 0x2A0, size 0x18
    class vector mChallenges[4]; // offset 0x2B8, size 0x30
    class PendingBattleScore * mPendingBattleScore; // offset 0x2E8, size 0x4
    class HighScoreSongStatusMgr * mHighScores; // offset 0x2EC, size 0x4
    class OnlineID * mComebackTarget; // offset 0x2F0, size 0x4
    class GameplayOptions mGameplayOptions; // offset 0x2F4, size 0x48
    int mUploadFriendsToken; // offset 0x33C, size 0x4
    unsigned char mHasCheated; // offset 0x340, size 0x1
};
class DataArray {
    // total size: 0x10
    class DataNode * mNodes; // offset 0x0, size 0x4
    class Symbol mFile; // offset 0x4, size 0x4
    signed short mSize; // offset 0x8, size 0x2
    signed short mRefs; // offset 0xA, size 0x2
    signed short mLine; // offset 0xC, size 0x2
    signed short mDeprecated; // offset 0xE, size 0x2
};
union /* @class$5318App_cpp */ {
    const char * symbol; // offset 0x0, size 0x4
    int integer; // offset 0x0, size 0x4
    float real; // offset 0x0, size 0x4
    class DataArray * array; // offset 0x0, size 0x4
    class DataNode * var; // offset 0x0, size 0x4
    class DataNode (* func)(class DataArray *); // offset 0x0, size 0x4
    class Object * object; // offset 0x0, size 0x4
};
class DataArrayPtr {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class DataArray * mData; // offset 0x4, size 0x4
};
class DataNode {
    // total size: 0x8
    union /* @class$5318App_cpp */ {
        const char * symbol; // offset 0x0, size 0x4
        int integer; // offset 0x0, size 0x4
        float real; // offset 0x0, size 0x4
        class DataArray * array; // offset 0x0, size 0x4
        class DataNode * var; // offset 0x0, size 0x4
        class DataNode (* func)(class DataArray *); // offset 0x0, size 0x4
        class Object * object; // offset 0x0, size 0x4
    } mValue; // offset 0x0, size 0x4
    enum DataType mType; // offset 0x4, size 0x4
};
class ObjRef {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__10BandScreen; // size: 0x8, address: 0x8085D1D0
struct {
    // total size: 0xC
} __vt__7Message; // size: 0xC, address: 0x8085D1D8
struct {
    // total size: 0x8
} __RTTI__7Message; // size: 0x8, address: 0x8085D1F0
struct {
    // total size: 0x8
} __RTTI__7UIPanel; // size: 0x8, address: 0x8085D218
struct {
    // total size: 0x8
} __RTTI__8UIScreen; // size: 0x8, address: 0x8085D240
struct {
    // total size: 0x8
} __RTTI__9ObjectDir; // size: 0x8, address: 0x8085D268
struct {
    // total size: 0x8
} __RTTI__9DirLoader; // size: 0x8, address: 0x8085D290
struct {
    // total size: 0x8
} __RTTI__Q23Hmx6Object; // size: 0x8, address: 0x8085D2B0
struct {
    // total size: 0x18
} __vt__6ObjRef; // size: 0x18, address: 0x8085D2B8
struct {
    // total size: 0x8
} __RTTI__6ObjRef; // size: 0x8, address: 0x8085D2D8
struct {
    // total size: 0x8
} __RTTI__6Loader; // size: 0x8, address: 0x8085D2E8
struct {
    // total size: 0x10
} __vt__8FilePath; // size: 0x10, address: 0x8085D2F0
struct {
    // total size: 0x8
} __RTTI__8FilePath; // size: 0x8, address: 0x8085D320
struct {
    // total size: 0x8
} __RTTI__6String; // size: 0x8, address: 0x8085D340
struct {
    // total size: 0x8
} __RTTI__10TextStream; // size: 0x8, address: 0x8085D358
struct Entry {
    // total size: 0x8
    const char * name; // offset 0x0, size 0x4
    class Object * obj; // offset 0x4, size 0x4
};
class KeylessHash {
    // total size: 0x20
    struct Entry * mEntries; // offset 0x0, size 0x4
    int mSize; // offset 0x4, size 0x4
    unsigned char mOwnEntries; // offset 0x8, size 0x1
    int mNumEntries; // offset 0xC, size 0x4
    struct Entry mEmpty; // offset 0x10, size 0x8
    struct Entry mRemoved; // offset 0x18, size 0x8
};
// Range: 0x8000DB6C -> 0x8000DC14
static void __sinit_\App_cpp() {
    // References
    // -> static class ObjDirPtr gCommonLabel3d;
    // -> static class ObjDirPtr gCommonTrack;
    // -> static class ObjDirPtr gCommonBank;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
}

struct {
    // total size: 0x18
} __vt__21ObjDirPtr<9ObjectDir>; // size: 0x18, address: 0x8085D360
struct {
    // total size: 0x8
} __RTTI__21ObjDirPtr<9ObjectDir>; // size: 0x8, address: 0x8085D3A0
class SongPos {
    // total size: 0x14
    float mTotalTick; // offset 0x0, size 0x4
    float mTotalBeat; // offset 0x4, size 0x4
    int mMeasure; // offset 0x8, size 0x4
    int mBeat; // offset 0xC, size 0x4
    int mTick; // offset 0x10, size 0x4
};
class TaskMgr : public Object {
    // total size: 0x88
    class TaskTimeline * mTimelines; // offset 0x28, size 0x4
    class SongPos mSongPos; // offset 0x2C, size 0x14
    unsigned char mAutoSecondsBeats; // offset 0x40, size 0x1
    class Timer mTime; // offset 0x48, size 0x38
    float mAVOffset; // offset 0x80, size 0x4
};
enum WaitType {
    kNone = 0,
    kGoto = 1,
    kPop = 2,
};
enum NetUIState {
    kNetUI_None = 0,
    kNetUI_Synchronized = 1,
    kNetUI_ReadyWorldTour = 2,
    kNetUI_ReadySetChallenges = 3,
    kNetUI_ReadyBotb = 4,
    kNetUI_Matchmaking = 5,
    kNetUI_TourMenu = 6,
    kNetUI_RockShop = 7,
    kNetUI_CreatingArt = 8,
    kNetUI_BandProfile = 9,
    kNetUI_Leaderboards = 10,
    kNetUI_Pause = 11,
    kNetUI_Loading = 12,
    kNetUI_MetaLoading = 13,
    kNetUI_SaveLoad = 14,
    kNetUI_PreAutoSave = 15,
    kNetUI_PostAutoSave = 16,
};
class NetSync : public Object {
    // total size: 0x4C
    unsigned char mTransitionSwitch; // offset 0x28, size 0x1
    unsigned char mSelectSwitch; // offset 0x29, size 0x1
    enum WaitType mInTransition[4]; // offset 0x2C, size 0x10
    class UIScreen * mDestinationScreen; // offset 0x3C, size 0x4
    int mDestinationDepth; // offset 0x40, size 0x4
    unsigned char mUIDisabled; // offset 0x44, size 0x1
    unsigned char mIsForcedTransitionActive; // offset 0x45, size 0x1
    unsigned char mSessionBusy; // offset 0x46, size 0x1
    class LockStepMgr * mLockStepMgr; // offset 0x48, size 0x4
};
class ObjDirPtr : public ObjRef {
    // total size: 0xC
protected:
    class CompositeCharacter * mDir; // offset 0x4, size 0x4
    class DirLoader * mLoader; // offset 0x8, size 0x4
};
class ObjDirPtr : public ObjRef {
    // total size: 0xC
protected:
    class CharClipSet * mDir; // offset 0x4, size 0x4
    class DirLoader * mLoader; // offset 0x8, size 0x4
};
struct CharEntry {
    // total size: 0x50
    enum ControllerType mControllerType; // offset 0x0, size 0x4
    const class CharData * mCharData; // offset 0x4, size 0x4
    class ObjDirPtr mChar; // offset 0x8, size 0xC
    class String mReplaceName; // offset 0x14, size 0xC
    class String mWorldName; // offset 0x20, size 0xC
    class Symbol mTrack; // offset 0x2C, size 0x4
    class ObjPtr mOld; // offset 0x30, size 0xC
    int mLastSelected; // offset 0x3C, size 0x4
    int mLastDir; // offset 0x40, size 0x4
    class ObjDirPtr mClips; // offset 0x44, size 0xC
};
enum Configuration {
    kCharCachePreWorld = 0,
    kCharCacheLoadingLipSync = 1,
    kCharCacheRandomizeClips = 2,
    kCharCacheWorld = 3,
    kCharCacheReclaimed = 4,
    kCharCachePreMeta = 5,
    kCharCachePreMetaWait = 6,
    kCharCacheLoadShellClips = 7,
    kCharCacheMetaWaitFrames = 8,
    kCharCacheMeta = 9,
};
class BandUser : public User {
    // total size: 0xBC
protected:
    enum Difficulty mDifficulty; // offset 0x48, size 0x4
    enum TrackType mTrackType; // offset 0x4C, size 0x4
    enum ControllerType mControllerType; // offset 0x50, size 0x4
    unsigned char mTrackSelected; // offset 0x54, size 0x1
    class CharData * mChar; // offset 0x58, size 0x4
    class GameplayOptions mGameplayOptions; // offset 0x5C, size 0x48
    enum NetUIState mNetUIState; // offset 0xA4, size 0x4
    unsigned char mAutoplay; // offset 0xA8, size 0x1
    class Symbol mPreviousAward; // offset 0xAC, size 0x4
    class Track * mTrack; // offset 0xB0, size 0x4
    class Player * mPlayer; // offset 0xB4, size 0x4
    unsigned char mIsWiiRemoteController; // offset 0xB8, size 0x1
    unsigned char mJustDisconnected; // offset 0xB9, size 0x1
};
class CharCache : public Object {
    // total size: 0xB8
protected:
    struct CharEntry * mEntries[4]; // offset 0x28, size 0x10
    class FileCache * mCache; // offset 0x38, size 0x4
    enum Configuration mConfiguration; // offset 0x3C, size 0x4
    class list mCompressTextures; // offset 0x40, size 0x8
    int mCompressPlayer; // offset 0x48, size 0x4
    int mCompressWait; // offset 0x4C, size 0x4
    unsigned char mEnableCache; // offset 0x50, size 0x1
    class ObjDirPtr mBlink; // offset 0x54, size 0xC
    class ObjDirPtr mPalettes; // offset 0x60, size 0xC
    class ObjDirPtr mMaleNaked; // offset 0x6C, size 0xC
    class ObjDirPtr mMaleTorso; // offset 0x78, size 0xC
    class ObjDirPtr mFemaleNaked; // offset 0x84, size 0xC
    class ObjDirPtr mFemaleTorso; // offset 0x90, size 0xC
    class ObjDirPtr mLipSync; // offset 0x9C, size 0xC
    class vector mSavedPlayers; // offset 0xA8, size 0xC
    int mWaitFrames; // offset 0xB4, size 0x4
};
class WiiNetInit {
    // total size: 0x1740
    unsigned char mThreadStack[4096]; // offset 0x0, size 0x1000
    int mThreadResult; // offset 0x1000, size 0x4
    unsigned char mThreadActive; // offset 0x1004, size 0x1
    struct OSThread mThread; // offset 0x1008, size 0x318
    unsigned char mThreadWaiting; // offset 0x1320, size 0x1
    unsigned short * mProfaneWord[1]; // offset 0x1324, size 0x4
    unsigned short mProfaneChars[501]; // offset 0x1328, size 0x3EA
    char mProfaneResults[10]; // offset 0x1712, size 0xA
    int mProfaneBadNum; // offset 0x171C, size 0x4
    int mProfaneWordCount; // offset 0x1720, size 0x4
    class String mDNSResult; // offset 0x1724, size 0xC
};
class RootObject {
    // total size: 0x1
};
class MutexPrimitive : public RootObject {
    // total size: 0x4
    void * m_hMutex; // offset 0x0, size 0x4
};
class LockChecker : public RootObject {
    // total size: 0x10
    unsigned char m_bLockRestrictionsInUse; // offset 0x0, size 0x1
    unsigned int m_uiLockMask; // offset 0x4, size 0x4
    unsigned int m_uiRecursionLevel; // offset 0x8, size 0x4
    unsigned int m_uiMaximumLockRecursion; // offset 0xC, size 0x4
};
class CriticalSection : public RootObject {
    // total size: 0x14
    class MutexPrimitive m_oMutex; // offset 0x0, size 0x4
    class LockChecker m_oLockChecker; // offset 0x4, size 0x10
};
class RefCountedObject : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned short m_ui16RefCount; // offset 0x4, size 0x2
};
class String : public RootObject {
    // total size: 0x4
    char * m_szContent; // offset 0x0, size 0x4
};
class Buffer : public RefCountedObject {
    // total size: 0x14
protected:
    unsigned char * m_pData; // offset 0x8, size 0x4
    unsigned int m_uiContentSize; // offset 0xC, size 0x4
    unsigned int m_uiBufSize; // offset 0x10, size 0x4
};
class Time : public RootObject {
    // total size: 0x8
    unsigned long long m_ui64Value; // offset 0x0, size 0x8
};
class ByteStream : public RootObject {
    // total size: 0xC
protected:
    unsigned char m_bErrorHasOccured; // offset 0x0, size 0x1
    class Buffer * m_pBuffer; // offset 0x4, size 0x4
    unsigned int m_uiPosition; // offset 0x8, size 0x4
};
class qResult {
    // total size: 0xC
    int m_iReturnCode; // offset 0x0, size 0x4
    const char * m_cszFilename; // offset 0x4, size 0x4
    int m_iLineNumber; // offset 0x8, size 0x4
};
union UserContextStorage {
    unsigned int m_uiValue; // offset 0x0, size 0x4
    float m_dValue; // offset 0x0, size 0x4
    unsigned char m_bValue; // offset 0x0, size 0x1
    void * m_pPointer; // offset 0x0, size 0x4
};
class UserContext : public RootObject {
    // total size: 0x4
    union UserContextStorage m_uContextStorage; // offset 0x0, size 0x4
};
enum Type {
    DO = 1,
    RVAuthentication = 2,
    RVSecure = 3,
    SandBoxMgmt = 4,
    NAT = 5,
    SessionDiscovery = 6,
    NATEcho = 7,
    Routing = 8,
    LastStreamType = 8,
};
class PseudoGlobalVariableList : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class PseudoGlobalVariableRoot : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class PseudoGlobalVariableRoot * m_pNext; // offset 0x4, size 0x4
};
class PluginObject : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class Plugin * m_pPlugin; // offset 0x4, size 0x4
};
class qProtectedList {
    // total size: 0x0
};
class ProfilingUnit : public RootObject {
    // total size: 0x38
    unsigned long long m_oTotalTime; // offset 0x0, size 0x8
    unsigned long long m_oMinTime; // offset 0x8, size 0x8
    unsigned long long m_oMaxTime; // offset 0x10, size 0x8
    unsigned long long m_oLastTime; // offset 0x18, size 0x8
    class Time m_tiStartTime; // offset 0x20, size 0x8
    unsigned int m_uiNbOccurence; // offset 0x28, size 0x4
    unsigned int m_uiLoggingFrequency; // offset 0x2C, size 0x4
    class String m_strName; // offset 0x30, size 0x4
    unsigned char m_bAutoLogEnabled; // offset 0x34, size 0x1
    signed short m_i16LastTracePeriod; // offset 0x36, size 0x2
};
class CompressionAlgorithm : public PluginObject {
    // total size: 0x98
    unsigned int m_uiUncompressedDataSize; // offset 0x8, size 0x4
    unsigned int m_uiCompressedDataSize; // offset 0xC, size 0x4
    class CriticalSection m_csCompression; // offset 0x10, size 0x14
    class ProfilingUnit m_puCompression; // offset 0x28, size 0x38
    class ProfilingUnit m_puDecompression; // offset 0x60, size 0x38
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    unsigned char * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    unsigned char * _M_start; // offset 0x0, size 0x4
    unsigned char * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class Key : public RefCountedObject {
    // total size: 0x14
    class qVector m_vbyData; // offset 0x8, size 0xC
};
class EncryptionAlgorithm : public PluginObject {
    // total size: 0x24
protected:
    class Key m_keyEncryption; // offset 0x8, size 0x14
    unsigned int m_uiMinimumKeyLength; // offset 0x1C, size 0x4
    unsigned int m_uiMaximumKeyLength; // offset 0x20, size 0x4
};
class StreamBundling : public RootObject {
    // total size: 0x18
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned char m_bEnabled; // offset 0x4, size 0x1
    int m_tiAutoFlushPeriod; // offset 0x8, size 0x4
    class Time m_tLastFlushTime; // offset 0x10, size 0x8
};
class StreamSettings : public RootObject {
    // total size: 0x50
    unsigned char m_byChecksumOffset; // offset 0x0, size 0x1
    class CompressionAlgorithm * m_pCompressionAlgorithm; // offset 0x4, size 0x4
    class EncryptionAlgorithm * m_pEncryptionAlgorithm; // offset 0x8, size 0x4
    class StreamBundling m_oStreamBundling; // offset 0x10, size 0x18
    unsigned int m_uiMaxRetransmission; // offset 0x28, size 0x4
    unsigned int m_uiKeepAliveTimeout; // offset 0x2C, size 0x4
    unsigned int m_uiMaxSilenceTime; // offset 0x30, size 0x4
    unsigned int m_uiWindowSize; // offset 0x34, size 0x4
    float m_rRetransmitTimeoutMultiplier; // offset 0x38, size 0x4
    float m_rExtraRetransmitTimeoutMultiplier; // offset 0x3C, size 0x4
    unsigned int m_uiExtraRetransmitTimeoutTrigger; // offset 0x40, size 0x4
    unsigned int m_uiInitialRTT; // offset 0x44, size 0x4
    unsigned int m_uiRTTRetransmit; // offset 0x48, size 0x4
    unsigned char m_bBroadcastEverywhere; // offset 0x4C, size 0x1
    unsigned char m_bActiveFaultDetection; // offset 0x4D, size 0x1
    unsigned char m_bTraceEnable; // offset 0x4E, size 0x1
};
class PseudoGlobalVariable : public PseudoGlobalVariableRoot {
    // total size: 0xB0
    class StreamSettings * m_pValueInContextList; // offset 0x8, size 0x4
    class StreamSettings m_oValueInDefaultContext; // offset 0x10, size 0x50
    class StreamSettings m_oDefaultValue; // offset 0x60, size 0x50
};
class Stream : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    enum Type m_oStreamType; // offset 0x4, size 0x4
};
class InetAddress : public RootObject {
    // total size: 0x80
    unsigned int m_oAddressBytes[32]; // offset 0x0, size 0x80
};
enum _URLType {
    unknown = 0,
    prudp = 1,
    prudps = 2,
    udp = 3,
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class qMap : public map, public RootObject {
    // total size: 0x18
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct _Rb_tree_base_iterator {
    // total size: 0x4
    struct _Rb_tree_node_base * _M_node; // offset 0x0, size 0x4
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class qMap : public map, public RootObject {
    // total size: 0x18
};
class StationURL : public RootObject {
    // total size: 0x58
    class InetAddress * m_pAddr; // offset 0x0, size 0x4
    enum _URLType m_urlType; // offset 0x4, size 0x4
    class qMap m_IntMap; // offset 0x8, size 0x18
    class qMap m_StrMap; // offset 0x20, size 0x18
    class qMap m_UserMap; // offset 0x38, size 0x18
    char * m_szURL; // offset 0x50, size 0x4
    unsigned char m_bDataValid; // offset 0x54, size 0x1
    unsigned char m_bStrValid; // offset 0x55, size 0x1
    unsigned char m_bURLValid; // offset 0x56, size 0x1
};
class TransportEventHandler : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class Links {
    // total size: 0x8
public:
    class PerfCounter * m_pNext; // offset 0x0, size 0x4
    class PerfCounter * m_pPrevious; // offset 0x4, size 0x4
};
class PerfCounter : public RootObject {
    // total size: 0x60
public:
    class Links m_oLinks; // offset 0x0, size 0x8
protected:
    class String m_strName; // offset 0x8, size 0x4
    unsigned int m_uiCurrent[10]; // offset 0xC, size 0x28
    unsigned int m_uiMin; // offset 0x34, size 0x4
    unsigned int m_uiMax; // offset 0x38, size 0x4
    unsigned int m_uiLast; // offset 0x3C, size 0x4
    unsigned int m_uiTotal; // offset 0x40, size 0x4
    class Time m_tLastTime; // offset 0x48, size 0x8
    class Time m_tStarted; // offset 0x50, size 0x8
    unsigned char m_bLogAlways; // offset 0x58, size 0x1
    unsigned char m_bGlobalVariable; // offset 0x59, size 0x1
};
class TransportPerfCounter : public PerfCounter {
    // total size: 0x60
};
class TransportPerfCounters : public RootObject {
    // total size: 0x480
    class TransportPerfCounter m_aPerfCounters[12]; // offset 0x0, size 0x480
};
class EmulationDevice : public RootObject {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    unsigned char m_bEnabled; // offset 0x4, size 0x1
    unsigned int m_uiProtocolHeaderSize; // offset 0x8, size 0x4
    unsigned int m_uiBandwidth; // offset 0xC, size 0x4
    unsigned int m_uiLatency; // offset 0x10, size 0x4
    unsigned int m_uiJitter; // offset 0x14, size 0x4
    float m_rPacketDropProbability; // offset 0x18, size 0x4
};
class OutputEmulationDevice : public EmulationDevice {
    // total size: 0x1C
};
class InputEmulationDevice : public EmulationDevice {
    // total size: 0x1C
};
struct pair {
    // total size: 0x0
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class qSortedVector : public RootObject {
    // total size: 0xC
    class qVector m_v; // offset 0x0, size 0xC
};
class TransportStreamManager : public RootObject {
    // total size: 0x10
    class qSortedVector m_mapVPort; // offset 0x0, size 0xC
    class RootTransport * m_pTransport; // offset 0xC, size 0x4
};
class VirtualNATDevice {
    // total size: 0x0
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class RootTransport : public RootObject {
    // total size: 0x4E8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    unsigned int m_uiMTU; // offset 0x4, size 0x4
    unsigned int m_uiTimeSlice; // offset 0x8, size 0x4
    unsigned char m_bUseUserThreadContext; // offset 0xC, size 0x1
    class TransportPerfCounters m_oPerfCounters; // offset 0x10, size 0x480
    class OutputEmulationDevice m_oOutputEmulationDevice; // offset 0x490, size 0x1C
    class InputEmulationDevice m_oInputEmulationDevice; // offset 0x4AC, size 0x1C
    class TransportStreamManager m_oTransportStreamManager; // offset 0x4C8, size 0x10
    class VirtualNATDevice * m_pVNATDevice; // offset 0x4D8, size 0x4
    unsigned short m_uiPreferredPortNumber; // offset 0x4DC, size 0x2
    class qList m_lstPacketRecognizers; // offset 0x4E0, size 0x8
};
class ConnectionOrientedStream : public Stream {
    // total size: 0x14
protected:
    class TransportEventHandler * m_pEventHandler; // offset 0x8, size 0x4
    class RootTransport * m_pUDPTransport; // offset 0xC, size 0x4
    unsigned char m_idStream; // offset 0x10, size 0x1
};
class EndPointEventHandler : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class EndPoint : public RootObject {
    // total size: 0x74
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class ConnectionOrientedStream * m_pStream; // offset 0x4, size 0x4
    class StationURL m_oStationURL; // offset 0x8, size 0x58
    class EndPointEventHandler * m_pEventHandler; // offset 0x60, size 0x4
    class UserContext m_oContext; // offset 0x64, size 0x4
    unsigned int m_idConnection; // offset 0x68, size 0x4
    unsigned int m_idPrincipal; // offset 0x6C, size 0x4
    unsigned int m_uiOpenCount; // offset 0x70, size 0x4
};
class Message : public ByteStream {
    // total size: 0x30
    class qResult m_rLastError; // offset 0xC, size 0xC
    class Time m_oIOTime; // offset 0x18, size 0x8
    unsigned int m_pidSource; // offset 0x20, size 0x4
    unsigned int m_cidSource; // offset 0x24, size 0x4
    class UserContext m_oContext; // offset 0x28, size 0x4
    class EndPoint * m_pSourceEndPoint; // offset 0x2C, size 0x4
};
class _DDL_Data : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class Data : public _DDL_Data {
    // total size: 0x4
};
class Holder {
    // total size: 0x4
    class Data * m_ptr; // offset 0x0, size 0x4
};
class AnyObjectAdapter {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class AnyObjectHolder : public Holder {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x4, size 0x4
};
class MessagingNotificationHandler : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class WiiMessagingNotificationHandler : public MessagingNotificationHandler {
    // total size: 0x8
public:
    unsigned char mInviteReceived; // offset 0x4, size 0x1
};
enum _State {
    Available = 0,
    CallInProgress = 1,
    CallSuccess = 2,
    CallFailure = 3,
    CallCancelled = 4,
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    class UserContext * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class UserContext * _M_start; // offset 0x0, size 0x4
    class UserContext * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class CallContext : public RefCountedObject {
    // total size: 0x48
protected:
    unsigned int m_uiFlags; // offset 0x8, size 0x4
private:
    enum _State m_eState; // offset 0xC, size 0x4
    class qList m_lstCompletionCallback; // offset 0x10, size 0x8
    class qVector m_vUserContext; // offset 0x18, size 0xC
    class qResult m_rCallOutcome; // offset 0x24, size 0xC
    unsigned int m_uiID; // offset 0x30, size 0x4
    void * m_pDependentConnection; // offset 0x34, size 0x4
    unsigned int m_idConnection; // offset 0x38, size 0x4
    class CallbackRoot * m_pCancellationCallback; // offset 0x3C, size 0x4
    class Time m_tDeadline; // offset 0x40, size 0x8
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    void * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    void * _M_start; // offset 0x0, size 0x4
    void * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class ProtocolCallContext : public CallContext {
    // total size: 0x60
    class qVector m_vReturnValuePtr; // offset 0x48, size 0xC
    unsigned char * m_pbResult; // offset 0x54, size 0x4
    class qResult * m_pqResult; // offset 0x58, size 0x4
};
class DateTime : public RootObject {
    // total size: 0x8
    unsigned long long m_ui64Value; // offset 0x0, size 0x8
};
class _DDL_UserMessage : public Data {
    // total size: 0x30
public:
    unsigned int m_uiID; // offset 0x4, size 0x4
    unsigned int m_idRecipient; // offset 0x8, size 0x4
    unsigned int m_uiRecipientType; // offset 0xC, size 0x4
    unsigned int m_uiParentID; // offset 0x10, size 0x4
    unsigned int m_pidSender; // offset 0x14, size 0x4
    class DateTime m_receptiontime; // offset 0x18, size 0x8
    unsigned int m_uiLifeTime; // offset 0x20, size 0x4
    unsigned int m_uiFlags; // offset 0x24, size 0x4
    class String m_strSubject; // offset 0x28, size 0x4
    class String m_strSender; // offset 0x2C, size 0x4
};
class _DDL_MessageRecipient : public RootObject {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int m_idRecipient; // offset 0x4, size 0x4
    unsigned int m_uiRecipientType; // offset 0x8, size 0x4
};
class UserMessage : public _DDL_UserMessage {
    // total size: 0x30
};
class _List_node : public _List_node_base {
    // total size: 0x38
public:
    class UserMessage _M_data; // offset 0x8, size 0x30
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    class AnyObjectHolder _M_data; // offset 0x8, size 0x8
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
enum FriendType {
    kAllFriends = 0,
    kOnlineFriends = 1,
    kPendingFriends = 2,
};
struct Vec2 {
    // total size: 0x8
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
};
struct MEMAllocatorFunc {
    // total size: 0x8
    void * (* pfAlloc)(struct MEMAllocator *, unsigned long); // offset 0x0, size 0x4
    void (* pfFree)(struct MEMAllocator *, void *); // offset 0x4, size 0x4
};
struct MEMAllocator {
    // total size: 0x10
    const struct MEMAllocatorFunc * pFunc; // offset 0x0, size 0x4
    void * pHeap; // offset 0x4, size 0x4
    unsigned long heapParam1; // offset 0x8, size 0x4
    unsigned long heapParam2; // offset 0xC, size 0x4
};
struct HBMDataInfo {
    // total size: 0x40
    void * layoutBuf; // offset 0x0, size 0x4
    void * spkSeBuf; // offset 0x4, size 0x4
    void * msgBuf; // offset 0x8, size 0x4
    void * configBuf; // offset 0xC, size 0x4
    void * mem; // offset 0x10, size 0x4
    int (* sound_callback)(int, int); // offset 0x14, size 0x4
    int backFlag; // offset 0x18, size 0x4
    int region; // offset 0x1C, size 0x4
    int cursor; // offset 0x20, size 0x4
    int messageFlag; // offset 0x24, size 0x4
    unsigned long configBufSize; // offset 0x28, size 0x4
    unsigned long memSize; // offset 0x2C, size 0x4
    float frameDelta; // offset 0x30, size 0x4
    struct Vec2 adjust; // offset 0x34, size 0x8
    struct MEMAllocator * pAllocator; // offset 0x3C, size 0x4
};
struct Vec {
    // total size: 0xC
    float x; // offset 0x0, size 0x4
    float y; // offset 0x4, size 0x4
    float z; // offset 0x8, size 0x4
};
struct /* @class$15292App_cpp */ {
    // total size: 0x1C
    struct Vec2 stick; // offset 0x0, size 0x8
    struct Vec acc; // offset 0x8, size 0xC
    float acc_value; // offset 0x14, size 0x4
    float acc_speed; // offset 0x18, size 0x4
};
struct /* @class$15293App_cpp */ {
    // total size: 0x24
    unsigned long hold; // offset 0x0, size 0x4
    unsigned long trig; // offset 0x4, size 0x4
    unsigned long release; // offset 0x8, size 0x4
    struct Vec2 lstick; // offset 0xC, size 0x8
    struct Vec2 rstick; // offset 0x14, size 0x8
    float ltrigger; // offset 0x1C, size 0x4
    float rtrigger; // offset 0x20, size 0x4
};
union KPADEXStatus {
    struct /* @class$15292App_cpp */ {
        // total size: 0x1C
        struct Vec2 stick; // offset 0x0, size 0x8
        struct Vec acc; // offset 0x8, size 0xC
        float acc_value; // offset 0x14, size 0x4
        float acc_speed; // offset 0x18, size 0x4
    } fs; // offset 0x0, size 0x1C
    struct /* @class$15293App_cpp */ {
        // total size: 0x24
        unsigned long hold; // offset 0x0, size 0x4
        unsigned long trig; // offset 0x4, size 0x4
        unsigned long release; // offset 0x8, size 0x4
        struct Vec2 lstick; // offset 0xC, size 0x8
        struct Vec2 rstick; // offset 0x14, size 0x8
        float ltrigger; // offset 0x1C, size 0x4
        float rtrigger; // offset 0x20, size 0x4
    } cl; // offset 0x0, size 0x24
};
struct KPADStatus {
    // total size: 0x84
    unsigned long hold; // offset 0x0, size 0x4
    unsigned long trig; // offset 0x4, size 0x4
    unsigned long release; // offset 0x8, size 0x4
    struct Vec acc; // offset 0xC, size 0xC
    float acc_value; // offset 0x18, size 0x4
    float acc_speed; // offset 0x1C, size 0x4
    struct Vec2 pos; // offset 0x20, size 0x8
    struct Vec2 vec; // offset 0x28, size 0x8
    float speed; // offset 0x30, size 0x4
    struct Vec2 horizon; // offset 0x34, size 0x8
    struct Vec2 hori_vec; // offset 0x3C, size 0x8
    float hori_speed; // offset 0x44, size 0x4
    float dist; // offset 0x48, size 0x4
    float dist_vec; // offset 0x4C, size 0x4
    float dist_speed; // offset 0x50, size 0x4
    struct Vec2 acc_vertical; // offset 0x54, size 0x8
    unsigned char dev_type; // offset 0x5C, size 0x1
    signed char wpad_err; // offset 0x5D, size 0x1
    signed char dpd_valid_fg; // offset 0x5E, size 0x1
    unsigned char data_format; // offset 0x5F, size 0x1
    union KPADEXStatus ex_status; // offset 0x60, size 0x24
};
struct HBMKPadData {
    // total size: 0x10
    struct KPADStatus * kpad; // offset 0x0, size 0x4
    struct Vec2 pos; // offset 0x4, size 0x8
    unsigned long use_devtype; // offset 0xC, size 0x4
};
struct HBMControllerData {
    // total size: 0x40
    struct HBMKPadData wiiCon[4]; // offset 0x0, size 0x40
};
enum _GXTexWrapMode {
    GX_CLAMP = 0,
    GX_REPEAT = 1,
    GX_MIRROR = 2,
    GX_MAX_TEXWRAPMODE = 3,
};
enum _GXTexFilter {
    GX_NEAR = 0,
    GX_LINEAR = 1,
    GX_NEAR_MIP_NEAR = 2,
    GX_LIN_MIP_NEAR = 3,
    GX_NEAR_MIP_LIN = 4,
    GX_LIN_MIP_LIN = 5,
};
struct TPLHeader {
    // total size: 0x24
    unsigned short height; // offset 0x0, size 0x2
    unsigned short width; // offset 0x2, size 0x2
    unsigned long format; // offset 0x4, size 0x4
    char * data; // offset 0x8, size 0x4
    enum _GXTexWrapMode wrapS; // offset 0xC, size 0x4
    enum _GXTexWrapMode wrapT; // offset 0x10, size 0x4
    enum _GXTexFilter minFilter; // offset 0x14, size 0x4
    enum _GXTexFilter magFilter; // offset 0x18, size 0x4
    float LODBias; // offset 0x1C, size 0x4
    unsigned char edgeLODEnable; // offset 0x20, size 0x1
    unsigned char minLOD; // offset 0x21, size 0x1
    unsigned char maxLOD; // offset 0x22, size 0x1
    unsigned char unpacked; // offset 0x23, size 0x1
};
enum _GXTlutFmt {
    GX_TL_IA8 = 0,
    GX_TL_RGB565 = 1,
    GX_TL_RGB5A3 = 2,
    GX_MAX_TLUTFMT = 3,
};
struct TPLClutHeader {
    // total size: 0xC
    unsigned short numEntries; // offset 0x0, size 0x2
    unsigned char unpacked; // offset 0x2, size 0x1
    unsigned char pad8; // offset 0x3, size 0x1
    enum _GXTlutFmt format; // offset 0x4, size 0x4
    char * data; // offset 0x8, size 0x4
};
struct TPLDescriptor {
    // total size: 0x8
    struct TPLHeader * textureHeader; // offset 0x0, size 0x4
    struct TPLClutHeader * CLUTHeader; // offset 0x4, size 0x4
};
struct TPLPalette {
    // total size: 0xC
    unsigned long versionNumber; // offset 0x0, size 0x4
    unsigned long numDescriptors; // offset 0x4, size 0x4
    struct TPLDescriptor * descriptorArray; // offset 0x8, size 0x4
};
class HomeMenu {
    // total size: 0x21C4
    struct HBMDataInfo mHomeMenuInfo; // offset 0x0, size 0x40
    struct HBMControllerData mControllerData; // offset 0x40, size 0x40
    unsigned char mAllowHomeMenu; // offset 0x80, size 0x1
    unsigned char mHomeMenuActive; // offset 0x81, size 0x1
    unsigned char mSoundActive; // offset 0x82, size 0x1
    unsigned char mInGame; // offset 0x83, size 0x1
    unsigned char mForcedHomeMenu; // offset 0x84, size 0x1
    int mHomeMenuLocked; // offset 0x88, size 0x4
    int mCountdown; // offset 0x8C, size 0x4
    unsigned char mBanIconActive; // offset 0x90, size 0x1
    signed char mBanIconMode; // offset 0x91, size 0x1
    unsigned long mBanIconTime; // offset 0x94, size 0x4
    struct TPLPalette * mIconTpl; // offset 0x98, size 0x4
    unsigned char mBanIconAlpha; // offset 0x9C, size 0x1
    unsigned char * mSoundBuf; // offset 0xA0, size 0x4
    unsigned char * mSoundData; // offset 0xA4, size 0x4
    float mLastProjection[7]; // offset 0xA8, size 0x1C
    struct KPADStatus mHomeMenuPadStatus[4][16]; // offset 0xC4, size 0x2100
};
struct ECRating {
    // total size: 0x10
    char * name; // offset 0x0, size 0x4
    char * rating; // offset 0x4, size 0x4
    long age; // offset 0x8, size 0x4
    char * descriptors; // offset 0xC, size 0x4
};
struct ECMoney {
    // total size: 0x40
    char amount[32]; // offset 0x0, size 0x20
    char currency[32]; // offset 0x20, size 0x20
};
struct ESLpEntry {
    // total size: 0x8
    unsigned long code; // offset 0x0, size 0x4
    unsigned long limit; // offset 0x4, size 0x4
};
struct ECLicensePricing {
    // total size: 0x8C
    long itemId; // offset 0x0, size 0x4
    struct ECMoney price; // offset 0x4, size 0x40
    struct ESLpEntry limits[8]; // offset 0x44, size 0x40
    unsigned long nLimits; // offset 0x84, size 0x4
    unsigned long licenseType; // offset 0x88, size 0x4
};
struct ECNameValuePair {
    // total size: 0x8
    char * name; // offset 0x0, size 0x4
    char * value; // offset 0x4, size 0x4
};
struct ECContentCatalogInfo {
    // total size: 0x30
    unsigned long long titleId; // offset 0x0, size 0x8
    struct ECRating * ratings; // offset 0x8, size 0x4
    unsigned long nRatings; // offset 0xC, size 0x4
    struct ECLicensePricing * licensePricings; // offset 0x10, size 0x4
    unsigned long nLicensePricings; // offset 0x14, size 0x4
    struct ECNameValuePair * attributes; // offset 0x18, size 0x4
    unsigned long nAttributes; // offset 0x1C, size 0x4
    long isTitleIncluded; // offset 0x20, size 0x4
    unsigned short * indexes; // offset 0x24, size 0x4
    unsigned long nIndexes; // offset 0x28, size 0x4
};
struct ECContentInfo {
    // total size: 0x10
    unsigned long flags; // offset 0x0, size 0x4
    unsigned short index; // offset 0x4, size 0x2
    unsigned short type; // offset 0x6, size 0x2
    unsigned long long size; // offset 0x8, size 0x8
};
struct DVDDiskID {
    // total size: 0x20
    char gameName[4]; // offset 0x0, size 0x4
    char company[2]; // offset 0x4, size 0x2
    unsigned char diskNumber; // offset 0x6, size 0x1
    unsigned char gameVersion; // offset 0x7, size 0x1
    unsigned char streaming; // offset 0x8, size 0x1
    unsigned char streamingBufSize; // offset 0x9, size 0x1
    unsigned char padding[14]; // offset 0xA, size 0xE
    unsigned long rvlMagic; // offset 0x18, size 0x4
    unsigned long gcMagic; // offset 0x1C, size 0x4
};
struct DVDCommandBlock {
    // total size: 0x30
    struct DVDCommandBlock * next; // offset 0x0, size 0x4
    struct DVDCommandBlock * prev; // offset 0x4, size 0x4
    unsigned long command; // offset 0x8, size 0x4
    long state; // offset 0xC, size 0x4
    unsigned long offset; // offset 0x10, size 0x4
    unsigned long length; // offset 0x14, size 0x4
    void * addr; // offset 0x18, size 0x4
    unsigned long currTransferSize; // offset 0x1C, size 0x4
    unsigned long transferredSize; // offset 0x20, size 0x4
    struct DVDDiskID * id; // offset 0x24, size 0x4
    void (* callback)(long, struct DVDCommandBlock *); // offset 0x28, size 0x4
    void * userData; // offset 0x2C, size 0x4
};
struct DVDFileInfo {
    // total size: 0x3C
    struct DVDCommandBlock cb; // offset 0x0, size 0x30
    unsigned long startAddr; // offset 0x30, size 0x4
    unsigned long length; // offset 0x34, size 0x4
    void (* callback)(long, struct DVDFileInfo *); // offset 0x38, size 0x4
};
class DiscErrorMgrWii {
    // total size: 0xC
    unsigned char mDiscError; // offset 0x0, size 0x1
    unsigned char mRetryError; // offset 0x1, size 0x1
    unsigned char mMovieReadError; // offset 0x2, size 0x1
    unsigned char mActive; // offset 0x3, size 0x1
    struct TPLPalette * mEjectErrorTpl; // offset 0x4, size 0x4
    struct TPLPalette * mRetryErrorTpl; // offset 0x8, size 0x4
};
class PlatformMgr : public MsgSource {
    // total size: 0x21B0
    int mSigninMask; // offset 0x1C, size 0x4
    int mSigninChangeMask; // offset 0x20, size 0x4
    int mSigninSameGuest; // offset 0x24, size 0x4
    void * mListener; // offset 0x28, size 0x4
    void * mFriendsEnum; // offset 0x2C, size 0x4
    void * mFriendsBuffer; // offset 0x30, size 0x4
    void * mFriendsAsync; // offset 0x34, size 0x4
    class Object * mFriendsCallback; // offset 0x38, size 0x4
    class vector * mFriendsList; // offset 0x3C, size 0x4
    unsigned char mXboxGuideShowing; // offset 0x40, size 0x1
    unsigned char mConfirmCancelSwapped; // offset 0x41, size 0x1
    unsigned char mConnected; // offset 0x42, size 0x1
    class UIPanel * mOverflowDialog; // offset 0x44, size 0x4
    unsigned char mDisabling; // offset 0x48, size 0x1
    unsigned char mJoypadOverflow; // offset 0x49, size 0x1
    unsigned char mMediaInserted; // offset 0x4A, size 0x1
    void * mSDBuffer; // offset 0x4C, size 0x4
    unsigned char mAllowAddFriend; // offset 0x50, size 0x1
    unsigned char mIsConnecting; // offset 0x51, size 0x1
    int mLastNetResult; // offset 0x54, size 0x4
    class WiiNetInit * mWiiNetInit; // offset 0x58, size 0x4
    unsigned char mNetCapable; // offset 0x5C, size 0x1
    class WiiMessagingNotificationHandler mMessagingHandler; // offset 0x60, size 0x8
    unsigned char mMessagingEnum; // offset 0x68, size 0x1
    class ProtocolCallContext * mMessagingContext; // offset 0x6C, size 0x4
    class Object * mMessagingCallback; // offset 0x70, size 0x4
    class vector * mMessagingList; // offset 0x74, size 0x4
    class qList mUserMessages; // offset 0x78, size 0x8
    class qList mMessages; // offset 0x80, size 0x8
    class ProtocolCallContext * mFriendsContext; // offset 0x88, size 0x4
    class qList mUserFriends; // offset 0x8C, size 0x8
    enum FriendType mFriendTypeRequested; // offset 0x94, size 0x4
    class ProtocolCallContext * mDummyContext; // offset 0x98, size 0x4
    class HomeMenu * mHomeMenuWii; // offset 0x9C, size 0x4
    unsigned char bCommerceOnline; // offset 0xA0, size 0x1
    long mCommerceAsyncOpId; // offset 0xA4, size 0x4
    char * mCommerceAsyncName; // offset 0xA8, size 0x4
    class Timer mCommerceTimeout; // offset 0xB0, size 0x38
    long opId; // offset 0xE8, size 0x4
    unsigned long long mTitleId; // offset 0xF0, size 0x8
    struct ECContentCatalogInfo * pContentSet; // offset 0xF8, size 0x4
    long price; // offset 0xFC, size 0x4
    char * attributes[6]; // offset 0x100, size 0x18
    unsigned long attributesNum; // offset 0x118, size 0x4
    unsigned long titleIdsNum; // offset 0x11C, size 0x4
    struct ECContentCatalogInfo * contentSets; // offset 0x120, size 0x4
    unsigned long contentSetsNum; // offset 0x124, size 0x4
    struct ECContentInfo * contents; // offset 0x128, size 0x4
    unsigned long size; // offset 0x12C, size 0x4
    void * buf; // offset 0x130, size 0x4
    unsigned long bufSize; // offset 0x134, size 0x4
    unsigned long total; // offset 0x138, size 0x4
    struct ECNameValuePair filters; // offset 0x13C, size 0x8
    unsigned long filtersNum; // offset 0x144, size 0x4
    char tempIndex[4]; // offset 0x148, size 0x4
    int mCommercePercent; // offset 0x14C, size 0x4
    unsigned char mCommerceSongsUpdated; // offset 0x150, size 0x1
    int mCommerceLastErrorCode; // offset 0x154, size 0x4
    unsigned char mCommerceActive; // offset 0x158, size 0x1
    unsigned char mCommercePCActive; // offset 0x159, size 0x1
    struct ECContentInfo mServerContents[512]; // offset 0x160, size 0x2000
    unsigned long mNumContents; // offset 0x2160, size 0x4
    unsigned char mFirstPoll; // offset 0x2164, size 0x1
    class Object * mCommerceCallback; // offset 0x2168, size 0x4
    class map * mContentList; // offset 0x216C, size 0x4
    class DiscErrorMgrWii mDiscErrorMgr; // offset 0x2170, size 0xC
    unsigned char mNetworkPlay; // offset 0x217C, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct JoypadRepeat {
    // total size: 0x80
    enum JoypadButton mLastBtn; // offset 0x0, size 0x4
    enum JoypadAction mLastAction; // offset 0x4, size 0x4
    int mLastPad; // offset 0x8, size 0x4
    class Timer mHoldTimer; // offset 0x10, size 0x38
    class Timer mRepeatTimer; // offset 0x48, size 0x38
};
class JoypadClient : public Object {
    // total size: 0x448
    int mUser; // offset 0x28, size 0x4
    class Object * mSink; // offset 0x2C, size 0x4
    int mBtnMask; // offset 0x30, size 0x4
    float mHoldMs; // offset 0x34, size 0x4
    float mRepeatMs; // offset 0x38, size 0x4
    struct JoypadRepeat mRepeats[8]; // offset 0x40, size 0x400
    unsigned char mVirtualDpad; // offset 0x440, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class UISink : public virtual Object {
    // total size: 0x34
public:
    void * __vptr$; // offset 0x4, size 0x4
};
class UIManager : public Object {
    // total size: 0xE8
    enum TransitionState mTransitionState; // offset 0x28, size 0x4
    unsigned char mWentBack; // offset 0x2C, size 0x1
    class list mPushedScreens; // offset 0x30, size 0x8
    int mMaxPushDepth; // offset 0x38, size 0x4
    class JoypadClient * mJoyClient; // offset 0x3C, size 0x4
    class UIScreen * mCurrentScreen; // offset 0x40, size 0x4
    class UIScreen * mTransitionScreen; // offset 0x44, size 0x4
    class list mResources; // offset 0x48, size 0x8
    class UISink * mSink; // offset 0x50, size 0x4
    class RndCam * mCam; // offset 0x54, size 0x4
    class RndEnviron * mEnv; // offset 0x58, size 0x4
    class Timer mTimer; // offset 0x60, size 0x38
    unsigned char mOverloadHorizontalNav; // offset 0x98, size 0x1
    unsigned char mCancelTransitionNotify; // offset 0x99, size 0x1
    class Timer mLoadTimer; // offset 0xA0, size 0x38
    class RndOverlay * mOverlay; // offset 0xD8, size 0x4
    unsigned char mRequireFixedText; // offset 0xDC, size 0x1
    class Automator * mAutomator; // offset 0xE0, size 0x4
};
class InviteAcceptedMsg : public Message {
    // total size: 0x8
};
class ConnectionStatusChangedMsg : public Message {
    // total size: 0x8
};
class DiskErrorMsg : public Message {
    // total size: 0x8
};
class BandUI : public UISink, public MsgSource {
    // total size: 0x84
    class DataArray * mEventType; // offset 0x24, size 0x4
    unsigned char mInviteAccepted; // offset 0x28, size 0x1
    unsigned char mHideEvent; // offset 0x29, size 0x1
    unsigned char mHandleRemotePlayerLeft; // offset 0x2A, size 0x1
    class Symbol mLastDisbandError; // offset 0x2C, size 0x4
    class String mContentName; // offset 0x30, size 0xC
    class UIPanel * mFXPanel; // offset 0x3C, size 0x4
    class UIPanel * mHelpbar; // offset 0x40, size 0x4
    class UIPanel * mEventDialog; // offset 0x44, size 0x4
    class UIPanel * mNetworkBusyPanel; // offset 0x48, size 0x4
    class UIPanel * mContentLoadingPanel; // offset 0x4C, size 0x4
    class UIPanel * mPassiveMessagesPanel; // offset 0x50, size 0x4
    unsigned char mTransitionCompleteSwitch; // offset 0x54, size 0x1
    unsigned char mEventDialogShowing; // offset 0x55, size 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    void (* _M_data)(); // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class Debug : public TextStream {
    // total size: 0xFC
    unsigned char mFailing; // offset 0x4, size 0x1
    unsigned char mExiting; // offset 0x5, size 0x1
    unsigned char mNoTry; // offset 0x6, size 0x1
    unsigned char mNoModal; // offset 0x7, size 0x1
    int mTry; // offset 0x8, size 0x4
    class TextFileStream * mLog; // offset 0xC, size 0x4
    unsigned char mAlwaysFlush; // offset 0x10, size 0x1
    class TextStream * mReflect; // offset 0x14, size 0x4
    void (* mModalCallback)(unsigned char &, char *, unsigned char); // offset 0x18, size 0x4
    class list mFailCallbacks; // offset 0x1C, size 0x8
    class list mExitCallbacks; // offset 0x24, size 0x8
    unsigned int mFailThreadStack[50]; // offset 0x2C, size 0xC8
    const char * mFailThreadMsg; // offset 0xF4, size 0x4
    const char * mNotifyThreadMsg; // offset 0xF8, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Loader * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class LoadMgr {
    // total size: 0x60
    class list mLoaders; // offset 0x0, size 0x8
    enum Platform mPlatform; // offset 0x8, size 0x4
    unsigned char mCacheMode; // offset 0xC, size 0x1
    unsigned char mEditMode; // offset 0xD, size 0x1
    class list mFactories; // offset 0x10, size 0x8
    float mPeriod; // offset 0x18, size 0x4
    class list mLoading; // offset 0x1C, size 0x8
    class Timer mTimer; // offset 0x28, size 0x38
};
enum /* @enum$38436App_cpp */ {
    kInactive = 0,
    kPlatformChecking = 1,
    kPlatformChecked = 2,
    kServerWait = 3,
    kServerTimeout = 4,
    kServerDone = 5,
};
enum /* @enum$38437App_cpp */ {
    kNone = 0,
    kBandNameCheck = 1,
    kBandMottoCheck = 2,
    kCharNameCheck = 3,
    kUpdateChar = 4,
    kUpdateBand = 5,
    kProfileUpload = 6,
};
class TourSavable : public virtual Object {
    // total size: 0x40
public:
    void * __vptr$; // offset 0x4, size 0x4
private:
    unsigned char mDirtySave; // offset 0x8, size 0x1
    unsigned char mDirtyUpload; // offset 0x9, size 0x1
    unsigned char mDirtyUploadSec; // offset 0xA, size 0x1
    struct DateTime mLastUpload; // offset 0xB, size 0x6
    unsigned char mNameUnchecked; // offset 0x11, size 0x1
    unsigned char mMottoUnchecked; // offset 0x12, size 0x1
};
class EntityUploader : public Object {
    // total size: 0x48
protected:
    enum /* @enum$38436App_cpp */ {
        kInactive = 0,
        kPlatformChecking = 1,
        kPlatformChecked = 2,
        kServerWait = 3,
        kServerTimeout = 4,
        kServerDone = 5,
    } mState; // offset 0x28, size 0x4
    enum /* @enum$38437App_cpp */ {
        kNone = 0,
        kBandNameCheck = 1,
        kBandMottoCheck = 2,
        kCharNameCheck = 3,
        kUpdateChar = 4,
        kUpdateBand = 5,
        kProfileUpload = 6,
    } mCallType; // offset 0x2C, size 0x4
    class DataArray * mUploadOps; // offset 0x30, size 0x4
    class DataArray * mEmptyArray; // offset 0x34, size 0x4
    class Object * mCallbackObj; // offset 0x38, size 0x4
private:
    struct DateTime mSubmittedTime; // offset 0x3C, size 0x6
    int mOpIdGenerator; // offset 0x44, size 0x4
};
enum /* @enum$12402App_cpp */ {
    kOffline = 0,
    kConnecting = 1,
    kOnline = 2,
    kDisconnecting = 3,
    kFailed = 4,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class Job {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    int mID; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class JobMgr {
    // total size: 0x10
    class Object * mCallback; // offset 0x0, size 0x4
    class list mJobQueue; // offset 0x4, size 0x8
    unsigned char mPreventStart; // offset 0xC, size 0x1
};
class Updatable {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class ContextWrapper * mContextWrapper; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class BotbBattlesParticipatedInRow {
    // total size: 0x28
    int mBattleID; // offset 0x0, size 0x4
    class String mBattleName; // offset 0x4, size 0xC
    int mBandRank; // offset 0x10, size 0x4
    unsigned char mBattleOpen; // offset 0x14, size 0x1
    class String mArtFilename; // offset 0x18, size 0xC
    int mNumPostedScores; // offset 0x24, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class BotbBattlesParticipatedInList : public Updatable {
    // total size: 0x18
    class list mBotbBattlesParticipatedInRowList; // offset 0x8, size 0x8
    class RBBotbBattlesParticipatedInQList * mQList; // offset 0x10, size 0x4
    unsigned char mUpdated; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class BotbNewsRow {
    // total size: 0x18
    class String mNewsItem; // offset 0x0, size 0xC
    class String mArtFilename; // offset 0xC, size 0xC
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class BotbNewsList : public Updatable {
    // total size: 0x34
    class list mBotbNewsRowList; // offset 0x8, size 0x8
    class RBBotbNewsQList * mQList; // offset 0x10, size 0x4
    class DateTime * mQDateTime; // offset 0x14, size 0x4
    struct DateTime mDateTime; // offset 0x18, size 0x6
    class String * mQCookies; // offset 0x20, size 0x4
    class String mCookies; // offset 0x24, size 0xC
    unsigned char mUpdated; // offset 0x30, size 0x1
};
class BotbRecordBattleResponse {
    // total size: 0x4
    class RBBotbRecordBattleResponse * mRecordBattleResponse; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class BotbBattleResultsRow {
    // total size: 0x34
    class String mName; // offset 0x0, size 0xC
    int mScore; // offset 0xC, size 0x4
    int mStars; // offset 0x10, size 0x4
    int mOverallRank; // offset 0x14, size 0x4
    class HxGuid mBandGuid; // offset 0x18, size 0x10
    class String mLogoName; // offset 0x28, size 0xC
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class BotbBattleResultsList : public Updatable {
    // total size: 0x18
    class list mBotbBattleResultsRowList; // offset 0x8, size 0x8
    class RBBotbBattleResultsQList * mQList; // offset 0x10, size 0x4
    unsigned char mUpdated; // offset 0x14, size 0x1
};
class BotbPlayBattleResponse {
    // total size: 0x14
    class RBBotbPlayBattleResponse * mPlayBattleResponse; // offset 0x0, size 0x4
    class OnlineID mOnlineID; // offset 0x4, size 0x10
};
class BotbBattleResultsByBandInfo {
    // total size: 0x4
    class RBBotbBattleResultsByBandInfo * mBattleResultsByBandInfo; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class BotbOpenBattleRow {
    // total size: 0x44
    int mBattleID; // offset 0x0, size 0x4
    class String mShortName; // offset 0x4, size 0xC
    class String mTitle; // offset 0x10, size 0xC
    unsigned char mAlreadyPlayed; // offset 0x1C, size 0x1
    class String mShowIn; // offset 0x20, size 0xC
    class String mVenue; // offset 0x2C, size 0xC
    class String mArtFilename; // offset 0x38, size 0xC
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class BotbOpenBattlesList : public Updatable {
    // total size: 0x18
    class list mBotbOpenBattlesRowList; // offset 0x8, size 0x8
    class RBBotbOpenBattlesQList * mQList; // offset 0x10, size 0x4
    unsigned char mUpdated; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class BotbBattleSongInfo {
    // total size: 0x24
    class String mShortName; // offset 0x0, size 0xC
    class String mFullName; // offset 0xC, size 0xC
    class String mArtist; // offset 0x18, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum WinMetric {
    kMetricScore = 0,
    kMetricStreak = 1,
    kMetricStars = 2,
};
class BotbBattleDetails {
    // total size: 0xC
    class RBBotbBattleDetails * mBattleDetails; // offset 0x0, size 0x4
    class list mSetList; // offset 0x4, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class PresenceResultRow {
    // total size: 0x20
    class OnlineID mOnlineID; // offset 0x0, size 0x10
    class String mName; // offset 0x10, size 0xC
    unsigned char mOnline; // offset 0x1C, size 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class PresenceResultList : public Updatable {
    // total size: 0x18
    class list mPresenceResultRowList; // offset 0x8, size 0x8
    class RBPresenceResultQList * mQList; // offset 0x10, size 0x4
    unsigned char mUpdated; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
enum IDType {
    kInvalid = 0,
    kBandID = 1,
    kPlayerID = 2,
};
class EntityID {
    // total size: 0x18
    enum IDType mType; // offset 0x0, size 0x4
    class HxGuid mGuid; // offset 0x4, size 0x10
    unsigned int mPlayerID; // offset 0x14, size 0x4
};
class LeaderboardResultRow {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
    class EntityID mLeaderboardID; // offset 0x4, size 0x18
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class LeaderboardResultList {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class list mResultRowList; // offset 0x4, size 0x8
};
class BandResultList : public Updatable, public LeaderboardResultList {
    // total size: 0x1C
    class RBBandResultQList * mQList; // offset 0x14, size 0x4
    unsigned char mUpdated; // offset 0x18, size 0x1
};
class PlayerResultList : public Updatable, public LeaderboardResultList {
    // total size: 0x1C
    class RBPlayerResultQList * mQList; // offset 0x14, size 0x4
    unsigned char mUpdated; // offset 0x18, size 0x1
};
class ProfileChangedMsg : public Message {
    // total size: 0x8
};
class RockCentralGateway : public MsgSource {
    // total size: 0xC8
    class ContextWrapperPool * mContextWrapperPool; // offset 0x1C, size 0x4
    class ProtocolCallContext * mConfigContext; // offset 0x20, size 0x4
    class String * mReceivedConfig; // offset 0x24, size 0x4
    class String * mReceivedVersion; // offset 0x28, size 0x4
    class RBEntitiesClient * mRBEntities; // offset 0x2C, size 0x4
    class RBScoresClient * mRBScores; // offset 0x30, size 0x4
    class RBLeaderboardsClient * mRBLeaderboards; // offset 0x34, size 0x4
    class RBConfigClient * mRBConfig; // offset 0x38, size 0x4
    class RBBotbClient * mRBBotb; // offset 0x3C, size 0x4
    enum /* @enum$12402App_cpp */ {
        kOffline = 0,
        kConnecting = 1,
        kOnline = 2,
        kDisconnecting = 3,
        kFailed = 4,
    } mState; // offset 0x40, size 0x4
    class Timer mTime; // offset 0x48, size 0x38
    float mRetryTime; // offset 0x80, size 0x4
    class BandProfileCache * mProfileCache; // offset 0x84, size 0x4
    class JobMgr mJobMgr; // offset 0x88, size 0x10
    unsigned char mLoginBlocked; // offset 0x98, size 0x1
};
class NetGameData {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class Net : public Object {
    // total size: 0x368
    class NetGameData * mGameData; // offset 0x28, size 0x4
    class NetSession * mSession; // offset 0x2C, size 0x4
    class SessionSearcher * mSearcher; // offset 0x30, size 0x4
    class Server * mServer; // offset 0x34, size 0x4
    class NetworkEmulator * mEmulator; // offset 0x38, size 0x4
    class GSMCodec * mCodec; // offset 0x3C, size 0x4
    class SyncStore * mSyncStore; // offset 0x40, size 0x4
    unsigned char * mThreadStack; // offset 0x44, size 0x4
    int mThreadResult; // offset 0x48, size 0x4
    unsigned char mThreadActive; // offset 0x4C, size 0x1
    struct OSThread mThread; // offset 0x50, size 0x318
};
class FilePath : public String {
    // total size: 0xC
};
class WiiDrawTarget {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
enum VITVMode {
    VI_TVMODE_NTSC_INT = 0,
    VI_TVMODE_NTSC_DS = 1,
    VI_TVMODE_NTSC_PROG = 2,
    VI_TVMODE_PAL_INT = 4,
    VI_TVMODE_PAL_DS = 5,
    VI_TVMODE_EURGB60_INT = 20,
    VI_TVMODE_EURGB60_DS = 21,
    VI_TVMODE_EURGB60_PROG = 22,
    VI_TVMODE_MPAL_INT = 8,
    VI_TVMODE_MPAL_DS = 9,
    VI_TVMODE_MPAL_PROG = 10,
    VI_TVMODE_DEBUG_INT = 12,
    VI_TVMODE_DEBUG_PAL_INT = 16,
    VI_TVMODE_DEBUG_PAL_DS = 17,
};
enum VIXFBMode {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF = 1,
};
struct _GXRenderModeObj {
    // total size: 0x3C
    enum VITVMode viTVmode; // offset 0x0, size 0x4
    unsigned short fbWidth; // offset 0x4, size 0x2
    unsigned short efbHeight; // offset 0x6, size 0x2
    unsigned short xfbHeight; // offset 0x8, size 0x2
    unsigned short viXOrigin; // offset 0xA, size 0x2
    unsigned short viYOrigin; // offset 0xC, size 0x2
    unsigned short viWidth; // offset 0xE, size 0x2
    unsigned short viHeight; // offset 0x10, size 0x2
    enum VIXFBMode xFBmode; // offset 0x14, size 0x4
    unsigned char field_rendering; // offset 0x18, size 0x1
    unsigned char aa; // offset 0x19, size 0x1
    unsigned char sample_pattern[12][2]; // offset 0x1A, size 0x18
    unsigned char vfilter[7]; // offset 0x32, size 0x7
};
struct GXFifoObj {
    // total size: 0x80
    unsigned char pad[128]; // offset 0x0, size 0x80
};
struct OSFontHeader {
    // total size: 0x30
    unsigned short fontType; // offset 0x0, size 0x2
    unsigned short firstChar; // offset 0x2, size 0x2
    unsigned short lastChar; // offset 0x4, size 0x2
    unsigned short invalChar; // offset 0x6, size 0x2
    unsigned short ascent; // offset 0x8, size 0x2
    unsigned short descent; // offset 0xA, size 0x2
    unsigned short width; // offset 0xC, size 0x2
    unsigned short leading; // offset 0xE, size 0x2
    unsigned short cellWidth; // offset 0x10, size 0x2
    unsigned short cellHeight; // offset 0x12, size 0x2
    unsigned long sheetSize; // offset 0x14, size 0x4
    unsigned short sheetFormat; // offset 0x18, size 0x2
    unsigned short sheetColumn; // offset 0x1A, size 0x2
    unsigned short sheetRow; // offset 0x1C, size 0x2
    unsigned short sheetWidth; // offset 0x1E, size 0x2
    unsigned short sheetHeight; // offset 0x20, size 0x2
    unsigned short widthTable; // offset 0x22, size 0x2
    unsigned long sheetImage; // offset 0x24, size 0x4
    unsigned long sheetFullSize; // offset 0x28, size 0x4
    unsigned char c0; // offset 0x2C, size 0x1
    unsigned char c1; // offset 0x2D, size 0x1
    unsigned char c2; // offset 0x2E, size 0x1
    unsigned char c3; // offset 0x2F, size 0x1
};
class WiiRnd : public Rnd, public WiiDrawTarget {
    // total size: 0x280
    struct _GXRenderModeObj mMode; // offset 0x138, size 0x3C
    void * mFrameBuffer; // offset 0x174, size 0x4
    unsigned char mFirstFrame; // offset 0x178, size 0x1
    void * mFifo; // offset 0x17C, size 0x4
    struct GXFifoObj * mFifoObj; // offset 0x180, size 0x4
    float mScreenOrthoProjXfm[4][4]; // offset 0x184, size 0x40
    float mWorldOrthoProjXfm[4][4]; // offset 0x1C4, size 0x40
    float mIdentityXfm[3][4]; // offset 0x204, size 0x30
    struct OSFontHeader * mFont; // offset 0x234, size 0x4
    unsigned char mNewLighting; // offset 0x238, size 0x1
    unsigned char mPostProcEnabled; // offset 0x239, size 0x1
    class WiiSplitPostProc * mSplitPostProc; // offset 0x23C, size 0x4
    void * mScreenshotWorkingBuffer; // offset 0x240, size 0x4
    float mTmpProjection[7]; // offset 0x244, size 0x1C
    float mTmpViewport[6]; // offset 0x260, size 0x18
    unsigned char mProgressiveScan; // offset 0x278, size 0x1
    unsigned char mProgressiveFlag; // offset 0x279, size 0x1
    unsigned char mMultiThread; // offset 0x27A, size 0x1
    unsigned char mAllowQuazalPolling; // offset 0x27B, size 0x1
    unsigned char mScreenDimmingEnabled; // offset 0x27C, size 0x1
    unsigned char mScreenshotsActive; // offset 0x27D, size 0x1
    unsigned char mDrawingWorld; // offset 0x27E, size 0x1
};

