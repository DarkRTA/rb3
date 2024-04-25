#include "midi/MidiParserMgr.h"
#include "os/Debug.h"
#include "obj/Dir.h"
#include "midi/MidiParser.h"

MidiParserMgr* TheMidiParserMgr = 0;

MidiParserMgr::MidiParserMgr(GemListInterface* gListInt, Symbol sym) : unk24(0), unk28(0), unk2c(0), unk30(0), unk34(0), unk38(0), mGems(gListInt),
    mLoaded(0), mFilename(0), unk48(), mSongName(), unk50(), unk58(true), unk59(true) {
    MILO_ASSERT(!TheMidiParserMgr, 0x27);
    TheMidiParserMgr = this;
    SetName("midiparsermgr", ObjectDir::sMainDir);
    mSongName = sym;
    MidiParser::Init();
    DataArray* arr = SystemConfig("beatmatcher")->FindArray("midi_parsers", false);
    if(arr){
        DataArray* initArr = arr->FindArray("init", false);
        if(initArr){
            initArr->ExecuteScript(1, this, 0, 1);
        }
        else {
            MILO_WARN("Could not find init block in midi parser array, no parsers will be constructed");
        }
    }
}

MidiParserMgr::~MidiParserMgr(){

}