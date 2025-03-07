#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"

class SetlistProvider : public UIListProvider, public Hmx::Object {
public:
    SetlistProvider() {}
    virtual ~SetlistProvider() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual int NumData() const;
};