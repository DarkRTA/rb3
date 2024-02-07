/*
    Compile unit: C:\rockband2\band2\src\meta\CharCache.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800C8384 -> 0x800CF38C
*/
class CharCache * TheCharCache; // size: 0x4, address: 0x80A4AA00
static class RndTex * sTexture; // size: 0x4, address: 0x80A4AA04
// Range: 0x800C8384 -> 0x800C83E0
unsigned char CharEntry::Match() {}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class FileCacheEntry * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class FileCacheEntry * * _M_start; // offset 0x0, size 0x4
    class FileCacheEntry * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class FileCache {
    // total size: 0x14
protected:
    int mMaxSize; // offset 0x0, size 0x4
    unsigned char mTryClear; // offset 0x4, size 0x1
    class vector mEntries; // offset 0x8, size 0xC
};
// Range: 0x800C83E0 -> 0x800C8430
void CharCache::Init() {
    // References
    // -> class ObjectDir * sMainDir;
    // -> class CharCache * TheCharCache;
}

class FilePathTracker {
    // total size: 0xC
protected:
    class FilePath mOldRoot; // offset 0x0, size 0xC
};
// Range: 0x800C8430 -> 0x800C86B8
void * CharCache::CharCache(class CharCache * const this /* r28 */) {
    // Local variables
    int i; // r30
    class FilePathTracker _fptracker; // r1+0x58

    // References
    // -> struct [anonymous] __vt__9CharCache;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndTex * _M_data; // offset 0x8, size 0x4
};
// Range: 0x800C86B8 -> 0x800C92BC
void * CharCache::~CharCache(class CharCache * const this /* r28 */) {
    // Local variables
    int i; // r30

    // References
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> struct [anonymous] __vt__31ObjDirPtr<18CompositeCharacter>;
    // -> struct [anonymous] __vt__39ObjPtr<18CompositeCharacter,9ObjectDir>;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__24ObjDirPtr<11CharClipSet>;
    // -> struct [anonymous] __vt__9CharCache;
}

// Range: 0x800C92BC -> 0x800C937C
void CharCache::CacheDefaults(class CharCache * const this /* r28 */, int priority /* r29 */) {
    // Local variables
    int gender; // r31
    char * genders[2]; // r1+0x8
    int instrument; // r30
    char * insts[3]; // r1+0x10
}

// Range: 0x800C937C -> 0x800C94A0
void CharCache::LoadingDraw(class CharCache * const this /* r30 */) {
    // Local variables
    class CompositeCharacter * c; // r31
    class RndTex * t; // r31

    // References
    // -> static class RndTex * sTexture;
    // -> class Debug TheDebug;
}

static class Symbol none; // size: 0x4, address: 0x80A4AA0C
static class Symbol guitar; // size: 0x4, address: 0x80A4AA14
static class Symbol vocals; // size: 0x4, address: 0x80A4AA1C
static class Symbol bass; // size: 0x4, address: 0x80A4AA24
static class Symbol drum; // size: 0x4, address: 0x80A4AA2C
static class Symbol mic; // size: 0x4, address: 0x80A4AA34
static class Symbol feet; // size: 0x4, address: 0x80A4AA3C
static class Symbol torso; // size: 0x4, address: 0x80A4AA44
static class Symbol legs; // size: 0x4, address: 0x80A4AA4C
// Range: 0x800C94A0 -> 0x800C9A70
void CharCache::CachePrefab(class CharCache * const this /* r25 */, const class DataArray * prefab /* r28 */, class Symbol & inst /* r26 */, int priority /* r27 */) {
    // Local variables
    class DataArray * outfit; // r29
    int i; // r28
    class FilePath p; // r1+0x78
    char buffer[256]; // r1+0x188
    class FilePath p; // r1+0x6C
    char base[256]; // r1+0x88
    class FilePath p; // r1+0x60

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol legs;
    // -> static class Symbol torso;
    // -> static class Symbol feet;
    // -> static class Symbol mic;
    // -> static class Symbol drum;
    // -> static class Symbol bass;
    // -> static class Symbol vocals;
    // -> static class Symbol guitar;
    // -> static class Symbol none;
}

// Range: 0x800C9A70 -> 0x800C9AE4
class Symbol CharCache::Singular() {
    // Local variables
    char buffer[256]; // r1+0x10
}

