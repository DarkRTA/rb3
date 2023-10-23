#include "textfilestream.hpp"
#include "filestream.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"
#include "simpletempomap.hpp"

// fn_8037A58C - TextFileStream ctor
TextFileStream::TextFileStream(const char *c, bool b) : unk4(c, b ? FileType3 : FileType1, true) { }

extern char lbl_808E5870; // "\r\n"

// fn_8037A5F8
void TextFileStream::Print(const char *c)
{
	char* p = (char*)c;
	while(*p != '\0'){
		if(*p == '\n' && p[1] != '\r')
			unk4.Write(&lbl_808E5870, 2);
		else unk4.Write(p, 1);
		p++;
	}
}