#pragma once
#include "ui/UIListProvider.h"

class ViewSettingsProvider : public UIListProvider {
public:
    ViewSettingsProvider();
    virtual ~ViewSettingsProvider() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir *);
    virtual UIColor *SlotColorOverride(int, int, class UIListWidget *, UIColor *c) const;

    void BuildFilters(Symbol);
};