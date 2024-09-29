#include "bandobj/BandWardrobe.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandDirector.h"
#include "char/CharInterest.h"
#include "obj/Utl.h"
#include "rndobj/TransProxy.h"
#include "rndobj/Wind.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

BandWardrobe* TheBandWardrobe;

const char* FlagString(int flags){
    const char* flagstrs[] = { "FR", "FD", "FB", "FS", "MR", "MD", "MB", "MS", "Required", "Dircut", "Intro",
        "FinaleArena", "FinaleBigClub", "FinaleFestival", "FemaleGenreSplit", "MaleGenreSplit" };
    char* str = (char*)MakeString("                                                                         ");
    const char** ptr = flagstrs;
    char* strptr = str;
    int i5 = 0;
    while(true){
        int i1 = 1 << (i5 & 0x3F);
        if(i1 > 0x8000) break;
        if(flags & i1){
            if(strptr != str){
                strcpy(strptr, *ptr);
                strptr += strlen(*ptr);
            }
        }
        ptr++;
        i5++;
    }
    *strptr = 0;
    return str;
}

const char* gGenres[4] = { "rocker", "dramatic", "banger", "spazz" };

int GetGenreGenderFlags(Symbol s1, Symbol s2){
    int gv = 0;
    for(int i = 0; i < 4; i++){
        if(s1 == gGenres[i]){
            gv = 1 << i;
            break;
        }
    }
    MILO_ASSERT(gv, 0x62);
    return s2 == "female" ? gv : gv << 4;
}

Symbol BandWardrobe::GetCoopMode(BandCamShot* shot){
    const char* modes[] = { "coop_bg", "coop_bk", "coop_gk" };
}

DECOMP_FORCEACTIVE(BandWardrobe, "%s is not valid for any modes",
    "%s: category %s is excluded from all play modes!", "coop_bg")

int BandWardrobe::GetShotFlags(CamShot* shot){
    int flags = 0x100;
    if(shot){
        const char* cat = shot->Category().Str();
        if(strncmp(cat, "directed_", 9) == 0){
            flags |= 0x200;
            DataNode* prop = shot->Property("free_dircuts", false);
            if(prop){
                DataArray* proparr = prop->Array(0);
                for(int i = 0; i < proparr->Size(); i++){
                    if(shot->Category() == proparr->Sym(i)){
                        flags &= ~0x200;
                        break;
                    }
                }
            }
        }
        else {
            if(strstr(cat, "INTRO")) flags |= 0x400;
            else if(strstr(cat, "WIN_FINALE")){
                const char* venuestr = unk78.Str();
                if(strstr(venuestr, "arena")) flags = 0x800;
                else if(strstr(venuestr, "big_club")) flags = 0x1000;
                else if(strstr(venuestr, "festival")) flags = 0x2000;
            }
        }
    }
    if(flags & 0x600){
        int camflags = shot->Flags();
        int u7 = camflags >> 8 & 0xF;
        if(camflags & 2) flags |= u7;
        if(camflags & 1) flags |= u7 << 4;
    }
    else flags |= 0xFF;
    return flags;
}

int BandWardrobe::TargetNames::FindTarget(Symbol s) const {
    if(!s.Null()){
        for(int i = 0; i < 4; i++){
            if(names[i] == s) return i;
        }
    }
    return -1;
}

void BandWardrobe::Init(){ Register(); }

