#ifndef RB3_TEXTFILE_HPP
#define RB3_TEXTFILE_HPP
#include "symbol.hpp"
#include "textstream.hpp"
struct TextFile : TextStream {
	virtual void virt1();
	int unk20;
	TextFile();
	static Symbol StaticClassName();
};
#endif
