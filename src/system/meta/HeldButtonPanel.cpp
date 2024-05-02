#include "meta/HeldButtonPanel.h"

HeldButtonPanel::HeldButtonPanel() : mHolder(new ButtonHolder(this, 0)), mHandling(0) {

}

HeldButtonPanel::~HeldButtonPanel(){
    delete mHolder;
}