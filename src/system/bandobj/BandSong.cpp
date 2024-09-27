#include "bandobj/BandSong.h"
#include "meta/DataArraySongInfo.h"
#include "beatmatch/SongData.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "obj/DataUtl.h"

void BandSong::CreateSong(Symbol s, DataArray* arr, HxSongData** songdata, HxMaster** hxmaster){
    SongData* sdata = new SongData();
    *songdata = sdata;
    DataMacroWarning(false);
    BeatMaster* bmaster = new BeatMaster(sdata, 1);
    *hxmaster = bmaster;
    DataMacroWarning(true);
    std::vector<MidiReceiver*> mreceivers;
    mreceivers.push_back(this);
    PlayerTrackConfigList plist(0);
    DataArraySongInfo info(arr, 0, s);
    bmaster->Load((SongInfo*)&info, 4, &plist, true, kSongData_NoValidation, &mreceivers);
}

DECOMP_FORCEFUNC(BandSong, BandSong, ClassName)
DECOMP_FORCEFUNC(BandSong, BandSong, SetType)