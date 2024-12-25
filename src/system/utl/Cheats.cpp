#include "utl/Cheats.h"
#include "os/Joypad.h"
#include "os/UserMgr.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

CheatsManager* gCheatsManager;
bool sKeyCheatsEnabled = true;

CheatsManager::CheatsManager() : mKeyCheatsEnabled(sKeyCheatsEnabled) {
    mLastButtonTime.Start();
    SystemConfig()->FindData("cheats_buffer", mMaxBuffer, true);
}

void CheatsManager::CallCheatScript(bool b1, DataArray* arr2, LocalUser* user, bool b2){
    if(!user && TheUserMgr){
        std::vector<LocalUser*> localUsers;
        TheUserMgr->GetLocalUsers(localUsers);
        for(std::vector<LocalUser*>::iterator it = localUsers.begin(); it != localUsers.end(); ++it){
            if((*it)->GetPadNum() == -1) break;
            JoypadData* data = JoypadGetPadData((*it)->GetPadNum());
            if(b1 && b2 && data->mType - 1U > 2 && data->mType - 0x13U > 2){
                user = *it;
                break;
            }
        }
    }
    if(user){
        switch(JoypadGetPadData(user->GetPadNum())->mType){
            case kJoypadDigital:
            case kJoypadAnalog:
            case kJoypadWiiCore:
            case kJoypadWiiFS:
            case kJoypadWiiClassic:
            case kJoypadDualShock:
                DataVariable("cheat_pad") = user ? user->GetPadNum() : 0;
                LogCheat(user ? user->GetPadNum() : -1, b1, arr2);
                if(b1){
                    int i = 2;
                    for(; arr2->Node(i).Type() != kDataCommand && i < arr2->Size(); i++);
                    if(i < arr2->Size()){
                        arr2->ExecuteScript(i, nullptr, nullptr, 1);
                    }
                }
                else arr2->Execute();
                Hmx::Object* uiObj = ObjectDir::Main()->Find<Hmx::Object>("ui", true);
                static Message msg("cheat_invoked", 0, 0);
                msg[0] = b1;
                msg[1] = DataNode(arr2, kDataArray);
                uiObj->Handle(msg, false);
                break;
            default:
                break;
        }
    }
}

BEGIN_HANDLERS(CheatsManager)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(KeyboardKeyMsg)
    HANDLE_CHECK(0x115)
END_HANDLERS

void InitQuickJoyCheats(const DataArray* arr, CheatsManager::ShiftMode shiftmode){
    for(int i = 1; i < arr->Size(); i++){
        DataArray* curArr = arr->Array(i);
        if(curArr->Int(0) >= 0 && curArr->Int(0) < 0x18){
            QuickJoyCheat cheat;
            cheat.unk0 = curArr->Int(0);
            cheat.unk4 = curArr;
            gCheatsManager->AddQuickJoyCheat(cheat, shiftmode);
        }
        else MILO_LOG("Error in quick_cheats: %s is not a valid button\n", curArr->Str(0));
    }
}

void InitLongJoyCheats(const DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        DataArray* curArr = arr->Array(i);
        DataArray* buttonArr = curArr->Array(0);
        if(buttonArr->Size() > 0x10){
            MILO_LOG("Too many buttons in long cheat, max %d\n", 0x10);
        }
        else {
            LongJoyCheat cheat;
            bool push = true;
            for(int j = 0; j < buttonArr->Size(); j++){
                int curBtn = buttonArr->Int(j);
                if(curBtn > 0x17U){
                    MILO_LOG("Error in long_cheats: %s is not a valid button\n", curBtn);
                    push = false;
                    break;
                }
                cheat.unk0.push_back(curBtn);
            }
            if(push){
                cheat.unkc = curArr->Command(1);
                gCheatsManager->AddLongJoyCheat(cheat);
            }
        }
    }
}

inline void CheatsManager::RebuildKeyCheatsForMode(){
    mKeyCheatPtrsMode.clear();
    for(std::vector<KeyCheat>::iterator it = mKeyCheats.begin(); it != mKeyCheats.end(); ++it){
        DataArray* modesArr = it->unk8->FindArray(modes, false);
        if(!modesArr || modesArr->Contains(mSymMode)){
            mKeyCheatPtrsMode.push_back(&*it);
        }
    }
    for(int i = 0; i < 2; i++){
        mJoyCheatPtrsMode[i].clear();
        for(std::vector<QuickJoyCheat>::iterator it = mQuickJoyCheats[i].begin(); it != mQuickJoyCheats[i].end(); ++it){
            DataArray* modesArr = it->unk4->FindArray(modes, false);
            if(!modesArr || modesArr->Contains(mSymMode)){
                mJoyCheatPtrsMode[i].push_back(&*it);
            }            
        }
    }
}

void InitKeyCheats(const DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        DataArray* cheat = arr->Array(i);
        if(cheat->Type(0) == kDataInt){
            if(cheat->Int(0) < 0){
                MILO_LOG("Error in quick_cheats: %i is not a valid key code\n", cheat->Int(0));
                continue;
            }
        }
        else {
            const char* key = cheat->Str(0);
            if(strlen(key) > 1){
                MILO_LOG("Error in quick_cheats: %s is not a valid key\n", key);
                continue;
            }
        }
        KeyCheat keyCheat;
        keyCheat.unk0 = cheat->Int(0);
        int subIndex = 1;
        for(; subIndex < cheat->Size() && cheat->Type(subIndex) == kDataSymbol; subIndex++){
            Symbol keyModifier = cheat->Sym(subIndex);
            if(keyModifier == ctrl) keyCheat.unk4 = 1;
            else if(keyModifier == alt) keyCheat.unk5 = 1;
            else {
                MILO_WARN("Unknown modifier symbol in cheat: %s", cheat->Sym(subIndex));
            }
        }
        MILO_ASSERT(cheat->Type( subIndex ) == kDataString, 0x251);
        keyCheat.unk8 = cheat;
        gCheatsManager->AddKeyCheat(keyCheat);
    }
    gCheatsManager->RebuildKeyCheatsForMode();
}