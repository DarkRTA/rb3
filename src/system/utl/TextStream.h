#ifndef UTL_TEXTSTREAM_H
#define UTL_TEXTSTREAM_H
#include "utl/Symbol.h"

// class DataArray;

/** A stream of text. */
class TextStream {
public:
    TextStream();
    virtual ~TextStream(){}
    virtual void Print(const char *) = 0;

    TextStream &operator<<(char);
    TextStream &operator<<(short);
    TextStream &operator<<(int);
    TextStream &operator<<(long);
    TextStream &operator<<(unsigned int);
    TextStream &operator<<(unsigned short);
    TextStream &operator<<(unsigned long);
    TextStream &operator<<(float);
    TextStream &operator<<(double);
    TextStream &operator<<(const char *);
    TextStream &operator<<(Symbol);
    TextStream &operator<<(bool);

    /** Writes a space to the text stream a set number of times.
     * @param [in] i: The number of times to write a space.
    */
    void Space(int i);
};

#endif
