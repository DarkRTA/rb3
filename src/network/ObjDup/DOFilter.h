#ifndef OBJDUP_DOFILTER_H
#define OBJDUP_DOFILTER_H

#include "Platform/RefCountedObject.h"

namespace Quazal {
    class DOFilter : public RefCountedObject {
        DOFilter();
        virtual ~DOFilter();
        virtual int GetMinimumValidHandle(); // these both return a struct
        virtual int GetMaximumValidHandle();
    };
}

#endif // OBJDUP_DOFILTER_H
