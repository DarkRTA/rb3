#include "file.hpp"
#include "asyncfilecnt.hpp"
#include "std/string.h"
#include "string.hpp"

extern char fn_802FB54C(const char *, int);

// fn_802E8680
AsyncFileCNT::AsyncFileCNT(const char *c, int a) : AsyncFile(c, a)
{
	char *temp_r30;
	int temp_r31;
	char *temp_r3_2;
	char *temp_r3_3;
	char *var_r31;
	char temp_r3;
	unk38 = 0;
	unk3c = 0;
	unk44 = -1;
	unk48 = 0;
	temp_r3 = fn_802FB54C(c, 0);
	if (temp_r3 != 0) {
		temp_r30 = (char *)c + 4;
		temp_r3_2 = strchr(temp_r30, 0x2F);
		if (temp_r3_2 != 0) {
			var_r31 = temp_r3_2 + 1;
			temp_r3_3 = strchr(var_r31, 0x2F);
			if (temp_r3_3 != 0) {
				var_r31 = temp_r3_3;
			}
		} else {
			var_r31 = temp_r30 + strlen(temp_r30);
		}
		temp_r31 = var_r31 - temp_r30;
		// strncpy(arg0 + 0x4A, temp_r30, temp_r31);
		// (arg0 + temp_r31)->unk4A = 0;
		fname = temp_r30 + temp_r31;
		fname.c_str();
		unk9 = 1;
	}

	//  if (temp_r3 != 0) {
	//     temp_r30 = arg1 + 4;
	//     temp_r3_2 = strchr(temp_r30, 0x2F);
	//     if (temp_r3_2 != 0) {
	//         var_r31 = temp_r3_2 + 1;
	//         temp_r3_3 = strchr(var_r31, 0x2F);
	//         if (temp_r3_3 != 0) {
	//             var_r31 = temp_r3_3;
	//         }
	//     } else {
	//         var_r31 = temp_r30 + strlen(temp_r30);
	//     }
	//     temp_r31 = var_r31 - temp_r30;
	//     strncpy(arg0 + 0x4A, temp_r30, temp_r31);
	//     (arg0 + temp_r31)->unk4A = 0;
	//     __as__6StringFPCc(arg0 + 0xC, temp_r30 + temp_r31);
	//     c_str__6StringCFv(arg0 + 0xC);
	//     arg0->unk9 = 1;
	// }
}

// fn_802E8B10
AsyncFileCNT::~AsyncFileCNT()
{
	Terminate();
}

// fn_802E8774
int AsyncFileCNT::V_Unk16(int *a)
{
	*a = 0;
	return 0;
}

// fn_802E8784
void AsyncFileCNT::_Open()
{
}

// fn_802E88C0
int AsyncFileCNT::V_Unk19()
{
	return 1;
}

// fn_802E88C8
int AsyncFileCNT::_Write(const void *, int)
{
}

// fn_802E88CC
int AsyncFileCNT::V_Unk21()
{
	return 1;
}

// fn_802E88D4
void AsyncFileCNT::_SeekToTell()
{
	if (Tell()) {
		failed = 1;
	}
}

// fn_802E892C
void AsyncFileCNT::_ReadAsync(void *a, int i)
{
}

// fn_802E89FC
int AsyncFileCNT::_ReadDone()
{
	return 0;
}

// fn_802E8AA4
void AsyncFileCNT::_Close()
{
}