#include "utl/MBT.h"
#include "utl/MakeString.h"
#include "math/MathFuncs.h"
#include <stdlib.h>
#include <string.h>

void ParseMBT(const char* str, int& measure, int& beat, int& tick){
    char buf[32];
    strncpy(buf, str, 0x20);
    buf[31] = '\0';
    int data[3] = { 1, 1, 0 };
    int i2 = 0;
    char* n = strtok(buf, ":");
    while(i2 < 3 && n != 0){
        data[i2++] = atoi(n);
        n = strtok(0, ":");
    }
    measure = data[0] - 1;
    beat = data[1] - 1;
    tick = data[2];
}

const char* TickFormat(int tick, const MeasureMap& map){
    int i1, i2, i3;
    if(tick >= 0){
        map.TickToMeasureBeatTick(tick, i1, i2, i3);
        return MakeString("%d:%d:%03d", i1 + 1, i2 + 1, i3);
    }
    else return "negative tick";
}

const char* FormatTimeMSH(float f){
    // this feels fake, double check retail and see if fmod_f or something to that effect got called
    double f2 = std::fmod((double)f, 60000.0);
    double f3 = std::fmod((double)f, 1000.0);
    return MakeString("%d:%02d.%02d", (int)(f / 60000.0f), (int)(f2 / 1000.0), (int)(f3 / 10.0));
}
