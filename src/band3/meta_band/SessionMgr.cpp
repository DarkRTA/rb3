#include "meta_band/SessionMgr.h"
#include "BandMachineMgr.h"
#include "BandNetGameData.h"
#include "net/Synchronize.h"

SessionMgr::SessionMgr(BandUserMgr* umgr, MatchMaker* mm) : Synchronizable("session_mgr"), mBandUserMgr(umgr), mMatchMaker(mm), unk54(0), mBandNetGameData(new BandNetGameData()), unk5c(0), unk70(0) {
    mMachineMgr = new BandMachineMgr(this, mBandUserMgr);
}

//   *(BandMachineMgr **)(this + 0x50) = this_01;
//   this_02 = (CriticalUserListener *)operator_new(0x28);
//   if (this_02 != (CriticalUserListener *)0x0) {
//     this_02 = (CriticalUserListener *)CriticalUserListener::CriticalUserListener(this_02,this);
//   }
//   *(CriticalUserListener **)(this + 0x54) = this_02;
//   *(undefined4 *)(this + 0x40) = 0;
//   *(undefined4 *)(this + 0x44) = 5;
//   *(undefined4 *)(this + 0x48) = 0;
//   (**(code **)(**(int **)this + 0x48))(*(int **)this,::@stringBase0,ObjectDir::sMainDir);
//   *(SessionMgr **)(*(int *)(this + 0x3c) + 0x78) = this;
//   *(undefined4 *)(this + 0x38) = TheNetSession;
//   if (@GUARD@Type__22SessionDisconnectedMsgFv@t_80C79BAC == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__22SessionDisconnectedMsgFv@t_80C89FC8,
//                    @STRING@Type__22SessionDisconnectedMsgFv_80B71764);
//     @GUARD@Type__22SessionDisconnectedMsgFv@t_80C79BAC = '\x01';
//   }
//   local_18 = gNullStr;
//   local_14[0] = @LOCAL@Type__22SessionDisconnectedMsgFv@t_80C89FC8;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)local_14,(Symbol)&local_18,0);
//   if (@GUARD@Type__14SessionBusyMsgFv@t_80C79BAA == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__14SessionBusyMsgFv@t_80C89FC0,
//                    @STRING@Type__14SessionBusyMsgFv_80B7178C);
//     @GUARD@Type__14SessionBusyMsgFv@t_80C79BAA = '\x01';
//   }
//   local_18 = gNullStr;
//   local_1c = @LOCAL@Type__14SessionBusyMsgFv@t_80C89FC0;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_1c,(Symbol)&local_18,0);
//   if (@GUARD@Type__16SigninChangedMsgFv@t_80C79BC8 == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__16SigninChangedMsgFv@t_80C8A078,
//                    @STRING@Type__16SigninChangedMsgFv_80B71F0C);
//     @GUARD@Type__16SigninChangedMsgFv@t_80C79BC8 = '\x01';
//   }
//   local_18 = gNullStr;
//   local_20 = @LOCAL@Type__16SigninChangedMsgFv@t_80C8A078;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_20,(Symbol)&local_18,0);
//   if (@GUARD@Type__13JoinResultMsgFv@t_80C79BAE == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__13JoinResultMsgFv@t_80C89FD0,
//                    @STRING@Type__13JoinResultMsgFv_80B71740);
//     @GUARD@Type__13JoinResultMsgFv@t_80C79BAE = '\x01';
//   }
//   local_18 = gNullStr;
//   local_24 = @LOCAL@Type__13JoinResultMsgFv@t_80C89FD0;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_24,(Symbol)&local_18,0);
//   if (@GUARD@Type__23ProcessedJoinRequestMsgFv@t_80C79BAD == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__23ProcessedJoinRequestMsgFv@t_80C89FCC,
//                    @STRING@Type__23ProcessedJoinRequestMsgFv_80B7174C);
//     @GUARD@Type__23ProcessedJoinRequestMsgFv@t_80C79BAD = '\x01';
//   }
//   local_18 = gNullStr;
//   local_28 = @LOCAL@Type__23ProcessedJoinRequestMsgFv@t_80C89FCC;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_28,(Symbol)&local_18,0);
//   if (@GUARD@Type__16NewRemoteUserMsgFv@t_80C79BB1 == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__16NewRemoteUserMsgFv@t_80C89FDC,
//                    @STRING@Type__16NewRemoteUserMsgFv_80B71710);
//     @GUARD@Type__16NewRemoteUserMsgFv@t_80C79BB1 = '\x01';
//   }
//   local_18 = gNullStr;
//   local_2c = @LOCAL@Type__16NewRemoteUserMsgFv@t_80C89FDC;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_2c,(Symbol)&local_18,0);
//   if (@GUARD@Type__17RemoteUserLeftMsgFv@t_80C79BB3 == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__17RemoteUserLeftMsgFv@t_80C89FE4,
//                    @STRING@Type__17RemoteUserLeftMsgFv_80B716E4);
//     @GUARD@Type__17RemoteUserLeftMsgFv@t_80C79BB3 = '\x01';
//   }
//   local_18 = gNullStr;
//   local_30 = @LOCAL@Type__17RemoteUserLeftMsgFv@t_80C89FE4;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_30,(Symbol)&local_18,0);
//   if (@GUARD@Type__16LocalUserLeftMsgFv@t_80C79BB0 == '\0') {
//     Symbol::Symbol((Symbol *)&@LOCAL@Type__16LocalUserLeftMsgFv@t_80C89FD8,
//                    @STRING@Type__16LocalUserLeftMsgFv_80B71720);
//     @GUARD@Type__16LocalUserLeftMsgFv@t_80C79BB0 = '\x01';
//   }
//   local_18 = gNullStr;
//   local_34 = @LOCAL@Type__16LocalUserLeftMsgFv@t_80C89FD8;
//   pOVar2 = (Object *)this;
//   if (this != (SessionMgr *)0x0) {
//     pOVar2 = *(Object **)this;
//   }
//   MsgSource::AddSink(*(MsgSource **)(this + 0x38),pOVar2,(Symbol)&local_34,(Symbol)&local_18,0);
//   if (TheGameMode != (MsgSource *)0x0) {
//     local_18 = gNullStr;
//     local_38 = gNullStr;
//     pOVar2 = (Object *)this;
//     if (this != (SessionMgr *)0x0) {
//       pOVar2 = *(Object **)this;
//     }
//     MsgSource::AddSink(TheGameMode,pOVar2,(Symbol)&local_38,(Symbol)&local_18,0);
//   }
//   this[0x68] = (SessionMgr)0x0;
//   uVar1 = RandomInt();
//   *(undefined4 *)(this + 0x6c) = uVar1;
//   return this;