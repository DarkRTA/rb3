#include "bandobj/BandConfiguration.h"
#include "utl/Symbols.h"

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

BEGIN_HANDLERS(BandConfiguration)
    HANDLE(store_configuration, OnStoreConfiguration)
    HANDLE(release_configuration, OnReleaseConfiguration)
    HANDLE_ACTION(sync_play_mode, SyncPlayMode())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x9F)
END_HANDLERS

BEGIN_PROPSYNCS(BandConfiguration)
END_PROPSYNCS