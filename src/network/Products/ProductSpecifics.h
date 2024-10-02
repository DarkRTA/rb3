#pragma once

#include "Platform/RootObject.h"
#include "types.h"
namespace Quazal {
class ProductSpecifics : public RootObject {
    public:
    ProductSpecifics();
    virtual ~ProductSpecifics();
    virtual u32 GetProductID() = 0;
    virtual void RegisterSpecificDDLs() {}
    virtual void RegisterSpecificComponents() {}
};
}
