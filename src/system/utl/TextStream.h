#ifndef UTL_TEXTSTREAM_H
#define UTL_TEXTSTREAM_H
#include "utl/Symbol.h"
#include <vector>
#include <list>

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

template<class T1, class T2> TextStream& operator<<(TextStream& ts, const std::vector<T1, T2>& vec){
    ts << "(size:" << vec.size() << ")";
    for(std::vector<T1, T2>::const_iterator it = vec.begin(); it != vec.end(); it++){
        ts << "\n" << it - vec.begin() << "\t" << *it;
    }
    return ts;
}

template<class T1, class T2> TextStream& operator<<(TextStream& ts, const std::list<T1, T2>& list){
    ts << "(size:" << list.size() << ")";
    int i = 0;
    for(std::list<T1, T2>::const_iterator it = list.begin(); it != list.end(); it++){
        ts << "\n" << i << "\t" << *it;
        i++;
    }
    return ts;
}

#endif
