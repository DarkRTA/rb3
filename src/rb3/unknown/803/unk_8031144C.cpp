#include "user.hpp"
#include "common.hpp"

User::User() : id(new OnlineID()), guid(), unk30(-1) {
    guid.Generate();
}
