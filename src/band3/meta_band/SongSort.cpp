#include "meta_band/SongSort.h"
#include "SongSortNode.h"
#include "decomp.h"
#include "game/GameMode.h"
#include "meta/Sorting.h"
#include "meta_band/AppLabel.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/SongRecord.h"
#include "meta_band/Utl.h"
#include "net_band/RockCentral.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

NodeSort::NodeSort() : mTree(0) {}

void NodeSort::DeleteTree() {
    ClearAndShrink(mList);
    FOREACH (it, mTree) {
        (*it)->DeleteAll();
        RELEASE(*it);
    }
    ClearAndShrink(mTree);
}

void NodeSort::DeleteList() {
    ClearAndShrink(mList);
    FOREACH_POST (it, mFunctions) {
        (*it)->DeleteAll();
        RELEASE(*it);
    }
    mFunctions.clear();
}

SortNode *NodeSort::GetNode(Symbol s) const {
    FOREACH (it, mList) {
        if (s == (*it)->GetToken()) {
            return *it;
        }
    }
    return nullptr;
}

SortNode *NodeSort::GetNode(int idx) const {
    int count = GetDataCount();
    if (idx >= count) {
        MILO_FAIL("Trying to access item %i in list of %i items!", idx, count);
    }
    return mList[idx];
}

FORCE_LOCAL_INLINE
int NodeSort::GetDataCount() const { return mList.size(); }
END_FORCE_LOCAL_INLINE

void NodeSort::Custom(int, int data, UIListCustom *custom, Hmx::Object *obj) const {
    if (data == 0 || !CustomForNode(mTree[data - 1], custom, obj)) {
        RndDrawable *d = dynamic_cast<RndDrawable *>(obj);
        if (d)
            d->SetShowing(false);
    }
}

void NodeSort::Text(int, int idx, UIListLabel *slot, UILabel *label) const {
    if (idx == 0) {
        label->SetTextToken(song_select_functions);
    } else if (!TextForNode(mTree[idx - 1], slot, label)) {
        AppLabel *appLabel = dynamic_cast<AppLabel *>(label);
        MILO_ASSERT(appLabel, 0x85);
        appLabel->SetFromSongSelectNode(mTree[idx - 1]);
    }
}

int NodeSort::NumData() const {
    MILO_ASSERT(mFunctions.size(), 0x8C);
    return mTree.size() + 1;
}

bool NodeSort::IsActive(int idx) const {
    if (idx == 0) {
        return true;
    } else
        return mTree[idx - 1]->IsActive();
}

int NodeSort::FirstActiveIxForShortcut(int idx) const {
    SortNode *node = idx == 0 ? mFunctions.front() : mTree[idx - 1]->GetFirstActive();
    MILO_ASSERT(node, 0xA0);
    return node->GetIndex();
}

int NodeSort::GetShortcutIx(SortNode *node) const {
    if (node->mShortcut)
        return node->mShortcut->mIndex + 1;
    else
        return 0;
}

Symbol NodeSort::FirstChar(const char *c, bool b) { return FirstSortChar(c, b); }

void SongSort::BuildSongTree(
    std::map<Symbol, SongRecord> &records, std::vector<StoreOffer *> &offers
) {
    if (IsReady()) {
        DeleteTree();
        Init();
        FOREACH_POST (it, records) {
            SongSortNode *newSong = NewSongNode(&it->second);
            std::pair<ShortcutNode **, ShortcutNode **> found;
            found =
                std::equal_range(mTree.begin(), mTree.end(), newSong, CompareShortcuts());
            ShortcutNode *shortcut;
            if (found.first != found.second) {
                shortcut = *found.first;
                MILO_ASSERT(0 == newSong->Compare(shortcut, kNodeShortcut), 0xCD);
            } else {
                shortcut = NewShortcutNode(newSong);
                mTree.insert(found.first, shortcut);
            }
            shortcut->Insert(newSong, this);
        }
        FOREACH (it, offers) {
            SongSortNode *newSong = NewSongNode(*it);
            std::pair<ShortcutNode **, ShortcutNode **> found;
            found =
                std::equal_range(mTree.begin(), mTree.end(), newSong, CompareShortcuts());
            ShortcutNode *shortcut;
            if (found.first != found.second) {
                shortcut = *found.first;
                MILO_ASSERT(0 == newSong->Compare(shortcut, kNodeShortcut), 0xE8);
            } else {
                shortcut = NewShortcutNode(newSong);
                mTree.insert(found.first, shortcut);
            }
            shortcut->Insert(newSong, this);
        }
        FOREACH (it, mTree) {
            (*it)->FinishSort(this);
        }
        for (int i = 0; i < mTree.size(); i++) {
            mTree[i]->mIndex = i;
        }
    }
}

void SongSort::BuildSongList() {
    if (IsReady()) {
        DeleteList();
        if (TheMusicLibrary->GetMakingSetlist(true) && IsLeaderLocal()) {
            mFunctions.insert(
                mFunctions.begin(),
                new FunctionSortNode(
                    nullptr,
                    true,
                    play_setlist,
                    play_setlist_by_line,
                    "ui/image/song_select_setlist_keep.png",
                    "highlight_function.mat"
                )
            );
        }

        mFunctions.insert(
            mFunctions.begin(),
            new FunctionSortNode(
                nullptr,
                true,
                random_song,
                random_song_by_line,
                "ui/image/song_select_random_keep.png",
                "highlight_function_random.mat"
            )
        );

        if (TheGameMode->InMode(qp_coop)) {
            mFunctions.insert(
                mFunctions.begin(),
                new FunctionSortNode(
                    nullptr,
                    true,
                    party_setlist,
                    party_setlist_by_line,
                    "ui/image/song_select_setlist_keep.png",
                    "highlight_function.mat"
                )
            );
            mFunctions.insert(
                mFunctions.begin(),
                new FunctionSortNode(
                    nullptr,
                    true,
                    view_setlists,
                    view_setlists_by_line,
                    "ui/image/song_select_setlist_keep.png",
                    "highlight_function_setlist.mat"
                )
            );
        }
        mList.reserve(6100);
        FOREACH (it, mFunctions) {
            (*it)->Renumber(mList);
        }
        FOREACH (it, mTree) {
            (*it)->Renumber(mList);
        }
        TrimExcess(mList);
    }
}

