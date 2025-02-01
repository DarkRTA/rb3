#pragma once
#include "utl/Symbol.h"
#include <vector>
#include <list>

/** A stream of text. */
class TextStream {
public:
    TextStream();
    virtual ~TextStream() {}
    virtual void Print(const char *) = 0;

    TextStream &operator<<(char);
    TextStream &operator<<(short);
    TextStream &operator<<(int);
    TextStream &operator<<(long);
    TextStream &operator<<(unsigned char);
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

// Note: `Allocator` here is actually the size/capacity type parameter on Wii.
// The name is based on Xbox 360 symbols, which show the allocator type instead.
template <class T, class Allocator>
TextStream &operator<<(TextStream &ts, const std::vector<T, Allocator> &vec) {
    ts << "(size:" << vec.size() << ")";
    for (std::vector<T, Allocator>::const_iterator it = vec.begin(); it != vec.end();
         ++it) {
        ts << "\n" << it - vec.begin() << "\t" << *it;
    }
    return ts;
}

template <class T, class Allocator>
TextStream &operator<<(TextStream &ts, const std::list<T, Allocator> &list) {
    ts << "(size:" << list.size() << ")";
    int i = 0;
    for (std::list<T, Allocator>::const_iterator it = list.begin(); it != list.end();
         ++it, ++i) {
        ts << "\n" << i << "\t" << *it;
    }
    return ts;
}