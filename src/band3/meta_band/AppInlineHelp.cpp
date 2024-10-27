#include "meta_band/AppInlineHelp.h"
#include "bandobj/InlineHelp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "meta_band/InputMgr.h"
#include "meta_band/MetaMessages.h"
#include "meta_band/SessionMgr.h"
#include "obj/ObjMacros.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

AppInlineHelp::AppInlineHelp() : mOverrideUser(0) {

}

void AppInlineHelp::Enter(){
    InlineHelp::Enter();
    TheInputMgr->AddSink(this, InputStatusChangedMsg::Type());
    TheSessionMgr->AddSink(this, AddLocalUserResultMsg::Type());
    TheSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
}

void AppInlineHelp::Exit(){
    TheInputMgr->RemoveSink(this, InputStatusChangedMsg::Type());
    TheSessionMgr->RemoveSink(this, AddLocalUserResultMsg::Type());
    TheSessionMgr->RemoveSink(this, LocalUserLeftMsg::Type());
    UIComponent::Exit();
}

void AppInlineHelp::UpdateIconTypes(bool b){
    mIconTypes.clear();
    if(mOverrideUser){
        ControllerType ty = mOverrideUser->GetControllerType();
        switch(ty){
            case kControllerVocals:
                mIconTypes.push_back(vocals);
                break;
            case kControllerGuitar:
                mIconTypes.push_back(guitar);
                break;
            case kControllerDrum:
                mIconTypes.push_back(drums);
                break;
            case kControllerKeys:
                mIconTypes.push_back(keys);
                break;
            case kControllerRealGuitar:
                mIconTypes.push_back(real_guitar);
                break;
            default:
                MILO_WARN("ControllerType with no InlineHelp icons: %i\n", ty);
                break;
        }
    }
    else {
        bool foundvocals = false;
        bool foundguitar = false;
        bool founddrum = false;
        bool foundkeys = false;
        bool foundrg = false;
        if(!mUseConnectedControllers){
            std::vector<LocalBandUser*> users;
            TheBandUserMgr->GetLocalBandUsersInSession(users);
            for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
                ControllerType ty = (*it)->ConnectedControllerType();
                switch(ty){
                    case kControllerVocals:
                        foundvocals = true;
                        break;
                    case kControllerGuitar:
                        foundguitar = true;
                        break;
                    case kControllerDrum:
                        founddrum = true;
                        break;
                    case kControllerKeys:
                        foundkeys = true;
                        break;
                    case kControllerRealGuitar:
                        foundrg = true;
                        break;
                    default:
                        MILO_WARN("ControllerType with no InlineHelp icons: %i\n", (int)ty);
                        break;
                }
            }
        }
        else {
            foundvocals = true;
            foundguitar = true;
            founddrum = true;
            foundkeys = true;
            foundrg = true;
        }

        if(foundvocals && TheInputMgr->IsActiveAndConnected(kControllerVocals)){
            mIconTypes.push_back(vocals);
        }
        if(foundguitar && TheInputMgr->IsActiveAndConnected(kControllerGuitar)){
            mIconTypes.push_back(guitar);
        }
        if(founddrum && TheInputMgr->IsActiveAndConnected(kControllerDrum)){
            mIconTypes.push_back(drums);
        }
        if(foundkeys && TheInputMgr->IsActiveAndConnected(kControllerKeys)){
            mIconTypes.push_back(keys);
        }
        if(foundrg && TheInputMgr->IsActiveAndConnected(kControllerRealGuitar)){
            mIconTypes.push_back(real_guitar);
        }
    }
    if(b) SyncLabelsToConfig();
}

void AppInlineHelp::SetOverrideUser(LocalBandUser* user){
    mOverrideUser = user;
    UpdateIconTypes(true);
}

DataNode AppInlineHelp::OnMsg(const InputStatusChangedMsg&){
    if(TheUI->GetTransitionState() == kTransitionNone || TheUI->GetTransitionState() == kTransitionFrom){
        UpdateIconTypes(true);
    }
    return 1;
}

DataNode AppInlineHelp::OnMsg(const LocalUserLeftMsg&){
    if(TheUI->GetTransitionState() == kTransitionNone || TheUI->GetTransitionState() == kTransitionFrom){
        UpdateIconTypes(true);
    }
    return 1;
}

DataNode AppInlineHelp::OnMsg(const AddLocalUserResultMsg& msg){
    int result = msg.GetResult();
    if(result){
        if(TheUI->GetTransitionState() == kTransitionNone || TheUI->GetTransitionState() == kTransitionFrom){
            UpdateIconTypes(true);
        }
    }
    return 1;
}

BEGIN_HANDLERS(AppInlineHelp)
    HANDLE_ACTION(set_override_user, SetOverrideUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_MESSAGE(AddLocalUserResultMsg)
    HANDLE_MESSAGE(InputStatusChangedMsg)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_SUPERCLASS(InlineHelp)
    HANDLE_CHECK(0xBE)
END_HANDLERS