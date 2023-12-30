#ifndef RB3_USER_HPP
#define RB3_USER_HPP
#include "hmx/object.hpp"
#include "hxguid.hpp"
#include "onlineid.hpp"

class User : public Hmx::Object {
public:
    User();

    OnlineID* id;
    UserGuid guid;
    int unk30;
};

#endif
