#include "simpletempomap.hpp"
#include "tempomap.hpp"

TempoMap* TheTempoMap = 0;
SimpleTempoMap gDefaultTempoMap(1000.0f);

void SetTheTempoMap(TempoMap* tmap){
    TheTempoMap = tmap;
}

void ResetTheTempoMap(){
    TheTempoMap = &gDefaultTempoMap;
}