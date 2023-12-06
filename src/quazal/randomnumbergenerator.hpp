#ifndef QUAZAL_RANDOMNUMBERGENERATOR_HPP
#define QUAZAL_RANDOMNUMBERGENERATOR_HPP

namespace Quazal {
    class RandomNumberGenerator {
    public:
        RandomNumberGenerator();
        ~RandomNumberGenerator();
        void SetRandomNumberSeed(unsigned int);
        unsigned int GetRandomNumber(unsigned int);
        float GetRealRandomNumber(float);
    };
}

#endif