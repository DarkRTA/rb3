#pragma once
#include "Extensions/VoiceChannel.h"
#include "ObjDup/DOHandle.h"

namespace Quazal {
    class DemuxEventHandler : public VoiceChannel::EventHandler {
    public:
        DemuxEventHandler();
        virtual ~DemuxEventHandler();
        virtual bool StreamOpened(unsigned char, DOHandle);
        virtual bool
        StreamPacketReceived(unsigned char, DOHandle, unsigned char *, unsigned int);
        virtual bool StreamClosed(unsigned char, DOHandle);
        virtual void SetAutoOpen(bool);

        VoiceChannel *m_pChannel; // 0x4
        qVector<int> m_vSinkDevices; // 0x8
        bool m_bAutoOpen; // 0x10
    };
}