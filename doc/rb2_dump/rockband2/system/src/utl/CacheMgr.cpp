/*
    Compile unit: C:\rockband2\system\src\utl\CacheMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806030D8 -> 0x80603604
*/
class CacheMgr * TheCacheMgr; // size: 0x4, address: 0x80A553A8
// Range: 0x806030D8 -> 0x80603168
void CacheMgrInit() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class CacheMgr * TheCacheMgr;
}

// Range: 0x80603168 -> 0x806031B0
void CacheMgrTerminate() {
    // References
    // -> class CacheMgr * TheCacheMgr;
}

// Range: 0x806031B0 -> 0x806031E0
class CacheMgr * CacheMgr::CreateCacheMgr() {}

// Range: 0x806031E0 -> 0x80603208
void * CacheMgr::CacheMgr() {
    // References
    // -> struct [anonymous] __vt__8CacheMgr;
}

// Range: 0x80603208 -> 0x806032CC
void * CacheMgr::~CacheMgr(class CacheMgr * const this /* r30 */) {}

// Range: 0x806032CC -> 0x8060332C
unsigned char CacheMgr::SearchAsync(class CacheMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8060332C -> 0x8060338C
unsigned char CacheMgr::ShowUserSelectUIAsync(class CacheMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8060338C -> 0x806033EC
unsigned char CacheMgr::CreateCacheID(class CacheMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x806033EC -> 0x806033FC
unsigned char CacheMgr::IsDone() {}

// Range: 0x806033FC -> 0x80603404
enum CacheResult CacheMgr::GetLastResult() {}

// Range: 0x80603404 -> 0x8060350C
void CacheMgr::AddCacheID(class CacheMgr * const this /* r29 */, class CacheID * pCacheID /* r30 */, class Symbol & symName /* r31 */) {
    // Local variables
    struct CacheIDStoreEntry * it; // r7

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060350C -> 0x806035A8
void CacheMgr::RemoveCacheID() {
    // Local variables
    struct CacheIDStoreEntry * it; // r8
}

// Range: 0x806035A8 -> 0x806035F4
class CacheID * CacheMgr::GetCacheID() {
    // Local variables
    struct CacheIDStoreEntry * it; // r7
    struct CacheIDStoreEntry entry; // r1+0x8
}

// Range: 0x806035F4 -> 0x806035FC
void CacheMgr::SetOp() {}

// Range: 0x806035FC -> 0x80603604
void CacheMgr::SetLastResult() {}

struct {
    // total size: 0x28
} __vt__8CacheMgr; // size: 0x28, address: 0x8092B530
struct {
    // total size: 0x8
} __RTTI__8CacheMgr; // size: 0x8, address: 0x8092B568
struct {
    // total size: 0x8
} __RTTI__PQ28CacheMgr17CacheIDStoreEntry; // size: 0x8, address: 0x8092B590

