#pragma once
#include "SongSortNode.h"
#include "StoreSongSortNode.h"
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
    virtual void Init() {}
    virtual ShortcutNode *NewShortcutNode(LeafSortNode *) const = 0;
    virtual HeaderSortNode *NewHeaderNode(LeafSortNode *) const = 0;
    virtual SubheaderSortNode *NewSubheaderNode(LeafSortNode *) const = 0;
    virtual void ConfirmSubheaders(HeaderSortNode *) {}
    virtual void Clear() {}
    virtual bool CustomForNode(ShortcutNode *, UIListCustom *, Hmx::Object *) const {
        return false;
    }
    virtual const char *TextForNode(ShortcutNode *, UIListLabel *, UILabel *) const {
        return nullptr;
    }
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

class SongSort : public NodeSort {
public:
    SongSort() {}
    virtual ~SongSort() {}
    virtual ShortcutNode *NewShortcutNode(LeafSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(LeafSortNode *) const;
    virtual SubheaderSortNode *NewSubheaderNode(LeafSortNode *) const;
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const = 0;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const = 0;
    virtual SubheaderSortNode *NewSubheaderNode(SongSortNode *) const {
        MILO_FAIL("Unimplemented");
        return nullptr;
    }
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const = 0;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const = 0;

    void BuildSongTree(std::map<Symbol, SongRecord> &, std::vector<StoreOffer *> &);
    void BuildSongList();
};

class SetlistSort : public NodeSort {
public:
    SetlistSort() {}
    virtual ~SetlistSort() {}
    virtual ShortcutNode *NewShortcutNode(LeafSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(LeafSortNode *) const;
    virtual SubheaderSortNode *NewSubheaderNode(LeafSortNode *) const;
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const = 0;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const = 0;
    virtual SubheaderSortNode *NewSubheaderNode(SongSortNode *) const;
    virtual ShortcutNode *NewShortcutNode(FunctionSortNode *) const = 0;
    virtual HeaderSortNode *NewHeaderNode(FunctionSortNode *) const = 0;
    virtual SetlistSortNode *NewSetlistNode(SetlistRecord *) const = 0;
    virtual FunctionSortNode *NewFunctionNode(Symbol) const = 0;

    void BuildSetlistTree(std::map<Symbol, SetlistRecord> &);
    void BuildSetlistList();
};

struct CompareShortcuts {
    int operator()(const Node *n1, const Node *n2) const {
        return n1->Compare(n2, kNodeShortcut) < 0;
    }
};