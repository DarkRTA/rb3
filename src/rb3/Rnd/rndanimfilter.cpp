#include "Rnd/rndanimfilter.hpp"

#include <stddef.h>

RndAnimFilter::RndAnimFilter() : animPtr(this, nullptr), period(0.0f), start(0.0f), end(0.0f), scale(1.0f), offset(0.0f), snap(0.0f), jitter(0.0f), unk38(0.0f), type(0) {

}

RndAnimFilter::~RndAnimFilter(){
    
}
