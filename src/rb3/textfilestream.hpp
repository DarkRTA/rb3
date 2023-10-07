#ifndef RB3_TEXTFILESTREAM_HPP
#define RB3_TEXTFILESTREAM_HPP
#include "textstream.hpp"
#include "filestream.hpp"
#include "binstream.hpp"

class TextFileStream : TextStream {
public:
	TextFileStream(const char*, bool);
	virtual ~TextFileStream(); // fn_8000F9D0
	virtual void Print(const char*); // fn_8037A5F8

	// FileStream unk4;
};

#endif
