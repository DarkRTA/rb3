/*
    Compile unit: C:\rockband2\band2\src\net_band\RBAdminDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80219B88 -> 0x80219B88
*/
class ScopedCS : public RootObject {
    // total size: 0x8
    unsigned char m_bInScope; // offset 0x0, size 0x1
    class CriticalSection * m_pCS; // offset 0x4, size 0x4
};
class CallbackRoot : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14ServerProtocol; // size: 0x8, address: 0x808AE2A8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14ClientProtocol; // size: 0x8, address: 0x808AE2F0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal8Protocol; // size: 0x8, address: 0x808AE328
struct {
    // total size: 0x8
} __RTTI__Q26Quazal15SystemComponent; // size: 0x8, address: 0x808AE360
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16RefCountedObject; // size: 0x8, address: 0x808AE390
unsigned char s_bNoOp; // size: 0x1, address: 0x80A55E50
class InstanceControl : public RootObject {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    unsigned int m_icInstanceContext; // offset 0x4, size 0x4
    unsigned int m_icInstanceType; // offset 0x8, size 0x4
    void * m_pDelegatorInstance; // offset 0xC, size 0x4
    unsigned char m_bIsValid; // offset 0x10, size 0x1
};
class InstantiationContext : public RootObject {
    // total size: 0x30
    class InstanceControl * m_icInstanceContext[11]; // offset 0x0, size 0x2C
    unsigned char m_IsValid; // offset 0x2C, size 0x1
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    class InstantiationContext * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class InstantiationContext * * _M_start; // offset 0x0, size 0x4
    class InstantiationContext * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class InstanceTable : public RootObject {
    // total size: 0x34
    class InstantiationContext m_oDefaultContext; // offset 0x0, size 0x30
    class qVector * m_pvContextVector; // offset 0x30, size 0x4
};
class InstanceTable s_oInstanceTable; // size: 0x34, address: 0x80A44034

