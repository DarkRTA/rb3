#include "meta_band/MainHubMessageProvider.h"
#include "MainHubPanel.h"
#include "meta_band/AppLabel.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
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

void MainHubMessageProvider::SetMessageLabel(AppLabel*, int) const {
    
}

void MainHubMessageProvider::AddUnlinkedMotd(const char* cc){ unk50 = cc; }

void MainHubMessageProvider::AddTickerData(TickerDataType, int, int, bool, bool){

}

void MainHubMessageProvider::ClearData(){
    mRoleStanding.isSet = false;
    unk38.isSet = false;
    unk44.isSet = false;
}

bool MainHubMessageProvider::IsTickerDataValid(TickerDataType ty){
    switch(ty){
        case 0:
            return mRoleStanding.isSet;
        case 2:
            return unk44.isSet;
        case 1:
            return unk38.isSet;
        default:
            MILO_FAIL("Invalid Ticker Data Type\n");
            return false;
    }
}