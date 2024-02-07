/*
    Compile unit: C:\rockband2\band2\src\meta\MoviePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80120A50 -> 0x80120F54
*/
class DataArray * types; // size: 0x4, address: 0x80A4BB40
// Range: 0x80120A50 -> 0x80120A54
unsigned char MoviePanel::IsLoaded() {}

// Range: 0x80120A54 -> 0x80120A94
void MoviePanel::Enter(class MoviePanel * const this /* r31 */) {}

// Range: 0x80120A94 -> 0x80120AD4
void MoviePanel::Exit(class MoviePanel * const this /* r31 */) {}

// Range: 0x80120AD4 -> 0x80120B14
void MoviePanel::Unload(class MoviePanel * const this /* r31 */) {}

static class Message movie_done; // size: 0x8, address: 0x80978FF0
// Range: 0x80120B14 -> 0x80120D0C
void MoviePanel::Poll(class MoviePanel * const this /* r31 */) {
    // Local variables
    class DataNode ret; // r1+0x20

    // References
    // -> static class Message movie_done;
    // -> struct [anonymous] __vt__7Message;
    // -> class UIManager TheUI;
}

// Range: 0x80120D0C -> 0x80120D38
void MoviePanel::Draw() {}

// Range: 0x80120D38 -> 0x80120F54
void MoviePanel::ChooseMovie(class MoviePanel * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std15_List_node<PCc>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std15_List_node<PCc>; // size: 0x8, address: 0x8088E120
struct {
    // total size: 0xAC
} __vt__10MoviePanel; // size: 0xAC, address: 0x8088E150
struct {
    // total size: 0x8
} __RTTI__10MoviePanel; // size: 0x8, address: 0x8088E228
struct {
    // total size: 0x8
} __RTTI__PPCc; // size: 0x8, address: 0x8088E298

