#include "char/FileMerger.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"

#define kNoHeap -3
#define kSystemHeap -1

FileMerger::FileMerger() : mMergers(this), mAsyncLoad(0), mLoadingLoad(0), unk44(0), unk50(0), mHeap(GetCurrentHeapNum()), unk58(this) {
    MILO_ASSERT(MemNumHeaps() == 0 || (mHeap != kNoHeap && mHeap != kSystemHeap), 0x73);
}

FileMerger::~FileMerger(){

}

BEGIN_CUSTOM_PROPSYNC(FileMerger::Merger)
    SYNC_PROP(name, o.mName)
    SYNC_PROP(selected, o.mSelected)
    SYNC_PROP_SET(loaded, o.mLoaded, )
    SYNC_PROP(dir, o.mDir)
    SYNC_PROP(proxy, o.mProxy)
    SYNC_PROP(subdirs, o.mSubdirs)
    SYNC_PROP(preclear, o.mPreClear)
    {
        static Symbol _s("loaded_objects");
        if(sym == _s && (_op & (kPropSize|kPropGet))){
            return PropSync(o.mLoadedObjects, _val, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("loaded_subdirs");
        if(sym == _s && (_op & (kPropSize|kPropGet))){
            return PropSync(o.mLoadedSubdirs, _val, _prop, _i + 1, _op);
        }
    }
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(FileMerger)
    SYNC_PROP(mergers, mMergers)
    SYNC_PROP(disable_all, sDisableAll)
    SYNC_PROP_SET(loading_load, mLoadingLoad, )
    SYNC_PROP_SET(async_load, mAsyncLoad, )
END_PROPSYNCS