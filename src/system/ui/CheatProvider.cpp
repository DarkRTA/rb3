#include "ui/CheatProvider.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "utl/Cheats.h"
#include "utl/Symbols.h"

CheatProvider *CheatProvider::sInstance;

CheatProvider::CheatProvider() : mFilterIdx(0) {
    SetName("cheat_provider", ObjectDir::Main());
    mFilters.push_back("all");
    DataArray *cfg = SystemConfig("quick_cheats");
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *arr = cfg->Array(i);
        Symbol cheatTypeSym = arr->Sym(0);
        const char *strtext = 0;
        if (cheatTypeSym == "keyboard")
            strtext = "KEYBOARD CHEATS";
        else if (cheatTypeSym == "right")
            strtext = "RIGHT CHEATS (R1 + R2)";
        else if (cheatTypeSym == "left")
            strtext = "LEFT CHEATS (L1 + L2)";
        mCheats.push_back(Cheat(strtext));
        for (int j = 1; j < arr->Size(); j++) {
            DataArray *arr2 = arr->Array(j);
            DataType nType = arr2->Node(0).Type();
            String theKeyStr;
            if (nType == kDataString || nType == kDataSymbol) {
                theKeyStr = arr2->Str(0);
            } else {
                const char *cheatStrStart = cheatTypeSym == "keyboard" ? "KB_" : "kPad_";
                theKeyStr = DataGetMacroByInt(arr2->Int(0), cheatStrStart).Str()
                    + strlen(cheatStrStart);
            }
            String theConcattedStr;
            int theNodeIdx = 1;
            while (arr2->Type(theNodeIdx) == kDataSymbol) {
                theKeyStr = String(arr2->Sym(theNodeIdx)) + String(" ") + theKeyStr;
                theNodeIdx++;
            }
            theConcattedStr = arr2->Str(theNodeIdx);
            mCheats.push_back(Cheat(theKeyStr, theConcattedStr, arr2));

            DataArray *filterArr = arr2->FindArray(filters, false);
            if (filterArr) {
                for (int k = 1; k < filterArr->Size(); k++) {
                    Symbol curFilt = filterArr->Sym(k);
                    if (std::find(mFilters.begin(), mFilters.end(), curFilt)
                        == mFilters.end()) {
                        mFilters.push_back(curFilt);
                    }
                }
            }
        }
        if (i < cfg->Size() - 1) {
            mCheats.push_back(gNullStr);
        }
    }
    ApplyFilter();
}

void CheatProvider::Init() {
    if (CheatsInitialized()) {
        MILO_ASSERT(!sInstance, 97);
        sInstance = new CheatProvider();
    }
}

void CheatProvider::Terminate() {
    MILO_ASSERT(sInstance, 104);
    RELEASE(sInstance);
}

CheatProvider::~CheatProvider() {}

void CheatProvider::InitData(RndDir *) { ApplyFilter(); }

void CheatProvider::Text(int i, int j, UIListLabel *listlabel, UILabel *label) const {
    const Cheat &cheat = mFilterCheats[j];
    if (listlabel->Matches("key")) {
        label->SetEditText(cheat.mKey.c_str());
    } else if (listlabel->Matches("description")) {
        label->SetEditText(cheat.mDesc.c_str());
    } else if (listlabel->Matches("value")) {
        if (!cheat.mScript)
            label->SetTextToken(gNullStr);
        else {
            DataArray *bool_arr = cheat.mScript->FindArray(value_bool, false);
            if (bool_arr) {
                label->SetEditText(bool_arr->Int(1) != 0 ? "ON" : "OFF");
            } else {
                DataArray *value_arr = cheat.mScript->FindArray(value, false);
                if (value_arr) {
                    const DataNode &n = value_arr->Node(1).Evaluate();
                    if (n.Type() == kDataSymbol || n.Type() == kDataString) {
                        label->SetEditText(n.Str());
                    } else if (n.Type() == kDataInt) {
                        label->SetInt(n.Int(), false);
                    } else if (n.Type() == kDataFloat) {
                        label->SetFloat("%f", n.Float());
                    } else
                        label->SetEditText("?");
                } else
                    label->SetEditText(gNullStr);
            }
        }
    }
}

int CheatProvider::NumData() const { return mFilterCheats.size(); }

bool CheatProvider::IsActive(int i) const { return !mFilterCheats[i].mKey.empty(); }

void CheatProvider::Invoke(int i, LocalUser *user) {
    DataArray *arr = mFilterCheats[i].mScript;
    if (!arr)
        return;
    CallQuickCheat(arr, user);
}

void CheatProvider::NextFilter() {
    mFilterIdx = (mFilterIdx + 1) % mFilters.size();
    ApplyFilter();
}

void CheatProvider::ApplyFilter() {
    Symbol curFilt = mFilters[mFilterIdx];
    mFilterCheats.clear();
    Cheat *curCheat = nullptr;
    for (std::vector<Cheat>::iterator it = mCheats.begin(); it != mCheats.end(); ++it) {
        if (it->mScript) {
            Symbol cheatMode = GetCheatMode();
            DataArray *modeArr = it->mScript->FindArray(modes, false);
            if (modeArr && !modeArr->Contains(cheatMode))
                continue;
        }
        if (curFilt != all) {
            if (!it->mScript) {
                if (!it->mDesc.empty()) {
                    curCheat = it;
                }
            } else {
                DataArray *filterArr = it->mScript->FindArray(filters, false);
                if (filterArr && filterArr->Contains(curFilt)) {
                    if (curCheat) {
                        if (!mFilterCheats.empty()) {
                            mFilterCheats.push_back(gNullStr);
                        }
                        mFilterCheats.push_back(*curCheat);
                        curCheat = nullptr;
                    }
                    mFilterCheats.push_back(*it);
                }
            }
        } else
            mFilterCheats.push_back(*it);
    }
}

BEGIN_HANDLERS(CheatProvider)
    HANDLE_ACTION(invoke, Invoke(_msg->Int(2), _msg->Obj<LocalUser>(3)))
    HANDLE_ACTION(next_filter, NextFilter())
    HANDLE_EXPR(filter, mFilters[mFilterIdx])
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xFF)
END_HANDLERS
