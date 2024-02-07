/*
    Compile unit: C:\rockband2\system\src\bandobj\TrackPanelDir.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802C2EB8 -> 0x802C3C2C
*/
// Range: 0x802C2EB8 -> 0x802C2EFC
void TrackPanelDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802C2EFC -> 0x802C3014
void TrackPanelDir::PreLoad(class TrackPanelDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> class Debug TheDebug;
}

// Range: 0x802C3014 -> 0x802C3058
class Symbol TrackPanelDir::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x802C3058 -> 0x802C3A88
void TrackPanelDir::SyncObjects(class TrackPanelDir * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__10Scoreboard;
    // -> struct [anonymous] __RTTI__13VocalTrackDir;
    // -> struct [anonymous] __RTTI__11GemTrackDir;
    // -> struct [anonymous] __RTTI__11EndingBonus;
    // -> struct [anonymous] __RTTI__14BandCrowdMeter;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x802C3A88 -> 0x802C3C1C
void TrackPanelDir::SetType(class TrackPanelDir * const this /* r29 */, class Symbol & TrackPanelDir /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x802C3C1C -> 0x802C3C24
class EndingBonus * TrackPanelDir::GetEndingBonus() {}

// Range: 0x802C3C24 -> 0x802C3C2C
class BandCrowdMeter * TrackPanelDir::GetCrowdMeter() {}


