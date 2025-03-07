#pragma once
#include "obj/Object.h"
#include "ui/UIListProvider.h"
#include "meta_band/SongSortNode.h"

class NodeSort : public UIListProvider, public Hmx::Object {
public:
    NodeSort();
    virtual ~NodeSort() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual void Custom(int, int, class UIListCustom *, Hmx::Object *) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void DeleteTree();
    virtual void Init();
    virtual int NewShortcutNode(LeafSortNode *) const = 0; // ret type?
    virtual int NewHeaderNode(LeafSortNode *) const = 0; // ret type?
    virtual int NewSubheaderNode(LeafSortNode *) const = 0; // ret type
    virtual void ConfirmSubheaders(HeaderSortNode *);
    virtual void Clear();
    virtual bool CustomForNode(ShortcutNode *, UIListCustom *, Hmx::Object *) const;
    virtual const char *TextForNode(ShortcutNode *, UIListLabel *, UILabel *) const;
    virtual bool IsReady() const;
    virtual void PollReady();
    virtual void MakeReady();
    virtual void CancelMakeReady();

    void DeleteList();
    SortNode *GetNode(Symbol) const;
    SortNode *GetNode(int) const;
    int GetDataCount() const;
    int FirstActiveIxForShortcut(int) const;
    int GetShortcutIx(SortNode *) const;

    static Symbol FirstChar(const char *, bool);

    std::vector<ShortcutNode *> mTree; // 0x20
    std::list<SortNode *> mFunctions; // 0x28
    std::vector<SortNode *> mList; // 0x30
    Symbol mShortName; // 0x38
};