BandWardrobe::BandWardrobe() : unk8(0), unk14(0), unk20(this, 0), mCurNames(&unk54), mVenueDir(0), mGenre(gGenres[0]), mTempo("medium"), unk90(this, 0), mShotSetPlayMode(1), mPlayShot5(0), mDemandLoad("") {
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

void BandWardrobe::SetDir(ObjectDir* dir){
    for(int i = 0; i < 4; i++) mTargets[i]->SetShowing(true);
    mVenueDir = dir;
    RndWind* worldwind = GetCharacter(0)->Find<RndWind>("world.wind", true);
    if(worldwind){
        RndWind* wind = dir->Find<RndWind>("Wind.wind", false);
        if(wind) worldwind->SetWindOwner(wind);
        else {
            worldwind->SetWindOwner(worldwind);
            worldwind->Zero();
        }
    }
    SyncInterestObjects();
    for(int i = 0; i < 4; i++){
        BandCharacter* bc = mTargets[i];
        if(bc){
            bc->SetFocusInterest(0, 0);
            bc->EnableBlinks(true, false);
        }
    }
    SyncTransProxies();
}

void BandWardrobe::SetVenueDir(ObjectDir* dir){
    static const char* genders[2] = { "male", "female" };
    mCurNames = &unk54;
    SetDir(dir);
    SyncPlayMode();
    SetContexts("venue");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            Character* thechar = dir->Find<Character>(MakeString("crowd_%s%02d", genders[j], i + 1), false);
            if(thechar){
                ObjectDir* gendir = thechar->Find<ObjectDir>(MakeString("%s_base", genders[j]), true);
                thechar->GetDriver()->SetClips(gendir);
            }
        }
    }
}

DataArray* BandWardrobe::GetRemap(Symbol s){
    static DataArray* arr = SystemConfig("objects", "BandWardrobe");
    return arr->FindArray(MakeString("%s_remap", s), true);
}

DataArray* BandWardrobe::GetGroupArray(BandCharDesc::CharInstrumentType ty){
    if(ty == BandCharDesc::kNumInstruments){
        MILO_WARN("Trying to get group array for no instrument");
    }
    static DataArray* arr = SystemConfig("objects", "BandWardrobe", "anim_groups");
    return arr->Array(ty + 1);
}

void BandWardrobe::StartVenueShot(BandCamShot* shot){
    if(!TheBandDirector){
        Symbol coopmode = GetCoopMode(shot);
        if(mShotSetPlayMode) SetPlayMode(coopmode, shot);
        else if(coopmode != GetPlayMode()){
            MILO_WARN("%s is not a valid camera for current play mode %s", shot->Name(), GetPlayMode());
        }
    }
    for(int i = 0; i < 4; i++){
        BandCharacter* bc = mTargets[i];
        if(bc){
            bc->unk5a3 = true;
            bc->unk5a2 = true;
        }
    }
}

Symbol BandWardrobe::GetPlayMode(){
    static DataNode& pm = DataVariable("band.play_mode");
    return pm.Sym(0);
}

void BandWardrobe::SetSongInfo(Symbol s1, Symbol s2){
    mTempo = s1;
    mVocalGender = s2;
}

void BandWardrobe::SetSongAnimGenre(Symbol s){
    mGenre = s;
}

void BandWardrobe::SetPlayMode(Symbol s, BandCamShot* shot){
    static DataNode& pm = DataVariable("band.play_mode");
    pm = DataNode(s);
    bool b1 = false;
    if(TheLoadMgr.EditMode() || !TheBandDirector || !mDemandLoad.Null()){
        b1 = true;
    }
    if(b1 && !unk78.Null()){
        LoadMainCharacters(shot);
        SetContexts("venue");
        SyncTransProxies();
        SyncPlayMode();
        if(TheBandDirector && !shot) TheBandDirector->HarvestDircuts();
    }
}

void BandWardrobe::SyncPlayMode(){
    if(unk90) unk90->Handle(sync_play_mode_msg, true);
}

void BandWardrobe::SyncInterestObjects(){
    ObjPtrList<CharInterest, ObjectDir> clist(this, kObjListNoNull);
    for(ObjDirItr<CharInterest> it(mVenueDir, true); it; ++it){
        clist.push_back(it);
    }
    for(int i = 0; i < 4; i++){
        BandCharacter* bc = mTargets[i];
        if(bc) bc->SetInterestObjects(clist, 0);
    }
}

