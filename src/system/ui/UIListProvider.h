#ifndef UI_UILISTPROVIDER_H
#define UI_UILISTPROVIDER_H
#include "utl/Symbol.h"

// holy guacamole that's a lot of forward decs
class RndMesh;
class RndDir;
class UIListLabel;
class UILabel;
class UIListMesh;
class UIListSubList;
class UIListCustom;
namespace Hmx {
    class Object;
}

class UIListProvider {
public:
    UIListProvider(){}
    virtual ~UIListProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int Mat(int, int, UIListMesh*) const; // return type probably not an int, fix this
    virtual int Provider(int, int, UIListSubList*) const; // return type also probably not an int
    virtual void Custom(int, int, UIListCustom*, Hmx::Object*) const;
    virtual void UpdateExtendedText(int, int, UILabel*) const;
    virtual void UpdateExtendedMesh(int, int, RndMesh*) const;
    virtual void UpdateExtendedCustom(int, int, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int DataIndex(Symbol) const;
    virtual short NumData() const = 0;
    virtual bool IsActive(int) const;
    virtual bool IsHidden(int) const;
    virtual void InitData(RndDir*);
    virtual float GapSize(int, int, int, int) const;
    // the rest all return states of other classes
    
};

#endif
