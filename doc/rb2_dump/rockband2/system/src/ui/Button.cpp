/*
    Compile unit: C:\rockband2\system\src\ui\Button.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803C8834 -> 0x803C8AA4
*/
class DataArray * types; // size: 0x4, address: 0x80A51868
class Symbol name; // size: 0x4, address: 0x80A51870
// Range: 0x803C8834 -> 0x803C8918
void * UIButton::UIButton(class UIButton * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8UIButton;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803C8918 -> 0x803C8974
void UIButton::Load(class UIButton * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803C8974 -> 0x803C8978
void UIButton::PostLoad() {}

// Range: 0x803C8978 -> 0x803C8A24
class DataNode UIButton::OnMsg(class UIButton * const this /* r29 */, const class ButtonDownMsg & msg /* r30 */) {}

// Range: 0x803C8A24 -> 0x803C8AA4
unsigned char UIButton::SyncProperty(class UIButton * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0x154
} __vt__8UIButton; // size: 0x154, address: 0x808E1934

