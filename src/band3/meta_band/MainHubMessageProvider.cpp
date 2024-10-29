#include "meta_band/MainHubMessageProvider.h"
#include "MainHubPanel.h"
#include "game/Defines.h"
#include "meta_band/AppLabel.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "utl/Locale.h"
#include "utl/LocaleOrdinal.h"
#include "utl/Symbol.h"

MainHubMessageProvider::MainHubMessageProvider(MainHubPanel* panel) : mMainHub(panel) {

}

bool MainHubMessageProvider::IsActive(int) const { return true; }
void MainHubMessageProvider::SetData(DataNode data){ mMessages = data; }

void MainHubMessageProvider::Text(int, int data, UIListLabel* slot, UILabel* label) const {
    if(mMessages.Array()){
        MILO_ASSERT(( 0) <= (data) && (data) < ( mMessages.Array()->Size()), 0x2B);
        if(slot->Matches("message_text")){
            SetMessageLabel((AppLabel*)label, data);
        }
        else label->SetTextToken(gNullStr);
    }
}

RndMat* MainHubMessageProvider::Mat(int, int, UIListMesh* slot) const { return slot->DefaultMat(); }

int MainHubMessageProvider::NumData() const {
    if(mMessages.Type() == kDataArray){
        return mMessages.Array()->Size();
    }
    else return 0;
}

void MainHubMessageProvider::SetMessageLabel(AppLabel* label, int idx) const {
    DataArray* messageArray = mMessages.Array();
    MILO_ASSERT(idx < messageArray->Size(), 0x43);
    switch(messageArray->Type(idx)){
        case kDataArray:
            label->SetTokenFmt(messageArray->Array(idx));
            break;
        case kDataSymbol:
            Symbol sym = messageArray->Sym(idx);
            if(sym == Symbol("motd")){
                label->SetMotd(mMainHub);
            }
            else if(sym == Symbol("dlc_motd")){
                label->SetDLCMotd(mMainHub);
            }
            else if(sym == Symbol("unlinked_motd")){
                label->SetUnlinkedMotd(this);
            }
            else if(sym == Symbol("leaderboard_band_summary")){
                MILO_ASSERT(mBandStanding.isSet, 0x57);
                if(mBandStanding.unk8){
                    if(mBandStanding.unk9){
                        Symbol perc("message_band_summary_percentile");
                        label->SetTokenFmt(perc, MakeString("%i", mBandStanding.unk4));
                    }
                    else {
                        Symbol global("message_band_summary_global");
                        label->SetTokenFmt(global, LocalizeOrdinal(mBandStanding.unk4, LocaleGenderMasculine, LocaleSingular, false));
                    }
                }
                else {
                    Symbol summary("message_band_summary");
                    label->SetTokenFmt(summary, LocalizeOrdinal(mBandStanding.unk4, LocaleGenderMasculine, LocaleSingular, false));
                }
            }
            else if(sym == Symbol("leaderboard_summary")){
                MILO_ASSERT(mRoleStanding.isSet, 0x6E);
                if(mRoleStanding.unk8){
                    if(mRoleStanding.unk9){
                        Symbol perc("message_leaderboard_summary_perc");
                        label->SetTokenFmt(perc,MakeString("%i", mRoleStanding.unk4), ScoreTypeToSym(mRoleStanding.unk0));
                    }
                    else {
                        Symbol global("message_leaderboard_summary_glob");
                        label->SetTokenFmt(global, LocalizeOrdinal(mRoleStanding.unk4, LocaleGenderMasculine, LocaleSingular, false), ScoreTypeToSym(mRoleStanding.unk0));
                    }
                }
                else {
                    Symbol summary("message_leaderboard_summary");
                    label->SetTokenFmt(summary,LocalizeOrdinal(mRoleStanding.unk4, LocaleGenderMasculine, LocaleSingular, false), ScoreTypeToSym(mRoleStanding.unk0));
                }
            }
            else if(sym == Symbol("battles_summary")){
                MILO_ASSERT(mBattleStanding.isSet, 0x87);
                if(mBattleStanding.unk4 == 1){
                    label->SetTokenFmt("message_battle_summary_singular", mBattleStanding.unk4);
                }
                else {
                    label->SetTokenFmt("message_battle_summary", mBattleStanding.unk4);
                }
            }
            else {
                label->SetTextToken(messageArray->Sym(idx));
            }
            break;
        default:
            MILO_FAIL("Invalid Message Type %i \n", messageArray->Type(idx));
            break;
    }
}

void MainHubMessageProvider::AddUnlinkedMotd(const char* cc){ unk50 = cc; }

void MainHubMessageProvider::AddTickerData(TickerDataType ty, int i1, int i2, bool b1, bool b2){
    switch(ty){
        case 0:
            mRoleStanding.unk0 = (ScoreType)i1;
            mRoleStanding.unk4 = i2;
            mRoleStanding.unk8 = b1;
            mRoleStanding.unk9 = b2;
            mRoleStanding.isSet = true;
            break;
        case 1:
            mBandStanding.unk0 = (ScoreType)i1;
            mBandStanding.unk4 = i2;
            mBandStanding.unk8 = b1;
            mBandStanding.unk9 = b2;
            mBandStanding.isSet = true;
            break;
        case 2:
            mBattleStanding.unk0 = (ScoreType)i1;
            mBattleStanding.unk4 = i2;
            mBattleStanding.unk8 = b1;
            mBattleStanding.unk9 = b2;
            mBattleStanding.isSet = true;
            break;
        default:
            MILO_FAIL("Invalid Ticker Data Type!\n");
            break;
    }
}

void MainHubMessageProvider::ClearData(){
    mRoleStanding.isSet = false;
    mBandStanding.isSet = false;
    mBattleStanding.isSet = false;
}

bool MainHubMessageProvider::IsTickerDataValid(TickerDataType ty){
    switch(ty){
        case 0:
            return mRoleStanding.isSet;
        case 2:
            return mBattleStanding.isSet;
        case 1:
            return mBandStanding.isSet;
        default:
            MILO_FAIL("Invalid Ticker Data Type\n");
            return false;
    }
}