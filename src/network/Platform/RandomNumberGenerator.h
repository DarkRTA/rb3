#ifndef PLATFORM_RANDOMNUMBERGENERATOR_H
#define PLATFORM_RANDOMNUMBERGENERATOR_H

namespace Quazal {
    class RandomNumberGenerator {
    public:
        RandomNumberGenerator();
        ~RandomNumberGenerator();

        void SetRandomNumberSeed(unsigned int);
        unsigned int GetRandomNumber(unsigned int);
        float GetRealRandomNumber(float);

        unsigned int m_mt[0x270];
        unsigned int m_mti;
        unsigned int m_mag01[2];
    };
}

#endif
