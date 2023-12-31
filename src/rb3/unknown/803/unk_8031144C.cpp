#include "user.hpp"
#include "common.hpp"

User::User() : id(new OnlineID()), guid(), unk30(-1) {
    guid.Generate();
}

void User::Reset(){
    unk30 = -1;
}

// User::Handle work: https://decomp.me/scratch/Qk51z