#include "ui/UIListSubList.h"
#include "utl/Symbols.h"

INIT_REVS(UIListSubList)

UIListSubList::UIListSubList() : mList(this, 0) {

}

UIList* UIListSubList::SubList(int i){
    UIListSubListElement* sle = dynamic_cast<UIListSubListElement*>(mElements[i]);
    MILO_ASSERT(sle, 0x5E);
    return sle->List();
}

SAVE_OBJ(UIListSubList, 0xAC)

BEGIN_LOADS(UIListSubList)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(UIListSlot)
    bs >> mList;
END_LOADS

BEGIN_COPYS(UIListSubList)
    COPY_SUPERCLASS(UIListSlot)
    CREATE_COPY_AS(UIListSubList, sl)
    MILO_ASSERT(sl, 0xBC);
    COPY_MEMBER_FROM(sl, mList)
END_COPYS

BEGIN_HANDLERS(UIListSubList)
    HANDLE_SUPERCLASS(UIListSlot)
    HANDLE_CHECK(0xC2)
END_HANDLERS

BEGIN_PROPSYNCS(UIListSubList)
    SYNC_PROP(list, mList)
    SYNC_SUPERCLASS(UIListSlot)
END_PROPSYNCS