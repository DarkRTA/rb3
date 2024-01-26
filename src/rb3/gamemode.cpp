#include "gamemode.hpp"
#include "objectdir.hpp"
#include "system.hpp"
#include "data.hpp"
#include "symbols.hpp"
#include "platformmgr.hpp"
#include "messages/modechangedmsg.hpp"

GameMode* TheGameMode;

void GameModeInit(){
    TheGameMode = new GameMode();
}

GameMode::GameMode(){
    SetName("gamemode", ObjectDir::sMainDir);
    SetMode("init");
}

GameMode::~GameMode(){

}

bool GameMode::InMode(Symbol target){
    if(curMode == target) return true;

    DataArray* modes = SystemConfig("modes");
    Symbol iter = curMode;
    
    while(modes->FindArray(iter, true)->FindArray(SymParentMode, false)){
        iter = modes->FindArray(iter, true)->FindArray(SymParentMode, true)->GetSymAtIndex(1);
        if(iter == target) return true;
    }
    
    return false;
}

DataNode GameMode::OnSetMode(const DataArray* da){
    da->GetNodeCount();
    SetMode(da->GetSymAtIndex(2));
    return DataNode(0);
}

ModeChangedMsg::ModeChangedMsg() : Message(Type()) {
    
}

Symbol ModeChangedMsg::Type(){
    static Symbol t("mode_changed");
    return t;
}

void PlatformMgr::SetUnkCE55(bool b){
    unkCE55 = b;
}

extern char* PathName(const Hmx::Object*);

DataNode GameMode::Handle(DataArray* da, bool b){
    Symbol sym = da->GetSymAtIndex(1);
    if(sym == SymInMode){
        return DataNode(InMode(da->GetSymAtIndex(2)));
    }
    if(sym == SymGetMode){
        return DataNode(curMode.m_string);
    }
    if(sym == SymSetMode){
        DataNode node = OnSetMode(da);
        if(node.GetType() != kDataUnhandled) return DataNode(node);
    }
    {
    DataNode hmxnode = Hmx::Object::Handle(da, false);
    if(hmxnode.GetType() != kDataUnhandled) return DataNode(hmxnode);
    }
    {
    DataNode msgnode = MsgSource::Handle(da, false);
    if(msgnode.GetType() != kDataUnhandled) return DataNode(msgnode);
    }
    if(b) PathName(this);
    return DataNode(kDataUnhandled, 0);
}