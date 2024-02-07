/*
    Compile unit: C:\rockband2\system\src\synth\Sequence.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80581F18 -> 0x80586484
*/
class DataArray * types; // size: 0x4, address: 0x80A54570
class Symbol name; // size: 0x4, address: 0x80A54578
class DataArray * types; // size: 0x4, address: 0x80A5457C
class Symbol name; // size: 0x4, address: 0x80A54584
class DataArray * types; // size: 0x4, address: 0x80A54588
class Symbol name; // size: 0x4, address: 0x80A54590
class DataArray * types; // size: 0x4, address: 0x80A54594
class Symbol name; // size: 0x4, address: 0x80A5459C
class DataArray * types; // size: 0x4, address: 0x80A545A0
class Symbol name; // size: 0x4, address: 0x80A545A8
// Range: 0x80581F18 -> 0x80581F5C
static float RandomVal(float center /* f3 */) {}

// Range: 0x80581F5C -> 0x80581FF0
void * Sequence::Sequence(class Sequence * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtrList<7SeqInst,9ObjectDir>;
    // -> struct [anonymous] __vt__8Sequence;
}

struct Node {
    // total size: 0xC
    class SeqInst * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x80581FF0 -> 0x8058214C
class SeqInst * Sequence::MakeInst(class Sequence * const this /* r30 */) {
    // Local variables
    class SeqInst * newInst; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058214C -> 0x805821E4
void Sequence::Play(float vol /* f29 */, float pan /* f30 */, float transpose /* f31 */) {
    // Local variables
    class SeqInst * newInst; // r31
}

// Range: 0x805821E4 -> 0x80582278
void Sequence::Stop() {}

// Range: 0x80582278 -> 0x805824D8
void * Sequence::~Sequence(class Sequence * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtrList<7SeqInst,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__8Sequence;
}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x805824D8 -> 0x8058261C
void Sequence::SynthPoll(class Sequence * const this /* r29 */) {
    // Local variables
    class iterator it; // r1+0x30
}

// Range: 0x8058261C -> 0x80582624
float Sequence::GetAvgVolume() {}

// Range: 0x80582624 -> 0x8058262C
float Sequence::GetVolSpread() {}

// Range: 0x8058262C -> 0x80582634
float Sequence::GetAvgTranspose() {}

// Range: 0x80582634 -> 0x8058263C
float Sequence::GetTransposeSpread() {}

// Range: 0x8058263C -> 0x80582644
float Sequence::GetAvgPan() {}

// Range: 0x80582644 -> 0x8058264C
float Sequence::GetPanSpread() {}

// Range: 0x8058264C -> 0x805826F0
void Sequence::Copy(class Sequence * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class Sequence * s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
}

static class Symbol volume; // size: 0x4, address: 0x80A545B0
static class Symbol pan; // size: 0x4, address: 0x80A545B8
static class Symbol transpose; // size: 0x4, address: 0x80A545C0
// Range: 0x805826F0 -> 0x8058281C
class DataNode Sequence::OnPlay(class Sequence * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    float v; // r1+0x1C
    float p; // r1+0x18
    float tp; // r1+0x14

    // References
    // -> static class Symbol transpose;
    // -> static class Symbol pan;
    // -> static class Symbol volume;
}

static class Symbol _s; // size: 0x4, address: 0x80A545C8
static class Symbol _s; // size: 0x4, address: 0x80A545D0
static class Symbol _s; // size: 0x4, address: 0x80A545D8
// Range: 0x8058281C -> 0x80582E08
class DataNode Sequence::Handle(class Sequence * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A545E0
static class Symbol _s; // size: 0x4, address: 0x80A545E8
static class Symbol _s; // size: 0x4, address: 0x80A545F0
static class Symbol _s; // size: 0x4, address: 0x80A545F8
static class Symbol _s; // size: 0x4, address: 0x80A54600
static class Symbol _s; // size: 0x4, address: 0x80A54608
// Range: 0x80582E08 -> 0x80583424
unsigned char Sequence::SyncProperty(class Sequence * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

class WaitSeq : public Sequence {
    // total size: 0x80
    float mAvgWaitSecs; // offset 0x78, size 0x4
    float mWaitSpread; // offset 0x7C, size 0x4
};
// Range: 0x80583424 -> 0x80583474
void * WaitSeq::WaitSeq(class WaitSeq * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7WaitSeq;
}

// Range: 0x80583474 -> 0x805834C0
class SeqInst * WaitSeq::MakeInstImpl(class WaitSeq * const this /* r31 */) {}

// Range: 0x805834C0 -> 0x80583504
void WaitSeq::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80583504 -> 0x805835B8
void WaitSeq::Load(class WaitSeq * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805835B8 -> 0x8058363C
void WaitSeq::Copy(class WaitSeq * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class WaitSeq * s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7WaitSeq;
}

static class Symbol _s; // size: 0x4, address: 0x80A54610
static class Symbol _s; // size: 0x4, address: 0x80A54618
// Range: 0x8058363C -> 0x805838AC
unsigned char WaitSeq::SyncProperty(class WaitSeq * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

class RandomGroupSeq : public GroupSeq {
    // total size: 0x90
    int mNumSimul; // offset 0x8C, size 0x4
};
// Range: 0x805838AC -> 0x805838F8
void * RandomGroupSeq::RandomGroupSeq(class RandomGroupSeq * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14RandomGroupSeq;
}

// Range: 0x80583AB8 -> 0x80583B04
class SeqInst * RandomGroupSeq::MakeInstImpl(class RandomGroupSeq * const this /* r31 */) {}

// Range: 0x80583B04 -> 0x80583B0C
int RandomGroupSeq::GetNumSimul() {}

// Range: 0x80583B0C -> 0x80583B88
void RandomGroupSeq::Copy(class RandomGroupSeq * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class RandomGroupSeq * s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RandomGroupSeq;
}

// Range: 0x80583B88 -> 0x80583BCC
void RandomGroupSeq::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80583BCC -> 0x80583C64
void RandomGroupSeq::Load(class RandomGroupSeq * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A54620
// Range: 0x80583C64 -> 0x80583DE4
unsigned char RandomGroupSeq::SyncProperty(class RandomGroupSeq * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

class SerialGroupSeq : public GroupSeq {
    // total size: 0x8C
};
// Range: 0x80583DE4 -> 0x80583E30
class SeqInst * SerialGroupSeq::MakeInstImpl(class SerialGroupSeq * const this /* r31 */) {}

// Range: 0x80583E30 -> 0x80583E74
void SerialGroupSeq::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80583E74 -> 0x80583EFC
void SerialGroupSeq::Load(class SerialGroupSeq * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

class ParallelGroupSeq : public GroupSeq {
    // total size: 0x8C
};
// Range: 0x80583EFC -> 0x80583F48
class SeqInst * ParallelGroupSeq::MakeInstImpl(class ParallelGroupSeq * const this /* r31 */) {}

// Range: 0x80583F48 -> 0x80583F8C
void ParallelGroupSeq::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80583F8C -> 0x80584014
void ParallelGroupSeq::Load(class ParallelGroupSeq * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80584014 -> 0x80584078
void * GroupSeq::GroupSeq(class GroupSeq * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtrList<8Sequence,9ObjectDir>;
    // -> struct [anonymous] __vt__8GroupSeq;
}

// Range: 0x80584078 -> 0x805843DC
void GroupSeq::Copy(class GroupSeq * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class GroupSeq * s; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8GroupSeq;
}

// Range: 0x805843DC -> 0x80584420
void GroupSeq::Save() {
    // References
    // -> class Debug TheDebug;
}

class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
// Range: 0x80584420 -> 0x80584810
void GroupSeq::Load(class GroupSeq * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0x24
    class ObjVector children; // r1+0x28
    int i; // r30

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
static class Symbol _s; // size: 0x4, address: 0x80A54628
// Range: 0x80584810 -> 0x805848E8
unsigned char GroupSeq::SyncProperty(class GroupSeq * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

// Range: 0x805848E8 -> 0x805849B4
void * SeqInst::SeqInst(class SeqInst * const this /* r30 */, class Sequence * owner /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7SeqInst;
}

// Range: 0x805849B4 -> 0x80584A14
void * SeqInst::~SeqInst(class SeqInst * const this /* r30 */) {}

// Range: 0x80584A14 -> 0x80584A2C
void SeqInst::Start() {}

// Range: 0x80584A2C -> 0x80584A40
void SeqInst::SetVolume() {}

class WaitSeqInst : public SeqInst {
    // total size: 0x48
    float mWaitMs; // offset 0x40, size 0x4
    float mEndTime; // offset 0x44, size 0x4
};
// Range: 0x80584A40 -> 0x80584AB0
void * WaitSeqInst::WaitSeqInst(class WaitSeqInst * const this /* r30 */, class WaitSeq * owner /* r31 */) {
    // References
    // -> struct [anonymous] __vt__11WaitSeqInst;
}

// Range: 0x80584AB0 -> 0x80584AF8
void WaitSeqInst::StartImpl(class WaitSeqInst * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80584AF8 -> 0x80584B04
void WaitSeqInst::Stop() {}

// Range: 0x80584B04 -> 0x80584B54
unsigned char WaitSeqInst::IsRunning(class WaitSeqInst * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class GroupSeqInst : public SeqInst {
    // total size: 0x50
protected:
    class ObjVector mSeqs; // offset 0x40, size 0x10
};
// Range: 0x80584B54 -> 0x80584DB4
void * GroupSeqInst::GroupSeqInst(class GroupSeqInst * const this /* r29 */, class GroupSeq * owner /* r25 */) {
    // Local variables
    class iterator itr; // r1+0x28
    class SeqInst * newInst; // r30

    // References
    // -> struct [anonymous] __vt__27ObjPtr<7SeqInst,9ObjectDir>;
    // -> struct [anonymous] __vt__12GroupSeqInst;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class SeqInst * mPtr; // offset 0x8, size 0x4
};
// Range: 0x80584DB4 -> 0x80584F08
void * GroupSeqInst::~GroupSeqInst(class GroupSeqInst * const this /* r30 */) {
    // Local variables
    class ObjPtr * itr; // r29

    // References
    // -> struct [anonymous] __vt__12GroupSeqInst;
}

// Range: 0x80584F08 -> 0x80584F0C
void GroupSeqInst::Poll() {}

// Range: 0x80584F0C -> 0x80584F8C
void GroupSeqInst::UpdateVolume(class GroupSeqInst * const this /* r29 */) {
    // Local variables
    class ObjPtr * it; // r30
}

// Range: 0x80584F8C -> 0x8058500C
void GroupSeqInst::SetPan(class GroupSeqInst * const this /* r30 */, float pan /* f31 */) {
    // Local variables
    class ObjPtr * it; // r31
}

// Range: 0x8058500C -> 0x8058508C
void GroupSeqInst::SetTranspose(class GroupSeqInst * const this /* r30 */, float tp /* f31 */) {
    // Local variables
    class ObjPtr * it; // r31
}

class SerialGroupSeqInst : public GroupSeqInst {
    // total size: 0x54
    class ObjPtr * mIt; // offset 0x50, size 0x4
};
// Range: 0x8058508C -> 0x805850D0
void * SerialGroupSeqInst::SerialGroupSeqInst(class SerialGroupSeqInst * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18SerialGroupSeqInst;
}

// Range: 0x805850D0 -> 0x805850EC
void SerialGroupSeqInst::StartImpl() {}

// Range: 0x805850EC -> 0x80585194
void SerialGroupSeqInst::Stop(class SerialGroupSeqInst * const this /* r30 */) {
    // Local variables
    class ObjPtr * itr; // r31
}

// Range: 0x80585194 -> 0x805851B0
unsigned char SerialGroupSeqInst::IsRunning() {}

// Range: 0x805851B0 -> 0x80585238
void SerialGroupSeqInst::Poll(class SerialGroupSeqInst * const this /* r31 */) {}

class ParallelGroupSeqInst : public GroupSeqInst {
    // total size: 0x54
    class ObjPtr * mIt; // offset 0x50, size 0x4
};
// Range: 0x80585238 -> 0x8058527C
void * ParallelGroupSeqInst::ParallelGroupSeqInst(class ParallelGroupSeqInst * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__20ParallelGroupSeqInst;
}

// Range: 0x8058527C -> 0x805852DC
void * ParallelGroupSeqInst::~ParallelGroupSeqInst(class ParallelGroupSeqInst * const this /* r30 */) {}

// Range: 0x805852DC -> 0x80585380
void ParallelGroupSeqInst::StartImpl(class ParallelGroupSeqInst * const this /* r30 */) {
    // Local variables
    class ObjPtr * it; // r31
}

// Range: 0x80585380 -> 0x805853E4
void ParallelGroupSeqInst::Stop(class ParallelGroupSeqInst * const this /* r30 */) {
    // Local variables
    class ObjPtr * itr; // r31
}

// Range: 0x805853E4 -> 0x80585400
unsigned char ParallelGroupSeqInst::IsRunning() {}

// Range: 0x80585400 -> 0x8058546C
void ParallelGroupSeqInst::Poll(class ParallelGroupSeqInst * const this /* r31 */) {}

class RandomGroupSeqInst : public GroupSeqInst {
    // total size: 0x68
    int mNumSeqs; // offset 0x50, size 0x4
    class ObjVector mPlayingSeqs; // offset 0x54, size 0x10
    class ObjPtr * mIt; // offset 0x64, size 0x4
};
// Range: 0x8058546C -> 0x805854D8
void * RandomGroupSeqInst::RandomGroupSeqInst(class RandomGroupSeqInst * const this /* r30 */, class RandomGroupSeq * owner /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18RandomGroupSeqInst;
}

// Range: 0x805854D8 -> 0x805855E8
void * RandomGroupSeqInst::~RandomGroupSeqInst(class RandomGroupSeqInst * const this /* r30 */) {}

// Range: 0x805855E8 -> 0x80585C40
void RandomGroupSeqInst::StartImpl(class RandomGroupSeqInst * const this /* r23 */) {
    // Local variables
    int num; // r26
    int child; // r0
    int i; // r26
    int left; // r25
    int candidate; // r24

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__27ObjPtr<7SeqInst,9ObjectDir>;
}

// Range: 0x80585C40 -> 0x80585CA4
void RandomGroupSeqInst::Stop(class RandomGroupSeqInst * const this /* r30 */) {
    // Local variables
    class ObjPtr * it; // r31
}

// Range: 0x80585CA4 -> 0x80585CC0
unsigned char RandomGroupSeqInst::IsRunning() {}

// Range: 0x80585CC0 -> 0x80585D2C
void RandomGroupSeqInst::Poll(class RandomGroupSeqInst * const this /* r31 */) {}

// Range: 0x80585D2C -> 0x80585E74
void Sequence::Init() {
    // References
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
}

class SfxSeq : public SerialGroupSeq {
    // total size: 0x8C
};
// Range: 0x80585E74 -> 0x80585EB8
void * SfxSeq::SfxSeq(class SfxSeq * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__6SfxSeq;
}

// Range: 0x8058607C -> 0x805860C0
void SfxSeq::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805860C0 -> 0x80586484
void SfxSeq::Load(class SfxSeq * const this /* r28 */, class BinStream & s /* r29 */) {
    // Local variables
    int rev; // r1+0x10
    class ObjPtr sfx; // r1+0x14

    // References
    // -> struct [anonymous] __vt__28ObjPtr<8Sequence,9ObjectDir>;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x18
} __vt__27ObjPtr<7SeqInst,9ObjectDir>; // size: 0x18, address: 0x8091DED0
struct {
    // total size: 0x8
} __RTTI__27ObjPtr<7SeqInst,9ObjectDir>; // size: 0x8, address: 0x8091DF10
struct {
    // total size: 0x70
} __vt__18RandomGroupSeqInst; // size: 0x70, address: 0x8091DF60
struct {
    // total size: 0x8
} __RTTI__18RandomGroupSeqInst; // size: 0x8, address: 0x8091E008
struct {
    // total size: 0x70
} __vt__20ParallelGroupSeqInst; // size: 0x70, address: 0x8091E010
struct {
    // total size: 0x8
} __RTTI__20ParallelGroupSeqInst; // size: 0x8, address: 0x8091E0C0
struct {
    // total size: 0x70
} __vt__18SerialGroupSeqInst; // size: 0x70, address: 0x8091E0C8
struct {
    // total size: 0x8
} __RTTI__18SerialGroupSeqInst; // size: 0x8, address: 0x8091E170
struct {
    // total size: 0x70
} __vt__12GroupSeqInst; // size: 0x70, address: 0x8091E178
struct {
    // total size: 0x8
} __RTTI__12GroupSeqInst; // size: 0x8, address: 0x8091E218
struct {
    // total size: 0x70
} __vt__11WaitSeqInst; // size: 0x70, address: 0x8091E220
struct {
    // total size: 0x8
} __RTTI__11WaitSeqInst; // size: 0x8, address: 0x8091E2B8
struct {
    // total size: 0x6C
} __vt__6SfxSeq; // size: 0x6C, address: 0x8091E2C0
struct {
    // total size: 0x8
} __RTTI__6SfxSeq; // size: 0x8, address: 0x8091E368
struct {
    // total size: 0x70
} __vt__7SeqInst; // size: 0x70, address: 0x8091E370
struct {
    // total size: 0x6C
} __vt__16ParallelGroupSeq; // size: 0x6C, address: 0x8091E408
struct {
    // total size: 0x8
} __RTTI__16ParallelGroupSeq; // size: 0x8, address: 0x8091E4B8
struct {
    // total size: 0x6C
} __vt__14SerialGroupSeq; // size: 0x6C, address: 0x8091E4C0
struct {
    // total size: 0x8
} __RTTI__14SerialGroupSeq; // size: 0x8, address: 0x8091E568
struct {
    // total size: 0x6C
} __vt__14RandomGroupSeq; // size: 0x6C, address: 0x8091E570
struct {
    // total size: 0x8
} __RTTI__14RandomGroupSeq; // size: 0x8, address: 0x8091E618
struct {
    // total size: 0x6C
} __vt__8GroupSeq; // size: 0x6C, address: 0x8091E620
struct {
    // total size: 0x8
} __RTTI__8GroupSeq; // size: 0x8, address: 0x8091E6C0
struct {
    // total size: 0x6C
} __vt__7WaitSeq; // size: 0x6C, address: 0x8091E718
struct {
    // total size: 0x8
} __RTTI__7WaitSeq; // size: 0x8, address: 0x8091E7B8
struct {
    // total size: 0x6C
} __vt__8Sequence; // size: 0x6C, address: 0x8091E7C0
struct {
    // total size: 0x18
} __vt__31ObjPtrList<7SeqInst,9ObjectDir>; // size: 0x18, address: 0x8091E860
struct {
    // total size: 0x8
} __RTTI__31ObjPtrList<7SeqInst,9ObjectDir>; // size: 0x8, address: 0x8091E8A8
struct {
    // total size: 0x8
} __RTTI__P28ObjPtr<8Sequence,9ObjectDir>; // size: 0x8, address: 0x8091E958
struct {
    // total size: 0x8
} __RTTI__P27ObjPtr<7SeqInst,9ObjectDir>; // size: 0x8, address: 0x8091E980

