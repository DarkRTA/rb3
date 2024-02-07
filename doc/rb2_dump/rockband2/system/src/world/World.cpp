/*
    Compile unit: C:\rockband2\system\src\world\World.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8044DEF4 -> 0x8044E178
*/
class Symbol name; // size: 0x4, address: 0x80A525FC
class Symbol name; // size: 0x4, address: 0x80A52604
class Symbol name; // size: 0x4, address: 0x80A5260C
// Range: 0x8044DEF4 -> 0x8044E178
void WorldInit() {
    // References
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct EventCall {
    // total size: 0x18
    class ObjPtr mDir; // offset 0x0, size 0xC
    class ObjPtr mEvent; // offset 0xC, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
struct KeyFrame {
    // total size: 0x10
    float mTime; // offset 0x0, size 0x4
    class ObjList mCalls; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class EventAnim : public RndAnimatable {
    // total size: 0x4C
    float mLastFrame; // offset 0x10, size 0x4
    class ObjList mKeys; // offset 0x14, size 0xC
};
class WorldInstance : public RndDir {
    // total size: 0x240
    class ObjDirPtr mDir; // offset 0x1F4, size 0xC
    class SharedGroup * mSharedGroup; // offset 0x200, size 0x4
};
class WiiDOFProc : public DOFProc, public PostProcessor {
    // total size: 0x4C
    unsigned char mEnabled; // offset 0x2C, size 0x1
    class RndTex * mDepthTex; // offset 0x30, size 0x4
    class RndTex * mBlurColorTex; // offset 0x34, size 0x4
    float mFocalPlane; // offset 0x38, size 0x4
    float mBlurDepth; // offset 0x3C, size 0x4
    float mMinBlur; // offset 0x40, size 0x4
    float mMaxBlur; // offset 0x44, size 0x4
    class RndCam * mCam; // offset 0x48, size 0x4
};

