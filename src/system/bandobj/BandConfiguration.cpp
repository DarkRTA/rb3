#include "bandobj/BandConfiguration.h"
#include "bandobj/BandCharacter.h"
#include "bandobj/BandWardrobe.h"
#include "obj/DataUtl.h"
#include "utl/Symbols.h"

INIT_REVS(BandConfiguration)
int BandConfiguration::TargTransforms::sNumPlayModes;

BandConfiguration::BandConfiguration(){
    for(int i = 0; i < 4; i++){
        Waypoint* wp = Hmx::Object::New<Waypoint>();
        wp->SetRadius(1000.0f);
        wp->SetStrictRadiusDelta(0);
        mXfms[i].mWay = wp;
        for(int j = 0; j < 3; j++){
            mXfms[i].xfms[j].xfm.Reset();
            mXfms[i].xfms[j].targName = "";
        }
    }
}

BandConfiguration::~BandConfiguration(){
    for(int i = 0; i < 4; i++){
        delete mXfms[i].mWay;
    }
}

#define kNumPlayModes 3

int BandConfiguration::ConfigIndex(){
    Symbol playmode = TheBandWardrobe->GetPlayMode();
    DataArray* macro = DataGetMacro("BAND_PLAY_MODES");
    MILO_ASSERT(macro->Size() == kNumPlayModes, 0x33);
    for(int i = 0; i < 3; i++){
        if(macro->Sym(i) == playmode) return i;
    }
    MILO_FAIL("invalid mode %s", playmode);
    return 0;
}

void BandConfiguration::SyncPlayMode(){
    int idx = ConfigIndex();
    for(int i = 0; i < 4; i++){
        TargTransform& curtargxfm = mXfms[i].xfms[idx];
        mXfms[i].mWay->SetLocalXfm(curtargxfm.xfm);
        BandCharacter* bchar = TheBandWardrobe->FindTarget(curtargxfm.targName, TheBandWardrobe->unk54);
        if(bchar) bchar->Teleport(mXfms[i].mWay);
    }
}

BinStream& operator>>(BinStream& bs, BandConfiguration::TargTransforms& tts){
    int i;
    for(i = 0; i < Min(3, BandConfiguration::TargTransforms::sNumPlayModes); i++){
        bs >> tts.xfms[i].targName;
        bs >> tts.xfms[i].xfm;
    }
    for(; i < BandConfiguration::TargTransforms::sNumPlayModes; i++){
        Symbol s;
        Transform t;
        bs >> s;
        bs >> t;
    }
    return bs;
}

SAVE_OBJ(BandConfiguration, 0x6E)

BEGIN_LOADS(BandConfiguration)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> TargTransforms::sNumPlayModes;
    for(int i = 0; i < 4; i++){
        bs >> mXfms[i];
    }
    if(TheBandWardrobe){
        TheBandWardrobe->unk90 = this;
    }
END_LOADS

BEGIN_COPYS(BandConfiguration)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(BandConfiguration)
    BEGIN_COPYING_MEMBERS
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                COPY_MEMBER(mXfms[i].xfms[j])
            }
        }
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(BandConfiguration)
    HANDLE(store_configuration, OnStoreConfiguration)
    HANDLE(release_configuration, OnReleaseConfiguration)
    HANDLE_ACTION(sync_play_mode, SyncPlayMode())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x9F)
END_HANDLERS

BEGIN_PROPSYNCS(BandConfiguration)
END_PROPSYNCS