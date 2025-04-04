#include "network/Extensions/ChannelMembers.h"
#include "VoiceChannelMember.h"

namespace Quazal {
    ChannelMembers::ChannelMembers() : unk8(0) {}
    ChannelMembers::~ChannelMembers() {}

    void ChannelMembers::Trace(unsigned int ui) const {
        for (qList<VoiceChannelMember>::const_iterator it = m_dsMemberList.begin();
             it != m_dsMemberList.end();
             ++it) {
            it->Trace(ui);
        }
    }
}