#include "bandobj/ScrollbarDisplay.h"
#include "utl/Symbols.h"

ScrollbarDisplay::ScrollbarDisplay() : mScrollbarList(this, 0), mScrollbarHeight(200.0f), mAlwaysShow(0), mListXOffset(0), mListYOffset(0), mMinThumbHeight(1.0f),
    unk12c(0), unk130(0), unk134(0), unk138(0), unk13c(0), unk140(-1), unk144(-1), unk148(-1), unk14c(-1), unk150(0), unk154(0) {

}

ScrollbarDisplay::~ScrollbarDisplay(){
    
}

BEGIN_HANDLERS(ScrollbarDisplay)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x1E9)
END_HANDLERS

BEGIN_PROPSYNCS(ScrollbarDisplay)
    SYNC_PROP_SET(scrollbar_list, GetList(), SetList(_val.Obj<BandList>(0)))
    SYNC_PROP_SET(always_show, mAlwaysShow, SetAlwaysShow(_val.Int(0)))
    SYNC_PROP_SET(list_attached, GetListAttached(), SetListAttached(_val.Int(0)))
    SYNC_PROP_SET(list_x_offset, mListXOffset, SetListXOffset(_val.Float(0)))
    SYNC_PROP_SET(list_y_offset, mListYOffset, SetListYOffset(_val.Float(0)))
    SYNC_PROP_SET(scrollbar_height, mScrollbarHeight, SetHeight(_val.Float(0)))
    SYNC_PROP_SET(min_thumb_height, mMinThumbHeight, SetMinThumbHeight(_val.Float(0)))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS