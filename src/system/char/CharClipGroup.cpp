#include "char/CharClipGroup.h"
#include "char/CharClip.h"
#include "decomp.h"
#include "math/Rand.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include <algorithm>
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

void CharClipGroup::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    int idx = 0;
    for(; idx < mClips.size(); idx++){
        if(mClips[idx] == from){
            mClips[idx] = dynamic_cast<CharClip*>(to);
        }
        if(mClips[idx] == nullptr){
            mClips.erase(mClips.begin() + idx);
            int s = mClips.size();
            if(mWhich > idx){
                mWhich--;
            }
            else if(mWhich == s){
                mWhich = Min<int>(0, s - 1);
            }
            MILO_ASSERT(mWhich < s, 0x5A);
            return;
        }
    }
}

int CharClipGroup::NumFlagDuplicates(CharClip* clip, int x){
    int count = 0;
    int flags = clip->Flags();
    for(int i = 0; i < mClips.size(); i++){
        if(clip != mClips[i]){
            if((x & flags) == (x & mClips[i]->Flags())) count++;
        }
    }
    return count;
}

void CharClipGroup::DeleteRemaining(int x){
    CharClip* clips[256];
    for(int i = 0; i < mClips.size(); i++){
        clips[i] = mClips[i];
    }
    CharClip::LockAndDelete(clips, mClips.size(), x);
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

bool CharClipGroup::HasClip(CharClip* clip) const {
    ObjVector<ObjOwnerPtr<CharClip> >::const_iterator it = mClips.begin();
    for(; it != mClips.end() && *it != clip; ++it);
    return it != mClips.end();
}

CharClip* CharClipGroup::FindClip(const char* clipName) const {
    for(int i = 0; i < mClips.size(); i++){
        if(streq(clipName, mClips[i]->Name())){
            return mClips[i];
        }
    }
    return nullptr;
}

void CharClipGroup::Randomize(){
    for(int i = 0; i < mClips.size(); i++){
        std::swap(mClips[i], mClips[RandomInt(i, mClips.size())]);
    }
}

void CharClipGroup::RandomizeIndex(){
    if(mClips.size() != 0){
        mWhich = RandomInt(0, mClips.size());
    }
}

struct Alphabetically {
    bool operator()(Hmx::Object* i, Hmx::Object* j) const { return strcmp(i->Name(), j->Name()) < 0; }
};

void CharClipGroup::Sort(){
    std::sort(mClips.begin(), mClips.end(), Alphabetically());
}

void CharClipGroup::SetClipFlags(int flags){
    for(int i = 0; i < mClips.size(); i++){
        mClips[i]->SetFlags(flags | mClips[i]->Flags());
    }
}

void CharClipGroup::MakeMRU(CharClip* clip){
    for(int i = 0; i < mClips.size(); i++){
        if(mClips[i] == clip){
            MakeMRU(i);
            return;
        }
    }
    MILO_ASSERT(false, 0x11F);
}

SAVE_OBJ(CharClipGroup, 0x127)

BEGIN_LOADS(CharClipGroup)
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mClips;
    bs >> mWhich;
    if(gRev > 1) bs >> mFlags;
    else mFlags = 0;
END_LOADS

DECOMP_FORCEACTIVE(CharClipGroup, "\t[%i] %s flag = %i\n")

BEGIN_COPYS(CharClipGroup)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharClipGroup)
    BEGIN_COPYING_MEMBERS
        if(ty == kCopyFromMax){
            for(int i = 0; i < c->mClips.size(); i++){
                CharClip* curClip = c->mClips[i];
                if(!FindClip(curClip->Name())){
                    mClips.push_back(ObjOwnerPtr<CharClip>(this, curClip));
                }
            }
        }
        else COPY_MEMBER(mClips)
        COPY_MEMBER(mWhich)
        COPY_MEMBER(mFlags)
    END_COPYING_MEMBERS
END_COPYS

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

BEGIN_PROPSYNCS(CharClipGroup)
    SYNC_PROP(clips, mClips)
    SYNC_PROP(flags, mFlags)
END_PROPSYNCS