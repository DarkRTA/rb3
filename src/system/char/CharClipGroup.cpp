#include "char/CharClipGroup.h"
#include "utl/Symbols.h"

INIT_REVS(CharClipGroup)

CharClipGroup::CharClipGroup() : mClips(this), mWhich(0), mFlags(0) {

}

CharClip* CharClipGroup::GetClip(){
    if(mClips.empty()) return 0;
    mWhich++;
    if(mWhich >= mClips.size()) mWhich = 0;
    return mClips[mWhich];
}

int CharClipGroup::NumFlagDuplicates(CharClip* clip, int x){
    int flags = clip->mFlags;
    int count = 0;
    for(int i = 0; i < mClips.size(); i++){
        if(clip != mClips[i]){
            if((x & flags) == (x & mClips[i]->mFlags)) count++;
        }
    }
    return count;
}

void CharClipGroup::DeleteRemaining(int x){
    CharClip* clip;
    for(int i = 0; i < mClips.size(); i++){
        clip = mClips[i];
        clip++;
    }
    // clip->LockAndDelete(&mClips[0].Ptr(), x, 0);
}

void CharClipGroup::AddClip(CharClip* clip){
    if(!HasClip(clip)) mClips.push_back(ObjOwnerPtr<CharClip, ObjectDir>(this, clip));
}

void CharClipGroup::RemoveClip(CharClip* clip){
    for(ObjVector<ObjOwnerPtr<CharClip, ObjectDir> >::iterator it = mClips.begin(); it != mClips.end(); it){
        if(*it == clip){
            it = mClips.erase(it);
        }
        else it++;
    }
}

SAVE_OBJ(CharClipGroup, 0x127)

void CharClipGroup::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    bs >> mClips;
    bs >> mWhich;
    if(gRev > 1) bs >> mFlags;
    else mFlags = 0;
}

BEGIN_HANDLERS(CharClipGroup)
    HANDLE_EXPR(get_clip, GetClip())
    HANDLE_ACTION(delete_remaining, DeleteRemaining(_msg->Int(2)))
    HANDLE_EXPR(get_size, (int)mClips.size())
    HANDLE_EXPR(has_clip, HasClip(_msg->Obj<CharClip>(2)))
    HANDLE_EXPR(find_clip, GetClip(_msg->Int(2)))
    HANDLE_ACTION(add_clip, AddClip(_msg->Obj<CharClip>(2)))
    HANDLE_ACTION(set_clip_flags, SetClipFlags(_msg->Int(2)))
    HANDLE_ACTION(randomize_index, RandomizeIndex())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x179)
END_HANDLERS