void BandWardrobe::SyncTransProxies(){
    for(ObjDirItr<RndTransProxy> it(mVenueDir, true); it != 0; ++it){
        const char* thisname = it->Name();
        for(int i = 0; i < 4; i++){
            const char* name = mCurNames->names[i].Str();
            if(*name){
                const char* str = strstr(thisname, name);
                if(str){
                    it->SetProxy(mTargets[i]);
                    break;
                }
            }
        }
    }
}

bool BandWardrobe::AllCharsLoaded(){
    for(int i = 0; i < 4; i++){
        BandCharacter* bc = mTargets[i];
        if(bc && bc->IsLoading()) return false;
    }
    return true;
}

bool BandWardrobe::DircutRecurse(BandCamShot* shot, int i){
    for(ObjVector<BandCamShot::Target>::iterator it = shot->mTargets.begin(); it != shot->mTargets.end(); ++it){
        if(!it->mAnimGroup.Null()){
            BandCharacter* bc = FindTarget(it->mTarget, unk54);
            if(bc){
                if(!AddDircut(bc, shot, it->mAnimGroup, i)) return false;
            }
        }
    }
    for(ObjPtrList<BandCamShot, ObjectDir>::iterator it = shot->mNextShots.begin(); it != shot->mNextShots.end(); ++it){
        if(!DircutRecurse(*it, i)) return false;
    }
    return true;
}

void BandWardrobe::ClearDircuts(){
    for(int i = 0; i < 4; i++) mTargets[i]->ClearDircuts();
}

bool BandWardrobe::AddDircut(BandCamShot* shot){
    if(shot) return DircutRecurse(shot, GetShotFlags(shot));
    else return true;
}

void BandWardrobe::SendMessage(Symbol s1, Symbol s2, bool b){
    static Message msg("");
    if(s1 == "mic") s1 = "vocal";
    for(int i = 0; i < 4; i++){
        if(strstr(unk54.names[i].Str(), s1.Str())){
            msg.SetType(s2);
            if(b) mTargets[i]->HandleType(msg);
            else mTargets[i]->Handle(msg, true);
        }
    }
}

const int gInstFocus[] = { 0x20000, 0x8000, 0x10000, 0x40000, 0x80000 };

bool BandWardrobe::ValidGenreGender(CamShot* shot){
    int flags = shot->Flags();
    if((flags & 0xF03) == 0xF03) return true;
    else {
        if(!IsPowerOf2(flags & 0xF8000)){
            MILO_FAIL("%s has bad focus flags", PathName(shot));
        }
        int instnum;
        for(instnum = 0; instnum < 4; instnum++){
            if(flags & gInstFocus[instnum]) break;
        }
        Symbol instsym = BandCharDesc::GetInstrumentSym(instnum);
        if(instsym == "mic") instsym = "vocals";
        instsym = MakeString("player_%s0", instsym);
        int shotflags = GetShotFlags(shot);
        int genderflags = 0;
        BandCharacter* bc = FindTarget(instsym, unk54);
        if(bc) genderflags = GetGenreGenderFlags(mGenre, bc->mGender);
        return (shotflags & genderflags) & 0xFF;
    }
}

BandCharacter* BandWardrobe::FindTarget(Symbol s, const TargetNames& names){
    int idx = names.FindTarget(s);
    if(idx != -1) return mTargets[idx];
    else return 0;
}

BandCharacter* BandWardrobe::FindTarget(Symbol s){
    MILO_ASSERT(mCurNames, 0x3E2);
    return FindTarget(s, *mCurNames);
}

void BandWardrobe::LoadCharacters(Symbol s, bool b){
    unk78 = s;
    unk7c = b;
    LoadMainCharacters(0);
}

int InstrumentIndex(std::vector<Symbol>& syms, Symbol s){
    int idx = 0;
    for(; idx < syms.size(); idx++){
        if(syms[idx] == s) break;
    }
    return idx;
}

SAVE_OBJ(BandWardrobe, 0x6D3)

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