#include "rand2.hpp"

// fn_802DDE34
Rand2::Rand2(int i) {
    num = i;
    if (i == 0) {
        num = 1;
        return;
    }
    if (i < 0)
        num = -i;
}

// fn_802DDE5C
int Rand2::Int() {
    int i = ((num % 127773) * 0x41A7) - ((num / 127773) * 0xB14);
    if (i > 0)
        num = i;
    else
        num = i + 0x7FFFFFFF;
    return num;
}