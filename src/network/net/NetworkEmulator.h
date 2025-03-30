#pragma once
#include "obj/Object.h"

class NetworkEmulator : public Hmx::Object {
public:
    NetworkEmulator();
    virtual ~NetworkEmulator() {}
    virtual DataNode Handle(DataArray *, bool);
};