#ifndef UTL_TEXTFILESTREAM_H
#define UTL_TEXTFILESTREAM_H
#include "utl/BinStream.h"
#include "utl/FileStream.h"
#include "utl/TextStream.h"

class TextFileStream : public TextStream {
public:
    TextFileStream(const char *, bool);
    virtual ~TextFileStream(){}
    virtual void Print(const char *); // fn_8037A5F8

    FileStream mFile;
};

#endif
