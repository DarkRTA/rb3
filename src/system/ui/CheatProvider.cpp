#include "ui/CheatProvider.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "utl/Cheats.h"
#include "utl/Symbols.h"

CheatProvider* CheatProvider::sInstance;

CheatProvider::CheatProvider() : mFilterIdx(0) {
    SetName("cheat_provider", ObjectDir::Main());
    mFilters.push_back("all");
    DataArray* cfg = SystemConfig("quick_cheats");
    if(cfg->Size() > 1){
        for(int i = 1; i < cfg->Size(); i++){
            DataArray* arr = cfg->Array(i);
            Symbol sym = arr->Sym(0);
            const char* strtext;
            if(sym == "keyboard") strtext = "KEYBOARD CHEATS";
            else if(sym == "right") strtext = "RIGHT CHEATS (R1 + R2)";
            else if(sym == "left") strtext = "LEFT CHEATS (L1 + L2)";
            mCheats.push_back(Cheat(strtext));
            for(int j = 1; j < arr->Size(); j++){

            }
        }
    }
    ApplyFilter();
}

extern bool CheatsInitialized();

void CheatProvider::Init() {
    if (CheatsInitialized()) {
        MILO_ASSERT(!sInstance, 97);
        sInstance = new CheatProvider;
    }
}

void CheatProvider::Terminate() {
    MILO_ASSERT(sInstance, 104);
    delete sInstance;
    sInstance = NULL;
}

CheatProvider::~CheatProvider(){

}

void CheatProvider::InitData(RndDir*){ ApplyFilter(); }

void CheatProvider::Text(int i, int j, UIListLabel* listlabel, UILabel* label) const {
    const Cheat& cheat = mFilterCheats[j];
    if(listlabel->Matches("key")){
        label->SetEditText(cheat.mKey.c_str());
    }
    else if(listlabel->Matches("description")){
        label->SetEditText(cheat.mDesc.c_str());
    }
    else if(listlabel->Matches("value")){
        if(!cheat.mScript) label->SetTextToken(gNullStr);
        else {
            DataArray* bool_arr = cheat.mScript->FindArray(value_bool, false);
            if(bool_arr){
                label->SetEditText(bool_arr->Int(1) != 0 ? "ON" : "OFF");
            }
            else {
                DataArray* value_arr = cheat.mScript->FindArray(value, false);
                if(value_arr){
                    DataNode& n = value_arr->Node(1).Evaluate();
                    if(n.Type() == kDataSymbol || n.Type() == kDataString){
                        label->SetEditText(n.Str());
                    }
                    else if(n.Type() == kDataInt){
                        label->SetInt(n.Int(), false);
                    }
                    else if(n.Type() == kDataFloat){
                        label->SetFloat("%f", n.Float());
                    }
                    else label->SetEditText("?");
                }
                else label->SetEditText(gNullStr);
            }
        }
    }
}

int CheatProvider::NumData() const { return mFilterCheats.size(); }

bool CheatProvider::IsActive(int i) const {
    return !mFilterCheats[i].mKey.empty();
}

void CheatProvider::Invoke(int i, LocalUser* user){
    DataArray* arr = mFilterCheats[i].mScript;
    if(!arr) return;
    CallQuickCheat(arr, user);
}

void CheatProvider::NextFilter(){
    mFilterIdx = (mFilterIdx + 1) % mFilters.size();
    ApplyFilter();
}

void CheatProvider::ApplyFilter(){

}

BEGIN_HANDLERS(CheatProvider)
    HANDLE_ACTION(invoke, Invoke(_msg->Int(2), _msg->Obj<LocalUser>(3)))
    HANDLE_ACTION(next_filter, NextFilter())
    HANDLE_EXPR(filter, mFilters[mFilterIdx])
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xFF)
END_HANDLERS
