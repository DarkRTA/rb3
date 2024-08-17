#include "beatmatch/VocalNote.h"
#include "beatmatch/SongData.h"
#include "os/System.h"
#include "utl/MemMgr.h"

inline const char* VocalNoteList::PrintTick(int tick) const {
    return TickFormat(tick, *mSongData->GetMeasureMap());
}

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

void VocalNoteList::Clear(){
    mPhrases.clear();
    mLyricPhrases.clear();
    mNotes.clear();
    mTambourineGems.clear();
    mFreestyleSections.clear();
}

void CopyPhraseVec(const std::vector<VocalPhrase>& src, std::vector<VocalPhrase>* dest){
    MILO_ASSERT(dest, 0x56);
    dest->clear();
    MILO_ASSERT(dest->size() == 0, 0x59);
    for(std::vector<VocalPhrase>::const_iterator it = src.begin(); it != src.end(); it++){
        dest->push_back(*it);
    }
    MILO_ASSERT(dest->size() == src.size(), 0x62);
}

void VocalNoteList::CopyPhrasesFrom(const VocalNoteList* srcList){
    MILO_ASSERT(srcList, 0x68);
    CopyPhraseVec(srcList->mPhrases, &mPhrases);
}

void VocalNoteList::CopyLyricPhrases(){
    CopyPhraseVec(mPhrases, &mLyricPhrases);
}

// fn_80497850
void VocalNoteList::AddNote(const VocalNote& note){
    MemDoTempAllocations tmp(true, false);
    if(!mNotes.empty() && mNotes.back().GetTick() == note.GetTick()){
        MILO_WARN("%s (%s): double note-on at %s", mSongData->SongFullPath(), mTrackName, PrintTick(note.GetTick()));
    }
    else mNotes.push_back(note);
}

// fn_80497928
void VocalNoteList::NotesDone(const TempoMap& tmap, bool b){
    static bool sDump;
    if(mPhrases.empty()){
        if(!mNotes.empty()){
            MILO_WARN("%s (PART VOCALS): Vocal notes exist, but no vocal phrases found", mSongData->SongFullPath());
        }
    }
    else if(!mNotes.empty()){

        int ticktouse = mPhrases[0].unk8 < mNotes[0].GetTick() ? mPhrases[0].unk8 : mNotes[0].GetTick();
        if(b){
            VocalPhrase phrase;
            phrase.unk8 = 0;
            phrase.unkc = ticktouse;
            if(0x280 < ticktouse) phrase.unkc = ticktouse - 0x280;
            mPhrases.insert(mPhrases.begin(), phrase);
        }
        // init stuff goes here
        int uvar19 = 0;
        if(sDump) MILO_LOG("parsing phrase data\n");
        for(int i = 1; i < mPhrases.size(); i++){
            VocalPhrase& phrase = mPhrases[i];
            phrase.unk18 = 0;
            phrase.unk19 = 0;
            phrase.unk10 = uvar19;
            phrase.unk14 = uvar19;
            for(; uvar19 < mNotes.size(); uvar19++){
                VocalNote& note = mNotes[uvar19];
                if(note.GetTick() < phrase.unk8){
                    if(b){
                        MILO_WARN("%s (%s): vocal note at tick %s is outside any phrases",
                            mSongData->SongFullPath(), mTrackName, PrintTick(note.GetTick()));
                            phrase.unk8 = note.GetTick();
                    }
                    else {
                        MILO_WARN("%s (%s): vocal note [%d-%d] at tick %s is outside any phrases",
                            mSongData->SongFullPath(), mTrackName, note.StartPitch(), note.EndPitch(), PrintTick(note.GetTick()));
                    }
                }
                if(phrase.unk8 + phrase.unkc <= note.GetTick()) break;
                phrase.unk14++;
                if(note.IsUnpitched()) phrase.unk19 = 1;
                if(b && phrase.unk8 + phrase.unkc < note.EndTick()){
                    MILO_WARN("%s (%s): vocal note at tick %s extends beyond phrase", mSongData->SongFullPath(), mTrackName, PrintTick(note.GetTick()));
                }
            }

            if(!phrase.Diff()){
                mNotes[phrase.unk14 - 1].SetPhraseEnd(true);
            }
            if(b) mLyricPhrases.push_back(phrase);
            for(int j = phrase.unk10; j < phrase.unk14; j++){
                if(!mNotes[j].IsUnpitched()){
                    phrase.unk18 = 1;
                    phrase.unk24 = Min<float>(phrase.unk24, mNotes[j].StartPitch());
                    phrase.unk28 = Max<float>(phrase.unk28, mNotes[j].EndPitch());
                }
                if(b){
                    if(mNotes[j].LyricShift()){
                        VocalPhrase& backphrase = mLyricPhrases.back();
                        int endtick = mNotes[j].EndTick();
                        backphrase.unkc = endtick - backphrase.unk8;
                        VocalPhrase newphrase;
                        newphrase.unk8 = endtick;
                        newphrase.unkc = backphrase.unk8 + backphrase.unkc - endtick;
                        mLyricPhrases.push_back(newphrase);
                    }
                }
            }


        //             pfVar6 = (float *)fn_800D3278(&local_124,curphrase + 0x24);
        // local_124 = *pfVar6;
        // pfVar6 = (float *)fn_800D3260(&local_128,curphrase + 0x28);
        // local_128 = *pfVar6;
        // if ((*(char *)(curphrase + 0x1a) != '\0') ||
        //    (uVar11 = std::vector::size(this), uVar16 + 1 == (uint)uVar11)) {
        //   while (uVar15 = uVar15 + 1, (int)uVar15 <= (int)uVar16) {
        //     curphrase = fn_800F23AC(this,uVar15);
        //     *(float *)(curphrase + 0x24) = local_124;
        //     curphrase = fn_800F23AC(this,uVar15);
        //     *(float *)(curphrase + 0x28) = local_128;
        //   }
        //   local_124 = (float)dVar19;
        //   local_128 = (float)dVar20;
        //   uVar15 = uVar16;
        // }

        }

        if(sDump){
            for(int i = 0; i < mPhrases.size(); i++){
                MILO_LOG("[%d] ticks: (%d, %d), min: %.0f max: %.0f bounding: %d\n",
                    i, mPhrases[i].unk8, mPhrases[i].unk8 + mPhrases[i].unkc, mPhrases[i].unk24, mPhrases[i].unk28, mPhrases[i].unk1a);
            }
        }

        if(uvar19 != mNotes.size()){
            MILO_WARN("%s (%s): vocal notes past end of last phrase are being discarded", mSongData->SongFullPath(), mTrackName);
        }

    }
}

void VocalNoteList::AddTambourineGem(int gem){
    mTambourineGems.push_back(gem);
}

void VocalNoteList::SetFreestyleSections(const std::vector<std::pair<float, float> >& sects){
    mFreestyleSections = sects;
}