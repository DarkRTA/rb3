#pragma once
#include "ChannelMembersDDL.h"

namespace Quazal {
    class ChannelMembers : public _DS_ChannelMembers {
    public:
        ChannelMembers();
        ~ChannelMembers();

        void Trace(unsigned int) const;

        int unk8;
    };
}