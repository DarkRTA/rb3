#include "bandobj/BandCharacter.h"

void BandCharacter::Init(){ Register(); }
void BandCharacter::Terminate(){}

BandCharacter::BandCharacter() : unk450(0), unk454(this, 0), unk460(0), unk464(0), unk528(0), mForceVertical(1), unk52c(this, 0), unk538(this, 0), mTempo("medium"), unk548(0),
    unk550(this, 0), unk55c(this, 0), unk568(this, 0), unk574(0), mTestPrefab(this, 0), mGenre("rocker"), mDrumVenue("small_club"), mTestTourEndingVenue(0), mInstrumentType("none"), unk594(this, 0),
    mInCloset(0), unk5a1(0), unk5a2(0), unk5a3(0), unk5a4(this, 0), unk5b0(this, kObjListNoNull), unk5c0(this, kObjListNoNull), unk5d0(this, kObjListNoNull),
    unk5e0(this, kObjListNoNull), unk5f0(this, kObjListNoNull), unk600(this, kObjListNoNull), unk610(this, kObjListNoNull), unk620(this, kObjListNoNull),
    unk630(this, kObjListNoNull), unk640(this, kObjListNoNull), unk650(this, kObjListNoNull), unk660(this, kObjListNoNull), unk670(this, kObjListNoNull),
    unk680(this, 0), unk68c(this, 0), unk698(this, 0), unk6a4(this, 0), unk6b0(this, 0), mUseMicStandClips(0), unk6bd(1), unk6c0(this, 0), mInTourEnding(0), unk6d8(0), unk6ec(0),
    unk738(0), unk73c(this, kObjListNoNull), unk74c(this, kObjListNoNull) {

}

#pragma push
#pragma dont_inline on
BandCharacter::~BandCharacter(){
    TheRnd->CompressTextureCancel(this);
}
#pragma pop

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