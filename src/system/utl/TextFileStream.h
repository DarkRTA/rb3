#ifndef UTL_TEXTFILESTREAM_H
#define UTL_TEXTFILESTREAM_H
#include "utl/FileStream.h"
#include "utl/TextStream.h"

class TextFileStream : public TextStream {
public:
    TextFileStream(const char *, bool);
    virtual ~TextFileStream() {}
    virtual void Print(const char *);

    FileStream mFile;
};

#endif
