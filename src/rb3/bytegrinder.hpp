#ifndef RB3_BYTEGRINDER_HPP
#define RB3_BYTEGRINDER_HPP


/** Handles MOGG/BIK encryption, as it is unique from BinStream encryption. */
class ByteGrinder {
public:
    ByteGrinder();
    virtual ~ByteGrinder(); // generic dtor
};

#endif
