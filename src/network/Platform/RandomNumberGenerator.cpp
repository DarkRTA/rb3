#include "Platform/RandomNumberGenerator.h"

namespace Quazal {

    RandomNumberGenerator::RandomNumberGenerator(){
        m_mag01[0] = 0;
        m_mag01[1] = 0x9908B0DF;
        m_mti = 0x271;
        //SetRandomNumberSeed(1);
        m_mt[0] = 1;
        m_mti = 1;
        for(; m_mti < 0x270; m_mti++){
            m_mt[m_mti] = m_mt[m_mti - 1] * 0x10DCD;
        }
    }

    RandomNumberGenerator::~RandomNumberGenerator(){

    }

    void RandomNumberGenerator::SetRandomNumberSeed(unsigned int ui){
        m_mt[0] = ui;
        m_mti = 1;
        for(; m_mti < 0x270; m_mti++){
            m_mt[m_mti] = m_mt[m_mti - 1] * 0x10DCD;
        }
    }

    unsigned int RandomNumberGenerator::GetRandomNumber(unsigned int ui){
        unsigned int i;
        unsigned int tmp2;
        if (0x270 <= m_mti) {
            if (m_mti == 0x271)
                SetRandomNumberSeed(0x1105);

            for (i = 0; i < 0xE3; i++) {
                unsigned int tmp =
                    (m_mt[i] & 0x80000000) | (m_mt[i + 1] & 0x7FFFFFFF & ~0x80000000);
                m_mt[i] = (tmp >> 1) ^ m_mt[i + 0x18D] ^ (m_mag01[tmp & 1]);
            }

            for (; i < 0x26F; i++) {
                unsigned int tmp =
                    (m_mt[i] & 0x80000000) | (m_mt[i + 1] & 0x7FFFFFFF & ~0x80000000);
                m_mt[i] = (tmp >> 1) ^ m_mt[i - 0xE3] ^ (m_mag01[tmp & 1]);
            }

            tmp2 = (m_mt[0] & 0x7FFFFFFF) | (m_mt[0x26F] & 0x80000000);
            m_mt[0x26F] = m_mt[0x18C] ^ (tmp2 >> 1) ^ m_mag01[(tmp2 & 1)];
            m_mti = 0;
        }
        int tmp = m_mti++;
        i = m_mt[tmp] ^ (m_mt[tmp] >> 0xB);
        i = i ^ ((i << 7) & 0x9D2C5680);
        i = i ^ ((i << 0xF) & 0xEFC60000);
        i = i ^ i >> 0x12;
        return i % ui;
    }

    float RandomNumberGenerator::GetRealRandomNumber(float f){
        return (GetRandomNumber(0x10000) / 65536.0f * f);
    }

}
