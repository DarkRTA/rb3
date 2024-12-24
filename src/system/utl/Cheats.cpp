#include "utl/Cheats.h"
#include "os/Joypad.h"
#include "os/UserMgr.h"
#include "obj/Dir.h"

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
            gCheatsManager->mQuickJoyCheats[shiftmode].push_back(cheat);
        }
        else MILO_LOG("Error in quick_cheats: %s is not a valid button\n", curArr->Str(0));
    }
}