ShortcutNode *SongSort::NewShortcutNode(LeafSortNode *node) const {
    SongSortNode *song = dynamic_cast<SongSortNode *>(node);
    MILO_ASSERT(song, 0x141);
    return NewShortcutNode(song);
}

HeaderSortNode *SongSort::NewHeaderNode(LeafSortNode *node) const {
    SongSortNode *song = dynamic_cast<SongSortNode *>(node);
    MILO_ASSERT(song, 0x148);
    return NewHeaderNode(song);
}

SubheaderSortNode *SongSort::NewSubheaderNode(LeafSortNode *node) const {
    SongSortNode *song = dynamic_cast<SongSortNode *>(node);
    MILO_ASSERT(song, 0x14F);
    return NewSubheaderNode(song);
}

void SetlistSort::BuildSetlistTree(std::map<Symbol, SetlistRecord> &records) {
    DeleteTree();
    Init();
    FOREACH (it, records) {
        SetlistSortNode *newSetlist = NewSetlistNode(&it->second);
        std::pair<ShortcutNode **, ShortcutNode **> found;
        found =
            std::equal_range(mTree.begin(), mTree.end(), newSetlist, CompareShortcuts());
        ShortcutNode *shortcut;
        if (found.first != found.second) {
            shortcut = *found.first;
            MILO_ASSERT(0 == newSetlist->Compare(shortcut, kNodeShortcut), 0x16B);
        } else {
            shortcut = NewShortcutNode((SongSortNode *)newSetlist);
            mTree.insert(found.first, shortcut);
        }
        shortcut->Insert(newSetlist, this);
    }
    FunctionSortNode *fsn = nullptr;
    if (TheMusicLibrary->NetSetlistsFailed()) {
        if (TheRockCentral.unk3c != 2) {
            fsn = NewFunctionNode(net_setlists_connect);
        } else
            fsn = NewFunctionNode(net_setlists_error);
    } else if (!TheMusicLibrary->NetSetlistsSucceeded())
        fsn = NewFunctionNode(net_setlists_getting);

    if (fsn) {
        std::pair<ShortcutNode **, ShortcutNode **> found;
        found = std::equal_range(mTree.begin(), mTree.end(), fsn, CompareShortcuts());
        ShortcutNode *shortcut;
        if (found.first != found.second) {
            shortcut = *found.first;
            MILO_ASSERT(0 == fsn->Compare(shortcut, kNodeShortcut), 0x197);
        } else {
            shortcut = NewShortcutNode(fsn);
            mTree.insert(found.first, shortcut);
        }
        shortcut->Insert(fsn, this);
    }
    FOREACH (it, mTree) {
        (*it)->FinishSort(this);
    }
    for (int i = 0; i < mTree.size(); i++) {
        mTree[i]->mIndex = i;
    }
}

void SetlistSort::BuildSetlistList() {
    DeleteList();
    mFunctions.insert(
        mFunctions.begin(),
        new FunctionSortNode(
            nullptr,
            true,
            make_a_setlist,
            make_a_setlist_by_line,
            "ui/image/song_select_setlist_keep.png",
            "highlight_function_setlist.mat"
        )
    );
    mFunctions.insert(
        mFunctions.begin(),
        new FunctionSortNode(
            nullptr,
            true,
            view_songs,
            view_songs_by_line,
            "ui/image/song_select_setlist_keep.png",
            "highlight_function_setlist.mat"
        )
    );
    mList.reserve(0x140);
    FOREACH_POST (it, mFunctions) {
        (*it)->Renumber(mList);
    }
    FOREACH (it, mTree) {
        (*it)->Renumber(mList);
    }
    TrimExcess(mList);
}

ShortcutNode *SetlistSort::NewShortcutNode(LeafSortNode *node) const {
    SetlistSortNode *setlist = dynamic_cast<SetlistSortNode *>(node);
    FunctionSortNode *fsn = dynamic_cast<FunctionSortNode *>(node);
    MILO_ASSERT(setlist || fsn, 0x1D2);
    if (setlist) {
        return NewShortcutNode((SongSortNode *)setlist);
    } else
        return NewShortcutNode(fsn);
}

HeaderSortNode *SetlistSort::NewHeaderNode(LeafSortNode *node) const {
    SetlistSortNode *setlist = dynamic_cast<SetlistSortNode *>(node);
    FunctionSortNode *fsn = dynamic_cast<FunctionSortNode *>(node);
    MILO_ASSERT(setlist || fsn, 0x1DD);
    if (setlist) {
        return NewHeaderNode((SongSortNode *)setlist);
    } else
        return NewHeaderNode(fsn);
}

SubheaderSortNode *SetlistSort::NewSubheaderNode(LeafSortNode *node) const {
    SetlistSortNode *setlist = dynamic_cast<SetlistSortNode *>(node);
    MILO_ASSERT(setlist, 0x1E7);
    return NewSubheaderNode((SongSortNode *)setlist);
}