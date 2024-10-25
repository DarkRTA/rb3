#include "meta_band/InterstitialMgr.h"
#include "BandUI.h"
#include "meta_band/Utl.h"
#include "math/Rand.h"
#include "net/Synchronize.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/MakeString.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

InterstitialMgr::InterstitialMgr() : Synchronizable("interstitial_mgr"), mRandomOverride(-1), mRandomSelection(0) {
    SetFromConfig();
    RefreshRandomSelection();
    SetName("interstitial_mgr", ObjectDir::Main());
}

void InterstitialMgr::SetFromConfig(){
    DataArray* cfg = SystemConfig(vignettes, interstitials);
    for(int i = 1; i < cfg->Size(); i++){
        DataArray* arr = cfg->Array(i);
        Symbol key = arr->Sym(0);
        std::map<Symbol, DataArray*> arrMap;
        for(int j = 1; j < arr->Size(); j++){
            DataArray* jarr = arr->Array(j);
            Symbol jkey = jarr->Sym(0);
            arrMap[jkey] = jarr;
        }
        mScreenInterstitialMap[key] = arrMap;
    }
}

void InterstitialMgr::GetInterstitialsFromScreen(UIScreen* screen, std::vector<UIPanel*>& panels){
    panels.clear();
    mCurrentInterstitials.clear();
    std::map<Symbol, DataArray*>& cur = mScreenInterstitialMap[screen->Name()];
    for(std::map<Symbol, DataArray*>::iterator it = cur.begin(); it != cur.end(); ++it){
        DataArray* val = it->second;
        for(int i = 1; i < val->Size(); i++){
            DataArray* arr = val->Array(i);
            if(arr->Int(0)){
                DataArray* a10 = arr->Array(1);
                int a10size = a10->Size();
                if(a10size){
                    const char* str = a10->Str(mRandomSelection % a10size);
                    UIPanel* panel = ObjectDir::Main()->Find<UIPanel>(MakeString("%s_panel", str), true);
                    UIScreen* foundscreen = ObjectDir::Main()->Find<UIScreen>(MakeString("%s_screen", str), false);
                    panels.push_back(panel);
                    mCurrentInterstitials[it->first] = foundscreen;
                }
                break;
            }
        }
    }
}

UIPanel* InterstitialMgr::PickInterstitialBetweenScreens(const char* c1, const char* c2){
    UIPanel* ret = nullptr;
    DataArray* arr = mScreenInterstitialMap[c1][c2];
    for(int i = 1; i < arr->Size(); i++){
        DataArray* iarr = arr->Array(i);
        if(iarr->Int(0)){
            DataArray* a = iarr->Array(1);
            int asize = a->Size();
            if(asize != 0){
                const char* str = a->Str(mRandomSelection % asize);
                ret = ObjectDir::Main()->Find<UIPanel>(MakeString("%s_panel", str), true);
            }
            break;
        }
    }
    return ret;
}

UIScreen* InterstitialMgr::CurrentInterstitialToScreen(UIScreen* screen) const {
    if(screen){
        std::map<Symbol, UIScreen*>::const_iterator it = mCurrentInterstitials.find(screen->Name());
        if(it != mCurrentInterstitials.end()) return it->second;
    }
    return nullptr;
}

void InterstitialMgr::RefreshRandomSelection(){
    if(HasSyncPermission()){
        if(mRandomOverride >= 0){
            mRandomSelection = mRandomOverride;
        }
        else mRandomSelection = RandomInt();
        SetSyncDirty(-1, false);
    }
}

void InterstitialMgr::SyncSave(BinStream& bs, unsigned int) const {
    bs << mRandomSelection;
}

void InterstitialMgr::SyncLoad(BinStream& bs, unsigned int){
    bs >> mRandomSelection;
}

bool InterstitialMgr::HasSyncPermission() const { return IsLeaderLocal(); }

void InterstitialMgr::PrintOverlay(UIScreen* scr1, UIScreen* scr2){
    String str("transition vignette: ");
    UIScreen* interstitalScreen = CurrentInterstitialToScreen(scr2);
    DataArray* arr = mScreenInterstitialMap[scr1->Name()][scr2->Name()];
    for(int i = 1; i < arr->Size(); i++){
        DataArray* iarr = arr->Array(i);
        if(iarr->Int(0)){
            DataArray* a = iarr->Array(1);
            for(int j = 0; j < a->Size(); j++){
                const char* astr = a->Str(j);
                if(streq(interstitalScreen->Name(), MakeString("%s_screen", astr))){
                    str += MakeString("(%s) ", astr);
                }
                else str += MakeString("%s ", astr);
            }
            break;
        }
    }
    TheBandUI.WriteToVignetteOverlay(str.c_str());
}

#pragma push
#pragma pool_data off
void InterstitialMgr::CycleRandomOverride(){
    static Hmx::Object* cd = ObjectDir::Main()->Find<Hmx::Object>("cheat_display", true);
    static Message show("show", 0);
    mRandomOverride++;
    if(mRandomOverride > 9) mRandomOverride = -1;
    if(mRandomOverride >= 0){
        show[0] = MakeString("vignette override: %i", mRandomOverride + 1);
    }
    else {
        show[0] = "vignette override off";
    }
    cd->Handle(show, false);
    RefreshRandomSelection();
}
#pragma pop

BEGIN_HANDLERS(InterstitialMgr)
    HANDLE_EXPR(pick_interstitial_between_screens, PickInterstitialBetweenScreens(_msg->Str(2), _msg->Str(3)))
    HANDLE_CHECK(0xE6)
END_HANDLERS