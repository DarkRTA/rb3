#include "meta_band/SongSortNode.h"
#include "meta_band/SongSort.h"
#include "decomp.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MusicLibrary.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

Node::~Node() { RELEASE(mCmp); }

FORCE_LOCAL_INLINE
bool Node::Compare(const Node *n, SongNodeType ty) const {
    return mCmp->Compare(n->Cmp(), ty);
}
END_FORCE_LOCAL_INLINE

ShortcutNode::ShortcutNode(SongSortCmp *cmp, Symbol token, bool localize)
    : Node(cmp), mToken(token), mLocalizeToken(localize), mDateTime(0) {
    SetParent(nullptr);
}

ShortcutNode::~ShortcutNode() { delete mDateTime; }
Symbol ShortcutNode::GetToken() const { return mToken; }
bool ShortcutNode::LocalizeToken() const { return mLocalizeToken; }
DateTime *ShortcutNode::GetDateTime() const { return mDateTime; }

void ShortcutNode::DeleteAll() {
    FOREACH_POST (it, mChildren) {
        (*it)->DeleteAll();
        RELEASE(*it);
    }
    mChildren.clear();
}

void ShortcutNode::FinishSort(NodeSort *node) {
    FOREACH_POST (it, mChildren) {
        (*it)->FinishSort(node);
    }
}

void ShortcutNode::Renumber(std::vector<SortNode *> &nodes) {
    FOREACH_POST (it, mChildren) {
        (*it)->Renumber(nodes);
    }
}

bool ShortcutNode::IsActive() const {
    FOREACH_POST (it, mChildren) {
        if ((*it)->IsEnabled())
            return true;
    }
    return false;
}

SortNode *ShortcutNode::GetFirstActive() {
    FOREACH_POST (it, mChildren) {
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
    HANDLE_EXPR(get_index, GetIndex())
    HANDLE_EXPR(shortcut_str, ShortcutStr())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x9E)
END_HANDLERS

SortNode::~SortNode() { RELEASE(mCmp); }

void SortNode::DeleteAll() {
    FOREACH_POST (it, mChildren) {
        (*it)->DeleteAll();
        RELEASE(*it);
    }
    mChildren.clear();
}

void SortNode::Renumber(std::vector<SortNode *> &nodes) {
    mStartIx = nodes.size();
    nodes.push_back(this);
    FOREACH_POST (it, mChildren) {
        (*it)->Renumber(nodes);
    }
}

void SortNode::FinishSort(NodeSort *node) {
    FOREACH_POST (it, mChildren) {
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
    HANDLE_EXPR(get_index, GetIndex())
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
    FOREACH_POST (it, mChildren) {
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
    FOREACH_POST (it, mChildren) {
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

SubheaderSortNode::SubheaderSortNode(SongSortCmp *cmp, Symbol token, bool localize)
    : HeaderSortNode(cmp, token, localize) {}

void SubheaderSortNode::Insert(LeafSortNode *node, NodeSort *n2, bool b3) {
    MILO_ASSERT(Compare(node, kNodeSubheader) == 0, 0x1D2);
    std::list<SortNode *>::iterator it =
        std::lower_bound(mChildren.begin(), mChildren.end(), node, CompareLeaves());
    node->SetShortcut(mShortcut);
    node->SetParent(this);
    mChildren.insert(it, node);
}

BEGIN_HANDLERS(SubheaderSortNode)
    HANDLE_SUPERCLASS(HeaderSortNode)
    HANDLE_MEMBER_PTR(GetFirstChildSong())
    HANDLE_CHECK(0x1FC)
END_HANDLERS

Symbol FunctionSortNode::GetToken() const { return mToken; }
bool FunctionSortNode::IsEnabled() const { return IsActive(); }
bool FunctionSortNode::IsActive() const { return mActive; }

BEGIN_HANDLERS(FunctionSortNode)
    HANDLE_EXPR(get_token, mToken)
    HANDLE_EXPR(get_byline, mByline)
    HANDLE_EXPR(get_row_mat_path, mRowMatPath.c_str())
    HANDLE_SUPERCLASS(SortNode)
    HANDLE_CHECK(0x215)
END_HANDLERS

void SongSortNode::FinishSort(NodeSort *) { mCmp->Finish(); }

BEGIN_HANDLERS(SongSortNode)
    HANDLE_EXPR(get_total_ms, GetTotalMs())
    HANDLE_SUPERCLASS(SortNode)
    HANDLE_CHECK(0x226)
END_HANDLERS

Symbol OwnedSongSortNode::GetToken() const { return mSongRecord->mShortName; }

bool OwnedSongSortNode::IsEnabled() const { return IsActive(); }

const char *OwnedSongSortNode::GetAlbumArtPath() {
    if (mSongRecord->mData->HasAlbumArt()) {
        return TheSongMgr.GetAlbumArtPath(GetToken());
    } else
        return "ui/image/blank_album_art_keep.png";
}

const char *OwnedSongSortNode::GetTitle() const { return mSongRecord->mData->Title(); }
const char *OwnedSongSortNode::GetArtist() const { return mSongRecord->mData->Artist(); }
bool OwnedSongSortNode::GetIsCover() const {
    return !mSongRecord->mData->IsMasterRecording();
}
const char *OwnedSongSortNode::GetAlbum() const { return mSongRecord->mData->Album(); }
int OwnedSongSortNode::GetTotalMs() const { return mSongRecord->mData->LengthMs(); }
int OwnedSongSortNode::GetTotalScore() { return mSongRecord->GetScore(); }

int OwnedSongSortNode::GetTier(Symbol s) const { return mSongRecord->GetTier(s); }

BEGIN_HANDLERS(OwnedSongSortNode)
    HANDLE_MEMBER_PTR(mSongRecord)
    HANDLE_SUPERCLASS(SongSortNode)
    HANDLE_CHECK(0x289)
END_HANDLERS

int SetlistSortNode::GetSongCount() { return mSetlistRecord->mSetlist->mSongs.size(); }
Symbol SetlistSortNode::GetToken() const { return mSetlistRecord->mToken; }

const char *SetlistSortNode::GetAlbumArtPath() {
    return "ui/image/song_select_setlist_keep.png";
}

int SetlistSortNode::GetTotalMs() const {
    return mSetlistRecord->mSetlist->GetLengthMs();
}

BEGIN_HANDLERS(SetlistSortNode)
    HANDLE_EXPR(get_record, mSetlistRecord)
    HANDLE_MEMBER_PTR(mSetlistRecord)
    HANDLE_SUPERCLASS(SortNode)
    HANDLE_CHECK(0x2D0)
END_HANDLERS