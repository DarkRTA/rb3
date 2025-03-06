#include "meta_band/MetaNetMsgs.h"
#include "MusicLibrary.h"
#include "math/Rand.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/Utl.h"
#include "net/NetMessage.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

NetMessage *JunkDataMsg::NewNetMessage() { return new JunkDataMsg(); }

void BandEventPreviewMsg::Save(BinStream &bs) const { bs << unk4; }
void BandEventPreviewMsg::Load(BinStream &bs) { bs >> unk4; }

void BandEventPreviewMsg::Dispatch() {
    UIPanel *panel = ObjectDir::Main()->Find<UIPanel>("tour_band_event_panel", true);
    static Message playMsg(play_preview, 0);
    playMsg[0] = unk4;
    panel->Handle(playMsg, true);
}

void TriggerBackSoundMsg::Dispatch() {
    DataArrayPtr ptr(synth, play, "button_down");
    ptr->Execute();
}

VerifyBuildVersionMsg::VerifyBuildVersionMsg() {
    SystemConfig()->FindData(version, mVersion, true);
}

void VerifyBuildVersionMsg::Save(BinStream &bs) const { bs << mVersion; }
void VerifyBuildVersionMsg::Load(BinStream &bs) { bs >> mVersion; }

void VerifyBuildVersionMsg::Dispatch() {
    String versionStr;
    SystemConfig()->FindData(version, versionStr, true);
    if (versionStr != mVersion) {
        MILO_WARN(
            "A machine with %s just joined our machine with %s. Mismatched builds can compromise network stability",
            mVersion,
            versionStr
        );
    }
}

void AppendSongToSetlistMsg::Dispatch() {
    MILO_ASSERT(IsLeaderLocal(), 0x55);
    TheMusicLibrary->AppendToSetlist(unk4);
}

void RemoveLastSongFromSetlistMsg::Dispatch() {
    MILO_ASSERT(IsLeaderLocal(), 0x5B);
    TheMusicLibrary->RemoveLastSongFromSetlist();
}

void InitJunkMsg() { JunkDataMsg::Register(); }

void SendJunkPatchesToUser(BandUser *user) {
    JunkDataMsg msg;
    TheSessionMgr->SendMsg(user, msg, kReliable);
    TheSessionMgr->SendMsg(user, msg, kReliable);
    TheSessionMgr->SendMsg(user, msg, kReliable);
}

void SendJunkPatchesToAll() {
    JunkDataMsg msg;
    TheSessionMgr->SendMsgToAll(msg, kReliable);
    TheSessionMgr->SendMsgToAll(msg, kReliable);
    TheSessionMgr->SendMsgToAll(msg, kReliable);
}

void JunkDataMsg::Save(BinStream &bs) const {
    char nums[0x2000];
    for (int i = 0; i < 0x2000; i++) {
        nums[i] = RandomInt(0, 0x100);
    }
    bs.Write(nums, 0x2000);
}

void JunkDataMsg::Load(BinStream &bs) {
    char nums[0x2000];
    bs.Read(nums, 0x2000);
}

void JunkDataMsg::Dispatch() {}