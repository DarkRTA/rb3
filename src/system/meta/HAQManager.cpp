#include "meta/HAQManager.h"
#include "os/Debug.h"
#include "obj/Dir.h"

HAQManager* TheHAQMgr;

HAQManager::HAQManager() : m_bEnabled(0) {
    MILO_ASSERT(!TheHAQMgr, 0x1A);
    TheHAQMgr = this;
    SetName("haq_mgr", ObjectDir::sMainDir);
}

HAQManager::~HAQManager(){
    
}

void HAQManager::Init(){
    
}

String HAQManager::GetLabelForType(HAQType type) const {
    String ret("");
    switch(type){
        case kHAQType_Screen: ret = "Screen"; break;
        case kHAQType_Focus: ret = "Focus"; break;
        case kHAQType_Button: ret = "Button"; break;
        case kHAQType_Slider: ret = "Slider"; break;
        case kHAQType_List: ret = "List"; break;
        case kHAQType_Song: ret = "Song"; break;
        default: MILO_ASSERT(false, 0x50); break;
    }
    return ret;
}
