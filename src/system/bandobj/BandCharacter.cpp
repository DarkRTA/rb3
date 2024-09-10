#include "bandobj/BandCharacter.h"
#include "utl/Symbols.h"

INIT_REVS(BandCharacter)

const char* BandIntensityString(int num){
    if(num != 0){
        int intensity = num & 0x7F000;
        switch(intensity){
            case 0x1000: return "realtime_idle";
            case 0x2000: return "idle";
            case 0x4000: return "idle_intense";
            case 0x8000: return "play_mellow";
            case 0x10000: return "play_normal";
            case 0x20000: return "play_intense";
            case 0x40000: return "play_solo";
            default:
                MILO_FAIL("Bad intensity %d!", intensity);
                break;
        }
    }
    return "";
}

void BandCharacter::Init(){ Register(); }
void BandCharacter::Terminate(){}

BandCharacter::BandCharacter() : unk450(0), unk454(this, 0), unk460(0), unk464(0), unk528(0), mForceVertical(1), unk52c(this, 0), unk538(this, 0), mTempo("medium"), unk548(0),
    unk550(this, 0), unk55c(this, 0), unk568(this, 0), unk574(0), mTestPrefab(this, 0), mGenre("rocker"), mDrumVenue("small_club"), mTestTourEndingVenue(0), mInstrumentType("none"), unk594(this, 0),
    mInCloset(0), unk5a1(0), unk5a2(0), unk5a3(0), unk5a4(this, 0), unk5b0(this, kObjListNoNull), unk5c0(this, kObjListNoNull), unk5d0(this, kObjListNoNull),
    unk5e0(this, kObjListNoNull), unk5f0(this, kObjListNoNull), unk600(this, kObjListNoNull), unk610(this, kObjListNoNull), unk620(this, kObjListNoNull),
    unk630(this, kObjListNoNull), unk640(this, kObjListNoNull), unk650(this, kObjListNoNull), unk660(this, kObjListNoNull), unk670(this, kObjListNoNull),
    unk680(this, 0), unk68c(this, 0), unk698(this, 0), unk6a4(this, 0), unk6b0(this, 0), mUseMicStandClips(0), unk6bd(1), unk6c0(this, 0), mInTourEnding(0), unk6d8(0), unk6ec(0),
    unk738(0), unk73c(this, kObjListNoNull), unk74c(this, kObjListNoNull) {
    mGroupName[0] = 0;
    unk4e8[0] = 0;
    unk4a8[0] = 0;
    unk54c = RndOverlay::Find("char_status", true);
    unk734 = Hmx::Object::New<Waypoint>();
    unk734->SetRadius(2.0f);
    unk734->SetStrictRadiusDelta(5.0f);
    unk734->SetAngRadius(0.17453292f);
    unk734->SetStrictAngDelta(0.2617994f);
}

#pragma push
#pragma dont_inline on
BandCharacter::~BandCharacter(){
    TheRnd->CompressTextureCancel(this);
    delete unk734;
}
#pragma pop

void BandCharacter::AddedObject(Hmx::Object* o){
    Character::AddedObject(o);
    if(streq(o->Name(), "main_add.drv")) unk460 = dynamic_cast<CharDriver*>(o);
    if(streq(o->Name(), "expression.drv")) unk464 = dynamic_cast<CharDriver*>(o);
    else if(streq(o->Name(), "head.lookat")) unk550 = dynamic_cast<CharLookAt*>(o);
    else if(streq(o->Name(), "neck.lookat")) unk55c = dynamic_cast<CharLookAt*>(o);
    else if(streq(o->Name(), "FileMerger.fm")) unk548 = dynamic_cast<FileMerger*>(o);
    else if(streq(o->Name(), "outfit")) unk52c = dynamic_cast<Character*>(o);
    else if(streq(o->Name(), "instrument")) unk538 = dynamic_cast<Character*>(o);
    else if(streq(o->Name(), "CharEyes.eyes")) unk568 = dynamic_cast<CharEyes*>(o);
    else if(streq(o->Name(), "singalong.weight")) unk5a4 = dynamic_cast<CharWeightSetter*>(o);
    else AddObject(o);
}

void BandCharacter::RemovingObject(Hmx::Object* o){
    Character::RemovingObject(o);
    if(o == unk460) unk460 = 0;
    else if(o == unk548) unk548 = 0;
}

SAVE_OBJ(BandCharacter, 0x3EB)

BEGIN_LOADS(BandCharacter)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandCharacter::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(8, 0);
    Character::PreLoad(bs);
    int hashsize = (mHashTable.mNumEntries + 20) * 2;
    int strsize = mStringTable.UsedSize();
    Reserve(hashsize, strsize + 440);
}

void BandCharacter::PostLoad(BinStream& bs){
    Character::PostLoad(bs);
    if(gLoadingProxyFromDisk){
        BandCharDescTest test;
        test.Load(bs);
    }
    else BandCharDesc::Load(bs);
}

