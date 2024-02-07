/*
    Compile unit: C:\rockband2\band2\src\meta\BotbNewsFeedPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80204B1C -> 0x80206854
*/
class DataArray * types; // size: 0x4, address: 0x80A4E6A0
static class Symbol botb_news_new_headline; // size: 0x4, address: 0x80A4E6A8
static class Symbol botb_news_over_headline; // size: 0x4, address: 0x80A4E6B0
static class Symbol botb_news_passed_headline; // size: 0x4, address: 0x80A4E6B8
static class Symbol botb_news_overall_headline; // size: 0x4, address: 0x80A4E6C0
static class Symbol botb_news_passed_headline_singular; // size: 0x4, address: 0x80A4E6C8
static class Symbol botb_news_overall_headline_singular; // size: 0x4, address: 0x80A4E6D0
// Range: 0x80204B1C -> 0x80204DA8
char * BotbNewsItem::GetHeadline(const class BotbNewsItem * const this /* r30 */) {
    // Local variables
    const char * string; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol botb_news_overall_headline_singular;
    // -> static class Symbol botb_news_passed_headline_singular;
    // -> static class Symbol botb_news_overall_headline;
    // -> static class Symbol botb_news_passed_headline;
    // -> static class Symbol botb_news_over_headline;
    // -> static class Symbol botb_news_new_headline;
}

static class Symbol botb_news_new_text; // size: 0x4, address: 0x80A4E6D8
static class Symbol botb_news_new_text_singular; // size: 0x4, address: 0x80A4E6E0
static class Symbol botb_news_new_text_none; // size: 0x4, address: 0x80A4E6E8
static class Symbol botb_news_over_text; // size: 0x4, address: 0x80A4E6F0
static class Symbol botb_news_passed_text; // size: 0x4, address: 0x80A4E6F8
static class Symbol botb_news_overall_text; // size: 0x4, address: 0x80A4E700
// Range: 0x80204DA8 -> 0x802050A0
char * BotbNewsItem::GetBody(const class BotbNewsItem * const this /* r30 */) {
    // Local variables
    const char * string; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol botb_news_overall_text;
    // -> static class Symbol botb_news_passed_text;
    // -> static class Symbol botb_news_over_text;
    // -> static class Symbol botb_news_new_text_none;
    // -> static class Symbol botb_news_new_text_singular;
    // -> static class Symbol botb_news_new_text;
}

// Range: 0x802050A0 -> 0x802052B0
void * BotbNewsProvider::BotbNewsProvider(class BotbNewsProvider * const this /* r27 */, class vector & items /* r30 */, const class vector & covers /* r29 */, class ObjectDir * dir /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __vt__16BotbNewsProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x802052B0 -> 0x802054B0
char * BotbNewsProvider::Text(const class BotbNewsProvider * const this /* r30 */, int data /* r28 */, class Symbol & slot /* r29 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802054B0 -> 0x802056C0
class RndMat * BotbNewsProvider::Mat(const class BotbNewsProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    class DynamicTex * const * c; // r0

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class _List_node : public _List_node_base {
    // total size: 0x20
public:
    class BotbNewsRow _M_data; // offset 0x8, size 0x18
};
// Range: 0x802056C0 -> 0x80205A50
void BotbNewsFeedPanel::Load(class BotbNewsFeedPanel * const this /* r28 */) {
    // Local variables
    class vector users; // r1+0x6C
    unsigned char firstTime; // r31
    struct DateTime newsTime; // r1+0x28
    class String cookies; // r1+0x60
    class BandUser * * u; // r30
    class Profile * profile; // r29
    struct DateTime t; // r1+0x20

    // References
    // -> class RockCentralGateway RockCentral;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Tour * TheTour;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80205A50 -> 0x80205DC0
class DataNode BotbNewsFeedPanel::OnMsg(class BotbNewsFeedPanel * const this /* r29 */) {
    // Local variables
    const class list * list; // r30
    struct _List_iterator it; // r1+0x24
    const char * path; // r0
    class BotbNewsItem item; // r1+0x60
    class vector users; // r1+0x54
    class BandUser * * u; // r26
    class Profile * profile; // r27
    struct DateTime dt; // r1+0x30
    class String cookies; // r1+0x48

    // References
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
}

// Range: 0x80205DC0 -> 0x80205F40
void BotbNewsFeedPanel::NewBand(class BotbNewsFeedPanel * const this /* r31 */) {
    // References
    // -> class Tour * TheTour;
}

// Range: 0x80205F40 -> 0x80206074
void BotbNewsFeedPanel::Exit(class BotbNewsFeedPanel * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x80206074 -> 0x802061AC
void BotbNewsFeedPanel::Enter(class BotbNewsFeedPanel * const this /* r28 */) {
    // Local variables
    class ObjectDir * dir; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802061AC -> 0x802062EC
void BotbNewsFeedPanel::Unload(class BotbNewsFeedPanel * const this /* r31 */) {}

// Range: 0x802062EC -> 0x80206308
unsigned char BotbNewsFeedPanel::IsLoaded() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E708
// Range: 0x80206308 -> 0x80206854
class DataNode BotbNewsFeedPanel::Handle(class BotbNewsFeedPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__24RockCentralOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xF4
} __vt__17BotbNewsFeedPanel; // size: 0xF4, address: 0x808AAD60
struct {
    // total size: 0x98
} __vt__16BotbNewsProvider; // size: 0x98, address: 0x808AAEA0
struct {
    // total size: 0x8
} __RTTI__16BotbNewsProvider; // size: 0x8, address: 0x808AAF68
struct {
    // total size: 0x8
} __RTTI__P12BotbNewsItem; // size: 0x8, address: 0x808AB1A0

