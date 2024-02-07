/*
    Compile unit: C:\rockband2\system\src\beatmatch\DrumPlayer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802DAB58 -> 0x802DADCC
*/
static char * seq_names[9]; // size: 0x24, address: 0x808CAD6C
// Range: 0x802DAB58 -> 0x802DAD54
void DrumPlayer::Play(class DrumPlayer * const this /* r31 */, int slot /* r27 */, float vol /* f31 */, class Symbol & sample_set /* r28 */) {
    // Local variables
    class DataArray * seq_list; // r29
    class DataArray * seq_cfg; // r28
    const char * seq_name; // r28

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Synth * TheSynth;
    // -> static char * seq_names[9];
}

// Range: 0x802DAD54 -> 0x802DADC0
void DrumPlayer::OverrideDrumSamples(class DrumPlayer * const this /* r30 */, class DataArray * seq_list /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802DADC0 -> 0x802DADCC
void DrumPlayer::ResetDrumSamples() {}


