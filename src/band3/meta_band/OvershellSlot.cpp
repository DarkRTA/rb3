#include "meta_band/OvershellSlot.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/SessionMgr.h"
#include "bandobj/OvershellDir.h"
#include "game/BandUserMgr.h"

OvershellSlot::OvershellSlot(int i, OvershellPanel* panel, OvershellDir* dir, BandUserMgr* umgr, SessionMgr* smgr) : unk1c(new OvershellSlotStateMgr()) {

}