#pragma once
#include "ChannelInfo.h"
#include "ChannelMembers.h"
#include "ObjDup/RootDO.h"

namespace Quazal {
    class _DO_VoiceChannel : public RootDO {
    public:
        _DO_VoiceChannel();
        virtual ~_DO_VoiceChannel();
        virtual bool HasGlobalDOProperty() const;
        virtual void CallOperationOnDatasets(DOOperation *, Operation::_Event);
        virtual bool IsACoreDO() const;

        static unsigned int s_uiClassID;

        ChannelInfo unk74;
        ChannelMembers unk80;
    };
}