#pragma once

#include "DuplicatedObject.h"
namespace Quazal {
    class _DO_RootDO : public DuplicatedObject {
    public:
        _DO_RootDO();
        virtual ~_DO_RootDO() {}
        virtual void CallOperationOnDatasets(DOOperation *, Operation::_Event);
        virtual bool IsACoreDO() const;
    };
}