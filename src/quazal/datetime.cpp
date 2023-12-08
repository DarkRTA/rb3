#include "datetime.hpp"

Quazal::DateTime::DateTime(){
    num = 0;
}

Quazal::DateTime::DateTime(const Quazal::DateTime& dt){
    num = dt.num;
}

Quazal::DateTime* Quazal::DateTime::operator=(const Quazal::DateTime& dt){
    num = dt.num;
}

Quazal::DateTime::operator unsigned long long() const {
    return num;
}

unsigned int Quazal::DateTime::GetYear() const {
    return (num & 0xFFFF0000) << 2 | (num & 0xFFFF) >> 0x1A;
}

// return (*(uint *)this & 0xff) << 6 | *(uint *)(this + 4) >> 0x1a;