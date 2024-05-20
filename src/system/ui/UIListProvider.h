#ifndef UI_UILISTPROVIDER_H
#define UI_UILISTPROVIDER_H
#include "utl/Symbol.h"
#include "ui/UIComponent.h"
#include "ui/UIListWidget.h"

// holy guacamole that's a lot of forward decs
class RndMesh;
class RndDir;
class UIListLabel;
class UILabel;
class UIListMesh;
class UIListSlot;
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
    virtual int Provider(int, int, UIListSubList*) const { return 0; } // return type also probably not an int
    virtual void Custom(int, int, UIListCustom*, Hmx::Object*) const {}
    virtual void UpdateExtendedText(int, int, UILabel*) const;
    virtual void UpdateExtendedMesh(int, int, RndMesh*) const;
    virtual void UpdateExtendedCustom(int, int, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const { return Symbol(); }
    virtual int DataIndex(Symbol) const;
    virtual short NumData() const = 0;
    virtual bool IsActive(int) const { return true; }
    virtual bool IsHidden(int) const { return false; }
    virtual void InitData(RndDir*){}
    virtual float GapSize(int, int, int, int) const { return 0.0f; }
    virtual UIComponent::State ComponentStateOverride(int, int, UIComponent::State s) const { return s; }
    virtual UIListWidgetState ElementStateOverride(int, int, UIListWidgetState s) const { return s; }
    virtual UIListWidgetState SlotElementStateOverride(int, int, UIListWidget*, UIListWidgetState s) const { return s; }
    virtual UIColor* SlotColorOverride(int, int, UIListWidget*, UIColor* c) const { return c; }
    virtual void PreDraw(int, int, UIListSlot*) const {}
    virtual int SnappableAtOrBeforeData(int) const { return -1; }
    virtual bool IsSnappableAtData(int) const { return false; }
};

#endif
