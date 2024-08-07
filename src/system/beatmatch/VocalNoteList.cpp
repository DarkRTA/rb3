#include "beatmatch/VocalNote.h"
#include "beatmatch/SongData.h"
#include "os/System.h"

VocalPhrase::VocalPhrase() : unk0(0), unk4(0), unk8(-1), unkc(-1), unk10(-1), unk14(-1), unk18(0), unk19(0), unk1a(0), unk1c(0), unk20(0), unk24(3.4028235E+38f), unk28(-3.4028235E+38f),
    unk2c(0), unk2d(0), unk30(0), unk34(0) {

}

VocalNoteList::VocalNoteList(SongData* data) : mSongData(data), mFreestyleMinDuration(0), mFreestylePad(0) {
    DataArray* scoringArr = SystemConfig()->FindArray("scoring", false);
    if(scoringArr){
        DataArray* vocalsArr = SystemConfig("scoring")->FindArray("vocals", false);
        if(vocalsArr){
            mFreestyleMinDuration = vocalsArr->FindArray("freestyle_min_duration", true)->Array(1);
            mFreestylePad = vocalsArr->FindArray("freestyle_pad", true)->Array(1);
            if(mFreestyleMinDuration->Size() != mFreestylePad->Size()){
                MILO_WARN("scoring.dta: must have same number of items in both freestyle_min_duration and freestyle_pad.");
            }
        }
    }
}