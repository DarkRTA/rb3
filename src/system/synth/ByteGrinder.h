#ifndef SYNTH_BYTEGRINDER_H
#define SYNTH_BYTEGRINDER_H


/** Handles MOGG/BIK encryption, as it is unique from BinStream encryption. */
class ByteGrinder {
public:
    ByteGrinder();
    virtual ~ByteGrinder(){} // generic dtor
    int pickOneOf32A(bool, long);
    int pickOneOf32B(bool, long);
    void GrindArray(long, long, unsigned char*, int, long);
    void Init();
};

#endif
