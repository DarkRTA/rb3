#include "meta_band/BandSongMetadata.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"

BandSongMetadata::BandSongMetadata(BandSongMgr* mgr) : unk100(mgr) {
    InitBandSongMetadata();
}

BandSongMetadata::BandSongMetadata(DataArray* main_arr, DataArray* backup_arr, bool onDisc, BandSongMgr* mgr) : SongMetadata(main_arr, backup_arr, onDisc), unk100(mgr) {
    InitBandSongMetadata();
    DataArray* member_arr;
    if(FIND_WITH_BACKUP(name)){
        unk40 = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(artist)){
        unk4c = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(album_name)){
        unk58 = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(album_track_number)){
        unk64 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(year_released)){
        unk6e = DateTime(member_arr->Int(1), 1, 1, 0, 0, 0);
    }
    if(FIND_WITH_BACKUP(year_recorded)){
        unk68 = DateTime(member_arr->Int(1), 1, 1, 0, 0, 0);
    }
    else unk68 = unk6e;
    if(FIND_WITH_BACKUP(genre)){
        unk74 = member_arr->Sym(1);
    }
    if(FIND_WITH_BACKUP(anim_tempo)){
        unk78 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(vocal_gender)){
        unk7c = member_arr->Sym(1);
    }
    if(FIND_WITH_BACKUP(song_length)){
        unk80 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(alternate_path)){
        unkf4 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(base_points)){
        unk84 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(bonus)){
        unkf5 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(fake)){
        bool ret = false;
        DataNode& node = CONST_ARRAY(member_arr)->Node(1);
        if(node.Type() == kDataInt){
            if(CONST_ARRAY(member_arr)->Node(1).LiteralInt(0)) ret = true;
        }
        unkf6 = ret;
    }
    if(FIND_WITH_BACKUP(tutorial)){
        unkf7 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(mute_win_cues)){
        unkf8 = true;
    }
    if(FIND_WITH_BACKUP(rank)){
        for(int i = 1; i < member_arr->Size(); i++){
            DataArray* arr = member_arr->Array(i);
            unk88[arr->Sym(0)] = arr->Float(1);
        }
    }
    if(FIND_WITH_BACKUP(rating)){
        unk66 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(guide_pitch_volume)){
        unka0 = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(vocal_tonic_note)){
        unka4 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(song_key)){
        unka8 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(song_tonality)){
        unkac = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(song_scroll_speed)){
        unkb0 = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(tuning_offset_cents)){
        unkb4 = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(bank)){
        unkb8 = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(drum_bank)){
        unkbc = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(band_fail_cue)){
        unkc0 = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(album_art)){
        unkf9 = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(master)){
        unkfa = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(tri_frame)){
        unkfb = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(real_guitar_tuning)){
        for(int i = 0; i < 6; i++){
            DataArray* arr = member_arr->Array(1);
            unkc4[i] = arr->Int(i);
        }
    }
    if(FIND_WITH_BACKUP(real_bass_tuning)){
        for(int i = 0; i < 4; i++){
            DataArray* arr = member_arr->Array(1);
            unkdc[i] = arr->Int(i);
        }
    }
    if(FIND_WITH_BACKUP(extra_authoring)){
        unkfc = member_arr->Contains(disc_update);
    }
    if(FIND_WITH_BACKUP(solo)){
        DataArray* arr = member_arr->Array(1);
        for(int i = 0; i < arr->Size(); i++){
            Symbol solosym = arr->Sym(i);
            if(solosym != vocals){
                if(solosym == vocal_percussion) solosym = vocals;
                unkec.push_back(solosym);
            }
        }
    }
    bool islatin1 = false;
    if(FIND_WITH_BACKUP(encoding)){
        islatin1 = member_arr->Sym(1) == latin1;
    }
    if(islatin1){
        char buf[0x100];
        ASCIItoUTF8(buf, 0x100, unk40.c_str());
        unk40 = buf;
        ASCIItoUTF8(buf, 0x100, unk4c.c_str());
        unk4c = buf;
        ASCIItoUTF8(buf, 0x100, unk58.c_str());
        unk58 = buf;
    }
}