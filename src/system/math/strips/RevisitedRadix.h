#ifndef MATH_STRIPS_REVISITEDRADIX_H
#define MATH_STRIPS_REVISITEDRADIX_H

class RadixSorter {
public:
    unsigned int* mHistogram;
    unsigned int* mOffset;
    unsigned int mCurrentSize;
    unsigned int* mIndices;
    unsigned int* mIndices2;

    RadixSorter();
    ~RadixSorter();
    RadixSorter& Sort(unsigned int* input, unsigned int nb, bool signedvalues);
    RadixSorter& ResetIndices();
};

#endif
