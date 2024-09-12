#include "bandobj/BandLabel.h"
#include "ui/UI.h"

void BandLabel::Init(){
    TheUI->InitResources("BandLabel");
    Register();
}

BandLabel::BandLabel() : UITransitionHandler(this), unk1e8(""), unk1f4(0) {

}

BandLabel::~BandLabel(){
    
}