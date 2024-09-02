#include "midi/MidiParserMgr.h"
#include "os/Debug.h"
#include "obj/Dir.h"
#include "midi/MidiParser.h"
#include "utl/TimeConversion.h"
#include "beatmatch/GemListInterface.h"
#include "utl/Symbols.h"

MidiParserMgr* TheMidiParserMgr = 0;

MidiParserMgr::MidiParserMgr(GemListInterface* gListInt, Symbol sym) : mGems(gListInt),
    mLoaded(0), mFilename(0), mTrackName(), mSongName(), unk50(), unk58(true), unk59(true) {
    MILO_ASSERT(!TheMidiParserMgr, 0x27);
    TheMidiParserMgr = this;
    SetName("midiparsermgr", ObjectDir::sMainDir);
    mSongName = sym;
    MidiParser::Init();
    DataArray* arr = MidiParserArray();
    if(arr){
        DataArray* initArr = arr->FindArray("init", false);
        if(initArr) initArr->ExecuteScript(1, this, 0, 1);
        else MILO_WARN("Could not find init block in midi parser array, no parsers will be constructed");
    }
}

MidiParserMgr::~MidiParserMgr(){
    ClearManagedParsers();
    TheMidiParserMgr = 0;
}

void MidiParserMgr::Reset(int i){
    if(mLoaded && unk59){
        float beat = TickToBeat(i);
        for(std::list<MidiParser*>::iterator it = MidiParser::sParsers.begin(); it != MidiParser::sParsers.end(); it++){
            (*it)->Reset(beat);
        }
    }
}

void MidiParserMgr::Reset(){
    if(mLoaded){
        for(std::list<MidiParser*>::iterator it = MidiParser::sParsers.begin(); it != MidiParser::sParsers.end(); it++){
            (*it)->Reset(-2e+30f);
        }
    }
}

void MidiParserMgr::Poll(){
    if(unk59){
        for(std::list<MidiParser*>::iterator it = MidiParser::sParsers.begin(); it != MidiParser::sParsers.end(); it++){
            (*it)->Poll();
        }
    }
}

void MidiParserMgr::FreeAllData(){
    unk30.clear();
    unk24.clear();
}

void MidiParserMgr::OnNewTrack(int i){
    MemDoTempAllocations m(true, false);
    MILO_ASSERT(!mSongName.Null(), 0x7C);
    FreeAllData();
    unk24.resize(128);
    unk30.reserve(2000);
    unk58 = true;
}

void MidiParserMgr::OnEndOfTrack(){
    if(!mTrackName.Null()){
        if(unk30.size() > 2000){
            MILO_WARN("%s track %s has %d text events which is over the limit of %d, if that is correct contact James to increase kMaxTextSize", mFilename, mTrackName, unk30.size(), 2000);
        }
        if(mGems) mGems->SetTrack(mTrackName);
        for(std::list<MidiParser*>::iterator it = MidiParser::sParsers.begin(); it != MidiParser::sParsers.end(); it++){
            if((*it)->mTrackName == mTrackName){
                int size = (*it)->ParseAll(mGems, unk30);
                if(size > 20000){
                    MILO_WARN("%s track %s has %d notes which is over the limit of %d, if that is correct contact James to increase kMaxNoteSize", mFilename, mTrackName, size, 20000);
                }
            }
        }
        FreeAllData();
        mTrackName = Symbol("");
    }
}

void MidiParserMgr::OnAllTracksRead(){}

void MidiParserMgr::FinishLoad(){
    DataArray* arr = MidiParserArray();
    if(arr){
        DataArray* finishArr = arr->FindArray("finish_loading", false);
        if(finishArr){
            finishArr->ExecuteScript(1, this, 0, 1);
        }
    }
    mLoaded = true;
}

BEGIN_PROPSYNCS(MidiParserMgr)
    SYNC_PROP(song_name, mSongName)
END_PROPSYNCS