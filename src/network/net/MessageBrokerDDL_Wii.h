#pragma once
#include "ObjDup/RootDO.h"

namespace Quazal {
    class _DO_MessageBroker : public RootDO {
    public:
        _DO_MessageBroker();
        virtual ~_DO_MessageBroker() {}
        virtual bool HasGlobalDOProperty() const;
        virtual void CallOperationOnDatasets(DOOperation *, Operation::_Event);
        virtual bool IsACoreDO() const;

        static unsigned int s_uiClassID;
        static void InitDOClass(unsigned int);
    };
}