#pragma once
#include "Extensions/VoiceChannelDDL.h"
#include "ObjDup/DOHandle.h"
#include "Platform/EventHandler.h"

namespace Quazal {
    class VoiceChannel : public _DO_VoiceChannel {
    public:
        class EventHandler {
        public:
            EventHandler() {}
            virtual ~EventHandler() {}
            virtual bool ApproveJoinRequest(DOHandle) { return true; }
            virtual void MembershipChanged() {}
        };
        VoiceChannel();
        virtual ~VoiceChannel();
        virtual bool ApproveFaultRecovery();
        virtual bool ApproveEmigration(unsigned int);
        virtual void OperationEnd(DOOperation *);
        virtual void Trace(unsigned int) const;
        virtual bool Publish();
    };
}