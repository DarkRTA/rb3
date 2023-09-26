#include "unk_803242cc.hpp"

#include "types.h"
#include "unknown.hpp"
#include "symbol.hpp"
#include "textfile.hpp"

static char sFile[] = "File";

// probably void DataInit(void)
// not renaming until i can confirm it
// NONMATCHING: instruction ordering. regalloc
void fn_803242CC(void)
{
	fn_80320CDC();
	fn_8034F3D0(&lbl_8097C1B8, "dta", &fn_80324278);
	fn_80324338();
	lbl_808E3060 = fn_8035C934("no_macro_warn", true);
	fn_80329CFC(0x4E1D, 0x249F0);
}

extern "C" void fn_80324338()
{
	fn_80335354(TextFile::StaticClassName(), (void *(*)())fn_8032436C);
}

// NONMATCHING: struct size
extern "C" TextFile *fn_8032436C(void)
{
	return new TextFile();
}

// NONMATCHING: parent struct needs work
TextFile::TextFile()
{
	/*
    fn_8033560C();
    fn_8037A67C(arg0 + 0x1C);
	*/
	//arg0->unk1C = (void *) (&lbl_80856610 + 0x5C);
	unk20 = 0;
}

Symbol TextFile::StaticClassName()
{
	static Symbol name = Symbol(sFile);
	return name;
}
