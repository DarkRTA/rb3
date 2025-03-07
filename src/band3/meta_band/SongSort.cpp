#include "meta_band/SongSort.h"
#include "SongSortNode.h"
#include "meta/Sorting.h"
#include "meta_band/AppLabel.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "utl/Std.h"
#include "utl/Symbols.h"

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
    FOREACH (it, mFunctions) {
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
    if (idx >= (int)mList.size()) {
        MILO_FAIL("Trying to access item %i in list of %i items!", idx, (int)mList.size());
    }
    return mList[idx];
}

int NodeSort::GetDataCount() const { return mList.size(); }

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
    return node->mStartIx;
}

int NodeSort::GetShortcutIx(SortNode *node) const {
    if (node->mShortcut)
        return node->mShortcut->mIndex + 1;
    else
        return 0;
}

Symbol NodeSort::FirstChar(const char *c, bool b) { return FirstSortChar(c, b); }