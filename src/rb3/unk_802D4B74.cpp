#include "common.hpp"

extern float fn_802D54E8(float);
// fn_802D54A8
double Sqrt(double d){
    return (float)d * fn_802D54E8(d);
}

// fn_802D54E8