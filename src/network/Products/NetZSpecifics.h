#pragma once

#include "Products/ProductSpecifics.h"
namespace Quazal {
class NetZSpecifics : public ProductSpecifics {
    public:
    NetZSpecifics();
    virtual ~NetZSpecifics();
    virtual u32 GetProductID();
    virtual void RegisterSpecificDDLs();
    virtual void RegisterSpecificComponents();
};
}
