#ifndef UTL_TEXTFILESTREAM_H
#define UTL_TEXTFILESTREAM_H
#include "TextStream.h"
#include "FileStream.h"
#include "BinStream.h"

class TextFileStream : public TextStream {
public:
    TextFileStream(const char *, bool);
    virtual ~TextFileStream(); // fn_8000F9D0
    virtual void Print(const char *); // fn_8037A5F8

    FileStream unk4;
};

#endif
