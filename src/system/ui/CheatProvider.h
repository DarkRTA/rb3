#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

/**
 * @brief Handles data for the debug cheat menu.
 */
class CheatProvider : public UIListProvider, public Hmx::Object {
public:
    /**
    * @brief Handles individual entries in cheats.lst
    */
    class Cheat {
    public:
        Cheat(const char* desc) : mKey(), mDesc(desc), mScript(0) {}
        Cheat(const String& key, const String& desc, DataArray* script) : mKey(key), mDesc(desc), mScript(script) {}
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

    void Invoke(int, LocalUser*);
    void NextFilter();
    void ApplyFilter();

    static void Init();
    static void Terminate();
    static CheatProvider* sInstance;

    std::vector<Cheat> mCheats; // 0x20
    std::vector<Cheat> mFilterCheats; // 0x28
    std::vector<Symbol> mFilters; // 0x30
    int mFilterIdx; // 0x38
};
