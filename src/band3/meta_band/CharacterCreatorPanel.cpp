#include "meta_band/CharacterCreatorPanel.h"
#include "FaceHairProvider.h"
#include "FaceOptionsProvider.h"
#include "OutfitProvider.h"
#include "game/BandUser.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/EyebrowsProvider.h"
#include "meta_band/FaceTypeProvider.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "os/Debug.h"
#include "ui/UIGridProvider.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

CharacterCreatorPanel::CharacterCreatorPanel() : unk4c(0), mClosetMgr(0), unk6c(0), unk70(0), mFaceTypeProvider(0), mOutfitProvider(0), mFaceHairProvider(0),
    mFaceOptionsProvider(0), mFaceOptionsGridProvider(0), mEyebrowsProvider(0), mEyebrowsGridProvider(0), unk90(gNullStr), unk94(gNullStr), unk98(0), unk99(0) {

}

CharacterCreatorPanel::~CharacterCreatorPanel(){
    unk50.clear();
}

void CharacterCreatorPanel::Load(){
    TexLoadPanel::Load();
    mClosetMgr = ClosetMgr::GetClosetMgr();
    LocalBandUser* closetUser = mClosetMgr->mUser;
    BandProfile* profile = TheProfileMgr.GetProfileForUser(closetUser);
    if(profile && closetUser && mClosetMgr){
        CreateNewCharacter();
        AddGridThumbnails(male);
        AddGridThumbnails(female);
        SetGender(male);
        MILO_ASSERT(!mOutfitProvider, 0xA7);
        mOutfitProvider = new OutfitProvider();
        MILO_ASSERT(!mFaceTypeProvider, 0xAA);
        mFaceTypeProvider = new FaceTypeProvider();
        MILO_ASSERT(!mFaceHairProvider, 0xAD);
        mFaceHairProvider = new FaceHairProvider();
        MILO_ASSERT(!mFaceOptionsProvider, 0xB0);
        mFaceOptionsProvider = new FaceOptionsProvider(mTexs);
        MILO_ASSERT(!mFaceOptionsGridProvider, 0xB3);
        mFaceOptionsGridProvider = new UIGridProvider(mFaceOptionsProvider, 3);
        MILO_ASSERT(!mEyebrowsProvider, 0xB6);
        mEyebrowsProvider = new EyebrowsProvider(mTexs);
        MILO_ASSERT(!mEyebrowsGridProvider, 0xB9);
        mEyebrowsGridProvider = new UIGridProvider(mEyebrowsProvider, 3);
    }
}