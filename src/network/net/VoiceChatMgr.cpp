#include "network/net/VoiceChatMgr.h"
#include "Extensions/CodecManager.h"
#include "Extensions/DemuxEventHandler.h"
#include "Extensions/SpeexCodec.h"
#include "ObjDup/Session.h"
#include "net/NetSession.h"
#include "os/Debug.h"

VoiceChatMgr *TheVoiceChatMgr;

namespace {
    class VoiceReceiver : public Quazal::DemuxEventHandler {
    public:
        VoiceReceiver() {}
        virtual ~VoiceReceiver() {}
        virtual bool StreamOpened(unsigned char, Quazal::DOHandle);
        virtual bool StreamPacketReceived(
            unsigned char, Quazal::DOHandle, unsigned char *, unsigned int
        );
        virtual bool StreamClosed(unsigned char, Quazal::DOHandle);
    };

    void CreateVoiceChannel() {}
}

VoiceChatMgr::VoiceChatMgr()
    : mCodec(new Quazal::SpeexCodec(0x50)), mReceiver(new VoiceReceiver()), unk24(0),
      unk28(0), unk2c(0), unk40(1), unk41(0), unk42(0) {
    MILO_ASSERT(!TheVoiceChatMgr, 0x75);
    TheVoiceChatMgr = this;
    Quazal::CodecManager::s_oInstance.RegisterCodec(0, mCodec);
    Quazal::Session::RegisterWellKnownDOsFactory(CreateVoiceChannel);
    MILO_ASSERT(TheNetSession, 0x7B);
    TheNetSession->AddSink(this, "remote_player_left");
}

VoiceChatMgr::~VoiceChatMgr() {}