// Range: 0x800C9AE4 -> 0x800C9BDC
void CharCache::CacheBodyAndClips(class CharCache * const this /* r27 */, const char * gender /* r29 */, int priority /* r28 */) {
    // Local variables
    class Symbol instrument; // r1+0x14
    class FilePath p; // r1+0x24

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

static class Symbol none; // size: 0x4, address: 0x80A4AA54
static class Symbol male; // size: 0x4, address: 0x80A4AA5C
static class Symbol female; // size: 0x4, address: 0x80A4AA64
static class Symbol characters; // size: 0x4, address: 0x80A4AA6C
static class Symbol creator; // size: 0x4, address: 0x80A4AA74
static class Symbol male; // size: 0x4, address: 0x80A4AA7C
static class Symbol female; // size: 0x4, address: 0x80A4AA84
static class DataArray * cc; // size: 0x4, address: 0x80A4AA88
// Range: 0x800C9BDC -> 0x800CA174
unsigned char CharCache::CacheChar(class CharCache * const this /* r26 */, int player /* r27 */, const class DataArray * * chars /* r23 */, int numChars /* r24 */, int which /* r25 */, int priority /* r28 */) {
    // Local variables
    class BandUser * pUser; // r30
    class Symbol inst; // r1+0x54
    enum ControllerType ct; // r0
    const char * name; // r29
    struct CharEntry * e; // r29
    class Symbol g; // r1+0x50
    const class DataArray * fab; // r0
    class DataArray * fab; // r0
    class vector users; // r1+0x58
    class CharData * cd; // r27

    // References
    // -> const char * gNullStr;
    // -> class GameConfig * TheGameConfig;
    // -> static class DataArray * cc;
    // -> static class Symbol female;
    // -> static class Symbol male;
    // -> static class Symbol creator;
    // -> static class Symbol characters;
    // -> class CharCreatorPanel * TheCharCreatorPanel;
    // -> static class Symbol female;
    // -> static class Symbol male;
    // -> static class Symbol none;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800CA174 -> 0x800CA384
void CharCache::UpdateCache(class CharCache * const this /* r27 */) {
    // Local variables
    const class vector & users; // r0
    int playerNum; // r30
    class BandUser * const * it; // r29
    const class BandUser * user; // r26
    class Profile * p; // r25
    int num; // r0
    class DataArray * chars[32]; // r1+0x8
    int numChars; // r28
    int i; // r24
    const class CharData * cd; // r3
    const class DataArray * arr; // r0
    int which; // r24
    int last; // r0
    int dir; // r0
    int i; // r25

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800CA384 -> 0x800CA38C
class vector & CharCache::SavedPlayers() {}

// Range: 0x800CA38C -> 0x800CAC8C
void CharCache::Request(class CharCache * const this /* r27 */, int user_num /* r30 */, enum ControllerType ct /* r28 */, const class CharData * char_data /* r29 */, unsigned char force /* r26 */) {
    // Local variables
    class Symbol instrument; // r1+0x44
    const class DataArray * prefab; // r25
    struct CharEntry * e; // r30
    class Symbol gender; // r1+0x40

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__10PrefabChar;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__14TourCharRemote;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800CAC8C -> 0x800CACF0
void CharCache::SetWorldNames(const char * worldName /* r30 */) {}

// Range: 0x800CACF0 -> 0x800CAD08
void CharCache::SetTrack() {}

// Range: 0x800CAD08 -> 0x800CAD1C
class Symbol CharCache::GetTrack() {}

// Range: 0x800CAD1C -> 0x800CAE14
void CharCache::Free(class CharCache * const this /* r30 */, int playerId /* r31 */) {
    // Local variables
    int * p; // r3
    struct CharEntry * e; // r31

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800CAE14 -> 0x800CB248
void CharCache::ForceDelete(struct CharEntry * e /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x800CB248 -> 0x800CB44C
class CompositeCharacter * CharCache::Loaded() {
    // Local variables
    struct CharEntry * e; // r26

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x800CB44C -> 0x800CB460
class CharData * CharCache::Requested() {}

// Range: 0x800CB460 -> 0x800CB4C4
unsigned char CharCache::Loaded(class CharCache * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800CB4C4 -> 0x800CB554
unsigned char CharCache::UsingCharacter(class CharCache * const this /* r29 */, class CompositeCharacter * d /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800CB554 -> 0x800CBB14
void CharCache::ChangeCharacters(class CharCache * const this /* r29 */, class ObjectDir * world /* r30 */) {
    // Local variables
    int i; // r31
    class CompositeCharacter * to; // r0
    class ObjDirItr dude; // r1+0x34

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x800CBB14 -> 0x800CBB78
void CharCache::ClearDircuts(class CharCache * const this /* r30 */) {
    // Local variables
    int i; // r31
    class CompositeCharacter * to; // r0
}

static class Message msg; // size: 0x8, address: 0x80977FC8
class _List_node : public _List_node_base {
    // total size: 0x44
public:
    struct CharData _M_data; // offset 0x8, size 0x3C
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class WorldCrowd * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x800CBB78 -> 0x800CC59C
unsigned char CharCache::LoadSongClips(class CharCache * const this /* r31 */) {
    // Local variables
    int i; // r29
    class CompositeCharacter * to; // r0
    class Symbol song; // r1+0x30
    class ObjDirItr crowd; // r1+0x60
    int i; // r29
    class CompositeCharacter * c; // r0

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10WorldCrowd;
    // -> class WorldDir * TheWorld;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x800CC59C -> 0x800CCA9C
void CharCache::LightCharacters(class CharCache * const this /* r26 */, class ObjectDir * world /* r27 */) {
    // Local variables
    class ObjDirItr dude; // r1+0x18
    int i; // r28
    class CompositeCharacter * to; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x800CCA9C -> 0x800CCAE0
void CharCache::ReclaimCharacter() {
    // Local variables
    class Character * c; // r5
}

// Range: 0x800CCAE0 -> 0x800CCC04
void CharCache::SwapPlayers(class CharCache * const this /* r28 */, int i /* r29 */, int j /* r30 */) {
    // Local variables
    struct CharEntry * tmp; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800CCC04 -> 0x800CCCD4
void CharCache::UpdateCharData(class CharCache * const this /* r27 */, class BandUser * pUser /* r29 */, class CharData * char_data /* r28 */) {
    // Local variables
    enum ControllerType ct; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800CCCD4 -> 0x800CCD80
int CharCache::FindIndex(const class CharCache * const this /* r29 */, class CompositeCharacter * c /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x800CCD80 -> 0x800CCDBC
enum ControllerType CharCache::FindControllerType(class CharCache * const this /* r31 */) {
    // Local variables
    int userNum; // r0
}

// Range: 0x800CCDBC -> 0x800CCDE0
class Symbol CharCache::FindControllerSym() {}

// Range: 0x800CCDE0 -> 0x800CCF60
int CharCache::SortEntries() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x800CCF60 -> 0x800CD050
void CharCache::SortExecute(class CharCache * const this /* r27 */, void (* CBack)(struct CharEntry *) /* r28 */, unsigned char fail /* r29 */) {
    // Local variables
    int count; // r31
    struct CharEntry * entries[4]; // r1+0x8
    int i; // r30
    int i; // r30

    // References
    // -> class Debug TheDebug;
}

static class Message msg; // size: 0x8, address: 0x80977FE0
// Range: 0x800CD050 -> 0x800CD294
void CharCache::WorldConfigureCBack(struct CharEntry * e /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80977FF8
// Range: 0x800CD294 -> 0x800CD420
void CharCache::LoadRealtimeClipsCBack(struct CharEntry * e /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80978010
// Range: 0x800CD420 -> 0x800CD5AC
void CharCache::LoadSongsCBack(struct CharEntry * e /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80978028
// Range: 0x800CD5AC -> 0x800CD778
void CharCache::MetaConfigureCBack(struct CharEntry * e /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x80978040
// Range: 0x800CD778 -> 0x800CD904
void CharCache::LoadingScreenConfigureCBack(struct CharEntry * e /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800CD904 -> 0x800CDA54
void CharCache::CheckOutsideRefs(class CharCache * const this /* r31 */) {
    // Local variables
    int player; // r30
    struct CharEntry * e; // r29
    class CompositeCharacter * cc; // r28
    struct _List_iterator i; // r1+0x18
    class ObjRef * ref; // r27
    class Object * owner; // r26

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x800CDA54 -> 0x800CDB24
void CharCache::PrintRequested(class CharCache * const this /* r29 */) {
    // Local variables
    int player; // r31
    const class CharData * cd; // r30

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A4AA94
static class Symbol _s; // size: 0x4, address: 0x80A4AA9C
static class Symbol _s; // size: 0x4, address: 0x80A4AAA4
static class Symbol _s; // size: 0x4, address: 0x80A4AAAC
static class Symbol _s; // size: 0x4, address: 0x80A4AAB4
static class Symbol _s; // size: 0x4, address: 0x80A4AABC
static class Symbol _s; // size: 0x4, address: 0x80A4AAC4
static class Symbol _s; // size: 0x4, address: 0x80A4AACC
static class Symbol _s; // size: 0x4, address: 0x80A4AAD4
static class Symbol _s; // size: 0x4, address: 0x80A4AADC
static class Symbol _s; // size: 0x4, address: 0x80A4AAE4
static class Symbol _s; // size: 0x4, address: 0x80A4AAEC
static class Symbol _s; // size: 0x4, address: 0x80A4AAF4
static class Symbol _s; // size: 0x4, address: 0x80A4AAFC
static class Symbol _s; // size: 0x4, address: 0x80A4AB04
static class Symbol _s; // size: 0x4, address: 0x80A4AB0C
static class Symbol _s; // size: 0x4, address: 0x80A4AB14
static class Symbol _s; // size: 0x4, address: 0x80A4AB1C
static class Symbol _s; // size: 0x4, address: 0x80A4AB24
static class Symbol _s; // size: 0x4, address: 0x80A4AB2C
static class Symbol _s; // size: 0x4, address: 0x80A4AB34
// Range: 0x800CDB24 -> 0x800CE6DC
class DataNode CharCache::Handle(class CharCache * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28
    class DataNode _n; // r1+0x20

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
}

// Range: 0x800CE6DC -> 0x800CE718
class DataNode CharCache::OnCacheClear() {}

// Range: 0x800CE718 -> 0x800CE788
class DataNode CharCache::OnCacheEnable(class CharCache * const this /* r30 */, class DataArray * msg /* r31 */) {}

// Range: 0x800CE788 -> 0x800CE824
class DataNode CharCache::OnLoaded(class CharCache * const this /* r30 */, class DataArray * msg /* r31 */) {}

// Range: 0x800CE824 -> 0x800CE8D4
class DataNode CharCache::OnSetClipMode(class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800CE8D4 -> 0x800CE978
class DataNode CharCache::OnFindCharData(class CharCache * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x800CE978 -> 0x800CE9C0
class DataNode CharCache::OnSetLoadingScreenMode() {}

// Range: 0x800CE9C0 -> 0x800CEA8C
class DataNode CharCache::OnWorldConfigureCharacters(class CharCache * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x800CEA8C -> 0x800CEB34
class DataNode CharCache::OnReclaimCharacters(class CharCache * const this /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x80978058
// Range: 0x800CEB34 -> 0x800CEF1C
class DataNode CharCache::OnMetaConfigureDone(class CharCache * const this /* r28 */) {
    // Local variables
    int i; // r29
    class CompositeCharacter * c; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x800CEF1C -> 0x800CEF58
class DataNode CharCache::OnLoadingScreenConfigureDone() {}

// Range: 0x800CEF58 -> 0x800CF0DC
class DataNode CharCache::OnIterate(class CharCache * const this /* r28 */, class DataArray * msg /* r29 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode val; // r1+0x18
    int i; // r30
    class CompositeCharacter * c; // r3
    int j; // r26
}

// Range: 0x800CF0DC -> 0x800CF11C
class DataNode CharCache::OnCompressionDone() {
    // References
    // -> static class RndTex * sTexture;
}

// Range: 0x800CF11C -> 0x800CF308
class DataNode CharCache::OnGetMatchingDude(class CharCache * const this /* r25 */, class DataArray * msg /* r23 */) {
    // Local variables
    class CompositeCharacter * me; // r0
    int i; // r28
    int j; // r27
    class CompositeCharacter * c; // r26

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x800CF308 -> 0x800CF38C
unsigned char CharCache::AreAllCharsLoaded(class CharCache * const this /* r30 */) {
    // Local variables
    int i; // r31
    class CompositeCharacter * c; // r0
}

struct {
    // total size: 0x8
} __RTTI__10WorldCrowd; // size: 0x8, address: 0x80881990
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharWeightable * mPtr; // offset 0x8, size 0x4
};
class CharWeightable : public virtual Object {
    // total size: 0x44
public:
    void * __vptr$; // offset 0x4, size 0x4
protected:
    float mWeight; // offset 0x8, size 0x4
    class ObjOwnerPtr mWeightOwner; // offset 0xC, size 0xC
};
class CharBonesObject : public CharBones, public virtual Object {
    // total size: 0x84
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharBonesObject * mPtr; // offset 0x8, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CharClip * mPtr; // offset 0x8, size 0x4
};
class CharClipDriver {
    // total size: 0x3C
public:
    int mPlayFlags; // offset 0x0, size 0x4
    float mBlendWidth; // offset 0x4, size 0x4
    float mTimeScale; // offset 0x8, size 0x4
    float mRampIn; // offset 0xC, size 0x4
    float mFrame; // offset 0x10, size 0x4
    float mDFrame; // offset 0x14, size 0x4
    float mBlendFrac; // offset 0x18, size 0x4
    float mAdvanceFrame; // offset 0x1C, size 0x4
    float mWeight; // offset 0x20, size 0x4
protected:
    class ObjOwnerPtr mClip; // offset 0x24, size 0xC
    class CharClipDriver * mNext; // offset 0x30, size 0x4
    int mNextEvent; // offset 0x34, size 0x4
    class DataArray * mEventData; // offset 0x38, size 0x4
};
enum ApplyMode {
    kApplyBlend = 0,
    kApplyAdd = 1,
    kApplyRotateTo = 2,
};
class CharBonesAlloc : public CharBonesObject {
    // total size: 0x84
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjOwnerPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjOwnerPtr * _M_start; // offset 0x0, size 0x4
    class ObjOwnerPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CharClipGroup : public virtual Object {
    // total size: 0x4C
public:
    void * __vptr$; // offset 0x4, size 0x4
protected:
    class ObjVector mClips; // offset 0x8, size 0x10
    int mWhich; // offset 0x18, size 0x4
    int mFlags; // offset 0x1C, size 0x4
};
class CharDriver : public RndHighlightable, public CharWeightable, public CharPollable {
    // total size: 0x9C
protected:
    class ObjPtr mBones; // offset 0x28, size 0xC
    class ObjDirPtr mClips; // offset 0x34, size 0xC
    class CharClipDriver * mFirst; // offset 0x40, size 0x4
    class ObjPtr mTestClip; // offset 0x44, size 0xC
    class Symbol mStarvedHandler; // offset 0x50, size 0x4
    class DataNode mLastNode; // offset 0x54, size 0x8
    float mOldBeat; // offset 0x5C, size 0x4
    unsigned char mRealign; // offset 0x60, size 0x1
    float mBeatScale; // offset 0x64, size 0x4
    enum ApplyMode mApply; // offset 0x68, size 0x4
    class CharBonesAlloc * mInternalBones; // offset 0x6C, size 0x4
};
struct {
    // total size: 0x54
} __vt__9CharCache; // size: 0x54, address: 0x80881AE0
struct {
    // total size: 0x8
} __RTTI__9CharCache; // size: 0x8, address: 0x80881B58
struct {
    // total size: 0x18
} __vt__24ObjDirPtr<11CharClipSet>; // size: 0x18, address: 0x80881BA8
struct {
    // total size: 0x8
} __RTTI__24ObjDirPtr<11CharClipSet>; // size: 0x8, address: 0x80881BE8
struct {
    // total size: 0x18
} __vt__31ObjDirPtr<18CompositeCharacter>; // size: 0x18, address: 0x80881BF0
struct {
    // total size: 0x8
} __RTTI__31ObjDirPtr<18CompositeCharacter>; // size: 0x8, address: 0x80881C38
struct {
    // total size: 0x18
} __vt__39ObjPtr<18CompositeCharacter,9ObjectDir>; // size: 0x18, address: 0x80881CB8
struct {
    // total size: 0x8
} __RTTI__39ObjPtr<18CompositeCharacter,9ObjectDir>; // size: 0x8, address: 0x80881D08
struct {
    // total size: 0x8
} __RTTI__11CharClipSet; // size: 0x8, address: 0x80881D50
class OutfitChar : public UIPanel {
    // total size: 0x6C
    class String mShotRoot; // offset 0x30, size 0xC
    int mShotNumber; // offset 0x3C, size 0x4
};
class CharCreatorPanel : public OutfitChar {
    // total size: 0x88
    class BandUser * mInputUser; // offset 0x40, size 0x4
    class TourCharLocal * mNewChar; // offset 0x44, size 0x4
    class DataArray * mNames; // offset 0x48, size 0x4
    class DataLoader * mLoader; // offset 0x4C, size 0x4
    class BandUser * mOwnerUser; // offset 0x50, size 0x4
    int mNextRand; // offset 0x54, size 0x4
    class Symbol mLastGender; // offset 0x58, size 0x4
};

