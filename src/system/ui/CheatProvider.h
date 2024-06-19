#ifndef UI_CHEATPROVIDER_H
#define UI_CHEATPROVIDER_H
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class CheatProvider : public UIListProvider, public Hmx::Object {
public:
    class Cheat {
    public:
        String mKey; // 0x0
        String mDesc; // 0xc
        DataArray* mScript; // 0x18
    };

    CheatProvider();
    virtual ~CheatProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir*);
    virtual DataNode Handle(DataArray*, bool);

    void ApplyFilter();

    std::vector<Cheat> mCheats; // 0x20
    std::vector<Cheat> mFilterCheats; // 0x28
    std::vector<Symbol> mFilters; // 0x30
    int mFilterIdx; // 0x38
};

#endif
