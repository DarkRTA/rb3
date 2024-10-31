#include "meta_band/Leaderboard.h"

Leaderboard::Leaderboard(EntityID id, Callback* cb) : unk40(0), unk44(0), unk48(1), mEntityID(id), mCallback(cb), unk74(0), unk78(0), unk7c(0), unk80(-1) {
    mShortcutProvider = new LeaderboardShortcutProvider(this);
}

Leaderboard::~Leaderboard(){
    
}