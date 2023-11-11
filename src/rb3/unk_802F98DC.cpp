#include "std/string.h"
#include "string.hpp"
#include "file_ops.hpp"
#include "data.hpp"
#include "common.hpp"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"

// fn_802FA190
void FileQualifiedFilename(String &s, const char *c)
{
	char lol[256];
	FileQualifiedFilename(lol, 0x100, c);
	s = lol;
}

extern "C" void FileNormalizePath(char *);
extern char fn_80018764(char);

// fn_802FA1D4
void FileNormalizePath(char *c)
{
	for (char *p = c; *p != 0; p++) {
		if (*p == '\\')
			*p = '/';
		else
			*p = fn_80018764(*p);
	}
}

extern "C" char *FileMakePath(char *, char *, char *);
extern char lbl_80852A60[]; // string table
extern char lbl_80906FC8[];

char *FileMakePath(char *c1, char *c2, char *c3)
{
	char *c3_ptr;
	char **c1_2;
	char sp88[256];
	char *sp8[32];
	bool is_slash;
	char *var_r3;

	if (c3 == 0)
		c3 = lbl_80906FC8;

	if ((c2 >= c3) && (c2 < (c3 + 4))) {
		strcpy(sp88, c2);
		c2 = sp88;
	} else if ((c1 >= c3) && (c1 < (c3 + 4))) {
		strcpy(sp88, c1);
		c1 = sp88;
	}

	char c2_res_inner;
	char *c2_res = FileGetDrive(c2);
	c2_res_inner = *c2_res;

	if (c2_res_inner != '\0') {
		c2 += strlen(c2_res) + 1;
	}
	if ((*c2 == '/') || (*c2 == '\\') || (*c2 == '\0')) {
		if (c2_res_inner != 0) {
			sprintf(c3, lbl_80852A60 + 0x104, c2_res, c2);
			c3_ptr = c3 + strlen(c2_res) + 1;
		} else {
			char *c1_res = FileGetDrive(c1);
			if (*c1_res != 0) {
				sprintf(c3, lbl_80852A60 + 0x104, c1_res, c2);
				c3_ptr = c3 + strlen(c1_res) + 1;
			} else {
				strcpy(c3, c2);
				c3_ptr = c3;
			}
		}
	} else {
		sprintf(c3, lbl_80852A60 + 0x10A, c1, c2);
		char *c1_res = FileGetDrive(c1);
		if (*c1_res != 0) {
			c3_ptr = c3 + strlen(c1_res) + 1;
		} else {
			c3_ptr = c3;
		}
	}

	FileNormalizePath(c3);
	c1_2 = sp8;
	is_slash = (*c3_ptr - '/') == 0;
	var_r3 = strtok(c3_ptr, lbl_80852A60 + 0x110);
	while (var_r3 != 0) {
		if (*var_r3 != '.')
			*c1_2++ = var_r3;
		else if ((var_r3[1] == '.') && (var_r3[2] == '\0')) {
			if ((c1_2 != sp8) && (*c1_2[-1] != '.'))
				c1_2--;
			else
				*c1_2++ = var_r3;
		}
		var_r3 = strtok((char *)0, lbl_80852A60 + 0x110);
	}
	if (c1_2 == sp8) {
		if (is_slash)
			*c3_ptr++ = '/';
		else
			*c3_ptr++ = '.';
	} else {
		for (char **p = sp8; p != c1_2; p++) {
			if ((p != sp8) || is_slash) {
				*c3_ptr++ = '/';
			}
			for (char *q = *p; *q != 0; q++, c3_ptr++) {
				*c3_ptr = *q;
			}
		}
	}
	*c3_ptr = 0;
	return c3;
}

extern char gRoot[];
extern char gExecRoot[];
extern char gSystemRoot[];

// fn_802F991C
char *FileRoot()
{
	return gRoot;
}

// fn_802F9928
char *FileExecRoot()
{
	return gExecRoot;
}

// fn_802F9934
char *FileSystemRoot()
{
	return gSystemRoot;
}

// fn_802F9940
DataNode OnFileExecRoot(DataArray *da)
{
	return DataNode(gExecRoot);
}

// fn_802F994C
DataNode OnFileRoot(DataArray *da)
{
	return DataNode(gRoot);
}

// fn_802F9958
DataNode OnFileGetDrive(DataArray *da)
{
	char *str = (char *)da->GetStrAtIndex(1);
	return DataNode(FileGetDrive(str));
}

// fn_802F999C
DataNode OnFileGetPath(DataArray *da)
{
	char *str = (char *)da->GetStrAtIndex(1);
	return DataNode(FileGetPath(str, '\0'));
}

// fn_802F99E4
DataNode OnFileGetBase(DataArray *da)
{
	char *str = (char *)da->GetStrAtIndex(1);
	return DataNode(FileGetBase(str, '\0'));
}

// fn_802F9A2C
DataNode OnFileGetExt(DataArray *da)
{
	char *str = (char *)da->GetStrAtIndex(1);
	return DataNode(FileGetExt(str));
}

// fn_802F9A70
DataNode OnFileMatch(DataArray *da)
{
	char *str2 = (char *)da->GetStrAtIndex(2);
	char *str1 = (char *)da->GetStrAtIndex(1);
	return DataNode(FileMatch(str1, str2));
}

// fn_802F9AD4
DataNode OnFileAbsolutePath(DataArray *da)
{
	char *str2 = (char *)da->GetStrAtIndex(2);
	char *str1 = (char *)da->GetStrAtIndex(1);
	return DataNode(FileMakePath(str1, str2, '\0'));
}

// fn_802F9B3C
DataNode OnFileRelativePath(DataArray *da)
{
	return DataNode();
}

// fn_802F9BA0
DataNode OnWithFileRoot(DataArray *da)
{
	return DataNode();
}

// fn_802F9C54
DataNode *EvaluateNodeAtIndex(DataArray *da, int i)
{
	DataNode *dn = da->GetNodeAtIndex(i);
	return dn->Evaluate();
}

// fn_802F9C78
DataNode OnSynchProc(DataArray *da)
{
	return DataNode();
}

extern "C" void FileInit();
extern "C" void fn_801F0530(char *);
extern "C" void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));
extern "C" char *OptionStr(const char *, const char *);

// fn_802F9CC4
void FileInit()
{
	strcpy(gRoot, ".");
	strcpy(gExecRoot, ".");
	char *path = FileMakePath(gExecRoot, "../../system/run", '\0');
	strcpy(gSystemRoot, path);
	fn_801F0530(gRoot);
	DataRegisterFunc(Symbol("file_root"), OnFileRoot);
	DataRegisterFunc(Symbol("file_exec_root"), OnFileExecRoot);
	DataRegisterFunc(Symbol("file_get_drive"), OnFileGetDrive);
	DataRegisterFunc(Symbol("file_get_path"), OnFileGetPath);
	DataRegisterFunc(Symbol("file_get_base"), OnFileGetBase);
	DataRegisterFunc(Symbol("file_get_ext"), OnFileGetExt);
	DataRegisterFunc(Symbol("file_match"), OnFileMatch);
	DataRegisterFunc(Symbol("file_absolute_path"), OnFileAbsolutePath);
	DataRegisterFunc(Symbol("file_relative_path"), OnFileRelativePath);
	DataRegisterFunc(Symbol("with_file_root"), OnWithFileRoot);
	DataRegisterFunc(Symbol("synch_proc"), OnSynchProc);
	char *str = OptionStr("file_order", '\0');
	if (str != nullptr && (*str != '\0')) {
	}
}