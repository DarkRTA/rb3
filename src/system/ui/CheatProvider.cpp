#include "ui/CheatProvider.h"
#include "ui/UIListLabel.h"
#include "utl/Symbols.h"

CheatProvider::CheatProvider() : mFilterIdx(0) {
    SetName("cheat_provider", ObjectDir::Main());
    mFilters.push_back("all");
    DataArray* cfg = SystemConfig("quick_cheats");
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
                        label->SetEditText(n.Str(0));
                    }
                    else if(n.Type() == kDataInt){
                        label->SetInt(n.Int(0), false);
                    }
                    else if(n.Type() == kDataFloat){
                        label->SetFloat("%f", n.Float(0));
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