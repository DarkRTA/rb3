#include "DOFilter.h"

namespace Quazal {
    DOFilter::DOFilter() {}
    DOFilter::~DOFilter() {}
    DOHandle DOFilter::GetMinimumValidHandle() { return 0; }
    DOHandle DOFilter::GetMaximumValidHandle() { return -1; }
}
