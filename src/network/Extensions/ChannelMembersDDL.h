#pragma once
#include "ObjDup/DataSet.h"
#include "Platform/RootObject.h"
#include "Platform/qStd.h"
#include "VoiceChannelMember.h"

namespace Quazal {
    class _DS_ChannelMembers : public RootObject {
    public:
        _DS_ChannelMembers() {}
        ~_DS_ChannelMembers() {}

        DataSet unk0; // 0x0
        qList<VoiceChannelMember> m_dsMemberList; // 0x4
    };
}