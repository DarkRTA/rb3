#include "char/CharPollGroup.h"
#include "utl/Symbols.h"

INIT_REVS(CharPollGroup);

CharPollGroup::CharPollGroup() : mPolls(this, kObjListNoNull), mChangedBy(this, 0), mChanges(this, 0) {

}

CharPollGroup::~CharPollGroup(){
    
}

void CharPollGroup::Enter(){
    for(ObjPtrList<CharPollable, ObjectDir>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
        (*it)->Enter();
    }
}

void CharPollGroup::Exit(){
    for(ObjPtrList<CharPollable, ObjectDir>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
        (*it)->Exit();
    }
}

void CharPollGroup::Poll(){
    if(mWeightOwner->mWeight != 0.0f){
        for(ObjPtrList<CharPollable, ObjectDir>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
            (*it)->Poll();
        }
    }
}

void CharPollGroup::ListPollChildren(std::list<RndPollable*>& l) const {
    for(ObjPtrList<CharPollable, ObjectDir>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
        l.push_back(*it);
    }
}

void CharPollGroup::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    if(mChangedBy || mChanges){
        changedBy.push_back(mChangedBy);
        change.push_back(mChanges);
    }
    else {
        for(ObjPtrList<CharPollable, ObjectDir>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
            (*it)->PollDeps(changedBy, change);
        }
    }
}

SAVE_OBJ(CharPollGroup, 0x58)

void CharPollGroup::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    Hmx::Object::Load(bs);
    if(gRev > 2) CharWeightable::Load(bs);
    bs >> mPolls;
    if(gRev > 1){
        bs >> mChangedBy;
        bs >> mChanges;
    }
}

BEGIN_HANDLERS(CharPollGroup)
    HANDLE_ACTION(sort_polls, SortPolls())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xA2)
END_HANDLERS

BEGIN_PROPSYNCS(CharPollGroup)
    SYNC_PROP(polls, mPolls)
    SYNC_PROP(changed_by, mChangedBy)
    SYNC_PROP(changes, mChanges)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS