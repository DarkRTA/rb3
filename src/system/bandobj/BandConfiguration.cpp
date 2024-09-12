#include "bandobj/BandConfiguration.h"

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