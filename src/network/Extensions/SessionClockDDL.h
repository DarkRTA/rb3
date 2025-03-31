#pragma once
#include "ObjDup/RootDO.h"

namespace Quazal {
    class _DO_SessionClock : public RootDO {
    public:
        _DO_SessionClock();
        virtual ~_DO_SessionClock() {}
        virtual bool HasGlobalDOProperty() const;
        virtual void CallOperationOnDatasets(DOOperation *, Operation::_Event);
        virtual bool IsACoreDO() const;
        virtual bool IsABootstrapDO() const;
    };
}