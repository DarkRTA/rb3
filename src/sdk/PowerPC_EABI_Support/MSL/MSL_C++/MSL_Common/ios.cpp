#include <MSL_C++/ios>
#include <MSL_C++/stdexcept>

#include <MSL_C++/Metrowerks/move_ptr.h>

#include "decomp.h"

DECOMP_FORCEBLOCK(locale, (), throw std::logic_error("");)
#pragma dont_inline on
DECOMP_FORCEBLOCK(locale, (Metrowerks::move_ptr<char, std::detail::default_delete<char[]>&> *p), p->~move_ptr();)
#pragma dont_inline off
