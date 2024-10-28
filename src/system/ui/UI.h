#ifndef UI_UI_H
#define UI_UI_H
#include "obj/Object.h"
#include "utl/Symbol.h"
#include "os/Joypad.h"
#include "os/Timer.h"
#include "rndobj/Cam.h"
#include "ui/UIMessages.h"
#include "os/JoypadMsgs.h"
#include <vector>

class JoypadClient;
class UIComponent;
class UIScreen;
class UIPanel;
class UIResource;
class RndOverlay;
class MsgSource;

// size 0x58
class Automator : public Hmx::Object {
public:
    Automator() : mScreenScripts(0), mRecord(0), mRecordPath("automator.dta"), mAutoPath("automator.dta"),
        mCurScript(0), mCurScreenIndex(0), mCurMsgIndex(0), mFramesSinceAdvance(0), mSkipNextQuickCheat(0) {}
    virtual ~Automator(){
        if(mScreenScripts){
            mScreenScripts->Release();
            mScreenScripts = 0;
        }
        FinishRecord();
        if(mRecord){
            mRecord->Release();
            mRecord = 0;
        }
    }
    virtual DataNode Handle(DataArray*, bool);

    void StartAuto(UIScreen*);
    const char* ToggleAuto();

    const char* AutoScript(){
        if(mScreenScripts && !mRecord) return mAutoPath.c_str();
        else return "OFF";
    }

    void FinishRecord();

    const char* ToggleRecord(){
        if(mRecord){
            FinishRecord();
            if(mRecord){
                mRecord->Release();
                mRecord = 0;
            }
        }
        else {
            mSkipNextQuickCheat = true;
            mRecord = new DataArray(0);
        }
        return RecordScript();
    }

    const char* RecordScript(){
        if(mRecord) return mRecordPath.c_str();
        else return "OFF";
    }

    void AddMessageType(MsgSource* src, Symbol s){
        src->AddSink(this, s, Symbol(), MsgSource::kHandle);
        mCustomMsgs.push_back(s);
    }

    void AddRecord(Symbol, DataArray*);

    DataNode OnMsg(const UITransitionCompleteMsg&);
    DataNode OnMsg(const ButtonDownMsg&);
    DataNode OnMsg(const UIComponentSelectMsg&);
    DataNode OnMsg(const UIComponentScrollMsg&);
    DataNode OnMsg(const UIComponentFocusChangeMsg&);
    DataNode OnMsg(const UIScreenChangeMsg&);
    DataNode OnCheatInvoked(const DataArray*);
    DataNode OnCustomMsg(const Message&);

    NEW_POOL_OVERLOAD(Automator)
    DELETE_POOL_OVERLOAD(Automator)

    DataArray* mScreenScripts; // 0x1c
    DataArray* mRecord; // 0x20
    String mRecordPath; // 0x24
    String mAutoPath; // 0x30
    DataArray* mCurScript; // 0x3c
    int mCurScreenIndex; // 0x40
    int mCurMsgIndex; // 0x44
    int mFramesSinceAdvance; // 0x48
    bool mSkipNextQuickCheat; // 0x4c
    std::list<Symbol> mCustomMsgs; // 0x50
};

enum TransitionState {
    kTransitionNone = 0,
    kTransitionTo = 1,
    kTransitionFrom = 2,
    kTransitionPop = 3,
};

class UIManager : public virtual Hmx::Object {
public:
    UIManager();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIManager();
    virtual void Init();
    virtual void Terminate();
    virtual void Poll();
    virtual void Draw();
    virtual void GotoScreen(const char*, bool, bool);
    virtual void GotoScreen(UIScreen*, bool, bool);
    virtual void PushScreen(UIScreen*);
    virtual void PopScreen(UIScreen*);
    virtual void ResetScreen(UIScreen*);
    virtual bool InComponentSelect();
    virtual bool IsBlockingTransition(){ return false; }
    virtual bool IsTimelineResetAllowed() const { return true; }
    virtual void SendTransitionComplete(UIScreen*, UIScreen*);

    void CancelTransition();
    void GotoScreenImpl(UIScreen*, bool, bool);
    class UIPanel* FocusPanel();
    UIComponent* FocusComponent();
    UIResource* Resource(const UIComponent*);
    void InitResources(Symbol);
    UIResource* FindResource(const DataArray*);
    void UseJoypad(bool, bool);
    bool OverloadHorizontalNav(JoypadAction, JoypadButton, Symbol) const;
    bool RequireFixedText() const;
    void SetRequireFixedText(bool);
    int PushDepth() const;
    void ScreenAtDepth(int);
    void ToggleLoadTimes();
    bool InTransition();
    bool BlockHandlerDuringTransition(Symbol, DataArray*);
    void EnableInputPerformanceMode(bool);
    void PrintLoadedDirs(const char*);
    void ShowNetError();
    bool WentBack() const { return mWentBack; }
    UIScreen* CurrentScreen(){ return mCurrentScreen; }
    UIScreen* TransitionScreen() const { return mTransitionScreen; }
    UIScreen* BottomScreen();
    DataNode OnGotoScreen(const DataArray*);
    DataNode OnGoBackScreen(const DataArray*);
    DataNode OnIsResource(DataArray*);
    DataNode ForeachScreen(const DataArray*);
    TransitionState GetTransitionState() const { return mTransitionState; }
    bool IsTransitioning() const { return mTransitionState != kTransitionNone; }

    TransitionState mTransitionState; // 0x8
    bool mWentBack; // 0xc
    std::vector<UIScreen*> mPushedScreens; // 0x10
    int mMaxPushDepth; // 0x18
    JoypadClient* mJoyClient; // 0x1c
    UIScreen* mCurrentScreen; // 0x20
    UIScreen* mTransitionScreen; // 0x24
    std::vector<UIResource*> mResources; // 0x28
    Hmx::Object* mSink; // 0x30
    RndCam* unk34; // 0x34
    RndEnviron* unk38; // 0x38
    int unk3c; // 0x3c
    Timer mTimer; // 0x40
    bool unk70; // 0x70
    bool unk71; // 0x71
    bool unk72; // 0x72
    int unk74; // 0x74
    Timer mLoadTimer; // 0x78
    RndOverlay* mOverlay; // 0xa8
    bool mRequireFixedText; // 0xac
    Automator* unkb0; // 0xb0
    bool unkb4; // 0xb4
    bool unkb5; // 0xb5
};

extern UIManager* TheUI;

#endif
