#ifndef QUAZAL_RANDOMNUMBERGENERATOR_HPP
#define QUAZAL_RANDOMNUMBERGENERATOR_HPP

namespace Quazal {
    class RandomNumberGenerator {
    public:
        unsigned int unk_arr[0x270];
        unsigned int unk_9c0;
        unsigned int unk_9c4;
        unsigned int unk_9c8;

        RandomNumberGenerator();
        ~RandomNumberGenerator();
        void SetRandomNumberSeed(unsigned int);
        unsigned int GetRandomNumber(unsigned int);
        float GetRealRandomNumber(float);
    };
}

#endif