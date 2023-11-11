#include "file.hpp"
#include "arkfile.hpp"

int File::sOpenCount[4];

#pragma dont_inline on
// fn_802E73DC
File::File()
{
	sOpenCount[0]++;
}

// fn_802E738C
File::~File()
{
	sOpenCount[0]--;
}
#pragma dont_inline reset

// fn_802E780C
String File::Filename()
{
	return String();
}

// fn_802E7818
int File::V_Unk15(int *a)
{
	*a = 0;
	return 1;
}

extern "C" char *FileMakePath(char *, char *, char *);
extern int lbl_80902234;
extern char *lbl_808517C0; // "."

// fn_802E72CC
ArkFile::ArkFile(const char *c, int a)
	: unk18(0), unk1c(0), fpos(0), unk24(0), unk2c(1), fname(c)
{
	FileMakePath(".", (char *)c, nullptr);
	if (a & 4) {
		unk24 = 1;
	}
}

extern int *lbl_80902278;
extern void fn_802E9888();

// fn_802E73FC
ArkFile::~ArkFile()
{
	if (unk18 > 0) {
		fn_802E9888();
	}
	fn_800E1114();
}

// fn_802E748C
int ArkFile::Read(void *c, int a)
{
	if (ReadAsync(c, a) == 0)
		return 0;
	int sp8 = -1;
	while (ReadDone(sp8) == 0)
		;
	return sp8;
}

// fn_802E7500
bool ArkFile::ReadAsync(void *c, int a)
{
	// this one's gross, i don't wanna do it
}

int ArkFile::V_Unk5(void *a, int b)
{
	return 0;
}

unsigned int ArkFile::Seek(int offset, int mode)
{
	switch (mode) {
	case 0:
		fpos = offset;
		break;
	case 1:
		fpos += offset;
		break;
	case 2:
		fpos = size + offset;
		break;
	default:
		break;
	}
	return fpos;
}

unsigned int ArkFile::Tell()
{
	return fpos;
}

// void ArkFile::Flush(){ }

bool ArkFile::Eof()
{
	return (size - fpos) == 0;
}

// fn_802E7810
String ArkFile::Filename()
{
	return fname;
}

// fn_802E7748
bool ArkFile::Fail()
{
	return (unk24 != 0);
}

// fn_802E7758
unsigned int ArkFile::Size()
{
	return size;
}

// fn_802E7760
unsigned int ArkFile::UncompressedSize()
{
	return size_uncompressed;
}

extern void fn_802EA488(int *); // this is BlockMgr::Poll()

// fn_802E7790
int ArkFile::ReadDone(int &a)
{
	fn_802EA488(
		lbl_80902278); // lbl_80902278 is a BlockMgr* named "TheBlockMgr"
	a = unk1c;
	return (unk18 == 0);
}

extern void fn_802EB6E4(int *, int, int, int);

// fn_802E77E4
int ArkFile::V_Unk16(int *a)
{
	fn_802EB6E4(a, unk4, unkc + fpos, unkc + fpos);
}

// fn_802E7768
void ArkFile::TaskDone(int a)
{
	unk18--;
	unk1c += a;
	fpos += a;
}