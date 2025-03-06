#include "meta_band/SongSortNode.h"
#include "meta_band/MusicLibrary.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

Node::~Node() { RELEASE(mCmp); }

bool Node::Compare(const Node *n, SongNodeType ty) const {
    return mCmp->Compare(n->mCmp, ty);
}

ShortcutNode::ShortcutNode(SongSortCmp *cmp, Symbol token, bool localize)
    : Node(cmp), mToken(token), mLocalizeToken(localize), mDateTime(0) {
    SetParent(nullptr);
}

ShortcutNode::~ShortcutNode() { delete mDateTime; }
Symbol ShortcutNode::GetToken() const { return mToken; }
bool ShortcutNode::LocalizeToken() const { return mLocalizeToken; }
DateTime *ShortcutNode::GetDateTime() const { return mDateTime; }

void ShortcutNode::DeleteAll() {
    FOREACH (it, mChildren) {
        (*it)->DeleteAll();
        RELEASE(*it);
    }
    mChildren.clear();
}

void ShortcutNode::FinishSort(NodeSort *node) {
    FOREACH (it, mChildren) {
        (*it)->FinishSort(node);
    }
}

void ShortcutNode::Renumber(std::vector<SortNode *> &nodes) {
    FOREACH (it, mChildren) {
        (*it)->Renumber(nodes);
    }
}

bool ShortcutNode::IsActive() const {
    FOREACH (it, mChildren) {
        if ((*it)->IsEnabled())
            return true;
    }
    return false;
}

SortNode *ShortcutNode::GetFirstActive() {
    FOREACH (it, mChildren) {
        SortNode *node = (*it)->GetFirstActive();
        if (node)
            return node;
    }
    return nullptr;
}

const char *ShortcutNode::ShortcutStr() {
    if (LocalizeToken()) {
        return Localize(GetToken(), nullptr);
    } else
        return GetToken().mStr;
}

BEGIN_HANDLERS(ShortcutNode)
    HANDLE_EXPR(get_index, mIndex)
    HANDLE_EXPR(shortcut_str, ShortcutStr())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x9E)
END_HANDLERS

SortNode::~SortNode() { RELEASE(mCmp); }

void SortNode::DeleteAll() {
    FOREACH (it, mChildren) {
        (*it)->DeleteAll();
        RELEASE(*it);
    }
    mChildren.clear();
}

void SortNode::Renumber(std::vector<SortNode *> &nodes) {
    mStartIx = nodes.size();
    nodes.push_back(this);
    FOREACH (it, mChildren) {
        (*it)->Renumber(nodes);
    }
}

void SortNode::FinishSort(NodeSort *node) {
    FOREACH (it, mChildren) {
        (*it)->FinishSort(node);
    }
}

void SortNode::SetShortcut(ShortcutNode *node) { mShortcut = node; }

int SortNode::GetTotalMs() const {
    int sum = 0;
    FOREACH (it, mChildren) {
        sum += (*it)->GetTotalMs();
    }
    return sum;
}

int SortNode::GetTotalScore() {
    int sum = 0;
    FOREACH (it, mChildren) {
        sum += (*it)->GetTotalScore();
    }
    return sum;
}

int SortNode::GetTotalStars(bool b) {
    int sum = 0;
    FOREACH (it, mChildren) {
        sum += (*it)->GetTotalStars(b);
    }
    return sum;
}

int SortNode::GetPotentialStars() {
    int sum = 0;
    FOREACH (it, mChildren) {
        sum += (*it)->GetPotentialStars();
    }
    return sum;
}

BEGIN_HANDLERS(SortNode)
    HANDLE_EXPR(album_art_path, GetAlbumArtPath())
    HANDLE_EXPR(get_node_type, GetType())
    HANDLE_EXPR(get_index, mStartIx)
    HANDLE_EXPR(get_token, GetToken())
    HANDLE_EXPR(get_total_ms, GetTotalMs())
    HANDLE_EXPR(get_total_score, GetTotalScore())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xFC)
END_HANDLERS

HeaderSortNode::HeaderSortNode(SongSortCmp *cmp, Symbol token, bool localize)
    : SortNode(cmp), unk34(0), unk38(0), unk3c(0), mToken(token),
      mLocalizeToken(localize), mDateTime(0) {}

HeaderSortNode::~HeaderSortNode() { delete mDateTime; }
Symbol HeaderSortNode::GetToken() const { return mToken; }
bool HeaderSortNode::LocalizeToken() const { return mLocalizeToken; }
DateTime *HeaderSortNode::GetDateTime() const { return mDateTime; }

SortNode *HeaderSortNode::GetFirstActive() {
    FOREACH (it, mChildren) {
        SortNode *node = (*it)->GetFirstActive();
        if (node) {
            return TheMusicLibrary->CanHeadersBeSelected() ? this : node;
        }
    }
    return nullptr;
}

bool HeaderSortNode::IsActive() const {
    return TheMusicLibrary->CanHeadersBeSelected() ? IsEnabled() : false;
}

bool HeaderSortNode::IsEnabled() const {
    FOREACH (it, mChildren) {
        SortNode *cur = *it;
        if (cur->GetType() == 3) {
            if (cur->IsEnabled())
                return true;
        } else if (cur->IsActive()) {
            return true;
        }
    }
    return false;
}

const char *HeaderSortNode::GetAlbumArtPath() {
    return "ui/image/song_select_header_keep.png";
}

BEGIN_HANDLERS(HeaderSortNode)
    HANDLE_EXPR(get_song_count, GetSongCount())
    HANDLE_EXPR(get_token, mToken)
    HANDLE_SUPERCLASS(SortNode)
    HANDLE_CHECK(0x1C4)
END_HANDLERS