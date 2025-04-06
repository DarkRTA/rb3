#pragma once
#include "ObjDup/DOHandle.h"
#include "VoiceChannelMemberDDL.h"

namespace Quazal {
    class VoiceChannelMember : public _DDL_VoiceChannelMember {
    public:
        VoiceChannelMember();
        virtual ~VoiceChannelMember();

        void Trace(unsigned int) const;

        DOHandle m_dohMemberStation; // 0x4
        DOHandle m_dohAssociatedDO; // 0x8
    };
}