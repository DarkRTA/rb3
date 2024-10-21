#include "meta_band/CharProvider.h"
#include "meta_band/CharData.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMgr.h"
#include "game/BandUser.h"
#include "os/Debug.h"
#include "tour/TourCharLocal.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

CharProvider::CharProvider(LocalBandUser* u, bool b1, bool b2) : unk20(u), unk2c(b1), unk2d(b2), unk30(-1) {

}

CharProvider::~CharProvider(){
    Clear();
}

void CharProvider::Reload(LocalBandUser* user){
    unk20 = user;
    Clear();
    if(unk2c){
        mCharacters.push_back(CharacterEntry(1, char_createnew, 0, 0, false));
    }
    else {
        mCharacters.push_back(CharacterEntry(0, none, 0, 0, false));
    }
    BandProfile* userprofile = TheProfileMgr.GetProfileForUser(unk20);
    if(userprofile) AddCharactersFromProfile(userprofile);
    mCharacters.push_back(CharacterEntry(4, char_prefab, 0, 0, false));

    CharData* chardata = unk20->GetChar();
    if(chardata && !chardata->IsCustomizable() && !unk2d){
        PrefabChar* pPrefab = dynamic_cast<PrefabChar*>(chardata);
        MILO_ASSERT(pPrefab, 0x54);
        mCharacters.push_back(CharacterEntry(2, pPrefab->GetPrefabName(), pPrefab, 0, true));
    }
    int numchars = mCharacters.size();
    std::vector<PrefabChar*> prefabs;

    if(unk2d){
        PrefabMgr::GetPrefabMgr()->GetPrefabs(prefabs);
    }
    else PrefabMgr::GetPrefabMgr()->GetAvailablePrefabs(prefabs);
    for(int i = 0; i < prefabs.size(); i++){
        PrefabChar* pChar = prefabs[i];
        if(!userprofile || !unk2d){
            int standinidx = userprofile->GetCharacterStandinIndex(pChar);
            if(standinidx == -1 || standinidx == unk30){
                mCharacters.push_back(CharacterEntry(2, pChar->GetPrefabName(), pChar, 0, false));
            }
        }
    }
    std::sort(mCharacters.begin() + numchars, mCharacters.end(), CompareCharacters());
}

void CharProvider::AddCharactersFromProfile(BandProfile* profile){
    MILO_ASSERT(profile, 0x7D);
    std::vector<TourCharLocal*> chars;
    if(unk2d){
        profile->GetAvailableStandins(unk30, chars);
    }
    else profile->GetAvailableCharacters(chars);
    CharData* pCurrentChar = unk20->GetChar();
    bool haschar = false;
    if(pCurrentChar && pCurrentChar->IsCustomizable()){
        TourCharLocal* pLocalChar = dynamic_cast<TourCharLocal*>(pCurrentChar);
        MILO_ASSERT(pLocalChar, 0x8F);
        haschar = profile->HasChar(pLocalChar);
    }
    if(chars.empty() || !haschar) return;
    else {
        mCharacters.push_back(CharacterEntry(4, char_header, 0, profile, false));
        if(haschar && !unk2d){
            MILO_ASSERT(pCurrentChar, 0xA0);
            MILO_ASSERT(pCurrentChar->IsCustomizable(), 0xA1);
            mCharacters.push_back(CharacterEntry(3, "", pCurrentChar, 0, true));
        }
        int numchars = mCharacters.size();
        for(std::vector<TourCharLocal*>::iterator it = chars.begin(); it != chars.end(); ++it){
            TourCharLocal* pCharacter = *it;
            MILO_ASSERT(pCharacter, 0xAD);
            mCharacters.push_back(CharacterEntry(3, "", pCharacter, 0, false));
        }
        std::sort(mCharacters.begin() + numchars, mCharacters.end(), CompareCharacters());
    }
}

void CharProvider::Clear(){
    mCharacters.clear();
}

Symbol CharProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x102);
    return mCharacters[data].unk8;
}

bool CharProvider::IsActive(int data) const {
    if(mCharacters.empty()) return false;
    else {
        MILO_ASSERT(( 0) <= (data) && (data) < ( mCharacters.size()), 0x117);
        return mCharacters[data].unk0;
    }
}

bool CharProvider::IsIndexNewChar(int idx){
    if(mCharacters.empty()) return false;
    else {
        MILO_ASSERT(( 0) <= (idx) && (idx) < ( mCharacters.size()), 0x134);
        return mCharacters[idx].unk0 == 1;
    }
}

BEGIN_HANDLERS(CharProvider)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x176)
END_HANDLERS