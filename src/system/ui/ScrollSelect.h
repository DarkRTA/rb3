#ifndef UI_SCROLLSELECT_H
#define UI_SCROLLSELECT_H

#include "obj/Data.h"
#include "obj/Object.h"
#include "utl/PoolAlloc.h"

class ScrollSelect {
    ScrollSelect();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~ScrollSelect();
    virtual int SelectedAux() const = 0;
    virtual void SetSelectedAux(int) = 0;

    void Store();
    void Reset();

    bool unk_0x4;
    int unk_0x8;

    void operator delete(void* v) { _PoolFree(sizeof(ScrollSelect), FastPool, v); }
};

#endif // UI_SCROLLSELECT_H
