#include "SimpleTempoMap.h"
#include "TempoMap.h"

SimpleTempoMap gDefaultTempoMap(1000.0f);
TempoMap* TheTempoMap = &gDefaultTempoMap;

void SetTheTempoMap(TempoMap* tmap){
    TheTempoMap = tmap;
}

void ResetTheTempoMap(){
    TheTempoMap = &gDefaultTempoMap;
}
