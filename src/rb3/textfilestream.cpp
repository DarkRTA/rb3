#include "textfilestream.hpp"
#include "filestream.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"
#include "simpletempomap.hpp"

// fn_8037A58C - TextFileStream ctor
TextFileStream::TextFileStream(const char *c, bool b) : unk4(c, b ? FileStream::FileType3 : FileStream::FileType1, true) { }

static const char kCRLF[2] = {'\r', '\n'};

// fn_8037A5F8
void TextFileStream::Print(const char *c)
{
	char* p = (char*)c;
	while(*p != '\0'){
		if(*p == '\n' && p[1] != '\r')
			unk4.Write(kCRLF, sizeof(kCRLF));
		else unk4.Write(p, 1);
		p++;
	}
}