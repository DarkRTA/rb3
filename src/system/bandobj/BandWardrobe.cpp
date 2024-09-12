#include "bandobj/BandWardrobe.h"
#include "bandobj/BandCharDesc.h"
#include "obj/Utl.h"
#include "utl/Symbols.h"

BandWardrobe* TheBandWardrobe;
const char* gGenres[4] = { "rocker", "dramatic", "banger", "spazz" };

BandWardrobe::BandWardrobe() : unk8(0), unk14(0), unk20(this, 0), unk64(&unk54), mVenueDir(0), mGenre(gGenres[0]), mTempo("medium"), unk90(this, 0), mShotSetPlayMode(1), mPlayShot5(0), mDemandLoad("") {
    static DataNode& bandwardrobe = DataVariable("bandwardrobe");
    if(TheBandWardrobe) MILO_WARN("Trying to make > 1 BandWardrobe, which should be single");
    bandwardrobe = DataNode(this);
    TheBandWardrobe = this;
}

BandWardrobe::~BandWardrobe(){
    if(TheBandWardrobe == this){
        static DataNode& bandwardrobe = DataVariable("bandwardrobe");
        bandwardrobe = DataNode((Hmx::Object*)0);
        TheBandWardrobe = 0;
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandWardrobe)
    HANDLE(find_target, OnFindTarget)
    HANDLE_ACTION(start_venue_shot, StartVenueShot(_msg->Obj<BandCamShot>(2)))
    HANDLE(enter_venue, OnEnterVenue)
    HANDLE(unload_venue, OnUnloadVenue)
    HANDLE(enter_closet, OnEnterCloset)
    HANDLE(enter_vignette, OnEnterVignette)
    HANDLE(select_extras, OnSelectExtras)
    HANDLE(on_extra_loaded, OnExtraLoaded)
    HANDLE_EXPR(chars_dir, Dir())
    HANDLE_EXPR(get_character, GetCharacter(_msg->Int(2)))
    HANDLE(list_venue_anim_groups, OnListVenueAnimGroups)
    HANDLE(sort_targets, OnSortTargets)
    if(sym == prefabs_list) return ObjectList(BandCharDesc::GetPrefabs(), "BandCharDesc", true);
    HANDLE(get_matching_dude, OnGetMatchingDude)
    HANDLE(list_interest_objects, OnGetCurrentInterests)
    HANDLE(enable_debug_interests, OnEnableDebugInterests)
    HANDLE_ACTION(load_prefab_prefs, LoadPrefabPrefs())
    HANDLE_ACTION(sync_interests, SyncInterestObjects())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x73A)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(BandWardrobe)
    SYNC_PROP(genre, mGenre)
    SYNC_PROP(tempo, mTempo)
    SYNC_PROP(vocal_gender, mVocalGender)
    SYNC_PROP_SET(play_mode, GetPlayMode(), SetPlayMode(_val.Sym(0), 0))
    SYNC_PROP(shot_set_play_mode, mShotSetPlayMode)
    SYNC_PROP(play_shot_5, mPlayShot5)
    SYNC_PROP_MODIFY(player0_forced_focus, mPlayerForcedFocuses[0], SyncVignetteInterest(0))
    SYNC_PROP_MODIFY(player1_forced_focus, mPlayerForcedFocuses[1], SyncVignetteInterest(1))
    SYNC_PROP_MODIFY(player2_forced_focus, mPlayerForcedFocuses[2], SyncVignetteInterest(2))
    SYNC_PROP_MODIFY(player3_forced_focus, mPlayerForcedFocuses[3], SyncVignetteInterest(3))
    SYNC_PROP_MODIFY(player0_enable_blinks, mPlayerEnableBlinks[0], SyncEnableBlinks(0))
    SYNC_PROP_MODIFY(player1_enable_blinks, mPlayerEnableBlinks[1], SyncEnableBlinks(1))
    SYNC_PROP_MODIFY(player2_enable_blinks, mPlayerEnableBlinks[2], SyncEnableBlinks(2))
    SYNC_PROP_MODIFY(player3_enable_blinks, mPlayerEnableBlinks[3], SyncEnableBlinks(3))
    SYNC_PROP_SET(player0_force_blink, 0, if(_val.Int(0)) ForceBlink(0))
    SYNC_PROP_SET(player1_force_blink, 0, if(_val.Int(0)) ForceBlink(1))
    SYNC_PROP_SET(player2_force_blink, 0, if(_val.Int(0)) ForceBlink(2))
    SYNC_PROP_SET(player3_force_blink, 0, if(_val.Int(0)) ForceBlink(3))
    SYNC_PROP(demand_load, mDemandLoad)
    SYNC_PROP(dir, mVenueDir)
END_PROPSYNCS