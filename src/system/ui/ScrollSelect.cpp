#include "ScrollSelect.h"
#include "obj/Object.h"
#include "utl/Symbols.h"

ScrollSelect::ScrollSelect() : unk_0x4(0) { Reset(); }

void ScrollSelect::Store() { unk_0x8 = SelectedAux(); }

void ScrollSelect::Reset() { unk_0x8 = -1; }
/*
BEGIN_HANDLERS(ScrollSelect)
    HANDLE_EXPR(is_scroll_selected, unk_0x8)
    HANDLE_ACTION(reset, Reset())
END_HANDLERS
*/
BEGIN_PROPSYNCS(ScrollSelect)
    SYNC_PROP(select_to_scroll, unk_0x4)
END_PROPSYNCS

ScrollSelect::~ScrollSelect() {}
