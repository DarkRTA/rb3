#include "codec.hpp"
#include "audiostreamformat.hpp"
#include "_ddl_audiostreamformat.hpp"

Quazal::_DDL_AudioStreamFormat::_DDL_AudioStreamFormat(){

}

Quazal::_DDL_AudioStreamFormat::~_DDL_AudioStreamFormat(){

}

Quazal::AudioStreamFormat::AudioStreamFormat(){
    Init(8000, 1, 8000, 16);
}

void Quazal::AudioStreamFormat::Init(int i1, int i2, int i3, int i4){
    unk4 = i1;
    unk8 = i2;
    unkc = i3;
    unk10 = i4;
}

Quazal::Codec::Codec(){

}

Quazal::Codec::~Codec(){

}