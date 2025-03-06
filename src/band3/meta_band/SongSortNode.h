#pragma once
#include "meta_band/SongSort.h"
#include "obj/Object.h"
#include "os/DateTime.h"

enum SongNodeType {
    kNodeNone = 0,
    kNodeShortcut = 1,
    kNodeHeader = 2,
    kNodeSubheader = 3,
    kNodeSong = 4,
    kNodeFunction = 5,
    kNodeSetlist = 6,
    kNodeStoreSong = 7
};

class SongSortCmp {
public:
    SongSortCmp() {}
    virtual ~SongSortCmp() {}
    virtual bool Compare(SongSortCmp const *, SongNodeType) const = 0;
    virtual bool HasSubheader() const { return false; }
    virtual void Finish() {}
};

class Node : public Hmx::Object {
public:
    Node(SongSortCmp *cmp) : mCmp(0), mParent(0) {}
    virtual ~Node();
    virtual SongNodeType GetType() const = 0;
    virtual Symbol GetToken() const = 0;
    virtual bool LocalizeToken() const { return true; }
    virtual DateTime *GetDateTime() const { return nullptr; }

    bool Compare(const Node *, SongNodeType) const;
    void SetParent(Node *parent) { mParent = parent; }

    SongSortCmp *mCmp; // 0x1c
    Node *mParent; // 0x20
};

class SortNode;

class ShortcutNode : public Node {
public:
    ShortcutNode(SongSortCmp *, Symbol, bool);
    virtual ~ShortcutNode();
    virtual DataNode Handle(DataArray *, bool);
    virtual SongNodeType GetType() const { return kNodeShortcut; }
    virtual Symbol GetToken() const;
    virtual bool LocalizeToken() const;
    virtual DateTime *GetDateTime() const;
    virtual void DeleteAll();

    void Insert(LeafSortNode *, NodeSort *);
    void FinishSort(NodeSort *);
    void Renumber(std::vector<SortNode *> &nodes);
    bool IsActive() const;
    SortNode *GetFirstActive();
    const char *ShortcutStr();

    int mIndex; // 0x24
    Symbol mToken; // 0x28
    bool mLocalizeToken; // 0x2c
    DateTime *mDateTime; // 0x30
    std::list<SortNode *> mChildren; // 0x34
};

class SortNode : public Node {
public:
    SortNode(SongSortCmp *cmp) : Node(cmp), mShortcut(0), mStartIx(-1) {}
    virtual ~SortNode();
    virtual DataNode Handle(DataArray *, bool);
    virtual void FinishSort(NodeSort *);
    virtual int GetSongCount() = 0;
    virtual SortNode *GetFirstActive() = 0;
    virtual bool IsActive() const = 0;
    virtual bool IsEnabled() const = 0;
    virtual const char *GetAlbumArtPath() = 0;
    virtual void DeleteAll();
    virtual void Renumber(std::vector<SortNode *> &);
    virtual int GetTotalMs() const;
    virtual int GetTotalScore();
    virtual int GetTotalStars(bool);
    virtual int GetPotentialStars();

    void SetShortcut(ShortcutNode *);

    std::list<SortNode *> mChildren; // 0x24
    ShortcutNode *mShortcut; // 0x2c
    int mStartIx; // 0x30
};

// LeafSortNode : SortNode
class LeafSortNode : public SortNode {
public:
    LeafSortNode(SongSortCmp *cmp) : SortNode(cmp) {}
    virtual ~LeafSortNode() {}
};

// HeaderSortNode : SortNode
class HeaderSortNode : public SortNode {
public:
    HeaderSortNode(SongSortCmp *, Symbol, bool);
    virtual ~HeaderSortNode();
    virtual DataNode Handle(DataArray *, bool);
    virtual SongNodeType GetType() const;
    virtual Symbol GetToken() const;
    virtual bool LocalizeToken() const;
    virtual DateTime *GetDateTime() const;
    virtual void FinishSort(NodeSort *);
    virtual int GetSongCount();
    virtual SortNode *GetFirstActive();
    virtual bool IsActive() const;
    virtual bool IsEnabled() const;
    virtual const char *GetAlbumArtPath();
    virtual void Insert(LeafSortNode *, NodeSort *, bool);

    bool unk34; // 0x34 - cover
    int unk38; // 0x38 - disc count
    int unk3c; // 0x3c - download count
    Symbol mToken; // 0x40
    bool mLocalizeToken; // 0x44
    DateTime *mDateTime; // 0x48
};