#pragma push
#pragma pool_data off
#pragma dont_inline on
void BandCharacter::AddObject(Hmx::Object* o){
    static Symbol ikScale("CharIKScale");
    static Symbol ikHand("CharIKHand");
    static Symbol collide("CharCollide");
    static Symbol charCuff("CharCuff");
    static Symbol charHair("CharHair");
    static Symbol meshDeform("MeshDeform");
    static Symbol charBoneOffset("CharBoneOffset");
    static Symbol outfitConfig("OutfitConfig");
    static Symbol charMeshHide("CharMeshHide");
    static Symbol ikMidi("CharIKMidi");
    static Symbol cdMidi("CharDriverMidi");
    static Symbol khMidi("CharKeyHandMidi");
    Symbol name = o->ClassName();
    if(name == ikScale) unk5c0.push_back(dynamic_cast<CharIKScale*>(o));
    else if(name == ikHand) unk5d0.push_back(dynamic_cast<CharIKHand*>(o));
    else if(name == collide) unk5e0.push_back(dynamic_cast<CharCollide*>(o));
    else if(name == charHair){
        CharHair* h = dynamic_cast<CharHair*>(o);
        h->SetManagedHookup(true);
        unk5f0.push_back(h);
    }
    else if(name == charCuff) unk600.push_back(dynamic_cast<CharCuff*>(o));
    else if(name == meshDeform){
        RndMeshDeform* md = dynamic_cast<RndMeshDeform*>(o);
        if(!md->Mesh()) MILO_FAIL("RndMeshDeform(%s) has no deform mesh.", md->Name());
        unk610.push_back(md);
    }
    else if(name == outfitConfig){
        OutfitConfig* cfg = dynamic_cast<OutfitConfig*>(o);
        unk738 |= cfg->OverlayFlags();
        unk620.push_back(cfg);
    }
    else if(name == charBoneOffset) unk640.push_back(dynamic_cast<CharBoneOffset*>(o));
    else if(name == charMeshHide) unk5b0.push_back(dynamic_cast<CharMeshHide*>(o));
    else if(name == ikMidi) unk650.push_back(dynamic_cast<CharIKMidi*>(o));
    else if(name == cdMidi) unk660.push_back(dynamic_cast<CharDriverMidi*>(o));
    else if(name == khMidi) unk670.push_back(dynamic_cast<CharKeyHandMidi*>(o));
}
#pragma pop

void BandCharacter::ClearDircuts(){ mDircuts.clear(); }

void BandCharacter::SetGroupName(const char* name){ strcpy(mGroupName, name); }

void BandCharacter::TextureCompressed(int i){
    std::list<int>::iterator it;
    for(it = mCompressedTextureIDs.begin(); it != mCompressedTextureIDs.end() && *it != i; ++it);
    if(it == mCompressedTextureIDs.end()) MILO_WARN("%s Could not find compress texture id %d\n", PathName(this), i);
    else mCompressedTextureIDs.erase(it);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandCharacter)
    HANDLE_EXPR(get_play_flags, unk450)
    HANDLE(play_group, OnPlayGroup)
    HANDLE(group_override, OnGroupOverride)
    HANDLE(change_face_group, OnChangeFaceGroup)
    HANDLE_ACTION(clear_group, ClearGroup())
    HANDLE(set_play, OnSetPlay)
    HANDLE_ACTION(start_load, StartLoad(_msg->Int(2), _msg->Size() > 3 ? _msg->Int(3) : mInCloset, false))
    HANDLE_EXPR(is_loading, IsLoading())
    HANDLE_EXPR(flag_string, FlagString(_msg->Int(2)))
    HANDLE(cam_teleport, OnCamTeleport)
    HANDLE(closet_teleport, OnClosetTeleport)
    HANDLE(install_filter, OnInstallFilter)
    HANDLE(pre_clear, OnPreClear)
    HANDLE(copy_prefab, OnCopyPrefab)
    HANDLE(save_prefab, OnSavePrefab)
    HANDLE(set_file_merger, OnSetFileMerger)
    if(sym == list_dircuts) return OnListDircuts();
    HANDLE(load_dircut, OnLoadDircut)
    HANDLE_ACTION(set_context, SetContext(_msg->Sym(2)))
    HANDLE_ACTION(save_from_closet, SavePrefabFromCloset())
    HANDLE_ACTION(set_singalong, SetSingalong(_msg->Float(2)))
    HANDLE(on_post_merge, OnPostMerge)
    HANDLE(hide_categories, OnHideCategories)
    HANDLE(restore_categories, OnRestoreCategories)
    HANDLE_ACTION(game_over, GameOver())
    HANDLE(toggle_interests_overlay, OnToggleInterestDebugOverlay)
    HANDLE(list_drum_venues, OnListDrumVenues)
    HANDLE(portrait_begin, OnPortraitBegin)
    HANDLE(portrait_end, OnPortraitEnd)
    HANDLE_SUPERCLASS(BandCharDesc)
    HANDLE_SUPERCLASS(Character)
    HANDLE_CHECK(0x9A6)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(BandCharacter)
    SYNC_PROP(tempo, mTempo)
    SYNC_PROP(genre, mGenre)
    SYNC_PROP(drum_venue, mDrumVenue)
    SYNC_PROP(force_vertical, mForceVertical)
    SYNC_PROP_SET(instrument_type, mInstrumentType, SetInstrumentType(_val.Sym(0)))
    SYNC_PROP_SET(group_name, mGroupName, SetGroupName(_val.Str(0)))
    SYNC_PROP_SET(head_lookat_weight, unk550 ? unk550->Weight() : 0, SetHeadLookatWeight(_val.Float(0)))
    SYNC_PROP_SET(in_closet, mInCloset, StartLoad(false, _val.Int(0), false))
    SYNC_PROP(test_prefab, mTestPrefab)
    SYNC_PROP(use_mic_stand_clips, mUseMicStandClips)
    SYNC_PROP(in_tour_ending, mInTourEnding)
    SYNC_PROP(test_tour_ending_venue, mTestTourEndingVenue)
    SYNC_SUPERCLASS(BandCharDesc)
    SYNC_SUPERCLASS(Character)
END_PROPSYNCS