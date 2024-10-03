#include "bandobj/BandWardrobe.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandDirector.h"
#include "char/CharInterest.h"
#include "obj/DataUtl.h"
#include "obj/Utl.h"
#include "rndobj/TransProxy.h"
#include "rndobj/Wind.h"
#include <algorithm>
#include "utl/Symbols.h"
#include "utl/Messages.h"

BandWardrobe* TheBandWardrobe;

INIT_REVS(BandWardrobe);

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

BandWardrobe::BandWardrobe() : unk8(0), unk14(0), unk20(this, 0), mCurNames(&mVenueNames), mVenueDir(0), mGenre(gGenres[0]), mTempo("medium"), mModeSink(this, 0), mShotSetPlayMode(1), mPlayShot5(0), mDemandLoad("") {
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
    mCurNames = &mVenueNames;
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
    if(mModeSink) mModeSink->Handle(sync_play_mode_msg, true);
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
            BandCharacter* bc = FindTarget(it->mTarget, mVenueNames);
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
        if(strstr(mVenueNames.names[i].Str(), s1.Str())){
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
        if(!PowerOf2(flags & 0xF8000)){
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
        BandCharacter* bc = FindTarget(instsym, mVenueNames);
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

DECOMP_FORCEACTIVE(BandWardrobe, "0")

int BandWardrobe::GetInstrumentForTarget(Symbol mode, int i){
    if(mode == "coop_bk"){
        int arr[4] = { 1, 2, 3, 4 };
        return arr[i];
    }
    else if(mode == "coop_gk"){
        int arr[4] = { 0, 2, 3, 4 };
        return arr[i];
    }
    else {
        MILO_ASSERT(mode == "coop_bg", 0x420);
        int arr[4] = { 1, 2, 3, 0 };
        return arr[i];
    }
}

void BandWardrobe::LoadCharacters(Symbol s, bool b){
    unk78 = s;
    unk7c = b;
    LoadMainCharacters(0);
}

int InstrumentIndex(std::vector<Symbol>& syms, Symbol s){
    int idx = 0;
    for(; idx < syms.size(); idx++){
        if(s == syms[idx]) break;
    }
    return idx;
}

Symbol GrabInstrument(std::vector<Symbol>& syms, Symbol s){
    int idx = InstrumentIndex(syms, s);
    if(idx == syms.size()) idx = 0;
    s = syms[idx];
    syms.erase(syms.begin() + idx);
    return s;
}

const char* PrefabSuffix(char* c){
    const char* names[2] = { "_male", "_female" };
}

DataNode BandWardrobe::GetUserTrack(int i){
    static Message msg("get_user_track", DataNode(0));
    msg[0] = DataNode(i);
    return HandleType(msg);
}

// TODO: remove this once LoadMainCharacters is fully matched
DECOMP_FORCEACTIVE(BandWardrobe, "DemandLoad() || !shot", "PowerOf2(ff)", "male", "pc", "xbox", "%s_budget_%s", "could not find fallback prefab",
    "none", "guitar", "bass", "drum", "keyboard",
    "j != DIM(instOrder)", "NOTIFY: %s (%s) has no %s\n", "kelly02_triburst", "mb4_triburst", "generic_zebra", "e935_resource", "m50_resource", "hey, we shouldn't be here")

void BandWardrobe::LoadMainCharacters(BandCamShot* shot){
    MILO_ASSERT(DemandLoad() || !shot, 0x45C);
    HandleType(on_loading_characters_msg);
    Symbol playmode = GetPlayMode();
    Symbol gender = female;
    if(shot){
        int shotflags = GetShotFlags(shot);
        if((shotflags & 0xFF) != 0xFF){
            int flags = shot->Flags();
            int ff = flags & 0xF8000;
            MILO_ASSERT(PowerOf2(ff), 0x479);
            for(int i = 0; i < 5; i++){
                if(ff == gInstFocus[i]){
                    if(shotflags & 0xF0){
                        gender = "male";
                    }
                    break;
                }
            }
            flags = shotflags >> 4;
            if(shotflags & 0xF) flags = shotflags;

            for(int i = 0; i < 4; i++){
                if(flags & 1 << i){
                    mGenre = gGenres[i];
                    break;
                }
            }
        }
    }
    std::vector<Symbol> syms(4);
    for(int i = 0; i < 4; i++){
        syms[i] = BandCharDesc::GetInstrumentSym(GetInstrumentForTarget(playmode, i));
    }
    int iarr[4];
    int count = 0;
    for(int i = 0; i < 4; i++){
        DataNode tracknode = GetUserTrack(i);
        Symbol inst = "none";
        if(tracknode.Type() != kDataUnhandled){
            int instidx = InstrumentIndex(syms, tracknode.Sym(0));
            if(instidx != syms.size()){
                inst = GrabInstrument(syms, tracknode.Sym(0));
                goto lol;
            }
            iarr[i] = i;
            count++;
        }
        else {
lol:
            mTargets[i]->SetInstrumentType(inst);
        }
    }
    for(int i = 0; i < count; i++){
        int i15 = iarr[i];
        Symbol instsyms[5] = { "guitar", "bass", "mic", "drum", "keyboard" };
        int instidx = 0;
        for(; instidx < 5; instidx++){
            if(InstrumentIndex(syms, instsyms[instidx]) != syms.size()) break;
        }
        mTargets[i15]->SetInstrumentType(GrabInstrument(syms, instsyms[instidx]));
    }
    if(InstrumentIndex(syms, mic) != syms.size()){

    }
}

void BandWardrobe::StartClipLoads(bool b, BandCamShot* shot){
    if(shot){
        ClearDircuts();
        AddDircut(shot);
        b = true;
    }
    for(int i = 0; i < 4; i++){
        if(b) mTargets[i]->SetTempoGenreVenue(mTempo, mGenre, unk78.Str());
        else mTargets[i]->SetTempoGenreVenue(Symbol(), Symbol(), unk78.Str());
        DataArray* mac = DataGetMacro("HX_SYSTEST");
        if(!mac && TheBandDirector->IsMusicVideo()){
            BandCharDesc* desc = Hmx::Object::New<BandCharDesc>();
            desc->mHead.mHide = true;
            mTargets[i]->CopyCharDesc(desc);
            delete desc;
            b = false;
        }
        else mTargets[i]->StartLoad(unk7c, mTargets[i]->mInCloset, false);
    }
    FileMerger* merger = Dir()->Find<FileMerger>("crowd_clips.fm", false);
    if(merger){
        static Message msg("load_tempo", DataNode(0), DataNode(0), DataNode(0));
        msg[0] = DataNode(b ? mTempo : Symbol());
        msg[1] = DataNode(unk7c);
        merger->HandleType(msg);
    }
}

void BandWardrobe::SetContexts(Symbol s){
    for(int i = 0; i < 4; i++){
        mTargets[i]->SetContext(s);
    }
}

#define kNumTargets 4

BandCharacter* BandWardrobe::GetCharacter(int which) const {
    MILO_ASSERT(which >= 0 && which < kNumTargets, 0x5AC);
    return mTargets[which];
}

DECOMP_FORCEACTIVE(BandWardrobe, "Bandcharacter is not target")

bool BandWardrobe::AddDircut(BandCharacter* bchar, BandCamShot*, Symbol, int){
    if(!bchar) MILO_FAIL("BandWardrobe::AddDircut character is NULL");
    MakeString("%s could not find directed cut group %s for inst %s");
    MakeString("%s intro camera looking for non-intro anim group");
    MakeString("%s can't load %s, group is %s, character is %s");
}

void BandWardrobe::SelectExtra(FileMerger::Merger& merger){
    FilePathTracker tracker(FileRoot());
    ObjectDir* dir = merger.mDir;
    if(!dir) return;
    else {
        DataNode node = dir->PropertyArray("proxies");
        DataArray* proparr = node.Array(0);
        for(std::list<Symbol>::iterator it = unk2c.begin(); it != unk2c.end(); ++it){
            Symbol cur = *it;
            for(int i = 0; i < proparr->Size(); i++){
                if(cur == proparr->Sym(i)){
                    unk2c.insert(it, *it);
                    FilePath fp(MakeString("char/extras/%s.milo", cur));
                }
            }
        }
        MILO_FAIL("Couldn't find match!");
    }
}

void BandWardrobe::LoadPrefabPrefs(){
    if(TheLoadMgr.EditMode()){
        for(int i = 0; i < 4; i++){
            BandCharDesc* desc = 0;
            for(int j = 0; j < 2 && !desc; j++){
                desc = GetPrefab(i, j);
            }
            if(desc){
                BandCharacter* bchar = mTargets[i];
                bchar->SetInstrumentType(bchar->mInstrumentType);
                if(bchar->SetPrefab(desc)){
                    bchar->StartLoad(false, false, false);
                }
            }
        }
    }
}

BandCharDesc* BandWardrobe::GetPrefab(int target, int variation){
    MILO_ASSERT(target < kNumTargets && target >= 0, 0x6AF);
    MILO_ASSERT(variation < 2 && target >= 0, 0x6B0);
    if(!mDemandLoad.Null()){
        char buf[256];
        const char* platstr = PlatformSymbol(TheLoadMgr.GetPlatform()).Str();
        Symbol platsym = streq(platstr, "pc") ? "xbox" : platstr;
        strcpy(buf, MakeString("%s_%s", mDemandLoad, platsym));
        if(variation == 1){
            char* suffix = (char*)PrefabSuffix(buf);
            strcpy(suffix + 1, strstr(suffix, "female") ? "male" : "female");
        }
        return BandCharDesc::FindPrefab(buf, false);
    }
    else {
        Symbol prefabsym = MakeString("milopref_prefab%d_%c", target, variation + 'a');
        Symbol findsym = DataVarExists(prefabsym) ? DataVariable(prefabsym).Sym(0) : Symbol();
        if(!findsym.Null()) return BandCharDesc::FindPrefab(findsym.Str(), false);
        else return 0;
    }
}

SAVE_OBJ(BandWardrobe, 0x6D3)

BEGIN_LOADS(BandWardrobe)
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev != 0){
        Symbol s;
        bs >> mGenre;
        bs >> mTempo;
        if(gRev > 4) bs >> mVocalGender;
        bs >> s;
        bs >> mShotSetPlayMode;
        bs >> mPlayShot5;
        if(gRev == 2 || gRev == 3){
            Symbol s2; bs >> s2;
            if(gRev > 2){
                bs >> s2;
                bs >> s2;
                bs >> s2;
            }
        }
        SetPlayMode(s, 0);
    }
    if(Dir()){
        for(int i = 0; i < 4; i++){
            mTargets[i] = Dir()->Find<BandCharacter>(MakeString("player%d", i), false);
        }
    }
END_LOADS

BEGIN_COPYS(BandWardrobe)
    COPY_SUPERCLASS(Hmx::Object)
END_COPYS

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

DataNode BandWardrobe::OnFindTarget(DataArray* da){
    if(TheLoadMgr.EditMode() && da->Size() > 3){
        StartVenueShot(da->Obj<BandCamShot>(3));
    }
    return DataNode(FindTarget(da->Sym(2), *mCurNames));
}

DataNode BandWardrobe::OnEnterVenue(DataArray* da){
    MILO_ASSERT(!TheBandDirector, 0x750);
    ObjectDir* dir = da->Obj<ObjectDir>(2);
    MILO_ASSERT(dir, 0x752);
    LoadCharacters(dir->Name(), false);
    SetVenueDir(dir);
    return DataNode(0);
}

DataNode BandWardrobe::OnUnloadVenue(DataArray* da){
    for(int i = 0; i < 4; i++){
        BandCharacter* bc = GetCharacter(i);
        if(bc){
            bc->ClearDircuts();
            bc->SetTempoGenreVenue(Symbol(), Symbol(), "");
            bc->SetInstrumentType(Symbol());
            bc->StartLoad(false, bc->mInCloset, true);
        }
    }
    return DataNode(0);
}

DataNode BandWardrobe::OnGetCurrentInterests(DataArray* da){
    int playerIdx = da->Int(2);
    MILO_ASSERT(playerIdx < kNumTargets, 0x772);
    if(mTargets[playerIdx]) return mTargets[playerIdx]->OnGetCurrentInterests(0);
    else {
        DataArray* arr = new DataArray(1);
        arr->Node(0) = DataNode(Symbol());
        DataNode ret(arr, kDataArray);
        arr->Release();
        return DataNode(ret);
    }
}

DataNode BandWardrobe::OnEnableDebugInterests(DataArray* da){
    int playerIdx = da->Int(2);
    bool i3 = da->Int(3);
    MILO_ASSERT(playerIdx < kNumTargets, 0x785);
    if(mTargets[playerIdx]){
        mTargets[playerIdx]->SetDebugDrawInterestObjects(i3);
    }
    return DataNode(0);
}

DataNode BandWardrobe::OnEnterCloset(DataArray* da){
    ObjectDir* dir = da->Obj<ObjectDir>(2);
    MILO_ASSERT(dir, 0x795);
    if(dir){
        int i3 = da->Int(3);
        if(i3 != -1){
            mCurNames = &mClosetNames;
            SetContexts("closet");
            CharDriver* driver = mTargets[i3]->GetDriver();
            if(driver){
                driver->SetClips(dir->Find<ObjectDir>("clips", false));
                for(int i = 0; i < 4; i++){
                    mClosetNames.names[i] = i == i3 ? "closet_character" : "";
                }
                SetDir(dir);
                for(int i = 0; i < 4; i++){
                    mTargets[i]->SetShowing(i == i3);
                }
            }
        }
    }
    return DataNode(0);
}

void BandWardrobe::SyncVignetteInterest(int playerIdx){
    MILO_ASSERT(playerIdx < kNumTargets, 0x876);
    BandCharacter* bc = FindTarget(mCurNames->names[playerIdx], *mCurNames);
    if(bc){
        bc->Character::SetFocusInterest(mPlayerForcedFocuses[playerIdx], 0);
    }
}

void BandWardrobe::SyncEnableBlinks(int playerIdx){
    MILO_ASSERT(playerIdx < kNumTargets, 0x883);
    BandCharacter* bc = FindTarget(mCurNames->names[playerIdx], *mCurNames);
    if(bc){
        bc->EnableBlinks(mPlayerEnableBlinks[playerIdx], false);
    }
}

void BandWardrobe::ForceBlink(int playerIdx){
    MILO_ASSERT(playerIdx < kNumTargets, 0x891);
    BandCharacter* bc = FindTarget(mCurNames->names[playerIdx], *mCurNames);
    if(bc){
        bc->ForceBlink();
    }
}

DataNode BandWardrobe::OnListVenueAnimGroups(DataArray* da){
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x947);
    BandCamShot* shot = da->Obj<BandCamShot>(3);
    StartVenueShot(shot);
    Symbol sym = da->Sym(2);
    BandCharacter* bchar = FindTarget(sym, mVenueNames);
    if(bchar){
        return bchar->ListAnimGroups(GetShotFlags(shot));      
    }
    else {
        Character* chr = mVenueDir->Find<Character>(sym.Str(), false);
        if(chr) return DataNode(0);
        else {
            DataArray* arr = new DataArray(1);
            arr->Node(0) = DataNode(Symbol());
            DataNode ret(arr, kDataArray);
            arr->Release();
            return DataNode(ret);
        }
    }
}

DataNode BandWardrobe::OnExtraLoaded(DataArray* da){
    Character* c1 = da->Obj<Character>(2);
    Character* c2 = da->Obj<Character>(3);
    if(c1 && c2){
        c2->CopyBoundingSphere(c1);
        c2->SetShowing(false);
    }
    return DataNode(0);
}

#pragma push
#pragma dont_inline on
DataNode BandWardrobe::OnSelectExtras(DataArray* da){
    FileMerger* merger = da->Obj<FileMerger>(2);
    if(unk20 != merger){
        ObjectDir* mergerdir = merger->Dir();
        merger->Clear();
        merger->Mergers().clear();
        unk20 = merger;
        unk2c.clear();
        for(ObjectDir::Entry* e = mergerdir->HashTable().Begin(); e != 0; e = mergerdir->HashTable().Next(e)){
            Hmx::Object* o = e->obj;
            if(o->Type() == extras && o->ClassName() == "Character"){
                FileMerger::Merger m(unk20);
                m.mName = o->Name();
                m.mDir = dynamic_cast<ObjectDir*>(o);
                m.mSubdirs = 3;
                unk20->Mergers().push_back(m);
                DataNode propnode = o->PropertyArray(proxies);
                DataArray* proparr = propnode.Array(0);
                for(int i = 0; i < proparr->Size(); i++){
                    unk2c.push_back(proparr->Sym(i));
                }
            }
        }
        unk2c.sort();
        unk2c.unique();
        int size = unk2c.size();
        for(std::list<Symbol>::iterator it = unk2c.begin(); it != unk2c.end(); ++it){
            int rint = RandomInt(0, size--);
            std::list<Symbol>::iterator cur = it;
            while(rint-- != 0) ++cur;
            std::swap<Symbol>(*cur, *it);
        }
    }
    for(int i = 0; i < merger->Mergers().size(); i++){
        SelectExtra(merger->Mergers()[i]);
    }
    std::sort(merger->Mergers().begin(), merger->Mergers().end(), FileMerger::Merger::SortBySelected());
    return DataNode(0);
}
#pragma pop

int NodeCmp(const void* a, const void* b){
    DataNode* na = (DataNode*)a;
    DataNode* nb = (DataNode*)b;
    const char* stra = na->Str(0);
    const char* strb = nb->Str(0);
    const char* strstra = strstr(stra, ".tp");
    const char* strstrb = strstr(strb, ".tp");
    if((strstra != 0) == (strstrb != 0)){
        return stricmp(stra, strb);
    }
    else return strstra != 0 ? -1 : 1;
}

DataNode BandWardrobe::OnSortTargets(DataArray* da){
    DataArray* arr = da->Array(2);
    qsort(arr->mNodes, arr->Size(), 8, NodeCmp);
    return DataNode(0);
}

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