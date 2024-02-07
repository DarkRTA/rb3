/*
    Compile unit: C:\rockband2\system\src\net\Net.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8052704C -> 0x80527D0C
*/
class _DDL_AudioStreamFormat : public RootObject {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int m_uiNbSamplesPerPacket; // offset 0x4, size 0x4
    unsigned int m_uiNbChannels; // offset 0x8, size 0x4
    unsigned int m_uiNbSamplesPerSec; // offset 0xC, size 0x4
    unsigned int m_uiNbBitsPerSample; // offset 0x10, size 0x4
};
class AudioStreamFormat : public _DDL_AudioStreamFormat {
    // total size: 0x14
};
class Codec : public RootObject {
    // total size: 0x18
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class AudioStreamFormat m_oAudioStreamFormat; // offset 0x4, size 0x14
};
class GSMCodec : public Codec {
    // total size: 0x1C
    unsigned int m_uiNbFramesPerPackets; // offset 0x18, size 0x4
};
class Net TheNet; // size: 0x368, address: 0x80981C40
enum _State {
    Running = 0,
    Stopping = 1,
    Stopped = 2,
};
class ObjectThread {
    // total size: 0x0
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    class ObjectThread * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjectThread * * _M_start; // offset 0x0, size 0x4
    class ObjectThread * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class WorkerThreads : public RootObject {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class CriticalSection m_csState; // offset 0x4, size 0x14
    enum _State m_eState; // offset 0x18, size 0x4
    class qVector m_vecThreads; // offset 0x1C, size 0xC
};
class SchedulerWorkerThread : public WorkerThreads {
    // total size: 0x2C
    class Scheduler * m_pScheduler; // offset 0x28, size 0x4
};
struct iterator {
    // total size: 0x1
};
class iterator : public iterator {
    // total size: 0x4
    class Job * m_link; // offset 0x0, size 0x4
};
class qChain : public RootObject {
    // total size: 0x10
    class iterator m_itFirst; // offset 0x0, size 0x4
    class iterator m_itLast; // offset 0x4, size 0x4
    class iterator m_itEnd; // offset 0x8, size 0x4
    unsigned long m_nbLinks; // offset 0xC, size 0x4
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
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
class multimap {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class qMultiMap : public multimap {
    // total size: 0x18
};
class Links {
    // total size: 0x8
public:
    class WaterMark * m_pNext; // offset 0x0, size 0x4
    class WaterMark * m_pPrevious; // offset 0x4, size 0x4
};
class WaterMark : public RootObject {
    // total size: 0x2C
public:
    class Links m_oLinks; // offset 0x0, size 0x8
private:
    unsigned int m_uiCount; // offset 0x8, size 0x4
    unsigned int m_uiHigh; // offset 0xC, size 0x4
    unsigned int m_uiLow; // offset 0x10, size 0x4
    const char * m_szDescription; // offset 0x14, size 0x4
    unsigned int m_uiLastTime; // offset 0x18, size 0x4
    unsigned int m_uiWindowSize; // offset 0x1C, size 0x4
    float m_dAverage; // offset 0x20, size 0x4
    float m_dWeight; // offset 0x24, size 0x4
    float m_dTotalWeightOfEntries; // offset 0x28, size 0x4
};
class HighResolutionChrono : public RootObject {
    // total size: 0x10
    unsigned long long m_HPStartTime; // offset 0x0, size 0x8
    class Time m_tStartTime; // offset 0x8, size 0x8
};
class Scheduler : public RootObject {
    // total size: 0x1B8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class Job * m_pCurrentJob; // offset 0x4, size 0x4
    unsigned char m_bCurrentJobValid; // offset 0x8, size 0x1
    class SchedulerWorkerThread * m_pWorkerThreads; // offset 0xC, size 0x4
    class EventHandler m_oEventHandler; // offset 0x10, size 0x24
    class Event * m_pWakeUpEvent; // offset 0x34, size 0x4
    class CriticalSection m_csSystemLock; // offset 0x38, size 0x14
    class CriticalSection m_csQueue; // offset 0x4C, size 0x14
    class qChain m_lstReadyQueue; // offset 0x60, size 0x10
    class qChain m_lstSuspendedQueue; // offset 0x70, size 0x10
    class qChain m_lstSpecialDispatchJobs; // offset 0x80, size 0x10
    class qMultiMap m_mapTimedQueue; // offset 0x90, size 0x18
    unsigned char m_bIgnoreWaitTime; // offset 0xA8, size 0x1
    class WaterMark m_oSchedulerJobs; // offset 0xAC, size 0x2C
    class WaterMark m_oBusyRatio; // offset 0xD8, size 0x2C
    class ProfilingUnit m_oJobProcessing; // offset 0x108, size 0x38
    class Time m_tiLastDispatchStart; // offset 0x140, size 0x8
    class Time m_tiLastDispatchEnd; // offset 0x148, size 0x8
    unsigned int m_icContext; // offset 0x150, size 0x4
    class SingleThreadCallPolicy m_oDispatchCallPolicy; // offset 0x154, size 0x14
    class ProfilingUnit m_puDispatchInterval; // offset 0x168, size 0x38
    class HighResolutionChrono m_oChrono; // offset 0x1A0, size 0x10
    unsigned char m_bRecordDispatchInterval; // offset 0x1B0, size 0x1
    unsigned char m_bTraceActivity; // offset 0x1B1, size 0x1
};
class Scheduler * gScheduler; // size: 0x4, address: 0x80A53CA8
class _DS_ChannelInfo : public DataSet {
    // total size: 0xC
public:
    unsigned char m_byCodec; // offset 0x0, size 0x1
    unsigned char m_byNbStreams; // offset 0x1, size 0x1
    unsigned char m_byTransmissionFrequency; // offset 0x2, size 0x1
    class String m_strDescription; // offset 0x4, size 0x4
    unsigned short m_uiPacketSize; // offset 0x8, size 0x2
};
class ChannelInfo : public _DS_ChannelInfo {
    // total size: 0xC
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class _DS_ChannelMembers : public DataSet {
    // total size: 0x8
public:
    class qList m_dsMemberList; // offset 0x0, size 0x8
};
class ChannelMembers : public _DS_ChannelMembers {
    // total size: 0xC
    class VoiceChannel * m_pAssociatedChannel; // offset 0x8, size 0x4
};
class _DO_VoiceChannel : public RootDO {
    // total size: 0x8C
public:
    class ChannelInfo m_dsChannelInfo; // offset 0x74, size 0xC
    class ChannelMembers m_dsChannelMembers; // offset 0x80, size 0xC
};
class EventHandler {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class VoiceStream {
    // total size: 0x0
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x4
public:
    class VoiceStream * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class VoiceStream * * _M_start; // offset 0x0, size 0x4
    class VoiceStream * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class qVector : public vector, public RootObject {
    // total size: 0xC
};
class VoiceChannel : public _DO_VoiceChannel {
    // total size: 0xB8
    unsigned char m_byNbAcquiredStreams; // offset 0x8C, size 0x1
    class EventHandler * m_pEventHandler; // offset 0x90, size 0x4
    class qVector m_vVoiceStreams; // offset 0x94, size 0xC
    class Time m_tiNextHouseKeeping; // offset 0xA0, size 0x8
    int m_tiJitterTolerance; // offset 0xA8, size 0x4
    unsigned char * m_pPacketRead; // offset 0xAC, size 0x4
    unsigned int m_uiTransmissionFrequency; // offset 0xB0, size 0x4
};
// Range: 0x8052704C -> 0x805270E0
static void CreateVoiceChannel() {
    // Local variables
    class VoiceChannel * channel; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class WKHandle gVoiceChannel;
}

// Range: 0x805270E0 -> 0x805271EC
void * QuazalUserThread() {
    // References
    // -> class InstanceTable s_oInstanceTable;
    // -> class Scheduler * gScheduler;
}

// Range: 0x805271EC -> 0x80527204
void NotifySessionUserReady() {
    // References
    // -> class Net TheNet;
}

// Range: 0x80527204 -> 0x80527210
static void TerminateTheNet() {
    // References
    // -> class Net TheNet;
}

// Range: 0x80527210 -> 0x8052725C
void * Net::Net(class Net * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__3Net;
}

static int _x; // size: 0x4, address: 0x80A53CAC
// Range: 0x8052725C -> 0x80527348
static void * QuazalAlloc(unsigned long size /* r30 */) {
    // Local variables
    int num; // r1+0x10
    int bytes; // r1+0xC
    int largest; // r1+0x8

    // References
    // -> static int _x;
    // -> class Net TheNet;
}

// Range: 0x80527348 -> 0x80527524
void Net::Init(class Net * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> class NetMessenger TheNetMessenger;
    // -> class CodecManager s_oInstance;
    // -> unsigned char s_bIsMemoryFunctionSet;
    // -> void (* s_fcnFree)(void *);
    // -> void * (* s_fcnMalloc)(unsigned long);
    // -> class LogFile NetLog;
    // -> unsigned char s_bUsesThreads;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x80527524 -> 0x8052767C
void Net::Terminate(class Net * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

class NetworkEmulator : public Object {
    // total size: 0x54
    int mEnabled; // offset 0x28, size 0x4
    class EmulationDevice * mInDevice; // offset 0x2C, size 0x4
    class EmulationDevice * mOutDevice; // offset 0x30, size 0x4
    int mInBandwidth; // offset 0x34, size 0x4
    int mOutBandwidth; // offset 0x38, size 0x4
    int mInJitter; // offset 0x3C, size 0x4
    int mOutJitter; // offset 0x40, size 0x4
    int mInLatency; // offset 0x44, size 0x4
    int mOutLatency; // offset 0x48, size 0x4
    int mInDropProb; // offset 0x4C, size 0x4
    int mOutDropProb; // offset 0x50, size 0x4
};
// Range: 0x8052767C -> 0x805276E8
void Net::Poll(class Net * const this /* r31 */) {
    // References
    // -> class NetMessenger TheNetMessenger;
}

// Range: 0x805276E8 -> 0x8052774C
class NetGameData * Net::GetGameData(class Net * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052774C -> 0x80527758
void Net::SetGameData() {}

// Range: 0x80527758 -> 0x805277D0
class User * Net::GetUser(int userNum /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x805277D0 -> 0x805277EC
void Net::ToggleLogging() {
    // References
    // -> class LogFile NetLog;
}

static class Symbol _s; // size: 0x4, address: 0x80A53CB4
// Range: 0x805277EC -> 0x80527CC4
class DataNode Net::Handle(class Net * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__3Net; // size: 0x54, address: 0x809057A0
struct {
    // total size: 0x8
} __RTTI__3Net; // size: 0x8, address: 0x80905808
// Range: 0x80527CC4 -> 0x80527D0C
static void __sinit_\Net_cpp() {
    // References
    // -> class Net TheNet;
}

class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
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
class qMap : public map, public RootObject {
    // total size: 0x18
};
class CodecManager : public RootObject {
    // total size: 0x18
protected:
    class qMap m_mapCodec; // offset 0x0, size 0x18
};
class CodecManager s_oInstance; // size: 0x18, address: 0x80A32EB4
unsigned char s_bIsMemoryFunctionSet; // size: 0x1, address: 0x80A55E70
void (* s_fcnFree)(void *); // size: 0x4, address: 0x80A55E78
void * (* s_fcnMalloc)(unsigned long); // size: 0x4, address: 0x80A55E74
unsigned char s_bUsesThreads; // size: 0x1, address: 0x80A48700

