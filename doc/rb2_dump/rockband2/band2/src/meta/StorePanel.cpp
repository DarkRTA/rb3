/*
    Compile unit: C:\rockband2\band2\src\meta\StorePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8018930C -> 0x8018EB28
*/
class Symbol t; // size: 0x4, address: 0x80A4CD5C
class DataArray * types; // size: 0x4, address: 0x80A4CD60
static class Symbol _s; // size: 0x4, address: 0x80A4CD68
// Range: 0x8018930C -> 0x801896B4
class DataNode SelectedFilter::Handle(class SelectedFilter * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class Symbol store_view_album; // size: 0x4, address: 0x80A4CD70
class Symbol store_view_pack; // size: 0x4, address: 0x80A4CD78
class Symbol name; // size: 0x4, address: 0x80A4CD80
class Symbol exit; // size: 0x4, address: 0x80A4CD88
class Symbol store_back_song; // size: 0x4, address: 0x80A4CD90
class Symbol store_preview_audio; // size: 0x4, address: 0x80A4CD98
class Symbol store_buy_now; // size: 0x4, address: 0x80A4CDA0
class Symbol store_download_again; // size: 0x4, address: 0x80A4CDA8
class Symbol store_view_album; // size: 0x4, address: 0x80A4CDB0
class Symbol store_view_pack; // size: 0x4, address: 0x80A4CDB8
class Symbol exit; // size: 0x4, address: 0x80A4CDC0
class Symbol song; // size: 0x4, address: 0x80A4CDC8
class Symbol store_delete; // size: 0x4, address: 0x80A4CDD0
static class Symbol _s; // size: 0x4, address: 0x80A4CDD8
static class Symbol _s; // size: 0x4, address: 0x80A4CDE0
static class Symbol _s; // size: 0x4, address: 0x80A4CDE8
static class Symbol _s; // size: 0x4, address: 0x80A4CDF0
class InfoProvider : public ListProvider, public Object {
    // total size: 0x44
    const class StoreOfferProvider * mStoreOfferProvider; // offset 0x2C, size 0x4
    const class StoreOffer * mOffer; // offset 0x30, size 0x4
    const class StoreOffer * mBackOffer; // offset 0x34, size 0x4
    class vector mOptions; // offset 0x38, size 0xC
};
// Range: 0x801896B4 -> 0x80189DC0
class DataNode InfoProvider::Handle(class InfoProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10StoreOffer;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80189DC0 -> 0x80189DD8
int InfoProvider::NumData() {}

// Range: 0x80189DD8 -> 0x8018A3F4
class DataNode InfoProvider::OnSetOffer(class InfoProvider * const this /* r30 */, class DataArray * pData /* r28 */) {
    // Local variables
    unsigned char showPreview; // r31
    class StoreOffer * a; // r28
    class StoreOffer * p; // r28

    // References
    // -> class Debug TheDebug;
    // -> class Symbol store_delete;
    // -> class Symbol song;
    // -> class Symbol exit;
    // -> class Symbol store_view_pack;
    // -> class Symbol store_view_album;
    // -> class Symbol store_download_again;
    // -> class Symbol store_buy_now;
    // -> class Symbol store_preview_audio;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10StoreOffer;
}

class Symbol track; // size: 0x4, address: 0x80A4CDF8
class Symbol name; // size: 0x4, address: 0x80A4CE00
static class Symbol _s; // size: 0x4, address: 0x80A4CE08
static class Symbol _s; // size: 0x4, address: 0x80A4CE10
class InfoSongProvider : public ListProvider, public Object {
    // total size: 0x34
    const class StoreOfferProvider * mStoreOfferProvider; // offset 0x2C, size 0x4
    const class StoreOffer * mOffer; // offset 0x30, size 0x4
};
// Range: 0x8018A3F4 -> 0x8018A8AC
class DataNode InfoSongProvider::Handle(class InfoSongProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10StoreOffer;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8018A8AC -> 0x8018A914
int InfoSongProvider::NumData(const class InfoSongProvider * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class NetLoader {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class String mStrRemotePath; // offset 0x4, size 0xC
    unsigned char mIsLoaded; // offset 0x10, size 0x1
    char * mBuffer; // offset 0x14, size 0x4
    unsigned char mBufferOwner; // offset 0x18, size 0x1
    int mSize; // offset 0x1C, size 0x4
};
class DataNetLoader {
    // total size: 0x8
    class NetLoader * mLoader; // offset 0x0, size 0x4
    class DataArray * mData; // offset 0x4, size 0x4
};
class StorePreviewMgrWii : public MsgSource {
    // total size: 0x60
    class String mStrPathCur; // offset 0x1C, size 0xC
    class StreamPlayer * mStreamPlayer; // offset 0x28, size 0x4
    unsigned char mIsDownloading; // offset 0x2C, size 0x1
    class NetLoader * mNetLoader; // offset 0x30, size 0x4
};
// Range: 0x8018A914 -> 0x8018AA20
void * StorePanel::StorePanel(class StorePanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10StorePanel;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class NetCacheLoader * _M_data; // offset 0x8, size 0x4
};
// Range: 0x8018AA20 -> 0x8018ABB8
void StorePanel::Load(class StorePanel * const this /* r28 */) {
    // References
    // -> const char * gNullStr;
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__14SelectedFilter;
}

// Range: 0x8018ABB8 -> 0x8018ACD8
void StorePanel::HandleNetCacheMgrFailure(class StorePanel * const this /* r29 */, int failType /* r30 */) {
    // References
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018ACD8 -> 0x8018AFB4
unsigned char StorePanel::IsLoaded(class StorePanel * const this /* r31 */) {
    // Local variables
    unsigned char ret; // r0
    unsigned char metadata_loaded; // r27

    // References
    // -> class Debug TheDebug;
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
}

static class Symbol offers; // size: 0x4, address: 0x80A4CE18
static class Symbol year_released; // size: 0x4, address: 0x80A4CE20
static class Symbol genre; // size: 0x4, address: 0x80A4CE28
static class Symbol song; // size: 0x4, address: 0x80A4CE30
static class Symbol album; // size: 0x4, address: 0x80A4CE38
static class Symbol store; // size: 0x4, address: 0x80A4CE40
static class Symbol filters; // size: 0x4, address: 0x80A4CE48
static class Symbol sorts; // size: 0x4, address: 0x80A4CE50
// Range: 0x8018AFB4 -> 0x8018B6E4
void StorePanel::FinishLoad(class StorePanel * const this /* r30 */) {
    // Local variables
    class DataArray * o; // r28
    int i; // r29
    class StoreOffer new_offer; // r1+0xA8
    enum StoreError se; // r4
    class vector decades; // r1+0x64
    class vector genres; // r1+0x58
    const class StoreOffer * s; // r27
    int year; // r0
    int decade; // r1+0x40
    class Symbol g; // r1+0x3C
    int i; // r27
    int i; // r27
    class DataArray * cfg; // r27
    class DataArray * f; // r28
    int i; // r29

    // References
    // -> static class Symbol sorts;
    // -> static class Symbol filters;
    // -> static class Symbol store;
    // -> static class Symbol album;
    // -> static class Symbol song;
    // -> static class Symbol genre;
    // -> static class Symbol year_released;
    // -> static class Symbol offers;
    // -> class DebugFailer TheDebugFailer;
    // -> const char * kAssertStr;
}

// Range: 0x8018B6E4 -> 0x8018B760
void * InfoProvider::InfoProvider(class InfoProvider * const this /* r30 */, const class StoreOfferProvider * op /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12InfoProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x8018B760 -> 0x8018B7CC
void * InfoSongProvider::InfoSongProvider(class InfoSongProvider * const this /* r30 */, const class StoreOfferProvider * op /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16InfoSongProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x8018B7CC -> 0x8018B800
void StorePanel::Enter(class StorePanel * const this /* r31 */) {}

static class Message msg; // size: 0x8, address: 0x80979E30
static class Message msg; // size: 0x8, address: 0x80979E48
static class Message msg; // size: 0x8, address: 0x80979E60
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8018B800 -> 0x8018BEC0
void StorePanel::Poll(class StorePanel * const this /* r29 */) {
    // Local variables
    struct _List_iterator l; // r1+0x40
    class NetCacheLoader * loader; // r28
    int size; // r27
    void * pBuffer; // r26
    class RndBitmap bmp; // r1+0xA4
    class BufStream stream; // r1+0x80
    enum NetCacheMgrFailType failType; // r26
    enum StoreError se; // r4

    // References
    // -> static class Message msg;
    // -> class UIManager TheUI;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetCacheMgr * TheNetCacheMgr;
}

// Range: 0x8018BEC0 -> 0x8018BEC4
void StorePanel::Exit() {}

// Range: 0x8018BEC4 -> 0x8018BEC8
unsigned char StorePanel::Exiting() {}

// Range: 0x8018BEC8 -> 0x8018C314
void StorePanel::Unload(class StorePanel * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x48

    // References
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> const char * gNullStr;
    // -> class PlatformMgr ThePlatformMgr;
}

class list : public _List_base {
    // total size: 0x8
};
class StoreEnumeration {
    // total size: 0x10
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class list mProducts; // offset 0x4, size 0x8
    class vector & mOffers; // offset 0xC, size 0x4
};
// Range: 0x8018C314 -> 0x8018C3EC
class StorePanel * StorePanel::Instance() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10StorePanel;
    // -> class ObjectDir * sMainDir;
}

static class Symbol motd; // size: 0x4, address: 0x80A4CE58
// Range: 0x8018C3EC -> 0x8018C464
char * StorePanel::Motd(const class StorePanel * const this /* r31 */) {
    // References
    // -> static class Symbol motd;
}

static class Symbol new_releases; // size: 0x4, address: 0x80A4CE60
// Range: 0x8018C464 -> 0x8018C4C8
class DataArray * StorePanel::GetNewReleaseData(const class StorePanel * const this /* r31 */) {
    // References
    // -> static class Symbol new_releases;
}

// Range: 0x8018C4C8 -> 0x8018C528
class Symbol StorePanel::CurSelectedFilter() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8018C528 -> 0x8018C5B8
class Symbol StorePanel::Filter(const class StorePanel * const this /* r30 */, int depth /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018C5B8 -> 0x8018C644
class StoreFilter * StorePanel::CurStoreFilter(const class StorePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018C644 -> 0x8018C6C4
int StorePanel::NumFiltersRequired(const class StorePanel * const this /* r31 */) {
    // Local variables
    const class StoreFilter * f; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018C6C4 -> 0x8018C740
class Symbol StorePanel::SortDifficultyPart(const class StorePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018C740 -> 0x8018C7B4
unsigned char StorePanel::IsEnumerating(const class StorePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018C7B4 -> 0x8018C7BC
unsigned char StorePanel::InCheckout() {}

// Range: 0x8018C7BC -> 0x8018C83C
class StoreOffer * StorePanel::FindOffer(const class StorePanel * const this /* r30 */, class Symbol & shortname /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018C83C -> 0x8018C90C
void StorePanel::PushFilter(class StorePanel * const this /* r31 */) {}

// Range: 0x8018C90C -> 0x8018C970
void StorePanel::PopFilter() {}

// Range: 0x8018C970 -> 0x8018C9A8
unsigned char __eq(const class String & rhs /* r31 */) {}

// Range: 0x8018C9A8 -> 0x8018CAB0
void StorePanel::LoadArt(class StorePanel * const this /* r28 */, const class String & strRemotePath /* r29 */, class RndTex * pending_tex /* r30 */, class Object * callback /* r31 */) {
    // Local variables
    struct _List_iterator l; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<P14NetCacheLoader>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class NetCacheMgr * TheNetCacheMgr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_List_node<P14NetCacheLoader>; // size: 0x8, address: 0x8089B858
// Range: 0x8018CAB0 -> 0x8018CAC4
void StorePanel::CancelArt() {}

static class Message msg; // size: 0x8, address: 0x80979E78
class ContentInstalledMsg : public Message {
    // total size: 0x8
};
static class ContentInstalledMsg msg2; // size: 0x8, address: 0x80979E90
// Range: 0x8018CAC4 -> 0x8018CD60
void StorePanel::FinishCheckout(class StorePanel * const this /* r30 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> struct [anonymous] __vt__19ContentInstalledMsg;
    // -> class Symbol t;
    // -> static class ContentInstalledMsg msg2;
    // -> class UIManager TheUI;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol store_load_failed; // size: 0x4, address: 0x80A4CE68
static class Message msg; // size: 0x8, address: 0x80979EA8
// Range: 0x8018CDE4 -> 0x8018D048
void StorePanel::ExitError(class StorePanel * const this /* r29 */, enum StoreError e /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class BandUI * TheBandUI;
    // -> static class Symbol store_load_failed;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018D048 -> 0x8018D060
unsigned char StorePanel::ToggleTestOffers() {}

// Range: 0x8018D060 -> 0x8018D10C
void StorePanel::UpdateFilterCrumb(class StorePanel * const this /* r30 */) {
    // Local variables
    class String str; // r1+0xC
    int i; // r31
}

// Range: 0x8018D10C -> 0x8018D120
enum StoreError StorePanel::FinishEnum(class StorePanel * const this /* r4 */) {}

// Range: 0x8018D120 -> 0x8018D210
class DataNode StorePanel::OnMsg(class StorePanel * const this /* r29 */, const class PlatformMgrOpCompleteMsg & msg /* r30 */) {}

static class Symbol song; // size: 0x4, address: 0x80A4CE70
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8018D210 -> 0x8018D58C
void StorePanel::ValidateOffers(class StorePanel * const this /* r30 */) {
    // Local variables
    class vector seen; // r1+0x64
    class vector songs; // r1+0x58
    class StoreOffer * o; // r1+0x4C
    class Symbol types[2]; // r1+0x50
    int i; // r28
    class Symbol type; // r1+0x48
    class StoreOffer * * s; // r27
    int count; // r26
    class StoreOffer * o; // r25

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol song;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class StoreOffer * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class StoreOffer * * _M_start; // offset 0x0, size 0x4
    class StoreOffer * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
static class Symbol _s; // size: 0x4, address: 0x80A4CE78
static class Symbol _s; // size: 0x4, address: 0x80A4CE80
static class Symbol _s; // size: 0x4, address: 0x80A4CE88
static class Symbol _s; // size: 0x4, address: 0x80A4CE90
static class Symbol _s; // size: 0x4, address: 0x80A4CE98
static class Symbol _s; // size: 0x4, address: 0x80A4CEA0
static class Symbol _s; // size: 0x4, address: 0x80A4CEA8
static class Symbol _s; // size: 0x4, address: 0x80A4CEB0
static class Symbol _s; // size: 0x4, address: 0x80A4CEB8
static class Symbol _s; // size: 0x4, address: 0x80A4CEC0
static class Symbol _s; // size: 0x4, address: 0x80A4CEC8
static class Symbol _s; // size: 0x4, address: 0x80A4CED0
static class Symbol _s; // size: 0x4, address: 0x80A4CED8
static class Symbol _s; // size: 0x4, address: 0x80A4CEE0
static class Symbol _s; // size: 0x4, address: 0x80A4CEE8
static class Symbol _s; // size: 0x4, address: 0x80A4CEF0
static class Symbol _s; // size: 0x4, address: 0x80A4CEF8
static class Symbol _s; // size: 0x4, address: 0x80A4CF00
static class Symbol _s; // size: 0x4, address: 0x80A4CF08
static class Symbol _s; // size: 0x4, address: 0x80A4CF10
static class Symbol _s; // size: 0x4, address: 0x80A4CF18
static class Symbol _s; // size: 0x4, address: 0x80A4CF20
// Range: 0x8018D58C -> 0x8018E000
class DataNode StorePanel::Handle(class StorePanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4CF28
static class Symbol _s; // size: 0x4, address: 0x80A4CF30
static class Symbol _s; // size: 0x4, address: 0x80A4CF38
static class Symbol _s; // size: 0x4, address: 0x80A4CF40
static class Symbol _s; // size: 0x4, address: 0x80A4CF48
static class Symbol _s; // size: 0x4, address: 0x80A4CF50
// Range: 0x8018E000 -> 0x8018E710
unsigned char StorePanel::SyncProperty(class StorePanel * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__16InfoSongProvider;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__12InfoProvider;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__13GroupProvider;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__18StoreOfferProvider;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14FilterProvider;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8018E710 -> 0x8018E75C
class RndMat * InfoSongProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018E75C -> 0x8018E8F4
char * InfoSongProvider::Text(const class InfoSongProvider * const this /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    class DataNode & song; // r31
    class StoreOffer * o; // r31

    // References
    // -> class Symbol name;
    // -> class Symbol track;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x9C
} __vt__16InfoSongProvider; // size: 0x9C, address: 0x8089BAC0
struct {
    // total size: 0x8
} __RTTI__16InfoSongProvider; // size: 0x8, address: 0x8089BB90
// Range: 0x8018E8F4 -> 0x8018E904
class Symbol InfoProvider::DataSymbol() {}

// Range: 0x8018E904 -> 0x8018E950
class RndMat * InfoProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8018E950 -> 0x8018EB28
char * InfoProvider::Text(const class InfoProvider * const this /* r31 */, int data /* r30 */) {
    // Local variables
    class Symbol tok; // r1+0x18
    class StoreOffer * album_or_pack; // r4

    // References
    // -> class Symbol store_back_song;
    // -> class Symbol exit;
    // -> class Symbol name;
    // -> class Symbol store_view_pack;
    // -> class Symbol store_view_album;
}

struct {
    // total size: 0x9C
} __vt__12InfoProvider; // size: 0x9C, address: 0x8089BB98
struct {
    // total size: 0x8
} __RTTI__12InfoProvider; // size: 0x8, address: 0x8089BC60
struct {
    // total size: 0xB0
} __vt__10StorePanel; // size: 0xB0, address: 0x8089BEE8
struct {
    // total size: 0x8
} __RTTI__10StorePanel; // size: 0x8, address: 0x8089BFC0
struct {
    // total size: 0x54
} __vt__14SelectedFilter; // size: 0x54, address: 0x8089BFC8
struct {
    // total size: 0x8
} __RTTI__14SelectedFilter; // size: 0x8, address: 0x8089C040
struct {
    // total size: 0xC
} __vt__19ContentInstalledMsg; // size: 0xC, address: 0x8089C088
struct {
    // total size: 0x8
} __RTTI__19ContentInstalledMsg; // size: 0x8, address: 0x8089C0B8
struct EnumProduct {
    // total size: 0x14
    unsigned short mContentId; // offset 0x0, size 0x2
    class String mGameCode; // offset 0x4, size 0xC
    unsigned char mHasPurchased; // offset 0x10, size 0x1
    unsigned char mDownloaded; // offset 0x11, size 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    struct EnumProduct _M_data; // offset 0x8, size 0x14
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct {
    // total size: 0x8
} __RTTI__PP10StoreOffer; // size: 0x8, address: 0x8089C1B8
struct {
    // total size: 0x8
} __RTTI__P11StoreFilter; // size: 0x8, address: 0x8089C1D0
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};

