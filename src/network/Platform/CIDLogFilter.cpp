#include "Platform/OutputFormat.h"
#include "Platform/RefCountedObject.h"
#include <decomp.h>

DECOMP_FORCEBLOCK(CIDLogFilter, (void), {Quazal::OutputFormat* r = dynamic_cast<Quazal::OutputFormat*>(new Quazal::RefCountedObject);})