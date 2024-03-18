#include "char/CharPollGroup.h"

CharPollGroup::CharPollGroup() : mPolls(this, kObjListNoNull), mChangedBy(this, 0), mChanges(this, 0) {

}

CharPollGroup::~CharPollGroup(){
    
}
