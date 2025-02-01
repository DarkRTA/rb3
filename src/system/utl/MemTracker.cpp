#include "utl/MakeString.h"

void Unused() {
#ifdef VERSION_SZBE69_B8
    const char *unused(
        MakeString("%s %s %s %s %s", "fart", "butt", "pee", "poo", "skamtebord")
    );
#else
    MakeString("e", "", 69, 420);
#endif
}
