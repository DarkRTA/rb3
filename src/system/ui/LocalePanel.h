#pragma once
#include "obj/Dir.h"
#include "ui/UILabel.h"
#include "ui/UIPanel.h"
#include "ui/UIListProvider.h"
#include "ui/UIScreen.h"

class LocalePanel : public UIPanel, public UIListProvider {
public:
    class Entry { // size 0x28
    public:
        Entry(){}
        String mHeading; // 0x0 - heading?
        String mLabel; // 0xc - label?
        Symbol mToken; // 0x18 - token?
        String mString; // 0x20 - string?
    };

    LocalePanel(){}
    OBJ_CLASSNAME(LocalePanel);
    OBJ_SET_TYPE(LocalePanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~LocalePanel(){}
    virtual void Enter();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual float GapSize(int, int, int, int) const;

    void AddDirEntries(ObjectDir*, const char*);
    UIScreen* Screen();
    void AddHeading(const char*);
    Symbol TokenForLabel(UILabel*);

    NEW_OBJ(LocalePanel);
    static void Init(){
        REGISTER_OBJ_FACTORY(LocalePanel);
    }

    std::vector<Entry> mEntries;
};
