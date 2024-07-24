#ifndef UI_UIGRIDPROVIDER_H
#define UI_UIGRIDPROVIDER_H
#include "ui/UIListProvider.h"

class UIGridProvider;
class UIGridSubProvider;

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

    void ResizeSubProviders() const;
    int NumDataForSublistIndex(int) const;
    void SetListToData(UIList*, int);
    void SetListToSymbol(UIList*, Symbol);
    int GetDataFromList(UIList*);
    Symbol GetSymbolFromList(UIList*);
    
    UIListProvider* mMasterProvider; // 0x4
    int mWidth; // 0x8
    std::vector<UIGridSubProvider*> mSubProviders; // 0xc
};

class UIGridSubProvider : public UIListProvider {
public:
    UIGridSubProvider(UIListProvider* lprov, UIGridProvider* gprov, int i) : mListProvider(lprov), mGridProvider(gprov), mIndex(i) {}
    virtual ~UIGridSubProvider(){}
    virtual void Text(int i, int j, UIListLabel* listlabel, UILabel* label) const {
        int idx = mIndex * mGridProvider->mWidth;
        mListProvider->Text(i + idx, j + idx, listlabel, label);
    }
    virtual RndMat* Mat(int i, int j, UIListMesh* mesh) const {
        int idx = mIndex * mGridProvider->mWidth;
        return mListProvider->Mat(i + idx, j + idx, mesh);
    }
    virtual void Custom(int i, int j, UIListCustom* custom, Hmx::Object* obj) const {
        int idx = mIndex * mGridProvider->mWidth;
        mListProvider->Custom(i + idx, j + idx, custom, obj);
    }
    virtual void UpdateExtendedText(int i, int j, UILabel* label) const {
        int idx = mIndex * mGridProvider->mWidth;
        mListProvider->UpdateExtendedText(i + idx, j + idx, label);
    }
    virtual void UpdateExtendedMesh(int i, int j, RndMesh* mesh) const {
        int idx = mIndex * mGridProvider->mWidth;
        mListProvider->UpdateExtendedMesh(i + idx, j + idx, mesh);
    }
    virtual void UpdateExtendedCustom(int i, int j, Hmx::Object* o) const {
        int idx = mIndex * mGridProvider->mWidth;
        mListProvider->UpdateExtendedCustom(i + idx, j + idx, o);
    }
    virtual Symbol DataSymbol(int i) const { return mListProvider->DataSymbol(i + mIndex * mGridProvider->mWidth); }
    virtual int DataIndex(Symbol s) const { return mListProvider->DataIndex(s) % mGridProvider->mWidth; }
    virtual int NumData() const { return mGridProvider->NumDataForSublistIndex(mIndex); }
    virtual bool IsActive(int i) const { return mListProvider->IsActive(i + mIndex * mGridProvider->mWidth); }
    virtual bool IsHidden(int i) const { return mListProvider->IsHidden(i + mIndex * mGridProvider->mWidth); }

    UIListProvider* mListProvider; // 0x4
    UIGridProvider* mGridProvider; // 0x8
    int mIndex; // 0xc
};

#endif