#include "rand2.hpp"

// fn_802DDE34
Rand2::Rand2(int i){
    num = i;
    if(i == 0){
        num = 1;
        return;
    }
    if(i >= -1) return;
    num = -i;
}