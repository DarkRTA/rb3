#include "world/Instance.h"
#include "rndobj/Group.h"

SharedGroup::SharedGroup(RndGroup* group) : unk8(group), unkc(this, 0) {
    AddPolls(group);
}

SharedGroup::~SharedGroup(){
    
}

void SharedGroup::ClearPollMaster(){
    unkc = 0;
}

WorldInstance::WorldInstance() : unk18c(), unk198(0), unk19c(0) {

}