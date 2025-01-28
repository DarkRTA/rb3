#include "beatmatch/TimeSpanVector.h"
#include "os/Debug.h"
#include <utility>

void IntersectTimeSpans(const std::vector<std::pair<float, float> >& v1, const std::vector<std::pair<float, float> >& v2, std::vector<std::pair<float, float> >& o_rIntersection){
    MILO_ASSERT(o_rIntersection.empty(), 0x14);
    for(std::vector<std::pair<float, float> >::const_iterator it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end() && it2 != v2.end(); ){
        float max1 = Max(it1->first, it2->first);
        float min2 = Min(it1->second, it2->second);
        if(max1 < min2){
            o_rIntersection.push_back(std::make_pair(max1, min2));
        }
        if(it1->second <= min2) ++it1;
        if(it2->second <= min2) ++it2;
    }
}