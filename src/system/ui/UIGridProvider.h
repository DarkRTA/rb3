#ifndef UI_UIGRIDPROVIDER_H
#define UI_UIGRIDPROVIDER_H
#include "ui/UIListProvider.h"

class UIGridProvider;

class UIGridSubProvider : public UIListProvider {
public:
    UIGridSubProvider(UIListProvider* lprov, UIGridProvider* gprov, int i) : mListProvider(lprov), mGridProvider(gprov), mIndex(i) {}
    virtual ~UIGridSubProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual void UpdateExtendedText(int, int, UILabel*) const;
    virtual void UpdateExtendedMesh(int, int, RndMesh*) const;
    virtual void UpdateExtendedCustom(int, int, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int DataIndex(Symbol) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual bool IsHidden(int) const;

    UIListProvider* mListProvider; // 0x4
    UIGridProvider* mGridProvider; // 0x8
    int mIndex; // 0xc
};

class UIGridProvider : public UIListProvider {
public:
    UIGridProvider(UIListProvider*, int);
    virtual ~UIGridProvider();
    virtual UIListProvider* Provider(int, int, UIListSubList*) const;
    virtual void UpdateExtendedText(int, int, UILabel*) const;
    virtual void UpdateExtendedMesh(int, int, RndMesh*) const;
    virtual void UpdateExtendedCustom(int, int, Hmx::Object*) const;
    virtual int NumData() const;
    virtual void InitData(RndDir*);
    
    UIListProvider* mMasterProvider; // 0x4
    int mWidth; // 0x8
    std::vector<UIGridSubProvider> mSubProviders; // 0xc
};

#endif
