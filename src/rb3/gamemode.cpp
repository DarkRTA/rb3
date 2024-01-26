#include "gamemode.hpp"
#include "objectdir.hpp"
#include "system.hpp"
#include "data.hpp"
#include "symbols.hpp"

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