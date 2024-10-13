#ifndef _MSL_TYPE_TRAITS_UTILITY
#define _MSL_TYPE_TRAITS_UTILITY

// clang-format off: conciseness

#ifdef DECOMP_IDE_FLAG
#define __static_assert(cond, msg)
#endif

#define __MWERKS_NOEVAL __static_assert(false, "Cannot be called from an evaluated context!")

namespace std {

    template <typename T>
    static T declval() { __MWERKS_NOEVAL; }

}

// clang-format on

#endif
